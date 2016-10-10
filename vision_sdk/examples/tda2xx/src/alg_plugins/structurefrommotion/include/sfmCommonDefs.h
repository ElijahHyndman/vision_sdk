/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                           EP Systems Lab
*                    Perception & Analytics Lab R&D
*
*         Copyright (c) 2015 Texas Instruments, Incorporated.
*                        All Rights Reserved.
*
*
*          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
*
*                 TI Confidential - Maximum Restrictions
*
*
*
*=======================================================================
 *
 *  File: sfmCommonDefs.h
 *
 *  Public (visible to framework) definitions for SfM library
 *  
 =======================================================================*/
 
 #ifndef _SFM_COMMON_DEFS_INCLUDED_
 #define _SFM_COMMON_DEFS_INCLUDED_

#ifndef PC_VERSION
	#include <include/link_api/system.h>
#else
	#include "../../../../../git/sfm/testplatform/system/system_simulator.h"
	#include <stdio.h> 
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>
#endif

#include "memRequestAlgo.h"

#define LIN_ALG_FLOUBLE_TYPE 0 /* 0 = float, 1 = double */
#include "../../commonutils/linAlg/linAlg2DTypes.h"
#include "../../commonutils/linAlg/linAlg3DTypes.h"

/***************************************************************************
PROCESS FLOW
****************************************************************************/
//#define ASSERTS_ON /*uncomment for assertions*/
//#define VERBOSE_ON /*uncomment for prints*/
//#define SFM_RUN_DUMMY_ALGORITHMS_ON /*uncomment for "dummy" algorithm process flow */
#define SFM_PRINT_OUTPUT_ON 30 /*uncomment for SfM result print every x frames*/
#ifndef PC_VERSION
	//#define SFM_MAIN_USE_DUMPED_DATA_ON /*uncomment usage of dumped data*/
#endif

/***************************************************************************
ALGORITHM PARAMETERS THAT DO NOT CHANGE WITH USECASE
***************************************************************************/
//SfM 
#define SFM_NUM_CAMS_LIMIT (6) /*maximum number of cameras supported*/
#define SFM_NUM_POINTS_LIMIT (1024) /*maximum number of points per camera supported*/
#define SFM_QRD_FUNCTION 2 /*0-numerical recipes, 1-DSPF C natural, 2-DSPF optimized*/
#define SFM_SVD_FUNCTION 2 /*0-numerical recipes, 1-DSPF C natural, 2-DSPF optimized*/
#define SFM_SVD_NUM_POINTS_LIMIT (1024) /*maximum number of points allowed in SVD (=max #rows)*/

//Mapping (OG, boxes)
#define SFM_MAP_NUM_OG_CELLS_LIMIT (22500) /*maximum number of cells supported (ca. 3m x 3m with 0.02m resolution)*/
#define SFM_MAP_NUM_BOXES_LIMIT (12) /*maximum number of boxes supported*/

/***************************************************************************
ALGORITHM-LEVEL PROCESS STATUS 
***************************************************************************/
#define ALGORITHM_PROCESS_OK 0
#define ALGORITHM_PROCESS_FAIL -1
#define ALGORITHM_PROCESS_DISABLED 2
 
 #endif

