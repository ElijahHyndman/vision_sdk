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
#include "chains_srvCalibration_Display_tda3x_priv.h"
Void chains_srvCalibration_Display_tda3x_SetLinkId(chains_srvCalibration_Display_tda3xObj *pObj){
       pObj->IssCaptureLinkID               = SYSTEM_LINK_ID_ISSCAPTURE_0;
       pObj->IssM2mIspLinkID                = SYSTEM_LINK_ID_ISSM2MISP_0;
       pObj->Alg_IssAewbLinkID              = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_1);
       pObj->DupLinkID                      = IPU1_0_LINK (SYSTEM_LINK_ID_DUP_0);
       pObj->Null_ispLinkID                 = IPU1_0_LINK (SYSTEM_LINK_ID_NULL_0);
       pObj->VPELinkID                      = SYSTEM_LINK_ID_VPE_0;
       pObj->SyncLinkID                     = IPU1_0_LINK (SYSTEM_LINK_ID_SYNC_0);
       pObj->Alg_DmaSwMsLinkID              = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->DisplayLinkID                  = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
       pObj->Capture_dsswbLinkID            = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->Null_disWbLinkID               = IPU1_0_LINK (SYSTEM_LINK_ID_NULL_1);
}

Void chains_srvCalibration_Display_tda3x_ResetLinkPrms(chains_srvCalibration_Display_tda3xObj *pObj){
       IssCaptureLink_CreateParams_Init(&pObj->IssCapturePrm);
       IssM2mIspLink_CreateParams_Init(&pObj->IssM2mIspPrm);
       AlgorithmLink_IssAewb_Init(&pObj->Alg_IssAewbPrm);
       DupLink_CreateParams_Init(&pObj->DupPrm);
       NullLink_CreateParams_Init (&pObj->Null_ispPrm);
       VpeLink_CreateParams_Init(&pObj->VPEPrm);
       SyncLink_CreateParams_Init(&pObj->SyncPrm);
       AlgorithmLink_DmaSwMsCreateParams_Init(&pObj->Alg_DmaSwMsPrm);
       DisplayLink_CreateParams_Init(&pObj->DisplayPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
       CaptureLink_CreateParams_Init(&pObj->Capture_dsswbPrm);
       NullLink_CreateParams_Init (&pObj->Null_disWbPrm);
}

Void chains_srvCalibration_Display_tda3x_SetPrms(chains_srvCalibration_Display_tda3xObj *pObj){
       (pObj->Alg_IssAewbPrm).baseClassCreate.size  = sizeof(AlgorithmLink_IssAewbCreateParams);
       (pObj->Alg_IssAewbPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_ISS_AEWB1;
       (pObj->DupPrm).numOutQue = 2;
       (pObj->Null_ispPrm).numInQue = 1;
       (pObj->Alg_DmaSwMsPrm).baseClassCreate.size  = sizeof(AlgorithmLink_DmaSwMsCreateParams);
       (pObj->Alg_DmaSwMsPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;
       (pObj->Null_disWbPrm).numInQue = 1;
}

Void chains_srvCalibration_Display_tda3x_ConnectLinks(chains_srvCalibration_Display_tda3xObj *pObj){

       //IssCapture -> IssM2mIsp
       pObj->IssCapturePrm.outQueParams.nextLink = pObj->IssM2mIspLinkID;
       pObj->IssM2mIspPrm.inQueParams[0].prevLinkId = pObj->IssCaptureLinkID;
       pObj->IssM2mIspPrm.inQueParams[0].prevLinkQueId = 0;

       //IssM2mIsp -> Dup
       pObj->IssM2mIspPrm.outQueParams[0].nextLink = pObj->DupLinkID;
       pObj->DupPrm.inQueParams.prevLinkId = pObj->IssM2mIspLinkID;
       pObj->DupPrm.inQueParams.prevLinkQueId = 0;

       //IssM2mIsp -> Alg_IssAewb
       pObj->IssM2mIspPrm.outQueParams[1].nextLink = pObj->Alg_IssAewbLinkID;
       pObj->Alg_IssAewbPrm.inQueParams.prevLinkId = pObj->IssM2mIspLinkID;
       pObj->Alg_IssAewbPrm.inQueParams.prevLinkQueId = 1;

       //Dup -> VPE
       pObj->DupPrm.outQueParams[0].nextLink = pObj->VPELinkID;
       pObj->VPEPrm.inQueParams.prevLinkId = pObj->DupLinkID;
       pObj->VPEPrm.inQueParams.prevLinkQueId = 0;

       //Dup -> Null_isp
       pObj->DupPrm.outQueParams[1].nextLink = pObj->Null_ispLinkID;
       pObj->Null_ispPrm.inQueParams[0].prevLinkId = pObj->DupLinkID;
       pObj->Null_ispPrm.inQueParams[0].prevLinkQueId = 1;

       //VPE -> Sync
       pObj->VPEPrm.outQueParams[0].nextLink = pObj->SyncLinkID;
       pObj->SyncPrm.inQueParams.prevLinkId = pObj->VPELinkID;
       pObj->SyncPrm.inQueParams.prevLinkQueId = 0;

       //Sync -> Alg_DmaSwMs
       pObj->SyncPrm.outQueParams.nextLink = pObj->Alg_DmaSwMsLinkID;
       pObj->Alg_DmaSwMsPrm.inQueParams.prevLinkId = pObj->SyncLinkID;
       pObj->Alg_DmaSwMsPrm.inQueParams.prevLinkQueId = 0;

       //Alg_DmaSwMs -> Display
       pObj->Alg_DmaSwMsPrm.outQueParams.nextLink = pObj->DisplayLinkID;
       pObj->DisplayPrm.inQueParams.prevLinkId = pObj->Alg_DmaSwMsLinkID;
       pObj->DisplayPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

       //Capture_dsswb -> Null_disWb
       pObj->Capture_dsswbPrm.outQueParams.nextLink = pObj->Null_disWbLinkID;
       pObj->Null_disWbPrm.inQueParams[0].prevLinkId = pObj->Capture_dsswbLinkID;
       pObj->Null_disWbPrm.inQueParams[0].prevLinkQueId = 0;

}

Int32 chains_srvCalibration_Display_tda3x_Create(chains_srvCalibration_Display_tda3xObj *pObj, Void *appObj){

       Int32 status;

       chains_srvCalibration_Display_tda3x_SetLinkId(pObj);
       chains_srvCalibration_Display_tda3x_ResetLinkPrms(pObj);

       chains_srvCalibration_Display_tda3x_SetPrms(pObj);
       chains_srvCalibration_Display_tda3x_SetAppPrms(pObj, appObj);

       chains_srvCalibration_Display_tda3x_ConnectLinks(pObj);
       status = System_linkCreate(pObj->IssCaptureLinkID, &pObj->IssCapturePrm, sizeof(pObj->IssCapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IssM2mIspLinkID, &pObj->IssM2mIspPrm, sizeof(pObj->IssM2mIspPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_IssAewbLinkID, &pObj->Alg_IssAewbPrm, sizeof(pObj->Alg_IssAewbPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->DupLinkID, &pObj->DupPrm, sizeof(pObj->DupPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Null_ispLinkID, &pObj->Null_ispPrm, sizeof(pObj->Null_ispPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPELinkID, &pObj->VPEPrm, sizeof(pObj->VPEPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->SyncLinkID, &pObj->SyncPrm, sizeof(pObj->SyncPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_DmaSwMsLinkID, &pObj->Alg_DmaSwMsPrm, sizeof(pObj->Alg_DmaSwMsPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->DisplayLinkID, &pObj->DisplayPrm, sizeof(pObj->DisplayPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Capture_dsswbLinkID, &pObj->Capture_dsswbPrm, sizeof(pObj->Capture_dsswbPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Null_disWbLinkID, &pObj->Null_disWbPrm, sizeof(pObj->Null_disWbPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_srvCalibration_Display_tda3x_Start(chains_srvCalibration_Display_tda3xObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Null_disWbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->DisplayLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_DmaSwMsLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->SyncLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Null_ispLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->DupLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_IssAewbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IssM2mIspLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IssCaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_srvCalibration_Display_tda3x_Stop(chains_srvCalibration_Display_tda3xObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Null_disWbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->DisplayLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_DmaSwMsLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->SyncLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Null_ispLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->DupLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_IssAewbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IssM2mIspLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IssCaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_srvCalibration_Display_tda3x_Delete(chains_srvCalibration_Display_tda3xObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Null_disWbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->DisplayLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_DmaSwMsLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->SyncLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPELinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Null_ispLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->DupLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_IssAewbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IssM2mIspLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IssCaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_srvCalibration_Display_tda3x_printBufferStatistics(chains_srvCalibration_Display_tda3xObj *pObj){
       System_linkPrintBufferStatistics(pObj->IssCaptureLinkID);
       System_linkPrintBufferStatistics(pObj->IssM2mIspLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_IssAewbLinkID);
       System_linkPrintBufferStatistics(pObj->DupLinkID);
       System_linkPrintBufferStatistics(pObj->Null_ispLinkID);
       System_linkPrintBufferStatistics(pObj->VPELinkID);
       System_linkPrintBufferStatistics(pObj->SyncLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_DmaSwMsLinkID);
       System_linkPrintBufferStatistics(pObj->DisplayLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       System_linkPrintBufferStatistics(pObj->Capture_dsswbLinkID);
       System_linkPrintBufferStatistics(pObj->Null_disWbLinkID);
       Task_sleep(500);
}

Void chains_srvCalibration_Display_tda3x_printStatistics(chains_srvCalibration_Display_tda3xObj *pObj){
       System_linkPrintStatistics(pObj->IssCaptureLinkID);
       System_linkPrintStatistics(pObj->IssM2mIspLinkID);
       System_linkPrintStatistics(pObj->Alg_IssAewbLinkID);
       System_linkPrintStatistics(pObj->DupLinkID);
       System_linkPrintStatistics(pObj->Null_ispLinkID);
       System_linkPrintStatistics(pObj->VPELinkID);
       System_linkPrintStatistics(pObj->SyncLinkID);
       System_linkPrintStatistics(pObj->Alg_DmaSwMsLinkID);
       System_linkPrintStatistics(pObj->DisplayLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       System_linkPrintStatistics(pObj->Capture_dsswbLinkID);
       System_linkPrintStatistics(pObj->Null_disWbLinkID);
       Task_sleep(500);
}

