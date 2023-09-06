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

#include "common/xf_headers.hpp"
#include "xf_resize_config.h"
/**********************************************Beta_Blue / 2************************************************************************************************/
#if Beta_r
int beta_b(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image  into ".png" */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;

 /*   OpenCV Function             */

 /*   Resize                      */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREA);
#endif

/*   Normalization                */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[0] = channels[0]/2; //red
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;

/*   Call HLS Function   */
    float normalization[6] = {0, 0, 0, 0.5, 1, 1};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_bb_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_bb_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Beta Blue Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Beta Blue Test matched.\n" );
    }

    return 0;
}
#endif
/**********************************************Beta_Green/2*************************************************************************************************/
#if Beta_g
int beta_g(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image  into ".png" */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;

 /* OpenCV Function */
 /*   Resize        */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREA);
#endif

/*   Normalization   */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[1] = channels[1]/2; //green
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;



/*   Call HLS Function   */
    float normalization[6] = {0, 0, 0, 1, 0.5, 1};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_bg_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_bg_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Beta Green Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Beta Green Test matched.\n" );
    }
    

    // return beta_r(argc, argv);
    return 0;
}
#endif
/**********************************************Beta_Red/2***************************************************************************************************/
#if Beta_r
int beta_r(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image into ".png"  */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;

 /*   OpenCV Function             */
 /*   Resize                      */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREA);
#endif

/*   Normalization                */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[2] = channels[2]/2; //red
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;



/*   Call HLS Function   */
    float normalization[6] = {0, 0, 0, 1, 1, 0.5};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_br_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_br_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Beta Red Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Beta Red Test matched.\n" );
    }

    // return beta_g(argc, argv);
    return 0;
}
#endif
/**********************************************Alpha_Blue -50***********************************************************************************************/
#if Alpha_b
int alpha_b(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image into ".png" */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;

 /*   OpenCV Function             */
 /*   Resize                      */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREA);
#endif

/*   Normalization                */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[0] = channels[0]- 50; //blue
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;



/*   Call HLS Function   */
    float normalization[6] = {50, 0, 0, 1, 1, 1};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_ab_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_ab_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Blue Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Blue Test matched.\n" );
    }

    // return beta_b(argc, argv);
    return 0;
}
#endif
/**********************************************Alpha_Green-50***********************************************************************************************/
#if Alpha_g
int alpha_g(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image into ".png" */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;

 /*   OpenCV Function             */
 /*   Resize                      */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREA);
#endif

/*   Normalization                */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[1] = channels[1]- 50; //green
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;



/*   Call HLS Function   */
    float normalization[6] = {0, 50, 0, 1, 1, 1};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_ag_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_ag_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Green Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Green Test matched.\n" );
    }

    // return alpha_r(argc, argv);
    return 0;
}
#endif
/**********************************************Alpha_Red-100************************************************************************************************/
#if Alpha_r
int alpha_r(int argc, char** argv){
    cv::Mat img, out_img, result_ocv, normalized_ocv, error;

    if (argc != 2) {
        fprintf(stderr, "Usage: <executable> <input image>\n");
        return -1;
    }
/*   Opencv image size  */
#if GRAY
    img.create(cv::Size(WIDTH, HEIGHT), CV_8UC1);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_8UC1);
#else
    img.create(cv::Size(WIDTH, HEIGHT), CV_32FC3);
    result_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_32FC3);
    out_img.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_32FC3);
    normalized_ocv.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_32FC3);
    error.create(cv::Size(NEWWIDTH, NEWHEIGHT), CV_32FC3);
#endif
/*   Reading mode in the color image   */
#if GRAY
    img = cv::imread(argv[1], 0);
#else
    img = cv::imread(argv[1], 1);
#endif
    if (!img.data) {
        return -1;
    }
/*   Writing the color image into ".png" */
    cv::imwrite("input.png", img);

    unsigned short in_width, in_height;
    unsigned short out_width, out_height;

    in_width = img.cols;
    in_height = img.rows;
    out_height = NEWHEIGHT;
    out_width = NEWWIDTH;
    std::cout << "Mat_img type: " << img.type() << std::endl;
    std::cout << "Mat_hls_out type: " << out_img.type() << std::endl;
    std::cout << "Mat ocv_out type: " << result_ocv.type() << std::endl;
    std::cout << "Mat normalize_ocv type: " << normalized_ocv.type() << std::endl;

 /*   OpenCV Function             */
 /*   Resize                      */   
#if INTERPOLATION == 0
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_NEAREST);
#endif
#if INTERPOLATION == 1
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_LINEAR);
#endif
#if INTERPOLATION == 2
    cv::resize(img, result_ocv, cv::Size(out_width, out_height), 0, 0, cv::INTER_AREyA);
#endif

/*   Normalization  */
    // cv::normalize(result_ocv, normalized_ocv, 0, 1, cv::NORM_MINMAX, CV_8U);
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels); 
    channels[2] = channels[2]- 50; //Red
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;



/*   Call HLS Function   */
    float normalization[6] = {0, 0, 50, 1, 1, 1};
    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_ar_out.png", out_img);
    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("normalized_ar_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Red Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Red Test matched.\n" );
    }

    // return alpha_g(argc, argv);
    return 0;
}
#endif
/**********************************************main*********************************************************************************************************/
int main(int argc, char** argv){
    // beta_b(argc, argv);
    // beta_g(argc, argv);
    // beta_r(argc, argv);
    // alpha_b(argc, argv);
    // alpha_g(argc, argv);
    alpha_r(argc, argv);

    return 0;

}