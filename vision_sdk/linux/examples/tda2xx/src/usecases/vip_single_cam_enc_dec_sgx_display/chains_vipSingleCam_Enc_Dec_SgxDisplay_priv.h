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

#ifndef _chains_vipSingleCam_Enc_Dec_SgxDisplay_H_
#define _chains_vipSingleCam_Enc_Dec_SgxDisplay_H_

#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/encLink.h>
#include <include/link_api/decLink.h>
#include <include/link_api/vpeLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/sgxFrmcpyLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    CaptureLinkID;
       UInt32    EncodeLinkID;
       UInt32    DecodeLinkID;
       UInt32    VPELinkID;
       UInt32    SyncLinkID;
       UInt32    IPCOut_IPU1_0_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_IPU1_0_0LinkID;
       UInt32    SgxFrmcpyLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_0LinkID;
       UInt32    Display_M4LinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       CaptureLink_CreateParams                CapturePrm;
       EncLink_CreateParams                    EncodePrm;
       DecLink_CreateParams                    DecodePrm;
       VpeLink_CreateParams                    VPEPrm;
       SyncLink_CreateParams                   SyncPrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_IPU1_0_0Prm;
       SgxFrmcpyLink_CreateParams              SgxFrmcpyPrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_0Prm;
       DisplayLink_CreateParams                Display_M4Prm;
       GrpxSrcLink_CreateParams                GrpxSrcPrm;
       DisplayLink_CreateParams                Display_GrpxPrm;
} chains_vipSingleCam_Enc_Dec_SgxDisplayObj;

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_SetLinkId(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_ResetLinkPrms(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_SetPrms(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_ConnectLinks(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Int32 chains_vipSingleCam_Enc_Dec_SgxDisplay_Create(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj, Void *appObj);

Int32 chains_vipSingleCam_Enc_Dec_SgxDisplay_Start(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Int32 chains_vipSingleCam_Enc_Dec_SgxDisplay_Stop(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Int32 chains_vipSingleCam_Enc_Dec_SgxDisplay_Delete(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_printBufferStatistics(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_printStatistics(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj);

Void chains_vipSingleCam_Enc_Dec_SgxDisplay_SetAppPrms(chains_vipSingleCam_Enc_Dec_SgxDisplayObj *pObj, Void *appObj);

#endif /* _chains_vipSingleCam_Enc_Dec_SgxDisplay_H_ */
