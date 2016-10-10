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

#ifndef _chains_lvdsVip2dSurroundView_H_
#define _chains_lvdsVip2dSurroundView_H_

#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/algorithmLink_geometricAlignment.h>
#include <include/link_api/algorithmLink_synthesis.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/epLink.h>
#include <include/link_api/algorithmLink_photoAlignment.h>

typedef struct {
       UInt32    CaptureLinkID;
       UInt32    Sync_svLinkID;
       UInt32    Dup_svLinkID;
       UInt32    IPCOut_IPU1_0_A15_0_2LinkID;
       UInt32    IPCIn_A15_0_IPU1_0_1LinkID;
       UInt32    epSink_2LinkID;
       UInt32    IPCOut_IPU1_0_DSP2_1LinkID;
       UInt32    IPCIn_DSP2_IPU1_0_1LinkID;
       UInt32    IPCOut_IPU1_0_DSP2_0LinkID;
       UInt32    IPCIn_DSP2_IPU1_0_0LinkID;
       UInt32    Alg_GeoAlignLinkID;
       UInt32    Alg_SynthesisLinkID;
       UInt32    IPCOut_DSP2_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_DSP2_0LinkID;
       UInt32    epSink_1LinkID;
       UInt32    Alg_PhotoAlignLinkID;

       CaptureLink_CreateParams                CapturePrm;
       SyncLink_CreateParams                   Sync_svPrm;
       DupLink_CreateParams                    Dup_svPrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_A15_0_2Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_IPU1_0_1Prm;
       EpLink_CreateParams                     epSink_2Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_DSP2_1Prm;
       IpcLink_CreateParams                    IPCIn_DSP2_IPU1_0_1Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_DSP2_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP2_IPU1_0_0Prm;
       AlgorithmLink_GAlignCreateParams        Alg_GeoAlignPrm;
       AlgorithmLink_SynthesisCreateParams     Alg_SynthesisPrm;
       IpcLink_CreateParams                    IPCOut_DSP2_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_DSP2_0Prm;
       EpLink_CreateParams                     epSink_1Prm;
       AlgorithmLink_PAlignCreateParams        Alg_PhotoAlignPrm;
} chains_lvdsVip2dSurroundViewObj;

Void chains_lvdsVip2dSurroundView_SetLinkId(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_ResetLinkPrms(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_SetPrms(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_ConnectLinks(chains_lvdsVip2dSurroundViewObj *pObj);

Int32 chains_lvdsVip2dSurroundView_Create(chains_lvdsVip2dSurroundViewObj *pObj, Void *appObj);

Int32 chains_lvdsVip2dSurroundView_Start(chains_lvdsVip2dSurroundViewObj *pObj);

Int32 chains_lvdsVip2dSurroundView_Stop(chains_lvdsVip2dSurroundViewObj *pObj);

Int32 chains_lvdsVip2dSurroundView_Delete(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_printBufferStatistics(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_printStatistics(chains_lvdsVip2dSurroundViewObj *pObj);

Void chains_lvdsVip2dSurroundView_SetAppPrms(chains_lvdsVip2dSurroundViewObj *pObj, Void *appObj);

#endif /* _chains_lvdsVip2dSurroundView_H_ */
