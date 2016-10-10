/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

 /**
  ******************************************************************************
 * \file captureLink_tsk.c
 *
 * \brief  This file has the implementation of Capture Link API
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 *           The state machine table is as shown below
 *
 *   Cmds   | CREATE | DETECT_VIDEO | START | NEW_DATA  | STOP   | DELETE |
 *   States |========|==============|=======|===========|========|========|
 *   IDLE   | READY  | -            | -     | -         | -      | -      |
 *   READY  | -      | READY        | RUN   | -         | READY  | IDLE   |
 *   RUN    | -      | -            | -     | RUN       | READY  | IDLE   |
 *
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Updates as per code review comments
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "captureLink_priv.h"

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */

Void CaptureLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);

Int32 CaptureLink_tskRun(CaptureLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gCaptureLink_tskStack, 32)
#pragma DATA_SECTION(gCaptureLink_tskStack, ".bss:taskStackSection")
UInt8 gCaptureLink_tskStack[CAPTURE_LINK_OBJ_MAX][CAPTURE_LINK_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
/* link object, stores all link related information */
CaptureLink_Obj gCaptureLink_obj[CAPTURE_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Run state of link.
 *
 * In this state link waits for command from application or next link or from
 * driver. Basically all are control commands except the new_data command where
 * link gets the captured frames from driver and puts in output queue. After
 * that it sends command to next link.
 *
 * \param  pObj     [IN] Capture link object
 * \param  pTsk     [IN] Capture link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not to
 *                       caller
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_tskRun(CaptureLink_Obj * pObj, Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    Utils_MsgHndl *pRunMsg;
    UInt32 cmd, instId, frmSkipMask;

    /* READY loop done and ackMsg status */
    *done = (Bool)FALSE;
    *ackMsg = (Bool)FALSE;
    *pMsg = NULL;

    /* RUN loop done and ackMsg status */
    runDone = (Bool)FALSE;
    runAckMsg = (Bool)FALSE;

    /* RUN state loop */
    while (!runDone)
    {
        /* wait for message */
        status = Utils_tskRecvMsg(pTsk, &pRunMsg, BSP_OSAL_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        /* extract message command from message */
        cmd = Utils_msgGetCmd(pRunMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                /* new data frames have been captured, process them */
                instId = (UInt32)Utils_msgGetPrm(pRunMsg);
                /* MISRA.CAST.PTR_TO_INT
                * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
                * State: Defer -> Waiver -> Case by case
                * Passing pointer arguments to functions which
                * takes arguments as UInt32 for legacy reasons and viceversa
                */
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);

                /* INVARIANT_CONDITION.UNREACH
                * MISRAC_2004_Rule_13.7
                * MISRAC_WAIVER:
                * Code is currently unreachable.
                * This is kept to ensure future updates by the called function.
                */
                status = CaptureLink_drvProcessData(pObj, instId);
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    /* in case of error exit RUN loop */
                    runDone = (Bool)TRUE;

                    /* since message is already ACK'ed or free'ed do not ACK
                     * or free it again */
                    runAckMsg = (Bool)FALSE;
                }
                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                /* new data frames have been captured, process them */

                CaptureLink_drvPrintStatus(pObj);

                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                CaptureLink_printBufferStatus(pObj);
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_STOP:
                /* stop RUN loop and goto READY state */
                runDone = (Bool)TRUE;

                /* ACK message after actually stopping the driver outside the
                 * RUN loop */
                runAckMsg = (Bool)TRUE;
                break;

            case SYSTEM_CMD_DELETE:

                /* stop RUN loop and goto IDLE state */

                /* exit RUN loop */
                runDone = (Bool)TRUE;

                /* exit READY loop */
                *done = (Bool)TRUE;

                /* ACK message after exiting READY loop */
                *ackMsg = (Bool)TRUE;

                /* Pass the received message to the READY loop */
                *pMsg = pRunMsg;

                break;
            case CAPTURE_LINK_CMD_SET_FRAME_SKIP_MASK:
                /* Command to change the frame skip mask parameter */
                frmSkipMask = *(UInt32 *)Utils_msgGetPrm(pRunMsg);
                /* This command would be called in limp home mode where
                 * the FPS is reduced when the temperature is very high.
                 */
                status = CaptureLink_drvUpdateFrmSkip(pObj, frmSkipMask);
                /* ACK or free message before proceding */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
            default:

                /* invalid command for this state ACK it and continue RUN
                 * loop */
                Utils_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop driver */
    CaptureLink_drvStop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
    {
        Utils_tskAckOrFreeMsg(pRunMsg, status);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function is the implementation of Idle state.
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 *******************************************************************************
 */
Void CaptureLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    CaptureLink_Obj *pObj;

    pObj = (CaptureLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
         * with error status */
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the driver */
        status = CaptureLink_drvCreate(pObj, Utils_msgGetPrm(pMsg));

        /* ACK based on create status */
        Utils_tskAckOrFreeMsg(pMsg, status);
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* create success, entering READY state */
        done = (Bool)FALSE;
        ackMsg = (Bool)FALSE;

        /* READY state loop */
        while (!done)
        {
            /* wait for message */
            status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
            /* extract message command from message */
            cmd = Utils_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    /* Start capture driver */
                    status = CaptureLink_drvStart(pObj);

                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);

                    /* if start status is error then remain in READY state */
                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        /* start success, entering RUN state */
                        status =
                            CaptureLink_tskRun(pObj, pTsk, &pMsg, &done, &ackMsg);

                        /** done = FALSE, exit RUN state
                        done = TRUE, exit RUN and READY state
                        */
                    }
                    break;

                case SYSTEM_CMD_DELETE:

                    /* exit READY state */
                    done = (Bool)TRUE;
                    ackMsg = (Bool)TRUE;
                    break;

                case CAPTURE_LINK_GET_SUBFRAME_INFO:
                    /* This cmd will be called by downstream link which processes
                    * subframe dataduring its create time.
                    */
                    status = CaptureLink_subframe_drvGetVIPOutFrameInfo
                                                (pObj, Utils_msgGetPrm(pMsg));
                    /* ACK based on create status */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;

                default:
                    /* invalid command for this state ACK it and continue READY
                    * loop */
                    Utils_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        /* exiting READY state, delete driver */
        CaptureLink_drvDelete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((ackMsg != (Bool)FALSE) && (pMsg != NULL))
        {
            Utils_tskAckOrFreeMsg(pMsg, status);
        }
    }
    /* entering IDLE state */
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for capture link. BIOS task for capture
 *  link gets created / registered in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 CaptureLink_init(void)
{
    Int32 status;
    UInt32    i;
    System_LinkObj linkObj;
    CaptureLink_Obj *pObj;

    /* register link with system API */

    for(i=0U; i<CAPTURE_LINK_OBJ_MAX; i++)
    {
        pObj = &gCaptureLink_obj[i];

        memset(pObj, 0, sizeof(*pObj));

        pObj->linkId = SYSTEM_LINK_ID_CAPTURE_0+i;

        linkObj.pTsk                = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &CaptureLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &CaptureLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &CaptureLink_getInfo;

        System_registerLink(pObj->linkId, &linkObj);

        /* Create link task, task remains in IDLE state
         * CaptureLink_tskMain is called when a message command is received
         */

        status = Utils_tskCreate(&pObj->tsk,
                CaptureLink_tskMain,
                CAPTURE_LINK_TSK_PRI,
                gCaptureLink_tskStack[i],
                CAPTURE_LINK_TSK_STACK_SIZE, pObj, "CAPTURE ",
                UTILS_TSK_AFFINITY_CORE0);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-Init function for capture link. BIOS task for capture
 *        link gets deleted in this function.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 CaptureLink_deInit(void)
{
    UInt32 i;
    CaptureLink_Obj *pObj;

    for(i=0U; i<CAPTURE_LINK_OBJ_MAX; i++)
    {
        pObj = &gCaptureLink_obj[i];

        /*
         * Delete link task
         */
        Utils_tskDelete(&pObj->tsk);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get the buffer and queue information about link.
 *
 * \param  ptr  [IN] Task Handle
 * \param  info [IN] Pointer to link information handle

 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 CaptureLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    CaptureLink_Obj *pObj = (CaptureLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->info, sizeof(*info));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to give full buffers to next
 *        link.
 *
 * Capture link sends message to next link about availability of buffers.
 * Next link calls this callback function to get full buffers from capture
 * output queue.
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 CaptureLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    CaptureLink_Obj *pObj = (CaptureLink_Obj *) pTsk->appData;
    Int32 status;

    UTILS_assert(queId < CAPTURE_LINK_MAX_OUT_QUE);
    UTILS_assert(NULL != pObj->linkStatsInfo);

    pObj->linkStatsInfo->linkStats.getFullBufCount++;

    /* CaptureLink_Obj uses a single queue. queId is still passed as
     * this function is common to all the links. Here we just ignore
     * the queId */
    status =  Utils_bufGetFull(&pObj->bufQue, pBufList, BSP_OSAL_NO_WAIT);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 *
 *
 * \param  ptr      [IN] Task Handle
 * \param  queId    [IN] queId from which buffers are required.
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/

/*
* MISRA.PPARAM.NEEDS.CONS
* MISRAC_2004_Rule_16.7
* Function parameter is not declared as a pointer to const.
* KW State: Defer -> Waiver -> Case by case
*/


Int32 CaptureLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                      System_BufferList * pBufList)
{
    Utils_TskHndl *pTsk = (Utils_TskHndl *) ptr;

    CaptureLink_Obj *pObj = (CaptureLink_Obj *) pTsk->appData;

    UTILS_assert(queId < CAPTURE_LINK_MAX_OUT_QUE);

    return CaptureLink_drvPutEmptyBuffers(pObj, pBufList);
}
