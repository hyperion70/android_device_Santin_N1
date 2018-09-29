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

#ifndef _PROGRAM_BINARY_DATA_H
#define _PROGRAM_BINARY_DATA_H

#include <stdint.h>


class ProgramBinaryData {
public:
    ProgramBinaryData(): mProgramFd(-1), mProgramBinaryLength(0),
            mProgramMapArrayLen(0), mProgramMap(NULL) { }

    ~ProgramBinaryData() {
        mProgramFd = -1;
        mProgramBinaryLength = 0;
        mProgramMapArrayLen = 0;

        if (mProgramMap) {
            delete mProgramMap;
            mProgramMap = NULL;
        }
    }

    void init(int fd, int programBinLen, int programMapLen, int64_t* programMapArray) {
        mProgramFd = fd;
        mProgramBinaryLength = programBinLen;
        mProgramMapArrayLen = programMapLen;

        if (mProgramMapArrayLen < 0) return;
        int len = mProgramMapArrayLen;
        mProgramMap = new int64_t[len];
        for (int i = 0; i < len; i++) {
            mProgramMap[i] = programMapArray[i];
        }
#if 0
        ALOGD("[ProgramBinaryData] Fd=%d, ProgramBinaryLength = %d, "
                "ProgramMapLength = %d, ProgramMapArray = 0x%x",
                mProgramFd, mProgramBinaryLength, mProgramMapArrayLen, mProgramMap);
#endif
    }

    int getFileDescriptor() { return mProgramFd; }
    int getProgramBinaryLen() { return mProgramBinaryLength; }
    int getProgramMapLen() { return mProgramMapArrayLen; }
    void getProgramMapArray(int64_t** programMapArray) {
        int len = mProgramMapArrayLen;
        *programMapArray = new int64_t[len];
        int64_t* mapArray = *programMapArray;
        for (int i = 0; i < len; i++) {
            mapArray[i] = mProgramMap[i];
        }
    }

private:
    // File descriptor of the program binary
    int mProgramFd;
    // Length of the program binary
    int mProgramBinaryLength;
    // Length of the program binary map.
    int mProgramMapArrayLen;
    /**
     * Descriobes how program binaries are placed in the buffer.
     * One entry contains 4 fileds.
     * long0: key, indicate the program description
     * long1: offset, offset to the binary pool's head
     * long2: length, binary length
     * long3: format, binary format
     */
    int64_t* mProgramMap;
};

#endif
