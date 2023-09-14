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
#include <bitset>

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
    cv::absdiff(channels[0],50, channels[0]);
    channels[0]= ~ channels[0] +1;
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;

/*   Call HLS Function   */
    float normalization[6] = {50, 0, 0, 1, 1, 1};
    // float normalization[6] = {0, 0, 0, 1, 1, 1};//hls_resize

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

    std::cout << "(ap_uint<INPUT_PTR_WIDTH>*)img type:" << (ap_uint<INPUT_PTR_WIDTH>*)img.type() << std::endl;
    std::cout << "hls_ab_out type:" << out_img.type() << std::endl;
    std::cout << "resize_ocv type:" << result_ocv.type() << std::endl;
    std::cout << "normalized_ab_ocv type:" << normalized_ocv.type() << std::endl;
    std::cout << "error type:" << error.type() << std::endl;
    // std::cout << "input_(10,10):" << img.at<cv::Vec3b>(10,10) << std::endl;
    std::cout << "resize_(360,360):" << result_ocv.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "hls_(360,360):" << out_img.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "opencv_(360,360):" << normalized_ocv.at<cv::Vec3b>(360,360) << std::endl;

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Blue Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Blue Test matched.\n" );
    }

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
    cv::absdiff(channels[1],50, channels[1]);
    channels[1]= ~ channels[1] +1;
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;

/*   Call HLS Function   */
    float normalization[6] = {0, 50, 0, 1, 1, 1};
    // float normalization[6] = {0, 0, 0, 1, 1, 1};//hls_resize

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

    std::cout << "(ap_uint<INPUT_PTR_WIDTH>*)img type:" << (ap_uint<INPUT_PTR_WIDTH>*)img.type() << std::endl;
    std::cout << "hls_ag_out type:" << out_img.type() << std::endl;
    std::cout << "resize_ocv type:" << result_ocv.type() << std::endl;
    std::cout << "normalized_ag_ocv type:" << normalized_ocv.type() << std::endl;
    std::cout << "error type:" << error.type() << std::endl;
    // std::cout << "input_(10,10):" << img.at<cv::Vec3b>(10,10) << std::endl;
    std::cout << "resize_(360,360):" << result_ocv.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "hls_(360,360):" << out_img.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "opencv_(360,360):" << normalized_ocv.at<cv::Vec3b>(360,360) << std::endl;

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Green Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Green Test matched.\n" );
    }

    return 0;
}
#endif
/**********************************************Alpha_Red-50************************************************************************************************/
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
    cv::absdiff(channels[2],50, channels[2]);
    channels[2]= ~ channels[2] +1;
    cv::merge(channels,normalized_ocv);
    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;

/*   Call HLS Function   */
    float normalization[6] = {0, 0, 50, 1, 1, 1};
    // float normalization[6] = {0, 0, 0, 1, 1, 1};//hls_resize

    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("resize_ocv.png", result_ocv);
    cv::imwrite("hls_ar_out.png", out_img);
    cv::imwrite("normalized_ar_ocv.png", normalized_ocv); // Save normalized image
    cv::imwrite("error.png", error);

    std::cout << "(ap_uint<INPUT_PTR_WIDTH>*)img type:" << (ap_uint<INPUT_PTR_WIDTH>*)img.type() << std::endl;
    std::cout << "hls_ab_out type:" << out_img.type() << std::endl;
    std::cout << "resize_ocv type:" << result_ocv.type() << std::endl;
    std::cout << "normalized_ab_ocv type:" << normalized_ocv.type() << std::endl;
    std::cout << "error type:" << error.type() << std::endl;
    // std::cout << "input_(10,10):" << img.at<cv::Vec3b>(10,10) << std::endl;
    std::cout << "resize_(360,360):" << result_ocv.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "hls_(360,360):" << out_img.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "opencv_(360,360):" << normalized_ocv.at<cv::Vec3b>(360,360) << std::endl;

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha Red Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha Red Test matched.\n" );
    }

    return 0;
}
#endif
/**********************************************Alpha_BGR-50************************************************************************************************/

