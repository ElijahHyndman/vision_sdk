#
# (c) Texas Instruments 2014
#
# Makefile to generate use-case code using Vision SDK use-case generation tool
#
# Pre-requisites
# --------------
# Make sure "dot" tool from Graphviz (http://www.graphviz.org/) is
# installed and is visible in your system path
#
# Type below at command prompt to confirm "dot" is visible in the system path
#
# dot -V
#
# Regenerating the use-cases
# --------------------------
# To regenerate the use-case's type below on windows command prompt
#
# gmake -f use_case_gen.mk
#
#
# Information about the tool
# --------------------------
#
# This tool take the below file as input. This file is written by the user.
# <usecase folder>\<usecase name>.txt
#
# This tool outputs the below files,
#
# <usecase folder>\<usecase name>_img.txt
#     - This is a "Graphviz" compatible graph description input file.
#     - This is used as input to "dot" tool from Graphviz to generate a
#       image file <usecase folder>\<usecase name>.jpg
#
# <usecase folder>\<usecase name>.jpg
#     - This file is generated using Graphviz "dot" tool.
#     - This shows the use-case in a visually friendly manner to the user
#
# <usecase folder>\<usecase name>_priv.h,
# <usecase folder>\<usecase name>_priv.c
#     - This is the code generated by the tool
#     - These files can be compiled by the target compiler
#       without any further modification.
#     - Typically user should not modify these files
#
# The tool does not generate the complete use-case code.
# Some portions of the code still needs to be written by the user
#
# Below file has the code which is manully written by user
# <usecase folder>\<usecase name>.c
#
#

TDA2XX_BIOS_USECASES = $(abspath ../../examples/tda2xx/src/usecases)

TDA2XX_LINUX_USECASES = $(abspath ../../linux/examples/tda2xx/src/usecases)

TDA2XX_BIOS_TS_USECASES = $(abspath ../../testsuite/tda2xx/src/)

ifeq ($(BUILD_OS),Linux)
USECASE_GEN_TOOL = ./vsdk_linux.out
else
USECASE_GEN_TOOL = ./vsdk_win32.exe
endif

