#ifndef HOLO_C_SENSORS_IFV300_IFV300_INPUT_DBC_H
#define HOLO_C_SENSORS_IFV300_IFV300_INPUT_DBC_H

/** \file
 * CAN DBC C-Headers
 *
 * These headers were generated by dbc2c.awk on 2019年 04月 10日 星期三 09:54:45 CST.
 *
 * The dbc2c.awk script parses Vector .dbc files, and generates C-style
 * headers with Doxygen documentation from a set of templates.
 *
 * The following databases were parsed:
 * - \ref DB_ifv300_veh_can
 */

/**
 * @defgroup DB_ifv300_veh_can CAN Database ifv300_veh_can
 *
 * Path to file: output/ifv300_veh_can.dbc
 *
 * Provides the following ECUs:
 * - \ref ECU_Camera_PCAN
 * - \ref ECU_camera_VCAN
 * - \ref ECU_MRR
 */

/**
 * @defgroup ECU_Camera_PCAN Electronics Control Unit Camera_PCAN
 *
 * This ECU was defined in \ref DB_ifv300_veh_can.
 *
 * TX messages:
 *
 * RX signals:
 *
 * @ingroup DB_ifv300_veh_can
 */

/**
 * @defgroup ECU_camera_VCAN Electronics Control Unit camera_VCAN
 *
 * This ECU was defined in \ref DB_ifv300_veh_can.
 *
 * TX messages:
 *
 * RX signals:
 * - \ref SIG_Vehicle_Speed_VehSpdAvgDrvnV
 * - \ref SIG_Vehicle_Speed_VehSpdAvgDrvn
 * - \ref SIG_Vehicle_Speed_VehSpdAvgNDrvnV
 * - \ref SIG_Vehicle_Speed_VehSpdAvgNDrvn
 * - \ref SIG_IMU_Yaw_IMUYawRtPri
 * - \ref SIG_IMU_Yaw_IMURollCntPri
 * - \ref SIG_IMU_Yaw_IMUYawRtPriV
 * - \ref SIG_IMU_Yaw_IMUChksumPri
 *
 * @ingroup DB_ifv300_veh_can
 */

/**
 * @defgroup ECU_MRR Electronics Control Unit MRR
 *
 * This ECU was defined in \ref DB_ifv300_veh_can.
 *
 * TX messages:
 * - \ref MSG_IMU_Yaw
 *
 * RX signals:
 *
 * @ingroup DB_ifv300_veh_can
 */

/**
 * @defgroup MSG_Vehicle_Speed Message Vehicle_Speed (0x3e9)
 *
 * Contains signal groups:
 *
 * Contains signals:
 * - \ref SIG_Vehicle_Speed_VehSpdAvgDrvnV
 * - \ref SIG_Vehicle_Speed_VehSpdAvgDrvn
 * - \ref SIG_Vehicle_Speed_VehSpdAvgNDrvnV
 * - \ref SIG_Vehicle_Speed_VehSpdAvgNDrvn
 *
 * @{
 */

/**
 * Message Vehicle_Speed configuration tuple.
 */
#define MSG_Vehicle_Speed 0x3e9, 0, 8

/**
 * Message Vehicle_Speed id.
 */
#define ID_Vehicle_Speed 0x3e9

/**
 * Message Vehicle_Speed extended id bit.
 */
#define EXT_Vehicle_Speed 0

/**
 * Message Vehicle_Speed Data Length Count.
 */
#define DLC_Vehicle_Speed 8

/**
 * Message Vehicle_Speed cycle time.
 */
#define CYCLE_Vehicle_Speed 100

/**
 * Message Vehicle_Speed fast cycle time.
 */
#define FAST_Vehicle_Speed 0