#if Alpha_bgr
int alpha_bgr(int argc, char** argv){
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

    int alpha_value = 0;
    std::vector<cv::Mat> channels;
    cv::split(result_ocv, channels);
    for(int i=0; i<3; i++){
        for (int row = 0; row < channels[i].rows; row++) {
            for (int col = 0; col < channels[i].cols; col++) {
                uchar pixel = channels[i].at<uchar>(row, col);

                if (pixel < alpha_value) {
                    channels[i].at<uchar>(row, col) =abs(int(pixel - alpha_value));
                    channels[i].at<uchar>(row, col) = ~channels[i].at<uchar>(row, col) + 1;
                } else {
                    channels[i].at<uchar>(row, col) = pixel - alpha_value;
                }
            }
        } 
    }

        // if(channels[i] >=50){
        //     channels[i]=channels[i]-50;
        // }else{
        //     cv::absdiff(channels[i],50, channels[i]);
        //     
        // }

        // cv::Mat tmp;
        // cv::absdiff(channels[i], 50, channels[i]);
        // cv::threshold(channels[i], tmp, 50, 255, cv::THRESH_BINARY);
        // channels[i]= ~ channels[i] ;

        // if (channels[0] >= 50){
        //     channels[0]=channels[0]-50;
        // }
        // else{
        //     cv::absdiff(channels[0],50, channels[0]);
        //     channels[0]= ~ channels[0] ;
        // }
        // if (channels[1] >= 50){
        //     channels[1]=channels[1]-50;
        // }
        // else{
        //     cv::absdiff(channels[1],50, channels[1]);
        //     channels[1]= ~ channels[1] ;
        // }
        // if (channels[2] >= 50){
        //     channels[2]=channels[2]-50;
        // }
        // else{
        //     cv::absdiff(channels[2],50, channels[2]);
        //     channels[2]= ~ channels[2] ;
        // }

    cv::merge(channels,normalized_ocv);


    // std::cout << "ocv_R_arry:" << normalized_ocv<< std::endl;

/*   Call HLS Function   */
    float normalization[6] = {alpha_value, alpha_value, alpha_value, 1, 1, 1};
    // float normalization[6] = {0, 0, 0, 1, 1, 1};//hls_resize

    resize_accel((ap_uint<INPUT_PTR_WIDTH>*)img.data, (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.data, in_height, in_width,
                 out_height, out_width, normalization);

/*   HLS & OPENCV difference error */
    float err_per;
    cv::absdiff(normalized_ocv, out_img, error);
    xf::cv::analyzeDiff(error, 5, err_per);

    cv::imwrite("hls_abgr_out.bmp", out_img);
    cv::imwrite("resize_ocv.bmp", result_ocv);
    cv::imwrite("normalized_abgr_ocv.bmp", normalized_ocv); // Save normalized image
    cv::imwrite("error.bmp", error);

    std::cout << "(ap_uint<INPUT_PTR_WIDTH>*)img type:" << (ap_uint<INPUT_PTR_WIDTH>*)img.type() << std::endl;
    std::cout << "(ap_uint<OUTPUT_PTR_WIDTH>*)out_img type:" << (ap_uint<OUTPUT_PTR_WIDTH>*)out_img.type() << std::endl;
    std::cout << "hls_abgr_out type:" << out_img.type() << std::endl;
    std::cout << "resize_ocv type:" << result_ocv.type() << std::endl;
    std::cout << "normalized_abgr_ocv type:" << normalized_ocv.type() << std::endl;
    std::cout << "error type:" << error.type() << std::endl;
    // std::cout << "input_(10,10):" << img.at<cv::Vec3b>(10,10) << std::endl;
    std::cout << "resize_(360,360):" << result_ocv.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "hls_(360,360):" << out_img.at<cv::Vec3b>(360,360) << std::endl;
    std::cout << "opencv_(360,360):" << normalized_ocv.at<cv::Vec3b>(360,360) << std::endl;

    if (err_per > 0.0f) {
        fprintf(stderr, "ERROR: Alpha BGR Test Failed.\n ");
        return -1;
    }
    else{
        fprintf(stdout, "Success:Alpha BGR Test matched.\n" );
    }

    return 0;
}
#endif
/**********************************************main*********************************************************************************************************/
int main(int argc, char** argv){
#if Beta_b
    beta_b(argc, argv);
#endif
#if Beta_g
    beta_g(argc, argv);
#if Beta_r    
#endif    
    beta_r(argc, argv);
#endif    
#if Alpha_b
    alpha_b(argc, argv);
#endif
#if Alpha_g
    alpha_g(argc, argv);
#endif
#if Alpha_r    
    alpha_r(argc, argv);
#endif
#if Alpha_bgr    
    alpha_bgr(argc, argv);
#endif
    return 0;

}