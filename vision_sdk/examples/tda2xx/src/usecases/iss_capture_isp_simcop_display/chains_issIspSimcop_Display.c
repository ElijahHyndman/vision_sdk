/*
 *******************************************************************************
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_issIspSimcop_Display_priv.h"
#include <examples/tda2xx/include/chains_common.h>
#include <examples/tda2xx/include/chains_common_iss.h>


#define CAPTURE_SENSOR_WIDTH      (1280)
#define CAPTURE_SENSOR_HEIGHT     (720)

#define CAPTURE_SENSOR_AR140_WIDTH      (1280)
#define CAPTURE_SENSOR_AR140_HEIGHT     (800)

#define CAPTURE_SENSOR_IMX224_NON_WDR_WIDTH  (1280)
#define CAPTURE_SENSOR_IMX224_NON_WDR_HEIGHT (960)


#define CAPTURE_SENSOR_IMX224_WDR_WIDTH  (1312)
#define CAPTURE_SENSOR_IMX224_WDR_HEIGHT (2164)
#define CAPTURE_SENSOR_IMX224_ISP_WIDTH  (1280)
#define CAPTURE_SENSOR_IMX224_ISP_HEIGHT (960)

#define CAPTURE_SENSOR_IMX224_LONG_LINE_OFFSET      (9U)
#define CAPTURE_SENSOR_IMX224_SHORT_LINE_OFFSET     (142U)
#define CAPTURE_SENSOR_IMX224_LONG_PIXEL_OFFSET     (0)
#define CAPTURE_SENSOR_IMX224_SHORT_PIXEL_OFFSET    (0)

/*
 * AEWB algorithm memory requirement cannot be calculated upfront.
 * This size is known by running the use-case once with large size
 * and then checking the log for unused memory in AEWB algorithm
 */
#define ALG_AEWB_MEM_SIZE                           (896*1024)

#define ENABLE_WDR_MERGE_PARAMS_CFG

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraFrameCopyObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issIspSimcop_DisplayObj ucObj;

    IssIspConfigurationParameters ispConfig;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    IssM2mSimcopLink_OperatingMode simcopMode;
    Bool bypassVtnf;
    Bool bypassLdc;

} chains_issIspSimcop_DisplayAppObj;


char gChains_IssIspSimcop_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n 1: Toggle VTNF ON/OFF"
"\r\n 2: Toggle LDC  ON/OFF"
"\r\n 3: Save Captured Frame"
"\r\n 4: Save SIMCOP Output Frame"
"\r\n 5: Save ISP Output Frame"
#ifdef ISS_ENABLE_DEBUG_TAPS
"\r\n 6: Enable Resizer Output"
"\r\n 7: Enable IPIPE Output"
"\r\n 8: Enable GLBCE Output"
"\r\n 9: Enable IPIPEIF Output"
"\r\n a: Enable Intermediate Output"
#endif
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

Void chains_issIspSimcop_Display_Config_Aewb(
        IssAewbAlgOutParams *pAewbAlgOut,
        Void *appData)
{
    chains_issIspSimcop_DisplayAppObj *pObj =
        (chains_issIspSimcop_DisplayAppObj *)appData;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pAewbAlgOut);

    /* AEWB Output parameters are already converted and stored in
       ispCfg parameter of alg out, so set it in the ISP using ISP
       Link */
    System_linkControl(
        pObj->ucObj.IssM2mIspLinkID,
        ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS,
        pAewbAlgOut,
        sizeof(IssAewbAlgOutParams),
        TRUE);

    /* Set the Sensor exposure and analog Gain */
    ChainsCommon_IssUpdateAewbParams(pAewbAlgOut);
}

Void chains_issIspSimcop_Display_Config_DCC_Params(
        IssIspConfigurationParameters *ispCfg,
        IssM2mSimcopLink_ConfigParams *simcopCfg,
        Void                          *appData)
{
    chains_issIspSimcop_DisplayAppObj *pObj =
        (chains_issIspSimcop_DisplayAppObj *)appData;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != ispCfg);
    UTILS_assert(NULL != simcopCfg);

    System_linkControl(
        pObj->ucObj.IssM2mIspLinkID,
        ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
        ispCfg,
        sizeof(IssIspConfigurationParameters),
        TRUE);

    if (NULL != simcopCfg->ldcConfig)
    {
        /* Copy LDC configuration and apply it,
           Will use same  */
        memcpy(
            &pObj->ldcCfg,
            simcopCfg->ldcConfig,
            sizeof(vpsissldcConfig_t));

        pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
        pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

        /* MUST be called after link create and before link start */
        System_linkControl(
                pObj->ucObj.IssM2mSimcopLinkID,
                ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
                &pObj->simcopConfig,
                sizeof(pObj->simcopConfig),
                TRUE);
    }
}