/**
 * Initialise message Vehicle_Speed buffer.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INIT_Vehicle_Speed(buf)                                                                                        \
    {                                                                                                                  \
        INITSIG_Vehicle_Speed_VehSpdAvgDrvnV(buf);                                                                     \
        INITSIG_Vehicle_Speed_VehSpdAvgDrvn(buf);                                                                      \
        INITSIG_Vehicle_Speed_VehSpdAvgNDrvnV(buf);                                                                    \
        INITSIG_Vehicle_Speed_VehSpdAvgNDrvn(buf);                                                                     \
    }

/**
 * @}
 */

/**
 * @defgroup MSG_IMU_Yaw Message IMU_Yaw (0x330)
 *
 * Sent by \ref ECU_MRR.
 *
 * Contains signal groups:
 *
 * Contains signals:
 * - \ref SIG_IMU_Yaw_IMUYawRtPri
 * - \ref SIG_IMU_Yaw_IMURollCntPri
 * - \ref SIG_IMU_Yaw_IMUYawRtPriV
 * - \ref SIG_IMU_Yaw_IMUChksumPri
 *
 * @ingroup ECU_MRR
 * @{
 */

/**
 * Message IMU_Yaw configuration tuple.
 */
#define MSG_IMU_Yaw 0x330, 0, 8

/**
 * Message IMU_Yaw id.
 */
#define ID_IMU_Yaw 0x330

/**
 * Message IMU_Yaw extended id bit.
 */
#define EXT_IMU_Yaw 0

/**
 * Message IMU_Yaw Data Length Count.
 */
#define DLC_IMU_Yaw 8

/**
 * Message IMU_Yaw cycle time.
 */
#define CYCLE_IMU_Yaw 10

/**
 * Message IMU_Yaw fast cycle time.
 */
#define FAST_IMU_Yaw 0

/**
 * Initialise message IMU_Yaw buffer.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INIT_IMU_Yaw(buf)                                                                                              \
    {                                                                                                                  \
        INITSIG_IMU_Yaw_IMUYawRtPri(buf);                                                                              \
        INITSIG_IMU_Yaw_IMURollCntPri(buf);                                                                            \
        INITSIG_IMU_Yaw_IMUYawRtPriV(buf);                                                                             \
        INITSIG_IMU_Yaw_IMUChksumPri(buf);                                                                             \
    }

/**
 * @}
 */

/**
 * @defgroup SIG_Vehicle_Speed_VehSpdAvgDrvnV Signal VehSpdAvgDrvnV of Message Vehicle_Speed (0x3e9)
 *
 * Contains the value table \ref ENUM_Vehicle_Speed_VehSpdAvgDrvnV.
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_Vehicle_Speed
 * @{
 */

/**
 * Signal VehSpdAvgDrvnV configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_Vehicle_Speed_VehSpdAvgDrvnV and \ref GET_Vehicle_Speed_VehSpdAvgDrvnV instead.
 */
#define SIG_Vehicle_Speed_VehSpdAvgDrvnV 1, 0, 7, 1

/**
 * Signal VehSpdAvgDrvnV setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_Vehicle_Speed_VehSpdAvgDrvnV or \ref INIT_Vehicle_Speed instead.
 */
#define SETUP_Vehicle_Speed_VehSpdAvgDrvnV 1, 0, 7, 1, 0

/**
 * Get signal VehSpdAvgDrvnV from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_Vehicle_Speed_VehSpdAvgDrvnV(buf) (0 | (uint8_t)(+(uint8_t)((buf[0] >> 7) & 0x01) << 0))

/**
 * Set signal VehSpdAvgDrvnV in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_Vehicle_Speed_VehSpdAvgDrvnV(buf, val)                                                                     \
    {                                                                                                                  \
        buf[0] &= ~(0x01 << 7);                                                                                        \
        buf[0] |= (((uint8_t)(val) >> 0) & 0x01) << 7;                                                                   \
    }

/**
 * Set signal VehSpdAvgDrvnV in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_Vehicle_Speed_VehSpdAvgDrvnV(buf) SET_Vehicle_Speed_VehSpdAvgDrvnV(buf, 0)

/**
 * Signal VehSpdAvgDrvnV value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_Vehicle_Speed_VehSpdAvgDrvnV(x, fmt) ((x)*fmt)

/**
 * Signal VehSpdAvgDrvnV raw initial value.
 */
