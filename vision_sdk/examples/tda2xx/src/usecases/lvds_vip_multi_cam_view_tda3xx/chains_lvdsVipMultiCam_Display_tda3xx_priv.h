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

#ifndef _chains_lvdsVipMultiCam_Display_tda3xx_H_
#define _chains_lvdsVipMultiCam_Display_tda3xx_H_

#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/algorithmLink_dmaSwMs.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    CaptureLinkID;
       UInt32    SelectLinkID;
       UInt32    Sync_2LinkID;
       UInt32    Alg_DmaSwMs_2LinkID;
       UInt32    Display_video2LinkID;
       UInt32    Sync_1LinkID;
       UInt32    Alg_DmaSwMs_1LinkID;
       UInt32    Display_video1LinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       CaptureLink_CreateParams                CapturePrm;
       SelectLink_CreateParams                 SelectPrm;
       SyncLink_CreateParams                   Sync_2Prm;
       AlgorithmLink_DmaSwMsCreateParams       Alg_DmaSwMs_2Prm;
       DisplayLink_CreateParams                Display_video2Prm;
       SyncLink_CreateParams                   Sync_1Prm;
       AlgorithmLink_DmaSwMsCreateParams       Alg_DmaSwMs_1Prm;
       DisplayLink_CreateParams                Display_video1Prm;
       GrpxSrcLink_CreateParams                GrpxSrcPrm;
       DisplayLink_CreateParams                Display_GrpxPrm;
} chains_lvdsVipMultiCam_Display_tda3xxObj;

Void chains_lvdsVipMultiCam_Display_tda3xx_SetLinkId(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_ResetLinkPrms(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_SetPrms(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_ConnectLinks(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Int32 chains_lvdsVipMultiCam_Display_tda3xx_Create(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj, Void *appObj);

Int32 chains_lvdsVipMultiCam_Display_tda3xx_Start(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Int32 chains_lvdsVipMultiCam_Display_tda3xx_Stop(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Int32 chains_lvdsVipMultiCam_Display_tda3xx_Delete(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_printBufferStatistics(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_printStatistics(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj);

Void chains_lvdsVipMultiCam_Display_tda3xx_SetAppPrms(chains_lvdsVipMultiCam_Display_tda3xxObj *pObj, Void *appObj);

#endif /* _chains_lvdsVipMultiCam_Display_tda3xx_H_ */