all:
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/avbrx_dec_display $(TDA2XX_BIOS_USECASES)/avbrx_dec_display/chains_avbRx_Dec_Display.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/avbrx_sv_ed $(TDA2XX_BIOS_USECASES)/avbrx_sv_ed/chains_avbRxSurroundViewEdgeDetect.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/iss_capture_isp_simcop_display $(TDA2XX_BIOS_USECASES)/iss_capture_isp_simcop_display/chains_issIspSimcop_Display.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_dual_cam_dual_display $(TDA2XX_BIOS_USECASES)/lvds_vip_dual_cam_dual_display/chains_lvdsVipDualCam_DualDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda2xx $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda2xx/chains_lvdsVipMultiCam_Display_tda2xx.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda2xx_mc $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda2xx_mc/chains_lvdsVipMultiCam_Display_tda2xx_mc.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda3xx $(TDA2XX_BIOS_USECASES)/lvds_vip_multi_cam_view_tda3xx/chains_lvdsVipMultiCam_Display_tda3xx.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_analytics_us $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_analytics_us/chains_lvdsVipSurroundViewAnalyticsUltrasound.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_standalone $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_standalone/chains_lvdsVipSurroundViewStandalone.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_tda3xx $(TDA2XX_BIOS_USECASES)/lvds_vip_sv_tda3xx/chains_lvdsVipSurroundView.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/network_rx_tx $(TDA2XX_BIOS_USECASES)/network_rx_tx/chains_networkRxDecDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/network_rx_tx $(TDA2XX_BIOS_USECASES)/network_rx_tx/chains_networkRxDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/network_rx_tx $(TDA2XX_BIOS_USECASES)/network_rx_tx/chains_networkTxCapture.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/network_rx_tx $(TDA2XX_BIOS_USECASES)/network_rx_tx/chains_networkTxEncCapture.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/network_rx_tx $(TDA2XX_BIOS_USECASES)/network_rx_tx/chains_networkTxMultiCamCapture.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda2xx $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda2xx/chains_vipSingleCameraAnalytics_tda2xx.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda2xx $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda2xx/chains_networkRxCameraAnalytics_tda2xx.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda3xx $(TDA2XX_BIOS_USECASES)/vip_single_cam_analytics_tda3xx/chains_vipSingleCameraAnalytics_tda3xx.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_dense_optical_flow $(TDA2XX_BIOS_USECASES)/vip_single_cam_dense_optical_flow/chains_vipSingleCameraDenseOpticalFlow_4eve.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_dense_optical_flow $(TDA2XX_BIOS_USECASES)/vip_single_cam_dense_optical_flow/chains_vipSingleCameraDenseOpticalFlow_1eve.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_dual_display $(TDA2XX_BIOS_USECASES)/vip_single_cam_dual_display/chains_vipSingleCam_DualDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_dual_display_edge_detection $(TDA2XX_BIOS_USECASES)/vip_single_cam_dual_display_edge_detection/chains_vipSingleCam_DualDisplayEdgeDetection.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_edge_detection $(TDA2XX_BIOS_USECASES)/vip_single_cam_edge_detection/chains_vipSingleCameraEdgeDetection.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_frame_copy $(TDA2XX_BIOS_USECASES)/vip_single_cam_frame_copy/chains_vipSingleCameraFrameCopy.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_frame_copy_safety $(TDA2XX_BIOS_USECASES)/vip_single_cam_frame_copy_safety/chains_vipSingleCameraSafeFrameCopy.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_lane_detection $(TDA2XX_BIOS_USECASES)/vip_single_cam_lane_detection/chains_vipSingleCameraLaneDetect.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_object_detection $(TDA2XX_BIOS_USECASES)/vip_single_cam_object_detection/chains_vipSingleCameraObjectDetect.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_sparse_optical_flow $(TDA2XX_BIOS_USECASES)/vip_single_cam_sparse_optical_flow/chains_vipSingleCameraSparseOpticalFlow.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_subframe_copy $(TDA2XX_BIOS_USECASES)/vip_single_cam_subframe_copy/chains_vipSingleCameraSubFrameCopy.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_single_cam_view $(TDA2XX_BIOS_USECASES)/vip_single_cam_view/chains_vipSingleCam_Display.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_stereo_calibration $(TDA2XX_BIOS_USECASES)/vip_stereo_calibration/chains_vipStereoCalibration.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_stereo_cam_analytics $(TDA2XX_BIOS_USECASES)/vip_stereo_cam_analytics/chains_vipStereoCameraAnalytics.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/vip_stereo_only_display $(TDA2XX_BIOS_USECASES)/vip_stereo_only_display/chains_vipStereoOnlyDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_USECASES)/ov490_vip_sv_standalone  $(TDA2XX_BIOS_USECASES)/ov490_vip_sv_standalone/chains_ov490VipSurroundViewStandalone.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/avb_rx_multi_cam_decode_sgx_display  $(TDA2XX_LINUX_USECASES)/avb_rx_multi_cam_decode_sgx_display/chains_avbRxDecodeDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_srv  $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_srv/chains_lvdsVipMultiCam_Sgx3Dsrv.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_view  $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_view/chains_lvdsVipMultiCam_SgxDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/vip_single_cam_analytics_sgx_display  $(TDA2XX_LINUX_USECASES)/vip_single_cam_analytics_sgx_display/chains_vipSingleCamAnalytics_SgxDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/vip_single_cam_enc_dec_sgx_display  $(TDA2XX_LINUX_USECASES)/vip_single_cam_enc_dec_sgx_display/chains_vipSingleCam_Enc_Dec_SgxDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/vip_single_cam_sgx_display  $(TDA2XX_LINUX_USECASES)/vip_single_cam_sgx_display/chains_vipSingleCam_SgxDisplay.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/ov490_vip_multi_cam_3d_srv  $(TDA2XX_LINUX_USECASES)/ov490_vip_multi_cam_3d_srv/chains_ov490VipMultiCam_Sgx3Dsrv.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_perception  $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_perception/chains_lvdsVipMultiCam_3d_perception.txt
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_srv_acalib  $(TDA2XX_LINUX_USECASES)/lvds_vip_multi_cam_3d_srv_acalib/chains_lvdsVipMultiCam_Sgx3DsrvACalib.txt

ts_all:
	$(USECASE_GEN_TOOL) -img -file -path $(TDA2XX_BIOS_TS_USECASES)/ts_ultrasonic_capture $(TDA2XX_BIOS_TS_USECASES)/ts_ultrasonic_capture/chains_ultrasonicCapture.txt