#define START_Vehicle_Speed_VehSpdAvgDrvnV 0

/**
 * Signal VehSpdAvgDrvnV raw minimum value.
 */
#define MIN_Vehicle_Speed_VehSpdAvgDrvnV 0

/**
 * Signal VehSpdAvgDrvnV raw maximum value.
 */
#define MAX_Vehicle_Speed_VehSpdAvgDrvnV 1

/**
 * Signal VehSpdAvgDrvnV raw offset value.
 */
#define OFF_Vehicle_Speed_VehSpdAvgDrvnV 0

/**
 * @}
 */

/**
 * @defgroup ENUM_Vehicle_Speed_VehSpdAvgDrvnV Value Table for Signal VehSpdAvgDrvnV in Message Vehicle_Speed (0x3e9)
 *
 * Enum values defined for \ref SIG_Vehicle_Speed_VehSpdAvgDrvnV.
 *
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgDrvnV
 */

/**
 * Value table Vehicle_Speed_VehSpdAvgDrvnV entry Valid.
 *
 * @ingroup ENUM_Vehicle_Speed_VehSpdAvgDrvnV
 */
#define Vehicle_Speed_VehSpdAvgDrvnV_Valid 0

/**
 * Value table Vehicle_Speed_VehSpdAvgDrvnV entry Invalid.
 *
 * @ingroup ENUM_Vehicle_Speed_VehSpdAvgDrvnV
 */
#define Vehicle_Speed_VehSpdAvgDrvnV_Invalid 1

/**
 * @defgroup SIG_Vehicle_Speed_VehSpdAvgDrvn Signal VehSpdAvgDrvn of Message Vehicle_Speed (0x3e9)
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_Vehicle_Speed
 * @{
 */

/**
 * Signal VehSpdAvgDrvn configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_Vehicle_Speed_VehSpdAvgDrvn and \ref GET_Vehicle_Speed_VehSpdAvgDrvn instead.
 */
#define SIG_Vehicle_Speed_VehSpdAvgDrvn 1, 0, 6, 15

/**
 * Signal VehSpdAvgDrvn setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_Vehicle_Speed_VehSpdAvgDrvn or \ref INIT_Vehicle_Speed instead.
 */
#define SETUP_Vehicle_Speed_VehSpdAvgDrvn 1, 0, 6, 15, 0

/**
 * Get signal VehSpdAvgDrvn from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_Vehicle_Speed_VehSpdAvgDrvn(buf)                                                                           \
    (0 | (uint16_t)(+(uint16_t)((buf[0] >> 0) & 0x7f) << 8) | (uint8_t)(+(uint8_t)((buf[1] >> 0) & 0xff) << 0))

/**
 * Set signal VehSpdAvgDrvn in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_Vehicle_Speed_VehSpdAvgDrvn(buf, val)                                                                      \
    {                                                                                                                  \
        buf[0] &= ~(0x7f << 0);                                                                                        \
        buf[0] |= ((uint8_t)((uint16_t)(val) >> 8) & 0x7f) << 0;                                                            \
        buf[1] &= ((uint8_t) ~(0xff << 0));                                                                              \
        buf[1] |= (((uint8_t)(val) >> 0) & 0xff) << 0;                                                                   \
    }

/**
 * Set signal VehSpdAvgDrvn in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_Vehicle_Speed_VehSpdAvgDrvn(buf) SET_Vehicle_Speed_VehSpdAvgDrvn(buf, 0)

/**
 * Signal VehSpdAvgDrvn value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_Vehicle_Speed_VehSpdAvgDrvn(x, fmt) ((x)*fmt / 64)

/**
 * Signal VehSpdAvgDrvn raw initial value.
 */