#ifdef ENABLE_WDR_MERGE_PARAMS_CFG
/* Function to get the exposure parameters from the sensor and update
   the merge parameters in the ISP. Called only when WDR merge is enabled. */
Void chains_issIspSimcop_Display_Config_Merge(
        IssAewbAlgOutParams *pAewbAlgOut,
        Void *appData)
{
    chains_issIspSimcop_DisplayAppObj *pObj =
        (chains_issIspSimcop_DisplayAppObj *)appData;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pAewbAlgOut);

    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    /* Get Exposure ratio parameters from the sensor */
    ChainsCommon_IssGetExposureParams(pAewbAlgOut);

    /* When dgain is applied only to long after split, there is a
        different ratio for split and merge */
    /* setting up merge parameters even for 2 pass wdr mode when AE is
       not enabled because merge parameter calculation uses digital gain
       for the calculation */
    if ((TRUE == pAewbAlgOut->outPrms[0].useAeCfg) ||
        ((TRUE == IssM2mIspLink_IsWdrMergeMode(
            pIssM2mIspPrm->channelParams[0].operatingMode)) &&
         (ALGORITHMS_ISS_AEWB_MODE_AWB == pAlg_IssAewbPrm->mode)))
    {
        System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS,
            pAewbAlgOut,
            sizeof(IssAewbAlgOutParams),
            TRUE);
    }
}
#endif

/*
 * This function shows an example of allocating memory for
 * a link from within the use-case instead of from within the link
 *
 * This allows user's to potentially allocate memory statically outside of
 * link implementation and then pass the memory to the link during use-case
 * create.
 *
 * If user wants the link to allocate memory then dont set below parameters
 * <link create params>.memAllocInfo.memSize,
 * <link create params>.memAllocInfo.memAddr
 */
Void chains_issIspSimcop_Display_SetMemAllocInfo(
                    chains_issIspSimcop_DisplayAppObj *pObj)
{
    UInt32 align = 32;
    IssCaptureLink_CreateParams             *pIssCapturePrm;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    VpeLink_CreateParams                    *pVPEPrm;
    IssM2mSimcopLink_CreateParams           *pIssM2mSimcopPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    pIssCapturePrm    = &pObj->ucObj.IssCapturePrm;
    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pVPEPrm           = &pObj->ucObj.VPEPrm;
    pIssM2mSimcopPrm  = &pObj->ucObj.IssM2mSimcopPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    pIssCapturePrm->memAllocInfo.memSize =
          SystemUtils_align(pObj->captureOutWidth, align)
        * pObj->captureOutHeight
        * 2 /* 16-bit per pixel */
        * (pIssCapturePrm->outParams[0].numOutBuf+1)
            /* +1 for RAW data dump */
        ;

    pAlg_IssAewbPrm->memAllocInfo.memSize = ALG_AEWB_MEM_SIZE;

    pIssM2mIspPrm->memAllocInfo.memSize = 0;

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A])
    {
#ifdef ISS_ENABLE_DEBUG_TAPS
        /* RSZ A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
            * 2 /* YUV420/422/RAW */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
#else
        /* RSZ A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
            * 1.5 /* YUV420SP */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
#endif
    }

    if( pIssM2mIspPrm->channelParams[0].operatingMode
          == ISSM2MISP_LINK_OPMODE_2PASS_WDR
       )
    {
        /* Intermediate buffer in 2 pass WDR mode */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pObj->captureOutWidth, align)
            * pObj->captureOutHeight
            * 2 /* 16-bit per pixel */
            ;
    }

    if( pIssM2mIspPrm->channelParams[0].operatingMode
          == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED
       )
    {
        /* Intermediate buffer in 2 pass WDR mode */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].wdrOffsetPrms.width, align)
            * pIssM2mIspPrm->channelParams[0].wdrOffsetPrms.height
            * 2 /* 16-bit per pixel */
            ;
    }

    if (pIssM2mIspPrm->allocBufferForDump)
    {
        /* For Dumping Output frame */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pObj->captureOutWidth, align)
            * pObj->captureOutHeight
            * 2 /* 16-bit per pixel */
            ;
    }

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B])
    {
        /* RSZ B output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszB, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszB
            * 1.5 /* YUV420SP */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
    }

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_H3A])
    {
        /* H3A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              ((pIssM2mIspPrm->channelParams[0].outParams.widthRszA/
                  pIssM2mIspPrm->channelParams[0].outParams.winWidthH3a)+1)
            * ((pIssM2mIspPrm->channelParams[0].outParams.heightRszA/
                  pIssM2mIspPrm->channelParams[0].outParams.winHeightH3a)+1)
            * ( sizeof(IssAwebH3aOutSumModeOverlay)
              + sizeof(IssAwebH3aOutUnsatBlkCntOverlay) )
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
    }

/* To support WDR, two sets of statistics must be produced, one for short exposure and the other one for long exposure
    that's why there is a factor 2
    */
    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_H3A_AF])
    {
        pIssM2mIspPrm->memAllocInfo.memSize +=  SystemUtils_align(2*pIssM2mIspPrm->channelParams[0].outParams.paxelNumHaf
            *pIssM2mIspPrm->channelParams[0].outParams.paxelNumVaf*sizeof(IssAfH3aOutOverlay), 128U) /* DSP cache requires 128 bytes alignment */
            *pIssM2mIspPrm->channelParams[0].numBuffersPerCh;
    }

    pVPEPrm->memAllocInfo.memSize =
          SystemUtils_align(pVPEPrm->chParams[0].outParams[0].width, align)
        * pVPEPrm->chParams[0].outParams[0].height
        * 1.5 /* YUV420SP */
        * pVPEPrm->chParams[0].outParams[0].numBufsPerCh
        ;

    pIssM2mSimcopPrm->memAllocInfo.memSize =
          SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
        * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
        * 1.5
        * (pIssM2mSimcopPrm->channelParams[0].numBuffersPerCh+1)
           /* +1 for YUV data dump */
        ;

    pIssCapturePrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssCapturePrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssCapturePrm->memAllocInfo.memAddr!=NULL);

    pAlg_IssAewbPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pAlg_IssAewbPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pAlg_IssAewbPrm->memAllocInfo.memAddr!=NULL);

    pIssM2mIspPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssM2mIspPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssM2mIspPrm->memAllocInfo.memAddr!=NULL);

    pVPEPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pVPEPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pVPEPrm->memAllocInfo.memAddr!=NULL);

    pIssM2mSimcopPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssM2mSimcopPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssM2mSimcopPrm->memAllocInfo.memAddr!=NULL);
}

