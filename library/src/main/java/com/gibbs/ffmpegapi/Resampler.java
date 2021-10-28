package com.gibbs.ffmpegapi;

import java.nio.ByteBuffer;

public class Resampler {
    private final long nativeObj;

    public Resampler(int srcRate, int srcChannels, int srcBitNum,
                     int dstRate, int dstChannels, int dstBitNum) {
        nativeObj = FFmpegApi.createSwrContext(srcRate, srcChannels, srcBitNum, dstRate, dstChannels, dstBitNum);
    }

    public int resample(ByteBuffer dstBuffer, int dstSamples, ByteBuffer srcBuffer, int srcSamples) {
        return FFmpegApi.resample(nativeObj, dstBuffer, dstSamples, srcBuffer, srcSamples);
    }

    public void release() {
        FFmpegApi.releaseSwrContext(nativeObj);
    }
}
