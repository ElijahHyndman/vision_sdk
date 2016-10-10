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

#ifndef _chains_bufLoop_H_
#define _chains_bufLoop_H_

#include <include/link_api/system.h>
#include <include/link_api/epLink.h>

typedef struct {
       UInt32    EpSourceLinkID;
       UInt32    EpSinkLinkID;

       EpLink_CreateParams                     EpSourcePrm;
       EpLink_CreateParams                     EpSinkPrm;
} chains_bufLoopObj;

Void chains_bufLoop_SetLinkId(chains_bufLoopObj *pObj);

Void chains_bufLoop_ResetLinkPrms(chains_bufLoopObj *pObj);

Void chains_bufLoop_SetPrms(chains_bufLoopObj *pObj);

Void chains_bufLoop_ConnectLinks(chains_bufLoopObj *pObj);

Int32 chains_bufLoop_Create(chains_bufLoopObj *pObj, Void *appObj);

Int32 chains_bufLoop_Start(chains_bufLoopObj *pObj);

Int32 chains_bufLoop_Stop(chains_bufLoopObj *pObj);

Int32 chains_bufLoop_Delete(chains_bufLoopObj *pObj);

Void chains_bufLoop_printBufferStatistics(chains_bufLoopObj *pObj);

Void chains_bufLoop_printStatistics(chains_bufLoopObj *pObj);

Void chains_bufLoop_SetAppPrms(chains_bufLoopObj *pObj, Void *appObj);

#endif /* _chains_bufLoop_H_ */