/*
 * This function free's memory allocated by the use-case, if any
 */
Void chains_issIspSimcop_Display_FreeMemory(
                    chains_issIspSimcop_DisplayAppObj *pObj)
{
    Int32 status;
    IssCaptureLink_CreateParams             *pIssCapturePrm;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    VpeLink_CreateParams                    *pVPEPrm;
    IssM2mSimcopLink_CreateParams           *pIssM2mSimcopPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    pIssCapturePrm    = &pObj->ucObj.IssCapturePrm;
    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pVPEPrm           = &pObj->ucObj.VPEPrm;
    pIssM2mSimcopPrm  = &pObj->ucObj.IssM2mSimcopPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    if(pIssCapturePrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssCapturePrm->memAllocInfo.memAddr,
                    pIssCapturePrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pAlg_IssAewbPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pAlg_IssAewbPrm->memAllocInfo.memAddr,
                    pAlg_IssAewbPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pIssM2mIspPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssM2mIspPrm->memAllocInfo.memAddr,
                    pIssM2mIspPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pVPEPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pVPEPrm->memAllocInfo.memAddr,
                    pVPEPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pIssM2mSimcopPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssM2mSimcopPrm->memAllocInfo.memAddr,
                    pIssM2mSimcopPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_issIspSimcop_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    DisplayLink_CreateParams *pPrm_VideoRszB,
                                    Chains_DisplayType displayType,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    UInt32 dispWidth, dispHeight;

    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        /* To maintain the aspect ratio, change the display tarWidth */
        dispWidth = captureWidth * displayHeight / captureHeight;
        dispHeight = displayHeight;

        if (dispWidth > displayWidth)
        {
            dispWidth = displayWidth;
            dispHeight = displayWidth * captureHeight / captureWidth;
        }


        pPrm_Video->rtParams.tarWidth  = dispWidth;
        pPrm_Video->rtParams.tarHeight = dispHeight;
        pPrm_Video->rtParams.posX      = (displayWidth - dispWidth) / 2U;
        pPrm_Video->rtParams.posY      = (displayHeight - dispHeight) / 2U;

        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_VideoRszB)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_VideoRszB->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_VideoRszB->rtParams.tarWidth  = displayWidth/3;
        pPrm_VideoRszB->rtParams.tarHeight = displayHeight/3;
        pPrm_VideoRszB->rtParams.posX      = displayWidth - pPrm_VideoRszB->rtParams.tarWidth - 10;
        pPrm_VideoRszB->rtParams.posY      = displayHeight - pPrm_VideoRszB->rtParams.tarHeight - 10;
        pPrm_VideoRszB->displayId          = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pPrm_Grpx)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

