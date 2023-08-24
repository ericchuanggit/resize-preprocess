/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xf_resize_config.h"

static constexpr int __XF_DEPTH = (HEIGHT * WIDTH * (XF_PIXELWIDTH(TYPE, NPC_T)) / 8) / (INPUT_PTR_WIDTH / 8);
static constexpr int __XF_DEPTH_OUT =
    (HEIGHT * WIDTH * (XF_PIXELWIDTH(TYPE, NPC_T)) / 8) / (OUTPUT_PTR_WIDTH / 8);

void resize_accel(ap_uint<INPUT_PTR_WIDTH>* img_inp,
                  ap_uint<OUTPUT_PTR_WIDTH>* img_out,
                  int rows_in,
                  int cols_in,
                  int rows_out,
                  int cols_out,
                  float params[2 * XF_CHANNELS(TYPE, NPC_T)]) {
// clang-format off
    #pragma HLS INTERFACE m_axi     port=img_inp  offset=slave bundle=gmem1 depth=__XF_DEPTH
    #pragma HLS INTERFACE m_axi     port=img_out  offset=slave bundle=gmem2 depth=__XF_DEPTH_OUT
    #pragma HLS INTERFACE m_axi     port=params   offset=slave bundle=gmem3 depth
    #pragma HLS INTERFACE s_axilite port=rows_in              
    #pragma HLS INTERFACE s_axilite port=cols_in              
    #pragma HLS INTERFACE s_axilite port=rows_out              
    #pragma HLS INTERFACE s_axilite port=cols_out              
    #pragma HLS INTERFACE s_axilite port=return
    // clang-format on

    xf::cv::Mat<TYPE, HEIGHT, WIDTH, NPC_T, XF_CV_DEPTH_IN> in_mat(rows_in, cols_in);

    xf::cv::Mat<TYPE, NEWHEIGHT, NEWWIDTH, NPC_T, XF_CV_DEPTH_OUT> resize_out_mat(rows_out, cols_out);

    xf::cv::Mat<TYPE, NEWHEIGHT, NEWWIDTH, NPC_T, XF_CV_DEPTH_OUT> out_mat(rows_in, cols_in);

// clang-format off
    #pragma HLS DATAFLOW
    // clang-format on

    xf::cv::Array2xfMat<INPUT_PTR_WIDTH, TYPE, HEIGHT, WIDTH, NPC_T, XF_CV_DEPTH_IN>(img_inp, in_mat);
    xf::cv::resize<INTERPOLATION, TYPE, HEIGHT, WIDTH, NEWHEIGHT, NEWWIDTH, NPC_T, XF_CV_DEPTH_IN, XF_CV_DEPTH_OUT,
                   MAXDOWNSCALE>(in_mat, resize_out_mat);
    xf::cv::preProcess<TYPE, TYPE, NEWHEIGHT, NEWWIDTH, NPC_T, XF_CV_DEPTH_IN, XF_CV_DEPTH_OUT, WIDTH_A, IBITS_A, WIDTH_B, IBITS_B, WIDTH_OUT,
                       IBITS_OUT>(resize_out_mat, out_mat, params);
    xf::cv::xfMat2Array<OUTPUT_PTR_WIDTH, TYPE, NEWHEIGHT, NEWWIDTH, NPC_T, XF_CV_DEPTH_OUT>(out_mat, img_out);
}
