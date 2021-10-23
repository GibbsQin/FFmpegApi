//
// Created by Gibbs on 2021/10/23.
//

#ifndef GPLAYER_RESAMPLING_AUDIO_H
#define GPLAYER_RESAMPLING_AUDIO_H

#include "../ffmpeg/libavutil/opt.h"
#include "../ffmpeg/libavutil/channel_layout.h"
#include "../ffmpeg/libavutil/samplefmt.h"
#include "../ffmpeg/libswresample/swresample.h"

struct SwrContext* init_swr_context(int src_rate, int src_nb_channels, int src_bit_num,
                                    int dst_rate, int dst_nb_channels, int dst_bit_num);

int resample(struct SwrContext *swr_cxt, uint8_t **dst_data, int dst_nb_samples, uint8_t **src_data, int src_nb_samples);

void release_swr_context(struct SwrContext *swr_cxt);

#endif //GPLAYER_RESAMPLING_AUDIO_H
