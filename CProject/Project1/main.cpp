
#include "stdio.h"
#include "math.h"
#include "stddef.h"

#define MAX_DIFF_LINEAR_VELOCITY 10
#define MAX_DIFF_ANGULAR_VELOCITY 10
#define MIN_IR_DATA 10
#define MIN_LDS_DATA 10

typedef struct LdsInformation_ {
    int frontObstacleDistance;
    int backObstacleDistance;
    int leftObstacleDistance;
    int rightObstacleDistance;
    int frontLeftObstacleDistance;
    int frontRightObstacleDistance;
    int backLeftObstacleDistance;
    int backRightObstacleDistace;
} LdsInformation;

typedef struct IrInformation_ {
    int leftIrData;
    int rightIrData;
    int frontLeftIrData;
    int frontRightIrData;
    int backLeftIrData;
    int backRightIrData;
} IrInformation;

typedef struct BumperStatus_ {
    _Bool leftBumper;
    _Bool rightBumper;
    _Bool ldsBumper;
} BumperStatus;

typedef struct GyroOriginData_ {
    int Pitch;
    int Roll;
    int Yaw;
} GyroOriginData;

typedef struct DiffLiearVelocitySlamEncoder_ {
    int diffLinearVelocitySlamEncoder;
} DiffLiearVelocitySlamEncoder;

typedef struct DiffAngularVelocityEncoderGyro_ {
    int diffAngularVelocityEncoderGyro;
} DiffAngularVelocityEncoderGyro;

typedef struct StuckIdentifyStatus_ {
    _Bool ldsOutputStuck;
    _Bool irOutputStuck;
    _Bool bumperOutputStuck;
    _Bool gyroOutputStuck;
    _Bool diffLinearOutputStuck;
    _Bool diffAngularOutputStuck;
} StuckIdentifyStatus;

typedef enum CheckResult_ {
    RobotFree = 0x00,
    RobotOneDirectionStucked = 0x01,
    RobotTwoDirectionStucked = 0x02,
    RobotThreeDirectionStucked = 0x03,
    RobotFourDirectionStucked = 0x04,
    RobotMultiDirectionStucked = 0x05,
    RobotIncline = 0x06,
    RobotCompleteStucked = 0x07,
} CheckResult;

typedef struct InputIdentifyVolume_ {
    LdsInformation ldsInformationl;
    IrInformation irInformation;
    BumperStatus bumperStatus;
    GyroOriginData gyroData;
    DiffLiearVelocitySlamEncoder diffLinearVelocity;
    DiffAngularVelocityEncoderGyro diffAngularVelocity;
    StuckIdentifyStatus stuckIdentifyStatus;
} InputStuckIdentifyVolume;


class RobotStuckedIdentify
{
public:
    InputStuckIdentifyVolume inputStuckIdentifyVolume;
    _Bool SlidWindowProcess(InputStuckIdentifyVolume input_stuck_identify_volume);
};



_Bool RobotStuckedIdentify::SlidWindowProcess(InputStuckIdentifyVolume input_stuck_identify_volume)
{
    static int checkCount = 0;
    static int checkCountEffect = 0;

    checkCount++;
    if (input_stuck_identify_volume.diffLinearVelocity > MAX_DIFF_LINEAR_VELOCITY) {
        checkCountEffect++;
    }
    else {
        if (checkCountEffect > 0) {
            checkCountEffect--;
        }
    }

    if (checkCountEffect > 5) {
        checkCountEffect = 0;
        checkCount = 0;
        return 1;
    }

}

void StuckIdentify(InputStuckIdentifyVolume input_stuck_identify_volume)
{
    return 0;
}

void main(void) {
    return 0;
}