#define START_Vehicle_Speed_VehSpdAvgDrvn 0

/**
 * Signal VehSpdAvgDrvn raw minimum value.
 */
#define MIN_Vehicle_Speed_VehSpdAvgDrvn 0

/**
 * Signal VehSpdAvgDrvn raw maximum value.
 */
#define MAX_Vehicle_Speed_VehSpdAvgDrvn 32767

/**
 * Signal VehSpdAvgDrvn raw offset value.
 */
#define OFF_Vehicle_Speed_VehSpdAvgDrvn 0

/**
 * @}
 */

/**
 * @defgroup SIG_Vehicle_Speed_VehSpdAvgNDrvnV Signal VehSpdAvgNDrvnV of Message Vehicle_Speed (0x3e9)
 *
 * Contains the value table \ref ENUM_Vehicle_Speed_VehSpdAvgNDrvnV.
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_Vehicle_Speed
 * @{
 */

/**
 * Signal VehSpdAvgNDrvnV configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_Vehicle_Speed_VehSpdAvgNDrvnV and \ref GET_Vehicle_Speed_VehSpdAvgNDrvnV instead.
 */
#define SIG_Vehicle_Speed_VehSpdAvgNDrvnV 1, 0, 39, 1

/**
 * Signal VehSpdAvgNDrvnV setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_Vehicle_Speed_VehSpdAvgNDrvnV or \ref INIT_Vehicle_Speed instead.
 */
#define SETUP_Vehicle_Speed_VehSpdAvgNDrvnV 1, 0, 39, 1, 0

/**
 * Get signal VehSpdAvgNDrvnV from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_Vehicle_Speed_VehSpdAvgNDrvnV(buf) (0 | (uint8_t)(+(uint8_t)((buf[4] >> 7) & 0x01) << 0))

/**
 * Set signal VehSpdAvgNDrvnV in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_Vehicle_Speed_VehSpdAvgNDrvnV(buf, val)                                                                    \
    {                                                                                                                  \
        buf[4] &= ~(0x01 << 7);                                                                                        \
        buf[4] |= (((uint8_t)(val) >> 0) & 0x01) << 7;                                                                   \
    }

/**
 * Set signal VehSpdAvgNDrvnV in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_Vehicle_Speed_VehSpdAvgNDrvnV(buf) SET_Vehicle_Speed_VehSpdAvgNDrvnV(buf, 0)

/**
 * Signal VehSpdAvgNDrvnV value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_Vehicle_Speed_VehSpdAvgNDrvnV(x, fmt) ((x)*fmt)

/**
 * Signal VehSpdAvgNDrvnV raw initial value.
 */
#define START_Vehicle_Speed_VehSpdAvgNDrvnV 0

/**
 * Signal VehSpdAvgNDrvnV raw minimum value.
 */
#define MIN_Vehicle_Speed_VehSpdAvgNDrvnV 0

/**
 * Signal VehSpdAvgNDrvnV raw maximum value.
 */
#define MAX_Vehicle_Speed_VehSpdAvgNDrvnV 1

/**
 * Signal VehSpdAvgNDrvnV raw offset value.
 */
#define OFF_Vehicle_Speed_VehSpdAvgNDrvnV 0

/**
 * @}
 */

/**
 * @defgroup ENUM_Vehicle_Speed_VehSpdAvgNDrvnV Value Table for Signal VehSpdAvgNDrvnV in Message Vehicle_Speed (0x3e9)
 *
 * Enum values defined for \ref SIG_Vehicle_Speed_VehSpdAvgNDrvnV.
 *
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgNDrvnV
 */

/**
 * Value table Vehicle_Speed_VehSpdAvgNDrvnV entry Valid.
 *
 * @ingroup ENUM_Vehicle_Speed_VehSpdAvgNDrvnV
 */
#define Vehicle_Speed_VehSpdAvgNDrvnV_Valid 0

