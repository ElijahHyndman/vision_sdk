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
#include "chains_vipSingleCam_DualDisplay_priv.h"
Void chains_vipSingleCam_DualDisplay_SetLinkId(chains_vipSingleCam_DualDisplayObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE;
       pObj->Dup_CaptureLinkID              = IPU1_0_LINK (SYSTEM_LINK_ID_DUP_0);
       pObj->Display_HDMILinkID             = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->Display_LCDLinkID              = SYSTEM_LINK_ID_DISPLAY_1;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_2;
}

Void chains_vipSingleCam_DualDisplay_ResetLinkPrms(chains_vipSingleCam_DualDisplayObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       DupLink_CreateParams_Init(&pObj->Dup_CapturePrm);
       DisplayLink_CreateParams_Init(&pObj->Display_HDMIPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_LCDPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_vipSingleCam_DualDisplay_SetPrms(chains_vipSingleCam_DualDisplayObj *pObj){
       (pObj->Dup_CapturePrm).numOutQue = 2;
}

Void chains_vipSingleCam_DualDisplay_ConnectLinks(chains_vipSingleCam_DualDisplayObj *pObj){

       //Capture -> Dup_Capture
       pObj->CapturePrm.outQueParams.nextLink = pObj->Dup_CaptureLinkID;
       pObj->Dup_CapturePrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->Dup_CapturePrm.inQueParams.prevLinkQueId = 0;

       //Dup_Capture -> Display_LCD
       pObj->Dup_CapturePrm.outQueParams[0].nextLink = pObj->Display_LCDLinkID;
       pObj->Display_LCDPrm.inQueParams.prevLinkId = pObj->Dup_CaptureLinkID;
       pObj->Display_LCDPrm.inQueParams.prevLinkQueId = 0;

       //Dup_Capture -> Display_HDMI
       pObj->Dup_CapturePrm.outQueParams[1].nextLink = pObj->Display_HDMILinkID;
       pObj->Display_HDMIPrm.inQueParams.prevLinkId = pObj->Dup_CaptureLinkID;
       pObj->Display_HDMIPrm.inQueParams.prevLinkQueId = 1;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_vipSingleCam_DualDisplay_Create(chains_vipSingleCam_DualDisplayObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleCam_DualDisplay_SetLinkId(pObj);
       chains_vipSingleCam_DualDisplay_ResetLinkPrms(pObj);

       chains_vipSingleCam_DualDisplay_SetPrms(pObj);
       chains_vipSingleCam_DualDisplay_SetAppPrms(pObj, appObj);

       chains_vipSingleCam_DualDisplay_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Dup_CaptureLinkID, &pObj->Dup_CapturePrm, sizeof(pObj->Dup_CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_HDMILinkID, &pObj->Display_HDMIPrm, sizeof(pObj->Display_HDMIPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_LCDLinkID, &pObj->Display_LCDPrm, sizeof(pObj->Display_LCDPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_DualDisplay_Start(chains_vipSingleCam_DualDisplayObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_LCDLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_HDMILinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Dup_CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_DualDisplay_Stop(chains_vipSingleCam_DualDisplayObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_LCDLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_HDMILinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Dup_CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_DualDisplay_Delete(chains_vipSingleCam_DualDisplayObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_LCDLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_HDMILinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Dup_CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleCam_DualDisplay_printBufferStatistics(chains_vipSingleCam_DualDisplayObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->Dup_CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->Display_HDMILinkID);
       System_linkPrintBufferStatistics(pObj->Display_LCDLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_vipSingleCam_DualDisplay_printStatistics(chains_vipSingleCam_DualDisplayObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->Dup_CaptureLinkID);
       System_linkPrintStatistics(pObj->Display_HDMILinkID);
       System_linkPrintStatistics(pObj->Display_LCDLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