Void chains_issIspSimcop_Display_SetSimcopConfig(
            chains_issIspSimcop_DisplayAppObj *pObj)
{
    ChainsCommon_SetIssSimcopLdcVtnfRtConfig(
        &pObj->ldcCfg,
        &pObj->vtnfCfg,
        pObj->bypassVtnf,
        pObj->bypassLdc);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* MUST be called after link create and before link start */
    System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
}


Void chains_issIspSimcop_Display_SetIspConfig(
            chains_issIspSimcop_DisplayAppObj *pObj)
{
    Int32 status;
    uint32_t ldcLutIdx;

    /* set default params */
    IssM2mSimcopLink_ConfigParams_Init(&pObj->simcopConfig);
    vpsissLdcCfg_init(&pObj->ldcCfg);
    vpsissVtnfCfg_init(&pObj->vtnfCfg);

    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    ldcLutIdx = ChainsCommon_GetLdcLutIdx(pObj->chainsCfg->sensorName);

    /* Set the Default SimCop configuration,
        This could get overwriten by DCC */
    ChainsCommon_SetIssSimcopConfig(
        &pObj->simcopConfig,
        pObj->bypassVtnf,
        pObj->bypassLdc,
        ldcLutIdx);

    ChainsCommon_IssGetDefaultIspSimcopConfig(
        pObj->ucObj.IssM2mIspPrm.channelParams[0].operatingMode,
        &pObj->ispConfig,
        &pObj->simcopConfig,
        pObj->ucObj.Alg_IssAewbLinkID);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
            pObj->ucObj.IssM2mIspLinkID,
            ISSM2MISP_LINK_CMD_SET_ISPCONFIG,
            &pObj->ispConfig,
            sizeof(pObj->ispConfig),
            TRUE);
    UTILS_assert(0 == status);

    /* MUST be called after link create and before link start */
    status = System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
    UTILS_assert(0 == status);
}

Void chains_issIspSimcop_Display_SetVpePrms(
        VpeLink_CreateParams *vpePrms,
        UInt32 outWidth,
        UInt32 outHeight)
{
    VpeLink_ChannelParams *pChPrms = NULL;

    vpePrms->enableOut[0U] = TRUE;
    vpePrms->procCore = VPE_PROCCORE_ISS;

    pChPrms = &vpePrms->chParams[0U];

    pChPrms->outParams[0U].width = outWidth;
    pChPrms->outParams[0U].height = outHeight;
    pChPrms->outParams[0U].dataFormat = SYSTEM_DF_YUV420SP_UV;

    pChPrms->scCfg.bypass = FALSE;
}