/**
 * Value table Vehicle_Speed_VehSpdAvgNDrvnV entry Invalid.
 *
 * @ingroup ENUM_Vehicle_Speed_VehSpdAvgNDrvnV
 */
#define Vehicle_Speed_VehSpdAvgNDrvnV_Invalid 1

/**
 * @defgroup SIG_Vehicle_Speed_VehSpdAvgNDrvn Signal VehSpdAvgNDrvn of Message Vehicle_Speed (0x3e9)
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_Vehicle_Speed
 * @{
 */

/**
 * Signal VehSpdAvgNDrvn configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_Vehicle_Speed_VehSpdAvgNDrvn and \ref GET_Vehicle_Speed_VehSpdAvgNDrvn instead.
 */
#define SIG_Vehicle_Speed_VehSpdAvgNDrvn 1, 0, 38, 15

/**
 * Signal VehSpdAvgNDrvn setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_Vehicle_Speed_VehSpdAvgNDrvn or \ref INIT_Vehicle_Speed instead.
 */
#define SETUP_Vehicle_Speed_VehSpdAvgNDrvn 1, 0, 38, 15, 0

/**
 * Get signal VehSpdAvgNDrvn from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_Vehicle_Speed_VehSpdAvgNDrvn(buf)                                                                          \
    (0 | (uint16_t)(+(uint16_t)((buf[4] >> 0) & 0x7f) << 8) | (uint8_t)(+(uint8_t)((buf[5] >> 0) & 0xff) << 0))

/**
 * Set signal VehSpdAvgNDrvn in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_Vehicle_Speed_VehSpdAvgNDrvn(buf, val)                                                                     \
    {                                                                                                                  \
        buf[4] &= ~(0x7f << 0);                                                                                        \
        buf[4] |= ((uint8_t)((uint16_t)(val) >> 8) & 0x7f) << 0;                                                            \
        buf[5] &= ((uint8_t) ~(0xff << 0));                                                                              \
        buf[5] |= (((uint8_t)(val) >> 0) & 0xff) << 0;                                                                   \
    }

/**
 * Set signal VehSpdAvgNDrvn in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_Vehicle_Speed_VehSpdAvgNDrvn(buf) SET_Vehicle_Speed_VehSpdAvgNDrvn(buf, 0)

/**
 * Signal VehSpdAvgNDrvn value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_Vehicle_Speed_VehSpdAvgNDrvn(x, fmt) ((x)*fmt / 64)

/**
 * Signal VehSpdAvgNDrvn raw initial value.
 */
#define START_Vehicle_Speed_VehSpdAvgNDrvn 0

/**
 * Signal VehSpdAvgNDrvn raw minimum value.
 */
#define MIN_Vehicle_Speed_VehSpdAvgNDrvn 0

/**
 * Signal VehSpdAvgNDrvn raw maximum value.
 */
#define MAX_Vehicle_Speed_VehSpdAvgNDrvn 32767

/**
 * Signal VehSpdAvgNDrvn raw offset value.
 */
#define OFF_Vehicle_Speed_VehSpdAvgNDrvn 0

/**
 * @}
 */

/**
 * @defgroup SIG_IMU_Yaw_IMUYawRtPri Signal IMUYawRtPri of Message IMU_Yaw (0x330)
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_IMU_Yaw
 * @{
 */

/**
 * Signal IMUYawRtPri configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_IMU_Yaw_IMUYawRtPri and \ref GET_IMU_Yaw_IMUYawRtPri instead.
 */
#define SIG_IMU_Yaw_IMUYawRtPri 1, 1, 4, 13

/**
 * Signal IMUYawRtPri setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_IMU_Yaw_IMUYawRtPri or \ref INIT_IMU_Yaw instead.
 */
#define SETUP_IMU_Yaw_IMUYawRtPri 1, 1, 4, 13, 0

