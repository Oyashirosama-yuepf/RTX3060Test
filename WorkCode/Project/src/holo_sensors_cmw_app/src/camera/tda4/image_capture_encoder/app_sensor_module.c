#include "app_sensor_module.h"
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
    status = appQueryImageSensor(sensorObj->sensor_name, &sensorObj->sensorParams);
    if(VX_SUCCESS != status)
    {
        printf("appQueryImageSensor returned %d\n", status);
        return status;
    }
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
    AppSensorCmdParams cmdPrms;
    
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
