package com.gibbs.ffmpegapi;

import java.nio.ByteBuffer;

public class FFmpegApi {
    static {
        System.loadLibrary("ffmpegapi-lib");
    }

    public static native long createSwrContext(int src_rate, int src_nb_channels, int src_bit_num,
                                               int dst_rate, int dst_nb_channels, int dst_bit_num);

    public static native int resample(long context, ByteBuffer dstBuffer, int dstSamples, ByteBuffer srcBuffer, int srcSamples);

    public static native void releaseSwrContext(long context);
}