/**
 * Get signal IMUYawRtPri from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_IMU_Yaw_IMUYawRtPri(buf)                                                                                   \
    (0 | (uint16_t)(-(uint16_t)((buf[0] >> 4) & 0x01) << 13) | (uint16_t)(+(uint16_t)((buf[0] >> 0) & 0x1f) << 8) |                \
     (uint8_t)(+(uint8_t)((buf[1] >> 0) & 0xff) << 0))

/**
 * Set signal IMUYawRtPri in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_IMU_Yaw_IMUYawRtPri(buf, val)                                                                              \
    {                                                                                                                  \
        buf[0] &= ~(0x1f << 0);                                                                                        \
        buf[0] |= ((uint8_t)((uint16_t)(val) >> 8) & 0x1f) << 0;                                                            \
        buf[1] &= ((uint8_t) ~(0xff << 0));                                                                              \
        buf[1] |= (((uint8_t)(val) >> 0) & 0xff) << 0;                                                                   \
    }

/**
 * Set signal IMUYawRtPri in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_IMU_Yaw_IMUYawRtPri(buf) SET_IMU_Yaw_IMUYawRtPri(buf, 0)

/**
 * Signal IMUYawRtPri value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_IMU_Yaw_IMUYawRtPri(x, fmt) ((x)*fmt * 3 / 125)

/**
 * Signal IMUYawRtPri raw initial value.
 */
#define START_IMU_Yaw_IMUYawRtPri 0

/**
 * Signal IMUYawRtPri raw minimum value.
 */
#define MIN_IMU_Yaw_IMUYawRtPri -4096

/**
 * Signal IMUYawRtPri raw maximum value.
 */
#define MAX_IMU_Yaw_IMUYawRtPri 4095

/**
 * Signal IMUYawRtPri raw offset value.
 */
#define OFF_IMU_Yaw_IMUYawRtPri 0

/**
 * @}
 */

/**
 * @defgroup SIG_IMU_Yaw_IMURollCntPri Signal IMURollCntPri of Message IMU_Yaw (0x330)
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_IMU_Yaw
 * @{
 */

/**
 * Signal IMURollCntPri configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_IMU_Yaw_IMURollCntPri and \ref GET_IMU_Yaw_IMURollCntPri instead.
 */
#define SIG_IMU_Yaw_IMURollCntPri 1, 0, 6, 2

/**
 * Signal IMURollCntPri setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_IMU_Yaw_IMURollCntPri or \ref INIT_IMU_Yaw instead.
 */
#define SETUP_IMU_Yaw_IMURollCntPri 1, 0, 6, 2, 0

/**
 * Get signal IMURollCntPri from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_IMU_Yaw_IMURollCntPri(buf) (0 | (uint8_t)(+(uint8_t)((buf[0] >> 5) & 0x03) << 0))

/**
 * Set signal IMURollCntPri in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_IMU_Yaw_IMURollCntPri(buf, val)                                                                            \
    {                                                                                                                  \
        buf[0] &= ~(0x03 << 5);                                                                                        \
        buf[0] |= (((uint8_t)(val) >> 0) & 0x03) << 5;                                                                   \
    }

/**
 * Set signal IMURollCntPri in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_IMU_Yaw_IMURollCntPri(buf) SET_IMU_Yaw_IMURollCntPri(buf, 0)

/**
 * Signal IMURollCntPri value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_IMU_Yaw_IMURollCntPri(x, fmt) ((x)*fmt)

/**
 * Signal IMURollCntPri raw initial value.
 */
#define START_IMU_Yaw_IMURollCntPri 0

/**
 * Signal IMURollCntPri raw minimum value.
 */
#define MIN_IMU_Yaw_IMURollCntPri 0

/**
 * Signal IMURollCntPri raw maximum value.
 */
#define MAX_IMU_Yaw_IMURollCntPri 3

/**
 * Signal IMURollCntPri raw offset value.
 */
#define OFF_IMU_Yaw_IMURollCntPri 0

/**
 * @}
 */

