#pragma once
#include <stdint.h>
#include "openrtk_user.h"

#define MAX_INCEPTIO_PACKET_TYPES 11

#pragma pack(push, 1)

	typedef struct {
		/* IMU */
		uint32_t imu_temp_status : 1; // imu temperature status
		uint32_t imu_acce_status : 1;  // imu accelerometer status
		uint32_t imu_gyro_status : 1; // imu gyro status
		uint32_t imu_sensor_status1 : 1; // imu sensor (#1, #2ㄛ #3) status
		uint32_t imu_sensor_status2 : 1; // imu sensor (#1, #2ㄛ #3) status
		uint32_t imu_sensor_status3 : 1; // imu sensor (#1, #2ㄛ #3) status
		uint32_t imu_overall_status : 1;

		/* GNSS status */
		uint32_t gnss_data_status : 1;
		uint32_t gnss_signal_status : 1;

		/* operation */
		uint32_t power : 1; // for the whole device, any component has no power then 0
		uint32_t MCU_status : 1;
		uint32_t pps_status : 1;

		uint32_t zupt_det : 1; // 1 每 zupt detected
		uint32_t odo_used : 1; // 1 每 odometer update used
		uint32_t odo_recv : 1; // 1 每 odometer data received

		/* IMU sensor fault flags:
		0 每 fault; 1 - normal*/
		uint32_t imu_s1_state : 1;
		uint32_t imu_s2_state : 1;
		uint32_t imu_s3_state : 1;
		/* Time valid flag: 0 每 fault; 1 - normal */
		uint32_t time_valid : 1;
		/* Antenna sensing status:
		 0 每 UNINIT
		 1 每 NORMAL
		 2 - OPEN
		 3 - SHORT
		 4 每 THERMAL SHUTDOWN
		 5 - REVERSE CURRENT
		 6 - OVERCURRENT
		 7 - RESERVED */
		uint32_t antenna_sensing : 3;
		/* GNSS chipset fault flag: 0 每 fault; 1 - normal */
		uint32_t gnss_chipset : 1;

		uint32_t rexerved : 9;
	} status_bit_t;


	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		float	 x_accel;
		float	 y_accel;
		float	 z_accel;
		float	 x_gyro;
		float	 y_gyro;
		float	 z_gyro;
	} inceptio_s1_t;

	struct inceptio_gN_more_early_t
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint8_t	 positionMode;
		uint32_t latitude;
		uint32_t longitude;
		float	 height;
		uint8_t  numberOfSVs;
		float    hdop;
		uint16_t diffage;
		int16_t	 velocityNorth;
		int16_t  velocityEast;
		int16_t  velocityUp;
	};

	struct inceptio_gN_early_t : inceptio_gN_more_early_t
	{
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
	};

	struct inceptio_gN_24_01_21_t
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint8_t	 positionMode;
		uint32_t latitude;
		uint32_t longitude;
		float	 height;
		uint8_t  numberOfSVs;
		float    hdop;
		float	 vdop;
		float	 tdop;
		uint16_t diffage;
		int16_t	 velocityNorth;
		int16_t  velocityEast;
		int16_t  velocityUp;
	};

	struct inceptio_gN_t : inceptio_gN_24_01_21_t
	{
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
		uint16_t pos_hor_pl;
		uint16_t pos_ver_pl;
		uint8_t pos_status;
		uint16_t vel_hor_pl;
		uint16_t vel_ver_pl;
		uint8_t vel_status;
	};

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint8_t  insStatus;
		uint8_t  insPositionType;
		int32_t	 latitude;
		int32_t	 longitude;
		float	 height;
		int16_t	 velocityNorth;
		int16_t  velocityEast;
		int16_t  velocityUp;
		int16_t  roll;
		int16_t  pitch;
		int16_t  heading;
	} inceptio_iN_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
		int16_t	 north_vel_std;
		int16_t  east_vel_std;
		int16_t  up_vel_std;
		int16_t  roll_std;
		int16_t  pitch_std;
		int16_t  heading_std;
	} inceptio_d1_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		int16_t	 latitude_std;
		int16_t	 longitude_std;
		int16_t	 height_std;
		int16_t	 north_vel_std;
		int16_t  east_vel_std;
		int16_t  up_vel_std;
		float  hor_pos_pl;
		float  ver_pos_pl;
		float  hor_vel_pl;
		float  ver_vel_pl;
		uint8_t pos_integrity_status;
		uint8_t vel_integrity_status;
	} inceptio_d2_t;

	typedef struct
	{
		uint32_t GPS_Week;
		double	 GPS_TimeOfWeek;
		uint16_t year;
		uint8_t	 mouth;
		uint8_t	 day;
		uint8_t	 hour;
		uint8_t  min;
		uint8_t  sec;
		status_bit_t status_bit;
		float  imu_temperature;
		float  mcu_temperature;
	} inceptio_sT_t;

	typedef struct
	{
		uint16_t GPS_Week;
		uint32_t GPS_TimeOfWeek;
		uint8_t	 mode;
		double	 speed;
		uint8_t	 fwd;
		uint64_t wheel_tick;
	} inceptio_o1_t;

	typedef enum {
		INCEPTIO_OUT_NONE = 0,
		INCEPTIO_OUT_SCALED1,
		INCEPTIO_OUT_SCALED2,
		INCEPTIO_OUT_INSPVA,
		INCEPTIO_OUT_STD1,
		INCEPTIO_OUT_STD2,
		INCEPTIO_OUT_GNSS,
		INCEPTIO_OUT_STATUS,
		INCEPTIO_OUT_ODO
	} InceptioOutPacketType;

#pragma pack(pop)

	extern void init_inceptio_data();
	extern void set_output_inceptio_file(int output);
	extern void set_base_inceptio_file_name(char* file_name);
	extern void write_inceptio_kml_files();
	extern void close_inceptio_all_log_file();

	extern int input_inceptio_raw(uint8_t data);

