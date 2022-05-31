/*
 *
 * Copyright (c) 2020 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <app_sensor_module.h>
#include <utils/sensors/include/app_sensors.h>
#include <utils/remote_service/include/app_remote_service.h>
#include <utils/ipc/include/app_ipc.h>


static char availableSensorNames[ISS_SENSORS_MAX_SUPPORTED_SENSOR][ISS_SENSORS_MAX_NAME];

vx_status app_querry_sensor(SensorObj *sensorObj)
{
    vx_status status = VX_SUCCESS;

    char* sensor_list[ISS_SENSORS_MAX_SUPPORTED_SENSOR];
    vx_uint8 selectedSensor = 0xFF;
    vx_bool sensorSelected = vx_false_e;
    vx_bool ldcSelected = vx_false_e;
    int32_t i;

    memset(availableSensorNames, 0, ISS_SENSORS_MAX_SUPPORTED_SENSOR*ISS_SENSORS_MAX_NAME);
    for(i = 0; i < ISS_SENSORS_MAX_SUPPORTED_SENSOR; i++)
    {
        sensor_list[i] = availableSensorNames[i];
    }

    memset(&sensorObj->sensorParams, 0, sizeof(IssSensor_CreateParams));
    status = appEnumerateImageSensor(sensor_list, &sensorObj->num_sensors_found);
    if(VX_SUCCESS != status)
    {
        printf("appCreateImageSensor returned %d\n", status);
        return status;
    }

    strcpy(sensorObj->sensor_name, FRONT_SENOSR_NAME);
    status = appQueryImageSensor(sensorObj->sensor_name, &sensorObj->sensorParams);

    sensorObj->num_cameras_enabled = NUM_CAPT_CHANNELS;
    /*
    Check for supported sensor features.
    It is upto the application to decide which features should be enabled.
    This demo app enables WDR, DCC and 2A if the sensor supports it.
    */

    sensorObj->sensor_features_supported = sensorObj->sensorParams.sensorInfo.features;

    if(ISS_SENSOR_FEATURE_COMB_COMP_WDR_MODE == (sensorObj->sensor_features_supported & ISS_SENSOR_FEATURE_COMB_COMP_WDR_MODE))
    {
        APP_PRINTF("WDR mode is supported \n");
        sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_COMB_COMP_WDR_MODE;
        sensorObj->sensor_wdr_enabled = 1;
    }else
    {
        APP_PRINTF("WDR mode is not supported. Defaulting to linear \n");
        sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_LINEAR_MODE;
        sensorObj->sensor_wdr_enabled = 0;
    }

    if(ISS_SENSOR_FEATURE_MANUAL_EXPOSURE == (sensorObj->sensor_features_supported & ISS_SENSOR_FEATURE_MANUAL_EXPOSURE))
    {
        APP_PRINTF("Expsoure control is supported \n");
        sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_MANUAL_EXPOSURE;
        sensorObj->sensor_exp_control_enabled = 1;
    }

    if(ISS_SENSOR_FEATURE_MANUAL_GAIN == (sensorObj->sensor_features_supported & ISS_SENSOR_FEATURE_MANUAL_GAIN))
    {
        APP_PRINTF("Gain control is supported \n");
        sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_MANUAL_GAIN;
        sensorObj->sensor_gain_control_enabled = 1;
    }

    if(ISS_SENSOR_FEATURE_CFG_UC1 == (sensorObj->sensor_features_supported & ISS_SENSOR_FEATURE_CFG_UC1))
    {
        if(sensorObj->usecase_option == APP_SENSOR_FEATURE_CFG_UC1)
        {
            APP_PRINTF("CMS Usecase is supported \n");
            sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_CFG_UC1;
        }
    }

    if(ISS_SENSOR_FEATURE_DCC_SUPPORTED == (sensorObj->sensor_features_supported & ISS_SENSOR_FEATURE_DCC_SUPPORTED))
    {
        sensorObj->sensor_features_enabled |= ISS_SENSOR_FEATURE_DCC_SUPPORTED;
        sensorObj->sensor_dcc_enabled = 1;
        APP_PRINTF("Sensor DCC is enabled \n");
    }else
    {
        sensorObj->sensor_dcc_enabled = 0;
        APP_PRINTF("Sensor DCC is disabled \n");
    }

    sensorObj->image_width   = sensorObj->sensorParams.sensorInfo.raw_params.width;
    sensorObj->image_height  = sensorObj->sensorParams.sensorInfo.raw_params.height;

    APP_PRINTF("Sensor width = %d\n", sensorObj->sensorParams.sensorInfo.raw_params.width);
    APP_PRINTF("Sensor height = %d\n", sensorObj->sensorParams.sensorInfo.raw_params.height);
    APP_PRINTF("Sensor DCC ID = %d\n", sensorObj->sensorParams.dccId);
    APP_PRINTF("Sensor Supported Features = 0x%08X\n", sensorObj->sensor_features_supported);
    APP_PRINTF("Sensor Enabled Features = 0x%08X\n", sensorObj->sensor_features_enabled);

    return (status);
}

vx_status app_init_sensor(SensorObj *sensorObj, uint32_t cmd)
{
    vx_status status = VX_SUCCESS;
    int32_t sensor_init_status = -1;

    //sensor_init_status = appInitImageSensor(sensorObj->sensor_name, sensorObj->sensor_features_enabled, ((1 << sensorObj->num_cameras_enabled) - 1));
    sensor_init_status = appRemoteServiceRun(APP_IPC_CPU_MCU2_0,"com.ti.image_sensor", cmd, sensorObj->sensor_name, strlen(sensorObj->sensor_name), 0);
    if(0 != sensor_init_status)
    {
        printf("Error initializing sensor %s \n", sensorObj->sensor_name);
        status = VX_FAILURE;
    }

    return status;
}


void app_deinit_sensor(SensorObj *sensorObj)
{
    appDeInitImageSensor(sensorObj->sensor_name);
}