/**
 * @defgroup SIG_IMU_Yaw_IMUYawRtPriV Signal IMUYawRtPriV of Message IMU_Yaw (0x330)
 *
 * Contains the value table \ref ENUM_IMU_Yaw_IMUYawRtPriV.
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_IMU_Yaw
 * @{
 */

/**
 * Signal IMUYawRtPriV configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_IMU_Yaw_IMUYawRtPriV and \ref GET_IMU_Yaw_IMUYawRtPriV instead.
 */
#define SIG_IMU_Yaw_IMUYawRtPriV 1, 0, 21, 1

/**
 * Signal IMUYawRtPriV setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_IMU_Yaw_IMUYawRtPriV or \ref INIT_IMU_Yaw instead.
 */
#define SETUP_IMU_Yaw_IMUYawRtPriV 1, 0, 21, 1, 0

/**
 * Get signal IMUYawRtPriV from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_IMU_Yaw_IMUYawRtPriV(buf) (0 | (uint8_t)(+(uint8_t)((buf[2] >> 5) & 0x01) << 0))

/**
 * Set signal IMUYawRtPriV in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_IMU_Yaw_IMUYawRtPriV(buf, val)                                                                             \
    {                                                                                                                  \
        buf[2] &= ~(0x01 << 5);                                                                                        \
        buf[2] |= (((uint8_t)(val) >> 0) & 0x01) << 5;                                                                   \
    }

/**
 * Set signal IMUYawRtPriV in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_IMU_Yaw_IMUYawRtPriV(buf) SET_IMU_Yaw_IMUYawRtPriV(buf, 0)

/**
 * Signal IMUYawRtPriV value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_IMU_Yaw_IMUYawRtPriV(x, fmt) ((x)*fmt)

/**
 * Signal IMUYawRtPriV raw initial value.
 */
#define START_IMU_Yaw_IMUYawRtPriV 0

/**
 * Signal IMUYawRtPriV raw minimum value.
 */
#define MIN_IMU_Yaw_IMUYawRtPriV 0

/**
 * Signal IMUYawRtPriV raw maximum value.
 */
#define MAX_IMU_Yaw_IMUYawRtPriV 1

/**
 * Signal IMUYawRtPriV raw offset value.
 */
#define OFF_IMU_Yaw_IMUYawRtPriV 0

/**
 * @}
 */

/**
 * @defgroup ENUM_IMU_Yaw_IMUYawRtPriV Value Table for Signal IMUYawRtPriV in Message IMU_Yaw (0x330)
 *
 * Enum values defined for \ref SIG_IMU_Yaw_IMUYawRtPriV.
 *
 * @ingroup SIG_IMU_Yaw_IMUYawRtPriV
 */

/**
 * Value table IMU_Yaw_IMUYawRtPriV entry Valid.
 *
 * @ingroup ENUM_IMU_Yaw_IMUYawRtPriV
 */
#define IMU_Yaw_IMUYawRtPriV_Valid 0

/**
 * Value table IMU_Yaw_IMUYawRtPriV entry Invalid.
 *
 * @ingroup ENUM_IMU_Yaw_IMUYawRtPriV
 */
#define IMU_Yaw_IMUYawRtPriV_Invalid 1

/**
 * @defgroup SIG_IMU_Yaw_IMUChksumPri Signal IMUChksumPri of Message IMU_Yaw (0x330)
 *
 * Received by the ECUs:
 * - \ref ECU_camera_VCAN
 *
 * @ingroup MSG_IMU_Yaw
 * @{
 */

/**
 * Signal IMUChksumPri configuration tuple.
 *
 * @deprecated
 *	Use \ref SET_IMU_Yaw_IMUChksumPri and \ref GET_IMU_Yaw_IMUChksumPri instead.
 */
#define SIG_IMU_Yaw_IMUChksumPri 1, 0, 50, 11

/**
 * Signal IMUChksumPri setup tuple.
 *
 * @deprecated
 *	Use \ref INITSIG_IMU_Yaw_IMUChksumPri or \ref INIT_IMU_Yaw instead.
 */
