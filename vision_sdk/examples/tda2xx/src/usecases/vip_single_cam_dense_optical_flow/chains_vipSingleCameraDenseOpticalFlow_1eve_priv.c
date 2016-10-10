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
#include "chains_vipSingleCameraDenseOpticalFlow_1eve_priv.h"
Void chains_vipSingleCameraDenseOpticalFlow_1eve_SetLinkId(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE;
       pObj->IPCOut_IPU1_0_EVE1_0LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_EVE1_IPU1_0_0LinkID      = EVE1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_DenseOptFlow_1LinkID       = EVE1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->IPCOut_EVE1_DSP1_0LinkID       = EVE1_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_DSP1_EVE1_0LinkID        = DSP1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_VectorToImageLinkID        = DSP1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->IPCOut_DSP1_IPU1_0_0LinkID     = DSP1_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_IPU1_0_DSP1_0LinkID      = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Display_VideoDofLinkID         = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void chains_vipSingleCameraDenseOpticalFlow_1eve_ResetLinkPrms(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_EVE1_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_EVE1_IPU1_0_0Prm);
       AlgorithmLink_DenseOptFlowCreateParams_Init(&pObj->Alg_DenseOptFlow_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_EVE1_DSP1_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_DSP1_EVE1_0Prm);
       AlgorithmLink_VectorToImageCreateParams_Init(&pObj->Alg_VectorToImagePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_DSP1_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_IPU1_0_DSP1_0Prm);
       DisplayLink_CreateParams_Init(&pObj->Display_VideoDofPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_vipSingleCameraDenseOpticalFlow_1eve_SetPrms(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){
       (pObj->Alg_DenseOptFlow_1Prm).baseClassCreate.size  = sizeof(AlgorithmLink_DenseOptFlowCreateParams);
       (pObj->Alg_DenseOptFlow_1Prm).baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_DENSE_OPTICAL_FLOW;
       (pObj->Alg_VectorToImagePrm).baseClassCreate.size  = sizeof(AlgorithmLink_VectorToImageCreateParams);
       (pObj->Alg_VectorToImagePrm).baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_VECTORTOIMAGE;
}

Void chains_vipSingleCameraDenseOpticalFlow_1eve_ConnectLinks(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){

       //Capture -> IPCOut_IPU1_0_EVE1_0
       pObj->CapturePrm.outQueParams.nextLink = pObj->IPCOut_IPU1_0_EVE1_0LinkID;
       pObj->IPCOut_IPU1_0_EVE1_0Prm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->IPCOut_IPU1_0_EVE1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_IPU1_0_EVE1_0 -> IPCIn_EVE1_IPU1_0_0
       pObj->IPCOut_IPU1_0_EVE1_0Prm.outQueParams.nextLink = pObj->IPCIn_EVE1_IPU1_0_0LinkID;
       pObj->IPCIn_EVE1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_EVE1_0LinkID;
       pObj->IPCIn_EVE1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_EVE1_IPU1_0_0 -> Alg_DenseOptFlow_1
       pObj->IPCIn_EVE1_IPU1_0_0Prm.outQueParams.nextLink = pObj->Alg_DenseOptFlow_1LinkID;
       pObj->Alg_DenseOptFlow_1Prm.inQueParams.prevLinkId = pObj->IPCIn_EVE1_IPU1_0_0LinkID;
       pObj->Alg_DenseOptFlow_1Prm.inQueParams.prevLinkQueId = 0;

       //Alg_DenseOptFlow_1 -> IPCOut_EVE1_DSP1_0
       pObj->Alg_DenseOptFlow_1Prm.outQueParams.nextLink = pObj->IPCOut_EVE1_DSP1_0LinkID;
       pObj->IPCOut_EVE1_DSP1_0Prm.inQueParams.prevLinkId = pObj->Alg_DenseOptFlow_1LinkID;
       pObj->IPCOut_EVE1_DSP1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_EVE1_DSP1_0 -> IPCIn_DSP1_EVE1_0
       pObj->IPCOut_EVE1_DSP1_0Prm.outQueParams.nextLink = pObj->IPCIn_DSP1_EVE1_0LinkID;
       pObj->IPCIn_DSP1_EVE1_0Prm.inQueParams.prevLinkId = pObj->IPCOut_EVE1_DSP1_0LinkID;
       pObj->IPCIn_DSP1_EVE1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_DSP1_EVE1_0 -> Alg_VectorToImage
       pObj->IPCIn_DSP1_EVE1_0Prm.outQueParams.nextLink = pObj->Alg_VectorToImageLinkID;
       pObj->Alg_VectorToImagePrm.inQueParams.prevLinkId = pObj->IPCIn_DSP1_EVE1_0LinkID;
       pObj->Alg_VectorToImagePrm.inQueParams.prevLinkQueId = 0;

       //Alg_VectorToImage -> IPCOut_DSP1_IPU1_0_0
       pObj->Alg_VectorToImagePrm.outQueParams.nextLink = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->Alg_VectorToImageLinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_DSP1_IPU1_0_0 -> IPCIn_IPU1_0_DSP1_0
       pObj->IPCOut_DSP1_IPU1_0_0Prm.outQueParams.nextLink = pObj->IPCIn_IPU1_0_DSP1_0LinkID;
       pObj->IPCIn_IPU1_0_DSP1_0Prm.inQueParams.prevLinkId = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCIn_IPU1_0_DSP1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_IPU1_0_DSP1_0 -> Display_VideoDof
       pObj->IPCIn_IPU1_0_DSP1_0Prm.outQueParams.nextLink = pObj->Display_VideoDofLinkID;
       pObj->Display_VideoDofPrm.inQueParams.prevLinkId = pObj->IPCIn_IPU1_0_DSP1_0LinkID;
       pObj->Display_VideoDofPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_vipSingleCameraDenseOpticalFlow_1eve_Create(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleCameraDenseOpticalFlow_1eve_SetLinkId(pObj);
       chains_vipSingleCameraDenseOpticalFlow_1eve_ResetLinkPrms(pObj);

       chains_vipSingleCameraDenseOpticalFlow_1eve_SetPrms(pObj);
       chains_vipSingleCameraDenseOpticalFlow_1eve_SetAppPrms(pObj, appObj);

       chains_vipSingleCameraDenseOpticalFlow_1eve_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_EVE1_0LinkID, &pObj->IPCOut_IPU1_0_EVE1_0Prm, sizeof(pObj->IPCOut_IPU1_0_EVE1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_EVE1_IPU1_0_0LinkID, &pObj->IPCIn_EVE1_IPU1_0_0Prm, sizeof(pObj->IPCIn_EVE1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_DenseOptFlow_1LinkID, &pObj->Alg_DenseOptFlow_1Prm, sizeof(pObj->Alg_DenseOptFlow_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_EVE1_DSP1_0LinkID, &pObj->IPCOut_EVE1_DSP1_0Prm, sizeof(pObj->IPCOut_EVE1_DSP1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_DSP1_EVE1_0LinkID, &pObj->IPCIn_DSP1_EVE1_0Prm, sizeof(pObj->IPCIn_DSP1_EVE1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_VectorToImageLinkID, &pObj->Alg_VectorToImagePrm, sizeof(pObj->Alg_VectorToImagePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_DSP1_IPU1_0_0LinkID, &pObj->IPCOut_DSP1_IPU1_0_0Prm, sizeof(pObj->IPCOut_DSP1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_IPU1_0_DSP1_0LinkID, &pObj->IPCIn_IPU1_0_DSP1_0Prm, sizeof(pObj->IPCIn_IPU1_0_DSP1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_VideoDofLinkID, &pObj->Display_VideoDofPrm, sizeof(pObj->Display_VideoDofPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraDenseOpticalFlow_1eve_Start(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_VideoDofLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_VectorToImageLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_EVE1_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_DenseOptFlow_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraDenseOpticalFlow_1eve_Stop(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_VideoDofLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_VectorToImageLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_EVE1_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_DenseOptFlow_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraDenseOpticalFlow_1eve_Delete(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_VideoDofLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_VectorToImageLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_EVE1_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_DenseOptFlow_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleCameraDenseOpticalFlow_1eve_printBufferStatistics(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_DenseOptFlow_1LinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_EVE1_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_DSP1_EVE1_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_VectorToImageLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       System_linkPrintBufferStatistics(pObj->Display_VideoDofLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_vipSingleCameraDenseOpticalFlow_1eve_printStatistics(chains_vipSingleCameraDenseOpticalFlow_1eveObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->Alg_DenseOptFlow_1LinkID);
       System_linkPrintStatistics(pObj->IPCOut_EVE1_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_DSP1_EVE1_0LinkID);
       System_linkPrintStatistics(pObj->Alg_VectorToImageLinkID);
       System_linkPrintStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       System_linkPrintStatistics(pObj->Display_VideoDofLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

