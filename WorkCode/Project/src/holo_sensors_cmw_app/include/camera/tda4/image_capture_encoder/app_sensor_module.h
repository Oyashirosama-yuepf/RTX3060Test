#ifndef _APP_SENSOR_MODULE
#define _APP_SENSOR_MODULE

#include "app_common.h"
#include "app_stream.h"

#define APP_SENSOR_FEATURE_CFG_UC0 (0)
#define APP_SENSOR_FEATURE_CFG_UC1 (1)
#define APP_SENSOR_FEATURE_CFG_UC2 (1)

#define CAP_IMAGE_WIDTH     (1280)
#define CAP_IMAGE_HEIGHT    (720)

typedef struct {
    IssSensor_CreateParams sensorParams;

    vx_user_data_object dcc_config;

    char availableSensorNames[ISS_SENSORS_MAX_SUPPORTED_SENSOR][ISS_SENSORS_MAX_NAME];
    vx_char sensor_name[ISS_SENSORS_MAX_NAME];

    uint8_t num_sensors_found;
    uint32_t sensor_features_enabled;
    uint32_t sensor_features_supported;
    uint32_t sensor_dcc_enabled;
    uint32_t sensor_wdr_enabled;
    uint32_t sensor_exp_control_enabled;
    uint32_t sensor_gain_control_enabled;

    uint32_t num_cameras_enabled;
    vx_int32 is_interactive;
    vx_int32 enable_ldc;
    vx_int32 sensor_index;
    vx_int32 usecase_option;

    vx_int32 image_width;
    vx_int32 image_height;

} SensorObj;

vx_status app_querry_sensor(SensorObj *sensorObj);
vx_status app_init_sensor(SensorObj *sensorObj, uint32_t cmd);
void app_deinit_sensor(SensorObj *sensorObj);


#endif //__APP_SENSOR_MODULE
