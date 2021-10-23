#include <android/log.h>
#include "resampling_audio.h"

static void resample_log(int level, const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    __android_log_vprint(level, "resample", fmt, arg);
    va_end(arg);
}

static enum AVSampleFormat bitNum2SampleFmt(int bit_num) {
    if (bit_num == 1) {
        return AV_SAMPLE_FMT_U8;
    } else if (bit_num == 2) {
        return AV_SAMPLE_FMT_S16;
    } else if (bit_num == 4) {
        return AV_SAMPLE_FMT_FLT;
    }

    return AV_SAMPLE_FMT_S16;
}

struct SwrContext *init_swr_context(int src_rate, int src_nb_channels, int src_bit_num,
                                    int dst_rate, int dst_nb_channels, int dst_bit_num) {
    struct SwrContext *swr_ctx = swr_alloc();
    if (!swr_ctx) {
        resample_log(2, "Could not allocate resampling context\n");
        return NULL;
    }

    /* set options */
    av_opt_set_int(swr_ctx, "in_channel_layout", av_get_default_channel_layout(src_nb_channels), 0);
    av_opt_set_int(swr_ctx, "in_sample_rate", src_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", bitNum2SampleFmt(src_bit_num), 0);

    av_opt_set_int(swr_ctx, "out_channel_layout", av_get_default_channel_layout(dst_nb_channels),0);
    av_opt_set_int(swr_ctx, "out_sample_rate", dst_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", bitNum2SampleFmt(dst_bit_num), 0);

    /* initialize the resampling context */
    int ret;
    if ((ret = swr_init(swr_ctx)) < 0) {
        resample_log(2, "Failed to initialize the resampling context %s\n", av_err2str(ret));
        return NULL;
    }
    resample_log(4, "Success to initialize the resampling context %d\n", swr_ctx);
    return swr_ctx;
}

int resample(struct SwrContext *swr_cxt, uint8_t **dst_data, int dst_nb_samples, uint8_t **src_data, int src_nb_samples) {
    resample_log(4, "resample %d %d %d\n", swr_cxt, dst_nb_samples, src_nb_samples);
    if (swr_cxt) {
        /* convert to destination format */
        int ret = swr_convert(swr_cxt, dst_data, dst_nb_samples, (const uint8_t **) src_data, src_nb_samples);
        if (ret < 0) {
            resample_log(2, "Error while converting %s\n", av_err2str(ret));
        }
        return ret;
    }
    return -1;
}

void release_swr_context(struct SwrContext *swr_cxt) {
    resample_log(4, "Success to release the resampling context %d\n", swr_cxt);
    swr_free(&swr_cxt);
}
