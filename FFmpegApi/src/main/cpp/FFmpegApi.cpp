#include <jni.h>
#include <string>
extern "C" {
#include "api/resampling_audio.h"
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_gibbs_ffmpegapi_FFmpegApi_createSwrContext(
        JNIEnv* env,
        jobject /* this */,
        jint src_rate, jint src_nb_channels, jint src_bit_num,
        jint dst_rate, jint dst_nb_channels, jint dst_bit_num) {
    struct SwrContext* swrContext = init_swr_context(src_rate, src_nb_channels, src_bit_num,
            dst_rate, dst_nb_channels, dst_bit_num);
    return reinterpret_cast<jlong>(swrContext);
}

extern "C" JNIEXPORT jint JNICALL
Java_com_gibbs_ffmpegapi_FFmpegApi_resample(
        JNIEnv* env,
        jobject /* this */,
        jlong context, jobject dstBuffer, jint dstSamples, jobject srcBuffer, jint srcSamples) {
    struct SwrContext *swrContext = reinterpret_cast<SwrContext *>(context);
    uint8_t* dst_buffer = (uint8_t*)env->GetDirectBufferAddress(dstBuffer);
    uint8_t* src_buffer = (uint8_t*)env->GetDirectBufferAddress(srcBuffer);
    return resample(swrContext, &dst_buffer, dstSamples, &src_buffer, srcSamples);
}

extern "C" JNIEXPORT void JNICALL
Java_com_gibbs_ffmpegapi_FFmpegApi_releaseSwrContext(
        JNIEnv* env,
        jobject /* this */,
        jlong context) {
    struct SwrContext *swrContext = reinterpret_cast<SwrContext *>(context);
    release_swr_context(swrContext);
}