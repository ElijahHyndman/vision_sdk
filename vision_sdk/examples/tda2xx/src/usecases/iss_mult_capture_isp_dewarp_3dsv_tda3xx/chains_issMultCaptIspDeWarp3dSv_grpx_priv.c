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
#include "chains_issMultCaptIspDeWarp3dSv_grpx_priv.h"
Void chains_issMultCaptIspDeWarp3dSv_grpx_SetLinkId(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_0;
}

Void chains_issMultCaptIspDeWarp3dSv_grpx_ResetLinkPrms(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_issMultCaptIspDeWarp3dSv_grpx_SetPrms(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){
}

Void chains_issMultCaptIspDeWarp3dSv_grpx_ConnectLinks(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_issMultCaptIspDeWarp3dSv_grpx_Create(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj, Void *appObj){

       Int32 status;

       chains_issMultCaptIspDeWarp3dSv_grpx_SetLinkId(pObj);
       chains_issMultCaptIspDeWarp3dSv_grpx_ResetLinkPrms(pObj);

       chains_issMultCaptIspDeWarp3dSv_grpx_SetPrms(pObj);
       chains_issMultCaptIspDeWarp3dSv_grpx_SetAppPrms(pObj, appObj);

       chains_issMultCaptIspDeWarp3dSv_grpx_ConnectLinks(pObj);
       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_issMultCaptIspDeWarp3dSv_grpx_Start(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_issMultCaptIspDeWarp3dSv_grpx_Stop(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_issMultCaptIspDeWarp3dSv_grpx_Delete(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_issMultCaptIspDeWarp3dSv_grpx_printBufferStatistics(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_issMultCaptIspDeWarp3dSv_grpx_printStatistics(chains_issMultCaptIspDeWarp3dSv_grpxObj *pObj){
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

