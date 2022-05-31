

#include <vector>

#include "holo/localization/vision/tidl/app_nms.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <VX/vx_khr_pipelining.h>
#include <utils/console_io/include/app_get.h>
#include <utils/draw2d/include/draw2d.h>
#include <utils/grpx/include/app_grpx.h>
#include <utils/perf_stats/include/app_perf_stats.h>

#ifdef APP_TIDL_TRACE_DUMP
#include <tivx_utils_tidl_trace.h>
#endif

#include <TI/j7.h>
#include <TI/j7_tidl.h>
#include <TI/tivx.h>
#include <TI/tivx_img_proc.h>
#include <TI/tivx_target_kernel.h>
#include <TI/tivx_task.h>
#include <tivx_utils_file_rd_wr.h>
#include <tivx_utils_graph_perf.h>

#include "itidl_ti.h"
#include "tiadalg_interface.h"
#include "time.h"
#include "tivx_kernels_host_utils.h"

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <cmath>

#include <iostream>
class GetTimeDiffApp
{
public:
    struct timeval start, end;
    void           StartTiming()
    {
        gettimeofday(&start, NULL);
    }
    float GetTimeDiff()  // ms
    {
        gettimeofday(&end, NULL);
        return (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;
    }
};

int main()
{
    std::cout << "#########  begin to init self kernel ... ##########" << std::endl;

    // the input and output data num, now default is: 2000 * 128
    int data_size_tmp = 2000 * 128;

    // now the size is 4, the first two is input, the last two is ouput, every data in vector represents the num of
    // input or output
    std::vector<int> data_len = {data_size_tmp, data_size_tmp, data_size_tmp, data_size_tmp};

    /// now the size is 4, the first two is input, the last two is ouput, every data in vector represents the type of
    //  input or output ---> 1 2 4 （int8, int16, float32）
    // input1: desc_a_list and desc_b_list;
    // input2: a_list_size, b_list_size, top_match_num
    std::vector<int> data_type_tmp = {4, 2, 2, 4};

    // default param
    auto AppSelfKernelTest = new AppSelfKernel(data_len, data_type_tmp);
    std::cout << "#########  init self kernel done ##########" << std::endl;

    int       desc_a_num = 2, desc_b_num = 2, match_top_num = 2;
    int       param_1_size = desc_a_num * 128;
    int       param_2_size = desc_b_num * 128;
    float*    descs_input1 = new float[param_1_size + param_2_size];  // input 1
    uint16_t* descs_input2 = new uint16_t[3];                         // input 2
    descs_input2[0]        = desc_a_num;
    descs_input2[1]        = desc_b_num;
    descs_input2[2]        = match_top_num;

    // read random number
    FILE* fp = fopen("/data/gpk/float_desc_a.txt", "rb");
    std::cout << "read file 1 ...\n";
    for (int i = 0; i < param_1_size; i++)
    {
        fscanf(fp, "%f", &descs_input1[i]);
    }
    std::cout << "read file 1 done !!!\n";

    FILE* fp1 = fopen("/data/gpk/float_desc_b.txt", "rb");
    for (int i = param_1_size; i < param_1_size + param_2_size; i++)
    {
        fscanf(fp1, "%f", &descs_input1[i]);
    }

    // print descs 1 data
    float desc_a_sum = 0, desc_b_sum = 0 /*, dis_a1b1 = 0, dis_a1b2 = 0, b2, dis_a2b1 = 0, dis_a2b2 = 0*/;
    for (int i = 0; i < param_1_size; i++)
    {
        if (i % 128 == 0 && i != 0)
        {
            std::cout << std::endl;
            std::cout << "desc a list norm: " << std::sqrt(desc_a_sum) << std::endl;
            desc_a_sum = 0;
        }
        desc_a_sum += descs_input1[i] * descs_input1[i];
        std::cout << descs_input1[i] << " ";
    }
    std::cout << "\nload descs a list done !!!" << std::endl;

    // print descs 2 data
    for (int i = param_1_size; i < param_1_size + param_2_size; i++)
    {
        if (i % 128 == 0 && i != 0)
        {
            std::cout << std::endl;
            std::cout << "desc b list norm: " << std::sqrt(desc_b_sum) << std::endl;
            desc_b_sum = 0;
        }
        std::cout << descs_input1[i] << " ";
        desc_b_sum += descs_input1[i] * descs_input1[i];
    }
    std::cout << "\nload descs b list done !!!" << std::endl;

    ///@todo (guopeikai@holomatic.com) calcu desc matching score on cpu for compare with the result from c66

    int            result_data_size     = data_size_tmp;
    uint16_t*      matching_result_data = new uint16_t[result_data_size];
    float*         score_result_data    = new float[result_data_size];
    GetTimeDiffApp t1;

    while (true)
    {
        t1.StartTiming();

        // set the first set of data
        AppSelfKernelTest->setdata((int8_t*)descs_input1, (param_1_size + param_2_size) * sizeof(float), 0);
        // set the second set of data
        AppSelfKernelTest->setdata((int8_t*)descs_input2, 3 * sizeof(uint16_t), 1);

        // get the matching result, the first data is matching num
        AppSelfKernelTest->getdata((int8_t*)matching_result_data, (match_top_num * sizeof(uint16_t) * 2), 0);

        // get the matching score
        AppSelfKernelTest->getdata((int8_t*)score_result_data, (match_top_num * 128 * 2 * sizeof(float)), 1);
        std::cout << "time use: " << t1.GetTimeDiff() << std::endl;

        usleep(1000000.0 - t1.GetTimeDiff());

        uint16_t matched_pair_size = matching_result_data[0];
        std::cout << "matched size: " << matched_pair_size << "\n";
        std::cout << "matching index : " << std::endl;
        for (int k = 0; k < 2; k++)
        {
            for (int i = 1; i <= matched_pair_size; i++)
            {
                std::cout << matching_result_data[k * matched_pair_size + i] << " ";
            }
            std::cout << std::endl;
            std::cout << "#####################" << std::endl;
        }

        std::cout << "matching result score : " << std::endl;
        for (int i = 0; i < matched_pair_size; i++)
        {
            // std::cout << i << std::endl;
            std::cout << score_result_data[i] << " ";
        }
        std::cout << std::endl;
    }

    delete[] descs_input1;
    delete[] descs_input2;
    delete[] matching_result_data;
    delete[] score_result_data;
    appDeInit();
}
