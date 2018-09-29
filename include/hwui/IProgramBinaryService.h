/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#ifndef _IPROGRAMBINARYSERVICE_H_
#define _IPROGRAMBINARYSERVICE_H_

#include <binder/IInterface.h>
#include <binder/Binder.h>
#include "ProgramBinaryData.h"


#define PROGRAM_BINARY_NAME "program_binary"

/**
 * Turn on to enable program binary service.
 *
 * Possible values:
 * "1", to disable program binary service.
 * "0", to enable program binary service.
 */
#define PROPERTY_DISABLE_PROGRAM_BINARY "debug.program_binary.disable"

/**
 * Turn on to debug program binary service.
 *
 * Possible values:
 * "1", to enable debug log.
 * "0", to disable debug log.
 */
#define PROPERTY_DEBUG_PROGRAM_BINARY "debug.program_binary.log"

/**
 * Turn on to debug program binary content.
 *
 * Possible values:
 * "1", to enable debug program binary content.
 * "0", to disable debug program binary content.
 */
#define PROPERTY_DEBUG_PROGRAM_BINARY_CONTENT "debug.program_binary.content"


/*
 * Debug ProgramBinary features.
 */
#define DEBUG_PROGRAM_BINARY 1

extern bool g_debug_program_binary;
extern bool g_debug_program_binary_content;

#if DEBUG_PROGRAM_BINARY
    #define DEBUG_LOGD(...) \
    {                               \
        if (g_debug_program_binary) \
            ALOGD(__VA_ARGS__);     \
    }

    #define CONTENT_LOGD(...) \
    {                               \
        if (g_debug_program_binary_content) \
            ALOGD(__VA_ARGS__);     \
    }
#else
    #define DEBUG_LOGD(...)
    #define CONTENT_LOGD(...)
#endif

namespace android {
/*
 * This class defines the Binder IPC interface for accessing various
 * ProgramBinary features.
 */
enum PROGRAM_BINARY_ENUM{
        GET_READY = IBinder::FIRST_CALL_TRANSACTION,
        SET_READY,
        GET_PROGRAM_BINARY_DATA,
        SET_PROGRAM_BINARY_DATA
};

class IProgramBinaryService: public IInterface {
public:
    DECLARE_META_INTERFACE(ProgramBinaryService);

    /**
     * Returns whether program binary data is ready or not.
     */
    virtual bool getReady() = 0;
    virtual void setReady(bool ready) = 0;

    /**
     * Returns ProgramBinaryData or null if it's not ready.
     *
     * Data in detail:
     *  File descriptor of the program binary
     *  Length of the program binary
     *  Length of the program binary map
     *  Map of the program binary
     *
     */
    virtual ProgramBinaryData* getProgramBinaryData() = 0;
    virtual void setProgramBinaryData(ProgramBinaryData* pbData) = 0;
};

class BnProgramBinaryService : public BnInterface<IProgramBinaryService> {
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0) = 0;

    bool getReady() {
        // Not in use.
        return false;
    }

    void setReady(bool) {
        // Not in use.
    }

    ProgramBinaryData* getProgramBinaryData() {
        return NULL;
    }

    void setProgramBinaryData(ProgramBinaryData*) {
        // Not in use
    }
};

class BpProgramBinaryService : public BpInterface<IProgramBinaryService> {
public:
    BpProgramBinaryService(const sp<IBinder>& impl);

    bool getReady();
    void setReady(bool ready);

    ProgramBinaryData* getProgramBinaryData();
    void setProgramBinaryData(ProgramBinaryData* pbData);
};

};  // namespace android
#endif
