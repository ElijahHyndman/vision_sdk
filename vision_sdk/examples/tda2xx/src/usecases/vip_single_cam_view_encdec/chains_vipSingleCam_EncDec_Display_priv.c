/*
*******************************************************************************
*
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
*
*******************************************************************************
*/

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/
#include "chains_vipSingleCam_EncDec_Display_priv.h"
Void chains_vipSingleCam_EncDec_Display_SetLinkId(chains_vipSingleCam_EncDec_DisplayObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE;
       pObj->EncodeLinkID                   = SYSTEM_LINK_ID_VENC_0;
       pObj->DecodeLinkID                   = SYSTEM_LINK_ID_VDEC_0;
       pObj->VPELinkID                      = SYSTEM_LINK_ID_VPE_0;
       pObj->Display_VideoLinkID            = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void chains_vipSingleCam_EncDec_Display_ResetLinkPrms(chains_vipSingleCam_EncDec_DisplayObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       EncLink_CreateParams_Init(&pObj->EncodePrm);
       DecLink_CreateParams_Init(&pObj->DecodePrm);
       VpeLink_CreateParams_Init(&pObj->VPEPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_VideoPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_vipSingleCam_EncDec_Display_SetPrms(chains_vipSingleCam_EncDec_DisplayObj *pObj){
}

Void chains_vipSingleCam_EncDec_Display_ConnectLinks(chains_vipSingleCam_EncDec_DisplayObj *pObj){

       //Capture -> Encode
       pObj->CapturePrm.outQueParams.nextLink = pObj->EncodeLinkID;
       pObj->EncodePrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->EncodePrm.inQueParams.prevLinkQueId = 0;

       //Encode -> Decode
       pObj->EncodePrm.outQueParams.nextLink = pObj->DecodeLinkID;
       pObj->DecodePrm.inQueParams.prevLinkId = pObj->EncodeLinkID;
       pObj->DecodePrm.inQueParams.prevLinkQueId = 0;

       //Decode -> VPE
       pObj->DecodePrm.outQueParams.nextLink = pObj->VPELinkID;
       pObj->VPEPrm.inQueParams.prevLinkId = pObj->DecodeLinkID;
       pObj->VPEPrm.inQueParams.prevLinkQueId = 0;

       //VPE -> Display_Video
       pObj->VPEPrm.outQueParams[0].nextLink = pObj->Display_VideoLinkID;
       pObj->Display_VideoPrm.inQueParams.prevLinkId = pObj->VPELinkID;
       pObj->Display_VideoPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_vipSingleCam_EncDec_Display_Create(chains_vipSingleCam_EncDec_DisplayObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleCam_EncDec_Display_SetLinkId(pObj);
       chains_vipSingleCam_EncDec_Display_ResetLinkPrms(pObj);

       chains_vipSingleCam_EncDec_Display_SetPrms(pObj);
       chains_vipSingleCam_EncDec_Display_SetAppPrms(pObj, appObj);

       chains_vipSingleCam_EncDec_Display_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->EncodeLinkID, &pObj->EncodePrm, sizeof(pObj->EncodePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->DecodeLinkID, &pObj->DecodePrm, sizeof(pObj->DecodePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPELinkID, &pObj->VPEPrm, sizeof(pObj->VPEPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_VideoLinkID, &pObj->Display_VideoPrm, sizeof(pObj->Display_VideoPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_EncDec_Display_Start(chains_vipSingleCam_EncDec_DisplayObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->DecodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->EncodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_EncDec_Display_Stop(chains_vipSingleCam_EncDec_DisplayObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->DecodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->EncodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_EncDec_Display_Delete(chains_vipSingleCam_EncDec_DisplayObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->DecodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->EncodeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleCam_EncDec_Display_printBufferStatistics(chains_vipSingleCam_EncDec_DisplayObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->EncodeLinkID);
       System_linkPrintBufferStatistics(pObj->DecodeLinkID);
       System_linkPrintBufferStatistics(pObj->VPELinkID);
       System_linkPrintBufferStatistics(pObj->Display_VideoLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_vipSingleCam_EncDec_Display_printStatistics(chains_vipSingleCam_EncDec_DisplayObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->EncodeLinkID);
       System_linkPrintStatistics(pObj->DecodeLinkID);
       System_linkPrintStatistics(pObj->VPELinkID);
       System_linkPrintStatistics(pObj->Display_VideoLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