#define SETUP_IMU_Yaw_IMUChksumPri 1, 0, 50, 11, 0

/**
 * Get signal IMUChksumPri from buffer.
 *
 * @param buf
 *	The can message buffer containing the signal
 * @return
 *	The raw signal
 */
#define GET_IMU_Yaw_IMUChksumPri(buf)                                                                                  \
    (0 | (uint16_t)(+(uint16_t)((buf[6] >> 0) & 0x07) << 8) | (uint8_t)(+(uint8_t)((buf[7] >> 0) & 0xff) << 0))

/**
 * Set signal IMUChksumPri in buffer.
 *
 * @param buf
 *	The can message buffer to add the signal to
 * @param val
 *	The raw value to set the signal to
 */
#define SET_IMU_Yaw_IMUChksumPri(buf, val)                                                                             \
    {                                                                                                                  \
        buf[6] &= ~(0x07 << 0);                                                                                        \
        buf[6] |= ((uint8_t)((uint16_t)(val) >> 8) & 0x07) << 0;                                                            \
        buf[7] &= ((uint8_t) ~(0xff << 0));                                                                              \
        buf[7] |= (((uint8_t)(val) >> 0) & 0xff) << 0;                                                                   \
    }

/**
 * Set signal IMUChksumPri in buffer to its initial value.
 *
 * @param buf
 *	The can message buffer to initialise
 */
#define INITSIG_IMU_Yaw_IMUChksumPri(buf) SET_IMU_Yaw_IMUChksumPri(buf, 0)

/**
 * Signal IMUChksumPri value conversion with 16 bit factor and offset.
 *
 * @param x
 *	The raw signal value
 * @param fmt
 *	A factor to adjust values, e.g. 10 to get one additional
 *	digit or 1 / 1000 to dispay a fraction
 * @return
 *	The signal value as a human readable number
 */
#define CALC_IMU_Yaw_IMUChksumPri(x, fmt) ((x)*fmt)

/**
 * Signal IMUChksumPri raw initial value.
 */
#define START_IMU_Yaw_IMUChksumPri 0

/**
 * Signal IMUChksumPri raw minimum value.
 */
#define MIN_IMU_Yaw_IMUChksumPri 0

/**
 * Signal IMUChksumPri raw maximum value.
 */
#define MAX_IMU_Yaw_IMUChksumPri 2047

/**
 * Signal IMUChksumPri raw offset value.
 */
#define OFF_IMU_Yaw_IMUChksumPri 0

/**
 * @}
 */

/**
 * Signal timeout by ECU camera_VCAN for signal VehSpdAvgDrvnV of message Vehicle_Speed (0x3e9).
 *
 * @ingroup ECU_camera_VCAN
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgDrvnV
 */
#define TO_camera_VCAN_SIG_Vehicle_Speed_VehSpdAvgDrvnV 0

/**
 * Signal timeout by ECU camera_VCAN for signal VehSpdAvgDrvn of message Vehicle_Speed (0x3e9).
 *
 * @ingroup ECU_camera_VCAN
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgDrvn
 */
#define TO_camera_VCAN_SIG_Vehicle_Speed_VehSpdAvgDrvn 250

/**
 * Signal timeout by ECU camera_VCAN for signal VehSpdAvgNDrvnV of message Vehicle_Speed (0x3e9).
 *
 * @ingroup ECU_camera_VCAN
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgNDrvnV
 */
#define TO_camera_VCAN_SIG_Vehicle_Speed_VehSpdAvgNDrvnV 0

/**
 * Signal timeout by ECU camera_VCAN for signal VehSpdAvgNDrvn of message Vehicle_Speed (0x3e9).
 *
 * @ingroup ECU_camera_VCAN
 * @ingroup SIG_Vehicle_Speed_VehSpdAvgNDrvn
 */
#define TO_camera_VCAN_SIG_Vehicle_Speed_VehSpdAvgNDrvn 250

#endif
