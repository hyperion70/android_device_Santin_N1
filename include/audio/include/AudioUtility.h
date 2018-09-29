#ifndef AUDIO_UTILITY_H
#define AUDIO_UTILITY_H


#include <stdlib.h>
#include <stdio.h>
#include "AudioDef.h"
#include "AudioType.h"
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <utils/Log.h>
#include <utils/String8.h>
#include <stdint.h>
#include <sys/stat.h>
#include <utils/Vector.h>
#include <utils/threads.h>
#include <utils/SortedVector.h>
#include <time.h>


#if defined(PC_EMULATION)
#include "Windows.h"
#include "WinBase.h"
#else
#include <hardware_legacy/AudioSystemLegacy.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#endif

#include "AudioLock.h"
#include <tinyalsa/asoundlib.h>
#include "MtkAudioComponent.h"
#include "audio_custom_exp.h"
#include "AudioCompFltCustParam.h"

/*
    this function should implement the basic function for debug information
    or basic function proviede to audio hardware modules
*/

namespace android
{
#define MAX_DUMP_NUM (1024)

enum
{
    AUDIO_LOG_HARDWARE = 1,
    AUDIO_LOG_A2DPHARDWARE,
    AUDIO_LOG_STREAMOUT,
    AUDIO_LOG_STREAMIN,
    AUDIO_LOG_I2SSTREAMIN,
    AUDIO_LOG_VOLUMECONTROLLER,
    AUDIO_LOG_RESOURCEMANAGER,
    AUDIO_LOG_AUDIODEVCE,
    AUDIO_LOG_ANALOG,
    AUDIO_LOG_DIGITAL,
    AUDIO_LOG_AUDIOFLINGER,
    AUDIO_LOG_SPEECHCONTROL,
    AUDIO_LOG_AUDIOPOLICYSERVICE,
    AUDIO_LOG_AUDIOPOLICYANAGER,
    AUDIO_LOG_AUDIOMIXER
};

enum
{
    AUDIO_SUPPORT_DMIC = 1,
    AUDIO_SUPPORT_2IN1_SPEAKER,
    AUDIO_SUPPORT_VIBRATION_SPEAKER,
    AUDIO_SUPPORT_EXTERNAL_BUILTIN_MIC,
    AUDIO_SUPPORT_EXTERNAL_ECHO_REFERENCE,
};

class AudioTimeStamp
{
    public:
        AudioTimeStamp();
        ~AudioTimeStamp();
        void SetSystemTimeValid(const char str);
    private:
        struct timespec systemtime[30];
        String8 TimeString[30];
        const int MaxRecord = 30;
        int index;
};

struct RingBuf
{
    char *pBufBase;
    char *pRead;
    char *pWrite;
    int   bufLen;
};

extern const char *audio_dump_path;
extern const char *streamout_ori;
extern const char *streamout_ori_propty;
extern const char *streamout_dcr;
extern const char *streamout_dcr_propty;

extern const char *streamout_s2m;
extern const char *streamout_s2m_propty;
extern const char *streamout_acf;
extern const char *streamout_acf_propty;
extern const char *streamout_hcf;
extern const char *streamout_hcf_propty;

extern const char *streamout;
extern const char *streamoutfinal;
extern const char *streamout_propty;
extern const char *aud_dumpftrace_dbg_propty;
extern const char *streaminIVCPMIn;
extern const char *streaminIVIn;
extern const char *streamout_vibsignal;
extern const char *streamout_notch;

extern const char *streaminmanager;
extern const char *streamin;;
extern const char *streaminOri;
extern const char *streaminI2S;
extern const char *streaminDAIBT;
extern const char *streaminSpk;
extern const char *streaminSpk_propty;
extern const char *capture_data_provider;

extern const char *streamin_propty;
extern const char *streamin_epl_propty;

extern const char *allow_low_latency_propty;
extern const char *streamhfp_propty;
extern const char *allow_offload_propty;
extern const char *streaminlog_propty;

extern bool bDumpStreamOutFlg;
extern bool bDumpStreamInFlg;


int AudiocheckAndCreateDirectory(const char *pC);
FILE *AudioOpendumpPCMFile(const char *filepath, const char *propty);
void AudioCloseDumpPCMFile(FILE  *file);
void AudioDumpPCMData(void *buffer , uint32_t bytes, FILE  *file);
timespec GetSystemTime(bool print =0);
unsigned long long TimeDifference(struct timespec time1, struct timespec time2);

//-------ring buffer operation
int RingBuf_getDataCount(const RingBuf *RingBuf1);
int RingBuf_getFreeSpace(const RingBuf *RingBuf1);
void RingBuf_copyToLinear(char *buf, RingBuf *RingBuf1, int count);
void RingBuf_copyFromLinear(RingBuf *RingBuf1, const char *buf, int count);
void RingBuf_fillZero(RingBuf *RingBuf1, int count);
void RingBuf_copyEmpty(RingBuf *RingBuft, RingBuf *RingBufs);
int RingBuf_copyFromRingBuf(RingBuf *RingBuft, RingBuf *RingBufs, int count);
void RingBuf_writeDataValue(RingBuf *RingBuf1, const int value, const int count);

void RingBuf_copyFromLinearSRC(void *pSrcHdl, RingBuf *RingBuft, char *buf, int num, int srt, int srs);
void RingBuf_copyEmptySRC(void *pSrcHdl, RingBuf *RingBuft, const RingBuf *RingBufs, int srt, int srs);

void CVSDLoopbackGetWriteBuffer(uint8_t **buffer, uint32_t *buf_len);
void CVSDLoopbackGetReadBuffer(uint8_t **buffer, uint32_t *buf_len);
void CVSDLoopbackReadDataDone(uint32_t len);
void CVSDLoopbackWriteDataDone(uint32_t len);
void CVSDLoopbackResetBuffer(void);
int32_t CVSDLoopbackGetFreeSpace(void);
int32_t CVSDLoopbackGetDataCount(void);

bool IsAudioSupportFeature(int dFeatureOption);


uint32_t GetMicDeviceMode(uint32_t mic_category);
unsigned int FormatTransfer(int SourceFormat, int TargetFormat,void *Buffer,unsigned int mReadBufferSize);
int InFactoryMode();
int In64bitsProcess();


#ifdef MTK_PERFSERVICE_SUPPORT

/**
 * regPerfServiceScn(int *mPerfServiceHandle, const int scn_freq_little)
 *    register scenario from perfService.
 *    only set freq of little core (only lower limit).
 *    Before unregister, PerfService will keep scenario's setting.
 * @scn_freq_little : 0, don't care. other, set freq of little core.
 */
void regPerfServiceScn(int *mPerfServiceHandle, const int scn_freq_little);

/**
 * unregPerfServiceScn(int *mPerfServiceHandle)
 *    unregister scenario from perfService.
 */
void unregPerfServiceScn(int *mPerfServiceHandle);

/**
 * setPerfServiceScn(const int mPerfServiceHandle, const int scn_freq_little)
 *    set freq of little core at lower and upper limit
 *    After re-enable scenario, the setting will be applied.
 */
void setPerfServiceScn(const int mPerfServiceHandle, const int scn_freq_little);

/**
 * enablePerfServiceScn(const int mPerfServiceHandle)
 *    enable scenario.
 */
void enablePerfServiceScn(const int mPerfServiceHandle);

/**
 * disablePerfServiceScn(const int mPerfServiceHandle)
 *    disable scenario
 */
void disablePerfServiceScn(const int mPerfServiceHandle);

#endif

/**
 * newMtkAudioBitConverter(uint32_t sampling_rate, uint32_t channel_num, BCV_PCM_FORMAT format)
 *    Using dlopen/dlsym to new MtkAudioBitConverterBase object
 */
MtkAudioBitConverterBase *newMtkAudioBitConverter(uint32_t sampling_rate, uint32_t channel_num, BCV_PCM_FORMAT format);

/**
 * newMtkAudioSrc(uint32_t input_SR, uint32_t input_channel_num, uint32_t output_SR, uint32_t output_channel_num, SRC_PCM_FORMAT format)
 *    Using dlopen/dlsym to new MtkAudioSrcBase object
 */
MtkAudioSrcBase *newMtkAudioSrc(uint32_t input_SR, uint32_t input_channel_num, uint32_t output_SR, uint32_t output_channel_num, SRC_PCM_FORMAT format);

/**
 * newMtkAudioLoud(uint32_t eFLTtype)
 *    Using dlopen/dlsym to new MtkAudioLoudBase object
 */
MtkAudioLoudBase *newMtkAudioLoud(uint32_t eFLTtype);


/**
 * deleteMtkAudioBitConverter(MtkAudioBitConverterBase* pObject)
 *    Using dlopen/dlsym to delete MtkAudioBitConverterBase object
 */
void deleteMtkAudioBitConverter(MtkAudioBitConverterBase *pObject);

/**
 * deleteMtkAudioSrc(MtkAudioSrcBase* pObject)
 *    Using dlopen/dlsym to delete MtkAudioSrcBase object
 */
void deleteMtkAudioSrc(MtkAudioSrcBase *pObject);

/**
 * newMtkAudioLoud(uint32_t eFLTtype)
 *    Using dlopen/dlsym to new MtkAudioLoudBase object
 */
void deleteMtkAudioLoud(MtkAudioLoudBase *pObject);

/**
 * setAudioCompFltCustParam(AudioCompFltType_t eFLTtype, AUDIO_ACF_CUSTOM_PARAM_STRUCT *audioParam)
 *    Using dlopen/dlsym to set Audio Parameters
 */
int setAudioCompFltCustParam(AudioCompFltType_t eFLTtype, AUDIO_ACF_CUSTOM_PARAM_STRUCT *audioParam);

/**
 * getAudioCompFltCustParam(AudioCompFltType_t eFLTtype, AUDIO_ACF_CUSTOM_PARAM_STRUCT *audioParam)
 *    Using dlopen/dlsym to get Audio Parameters
 */
int getAudioCompFltCustParam(AudioCompFltType_t eFLTtype, AUDIO_ACF_CUSTOM_PARAM_STRUCT *audioParam);

}

#endif