/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_SetAppPrms(chains_issIspSimcop_DisplayObj *pUcObj, Void *appObj)
{
    UInt32 flipAndMirror;

    chains_issIspSimcop_DisplayAppObj *pObj
        = (chains_issIspSimcop_DisplayAppObj*)appObj;
    IssM2mIspLink_WdrOffsetParams_t wdrOffsetPrms;
    IssM2mIspLink_OperatingMode ispOpMode;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF;
    pObj->bypassVtnf = FALSE;
    pObj->bypassLdc  = FALSE;

    if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
        (pObj->chainsCfg->issVtnfEnable == TRUE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = FALSE;
        pObj->bypassLdc  = TRUE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == TRUE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = FALSE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = TRUE;
    }

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    ispOpMode = pObj->chainsCfg->ispOpMode;

    ChainsCommon_SetIssCreatePrms(
        pObj->chainsCfg->sensorName,
        &pUcObj->IssCapturePrm,
        &pUcObj->IssM2mIspPrm,
        &pUcObj->IssM2mSimcopPrm,
        &pUcObj->Alg_IssAewbPrm,
        NULL,//&pUcObj->Alg_SceneObstructionDetectPrm,
        pObj->displayWidth,
        pObj->displayHeight,
        pObj->simcopMode,
        ispOpMode,
        &wdrOffsetPrms);
    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;

    if ((CHAINS_CAPTURE_SRC_OV10640_CSI2 == pObj->chainsCfg->captureSrc) ||
        (CHAINS_CAPTURE_SRC_OV10640_PARALLEL == pObj->chainsCfg->captureSrc))
    {
        /* Refer CHAINS_ISS_SENSOR_SET_FLIP_MIRROR for details */
        flipAndMirror = 1U; /* Flip enabled and mirroring disabled */
        ChainsCommon_IssUpdateFlipParams(&flipAndMirror);
    }

    /* Since we are operating in Linear mode, disable backlight compensation */
    if ((ispOpMode == ISSM2MISP_LINK_OPMODE_12BIT_LINEAR) ||
        (ispOpMode == ISSM2MISP_LINK_OPMODE_1PASS_WDR))
    {
        pUcObj->Alg_IssAewbPrm.aeDynParams.enableBlc = FALSE;
    }

    pUcObj->Alg_IssAewbPrm.appData = pObj;
    pUcObj->Alg_IssAewbPrm.cfgCbFxn = chains_issIspSimcop_Display_Config_Aewb;

    #ifdef ENABLE_WDR_MERGE_PARAMS_CFG
    /* No Need to enable merge function for single pass wdr flow */
    if (TRUE == IssM2mIspLink_IsWdrMergeMode(pObj->chainsCfg->ispOpMode))
    {
        pUcObj->Alg_IssAewbPrm.mergeCbFxn =
            chains_issIspSimcop_Display_Config_Merge;
    }
    #endif

    pUcObj->Alg_IssAewbPrm.dccIspCfgFxn =
        chains_issIspSimcop_Display_Config_DCC_Params;

    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    chains_issIspSimcop_Display_SetVpePrms(
        &pUcObj->VPEPrm,
        ((pObj->displayWidth/3) & ~0x1), /* Even value needed */
        (pObj->displayHeight/3));

    pObj->captureOutWidth = pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->captureOutHeight = pUcObj->IssCapturePrm.outParams[0U].height;

    /*
     * call this function to allocate memory from use-case
     * if this function is not called memory is allocated
     * from within the respective link
     */
    chains_issIspSimcop_Display_SetMemAllocInfo(pObj);

    chains_issIspSimcop_Display_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                           &pUcObj->Display_GrpxPrm,
                                           &pUcObj->Display_VideoRszBPrm,
                                           pObj->chainsCfg->displayType,
                                           pObj->displayWidth,
                                           pObj->displayHeight,
                                           pUcObj->IssM2mIspPrm.channelParams[0U].outParams.widthRszA,
                                           pUcObj->IssM2mIspPrm.channelParams[0U].outParams.heightRszA
                                           );

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_issIspSimcop_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StartApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_issIspSimcop_Display_SetIspConfig(pObj);

    ChainsCommon_IssStartCaptureDevice();

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issIspSimcop_Display_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_issIspSimcop_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StopAndDeleteApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    chains_issIspSimcop_Display_Stop(&pObj->ucObj);
    chains_issIspSimcop_Display_Delete(&pObj->ucObj);

    chains_issIspSimcop_Display_FreeMemory(pObj);

    ChainsCommon_StopDisplayCtrl();

    ChainsCommon_IssStopAndDeleteCaptureDevice();

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_issIspSimcop_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_issIspSimcop_DisplayAppObj chainsObj;
    IssM2mIspLink_IspOutputTapParams ispTapPrms;

    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */

    if (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Please make sure BSP is build with WDR and LDC enabled !!!\n");
    }

    chainsObj.chainsCfg = chainsCfg;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_issIspSimcop_Display_Create(&chainsObj.ucObj, &chainsObj);
    ChainsCommon_SetIssCaptureErrorHandlingCb(chainsObj.ucObj.IssCaptureLinkID);
    chains_issIspSimcop_Display_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_IssIspSimcop_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                /* toogle VTNF ON/OFF */
                chainsObj.bypassVtnf ^= 1;
                chains_issIspSimcop_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassVtnf)
                {
                    Vps_printf(" CHAINS: VTNF is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: VTNF is ENABLED !!!\n");
                }
                break;
            case '2':
                /* toogle LDC ON/OFF */
                chainsObj.bypassLdc ^= 1;
                chains_issIspSimcop_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassLdc)
                {
                    Vps_printf(" CHAINS: LDC is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: LDC is ENABLED !!!\n");
                }
                break;

            case '3':
                /* Send command to Capture Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssCaptureLinkID,
                        ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                break;
            case '4':
                /* Send command to Capture Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mSimcopLinkID,
                        ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                break;
            case '5':
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                break;
            case '6':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_RESIZER_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '7':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_IPIPE_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '8':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_GLBCE_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '9':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_IPIPEIF_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case 'a':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_issIspSimcop_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_issIspSimcop_Display_StopAndDeleteApp(&chainsObj);

}

