LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#LOCAL_SRC_FILES := mtk_bionic.cpp
#LOCAL_MODULE := libshim_bio
#LOCAL_MODULE_TAGS := optional
#include $(BUILD_SHARED_LIBRARY)

# /system/vendor/lib/libvtmal.so ( _ZN7android12AudioPCMxWayD1Ev )
include $(CLEAR_VARS)
LOCAL_SRC_FILES := program_binary_builder.cpp
LOCAL_SHARED_LIBRARIES := libui
LOCAL_MODULE := libshim_ui
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

# /system/vendor/bin/program_binary_builder ( _ZN7android10uirenderer12ProgramAtlas14createProgramsEPlPi )
include $(CLEAR_VARS)
LOCAL_SRC_FILES := vtservice.cpp
LOCAL_MODULE := libshim_aud
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

# /system/vendor/bin/thermal ( ifc_set_txq_state ) : /system/vendor/lib*/mtk-ril.so ( ifc_ipv6_trigger_rs )
include $(CLEAR_VARS)
LOCAL_SRC_FILES := netutils.c
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_MODULE := libshim_ifc
LOCAL_C_INCLUDES += system/core/libnetutils/include
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
