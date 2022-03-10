#pragma once
#include <stdint.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include "kml.h"

namespace Ins401_Tool {

#pragma pack(push, 1)
	typedef struct {
		uint8_t nmea_flag;
		uint8_t flag;			//header是否满足包的条件 0:未满足, 1:满足
		uint8_t header_len;
		uint8_t header[4];
		uint32_t nbyte;
		uint32_t length;
		uint8_t buff[1280];
		uint32_t nmeabyte;
		uint8_t nmea[256];
		uint16_t packet_type;
	} raw_t;

	typedef struct {
		/* IMU */
		uint32_t master_fail : 1; // 0 = normal; 1 = fatal error occured
		uint32_t hw_err : 1;  // 0 = normal; 1 = hardware exception detected
		uint32_t sw_err : 1; // 0 = normal; 1 = software exception detected
		uint32_t config_err : 1; // 0 = normal; 1 = config error detected by periodic self-test
		uint32_t calib_err : 1; // 0 = normal; 1 = calibration data corrupted
		uint32_t accel_degradation : 1; // // 0= normal; 1 = accel data degradation due to sensor exception
		uint32_t gyro_degradation : 1; // 0= normal; 1 = gyro data degradation due to sensor exception
		uint32_t forced_restart : 1; // 0 = normal; 1 = forced restart 
		uint32_t crc_err : 1; // 0 = normal; 1 = Application CRC error detected
		uint32_t tx_overflow_err : 1; // 0 = normal; 1 = Tx Overflow occurred 10 consecutive cycles
		/* GNSS unit status */
		uint32_t pps_status : 1;  // 0 = normal; 1 = 1PPS pulse exception
		uint32_t gnss_data_status : 1; // 0 = normal; 1 = GNSS chipset has NO data output
		uint32_t gnss_signal_status : 1; // 0 = normal; 1 = GNSS chipset has data output but no valid signal detected
		/* operation */
		uint32_t power : 1; //  0 = normal; 1 = any component has no power
		uint32_t MCU_status : 1; // 0 = normal; 1 = MCU failure
		uint32_t temperature_under_mcu_flag : 1;  // 0 = normal; 1 = under temperature
		uint32_t temperature_under_sta_flag : 1;  // 0 = normal; 1 = under temperature
		uint32_t temperature_under_imu_flag : 1;  // 0 = normal; 1 = under temperature

		uint32_t temperature_over_mcu_flag : 1;   // 0 = normal; 1 = over temperature
		uint32_t temperature_over_sta_flag : 1;   // 0 = normal; 1 = over temperature
		uint32_t temperature_over_imu_flag : 1;   // 0 = normal; 1 = over temperature
		uint32_t reserved : 11;
	} status_bit_t;

	typedef struct {
		uint16_t	gps_week;
		uint32_t	gps_millisecs;
		float		accel_x;
		float		accel_y;
		float		accel_z;
		float		gyro_x;
		float		gyro_y;
		float		gyro_z;
	}raw_imu_t;

	typedef struct {
		uint16_t	gps_week;
		uint32_t	gps_millisecs;
		/*
		0: INVALID
		1: Single-point positioning (SPP)
		2: Real time differential GNSS (RTD)
		4: Real time kinematic (RTK), ambiguity fixed (RTK_FIXED)
		5: RTK with ambiguity float (RTK_FLOAT)
		*/
		uint8_t		position_type;
		double		latitude;
		double		longitude;
		double		height;
		float		latitude_std;
		float		longitude_std;
		float		height_std;
		uint8_t		numberOfSVs;
		uint8_t		numberOfSVs_in_solution;
		float		hdop;
		float		diffage;
		float		north_vel;
		float		east_vel;
		float		up_vel;
		float		north_vel_std;
		float		east_vel_std;
		float		up_vel_std;
	}gnss_sol_t;

	struct ins_sol_t_20211207 {
		uint16_t	gps_week;
		uint32_t	gps_millisecs;
		/*
		0:INVALID
		1:INS_ALIGNING
		2:INS_HIGH_VARIANCE
		3:INS_SOLUTION_GOOD
		4:INS_SOLUTION_FREE
		5:INS_ALIGNMENT_COMPLETE 
		*/
		uint8_t		ins_status;
		/*
		0:INVALID
		1:SPP/INS
		2:RTD/INS
		3:INS_PROPAGATE
		4:RTK_FIXED/INS
		5:RTK_FLOAT/INS
		*/
		uint8_t		ins_position_type;
		double		latitude;
		double		longitude;
		double		height;
		float		north_velocity;
		float		east_velocity;
		float		up_velocity;
		float		longitudinal_velocity;
		float		lateral_velocity;
		float		roll;
		float		pitch;
		float		heading;
		float		latitude_std;
		float		longitude_std;
		float		height_std;
		float		north_velocity_std;
		float		east_velocity_std;
		float		up_velocity_std;
		float		long_vel_std;
		float		lat_vel_std;
		float		roll_std;
		float		pitch_std;
		float		heading_std;
	};

	struct ins_sol_t: ins_sol_t_20211207 {
		int16_t id_contient;
	};	

	typedef struct {
		uint16_t		gps_week;
		uint32_t		gps_millisecs;
		status_bit_t	status_bit;
		float			IMU_Unit_temperature;
		float			MCU_temperature;
		float			STA9100_temperature;
	}diagnostic_msg_t;

	typedef struct
	{
		uint16_t GPS_Week;
		uint32_t GPS_TimeOfWeek;
		uint8_t	 mode;
		double	 speed;
		uint8_t	 fwd;
		uint64_t wheel_tick;
	} odo_t;

	typedef struct {
		uint16_t gps_week;
		uint32_t gps_millisecs;
		int8_t flag;
		double RVB[3];
		double CVB[9];
	} binary_misalign_t;

	typedef struct  SaveConfig
	{
		int16_t gnss_week;
		int32_t gnss_second;
		int8_t solution_type;
		int8_t position_type;
		double latitude;
		double longitude;
		float height;
		int16_t north_velocity;
		int16_t east_velocity;
		int16_t down_velocity;
		int16_t roll;
		int16_t pitch;
		int16_t azimuth;
		int16_t latitude_std;
		int16_t longitude_std;
		int16_t altitude_std;
		int16_t north_velocity_std;
		int16_t east_velocity_std;
		int16_t down_velocity_std;
		int16_t roll_std;
		int16_t pitch_std;
		int16_t azimuth_std;
		int16_t gyro_bias_x;
		int16_t gyro_bias_y;
		int16_t gyro_bias_z;
		int16_t acc_bias_x;
		int16_t acc_bias_y;
		int16_t acc_bias_z;
		int16_t std_gyro_bias_x;
		int16_t std_gyro_bias_y;
		int16_t std_gyro_bias_z;
		int16_t std_acc_bias_x;
		int16_t std_acc_bias_y;
		int16_t std_acc_bias_z;
		int8_t static_type;
		double reserve1;
		double reserve2;
	}SaveConfig;

	typedef struct SaveMsg
	{
		uint8_t sync1;            //!< start of packet first byte (0xAA)
		uint8_t sync2;            //!< start of packet second byte (0x44)
		uint8_t sync3;            //!< start of packet third  byte (0x12)
		uint16_t message_length;  //!< Message length (Not including header or CRC)
		uint16_t message_id;      //!< Message ID number
		SaveConfig saveConfig;
		uint8_t crc[4];                           //!< 32-bit cyclic redundancy check (CRC)
	}SaveMsg;

	/**** Start Up ****/
	typedef struct {
		uint32_t adc : 4;				/* bit0: Adc_In, bit1: Adc_Core, bit2: Adc_1V2, bit3: GND */
		uint32_t exOsc : 1;           /* exOsci = 24MHz */
		uint32_t power : 1;
		uint32_t ram : 3;				/* bit0: Sram0, bit1: Sram1, bit2: Sram2 */
		uint32_t wdg : 1;
		uint32_t flash : 2;			/* bit0: cflash bit1: wflash*/
		uint32_t clkCSV : 1;
		uint32_t BackUp : 19;
	}stFdHwStUp;

	/**** Run time ****/
	typedef struct {
		uint32_t  volt : 1;
		uint32_t  clock : 1;
		uint32_t  core : 1;
		uint32_t  sram : 1;
		uint32_t  flash : 1;
		uint32_t  BackUp : 27;
	}stFdHwMonitor;

	typedef struct {
		stFdHwStUp  start_up;
		stFdHwMonitor runtime;
	}stPacketCheck;

	typedef struct {
		uint16_t spp_hor_pos_s : 1;
		uint16_t spp_ver_pos_s : 1;
		uint16_t spp_hor_vel_s : 1;
		uint16_t spp_ver_vel_s : 1;
		uint16_t rtk_hor_pos_s : 1;
		uint16_t rtk_ver_pos_s : 1;
		uint16_t rtk_hor_vel_s : 1;
		uint16_t rtk_ver_vel_s : 1;
		uint16_t rtk_heading_s : 1;
		uint16_t reserved : 7;
	}gnss_sol_integ_bit;

	typedef struct {
		uint16_t	week;
		double		gps_millisecs;
		uint32_t	spp_fail_rate;
		uint32_t	rtk_fail_rate;
		uint16_t	spp_hor_pos_pl;
		uint16_t	spp_ver_pos_pl;
		uint16_t	spp_hor_vel_pl;
		uint16_t	spp_ver_vel_pl;
		uint16_t	rtk_hor_pos_pl;
		uint16_t	rtk_ver_pos_pl;
		uint16_t	rtk_hor_vel_pl;
		uint16_t	rtk_ver_vel_pl;
		uint16_t	rtk_heading_pl;
		uint16_t	spp_hor_pos_al;
		uint16_t	spp_ver_pos_al;
		uint16_t	spp_hor_vel_al;
		uint16_t	spp_ver_vel_al;
		uint16_t	rtk_hor_pos_al;
		uint16_t	rtk_ver_pos_al;
		uint16_t	rtk_hor_vel_al;
		uint16_t	rtk_ver_vel_al;
		uint16_t	rtk_heading_al;
		gnss_sol_integ_bit	status_bit;
	}gnss_integ_t;

	typedef struct {
		uint16_t gps_week;
		uint32_t gps_millisecs;
		uint8_t ins_aid;
	} binary_rtk_debug1_t;

	typedef struct {
		uint8_t gnss_err_out_pin;
		uint8_t gnss_rf_err_pin;
		uint8_t gnss_ant_err_pin;
		uint8_t gnss_handshake_flag; // 1 ok ,0 failure
	} system_fault_detection_t;

#pragma pack(pop)

	enum emPackageType {
		em_RAW_IMU = 0x0a01,
		em_GNSS_SOL = 0x0a02,
		em_INS_SOL = 0x0a03,
		em_RAW_ODO = 0x0a04,
		em_DIAGNOSTIC_MSG = 0x0a05,
		em_ROVER_RTCM = 0x0a06,
		em_MISALIGN = 0x0a07,
		PowerUpDR_MES = 0x0a09,
		em_CHECK = 0x4D44,
		em_GNSS_SOL_INTEGEITY = 0x6749,
		em_RTK_DEBUG1 = 0xd101,
		em_PACKAGE_FD = 0x6664,
	};

	typedef std::map<std::string, FILE*> FilesMap;
	class Ins401_decoder {
	public:
		Ins401_decoder();
		~Ins401_decoder();
	private:
		raw_t raw;
		raw_imu_t imu;
		gnss_sol_t gnss;
		ins_sol_t ins;
		odo_t odo;
		binary_misalign_t misa;
		diagnostic_msg_t dm;
		SaveMsg powerup_dr;
		stPacketCheck packetcheck;
		gnss_integ_t gnss_integ;
		binary_rtk_debug1_t rtk_debug1;
		system_fault_detection_t system_fault_detection;
		kml_gnss_t gnss_kml;
		kml_ins_t ins_kml;
		char base_file_name[256];
		char output_msg[1024];
		FILE* f_log;
		FILE* f_nmea;
		FILE* f_process;
		FILE* f_imu_csv;
		FILE* f_imu_txt;
		FILE* f_imu_bin;
		FILE* f_gnss_csv;
		FILE* f_gnss_txt;
		FILE* f_ins_csv;
		FILE* f_ins_txt;
		FILE* f_odo_csv;
		FILE* f_odo_txt;
		FILE* f_misa_csv;
		FILE* f_misa_txt;
		FILE* f_dm_csv;
		FILE* f_rover_rtcm;
		FILE* f_ins_log;
		FILE* f_ins_save;
		bool show_format_time;
		int pack_num;
		int crc_right_num;
		int crc_error_num;
		std::map<uint16_t, int> all_type_pack_num;
		FilesMap output_file_map;			//现在输出文件不断增加，把文件指针都保存到map中
		bool m_MI_file_switch;				//输出小米文件开关
		float height_msl;					//海平面高
		uint32_t last_gnss_integ_millisecs;	//上次gnss完好性包的周内秒，因为在没有gnss的情况下会不断输出同一个包
	private:
		void close_all_files();
		void create_file(FILE * &file, const char * suffix, const char * title, bool format_time);
		char * week_2_time_str(int week, uint32_t millisecs);
		void append_gnss_kml();
		void append_ins_kml();
		void output_imu_raw();
		void MI_output_imu_raw();
		void output_gnss_sol();
		void MI_output_gnss_sol();
		void output_ins_sol();
		void MI_output_ins_sol();
		void output_odo_raw();
		void output_dm_raw();
		void output_rover_rtcm();
		void output_misa_sol();
		void output_gnss_integ();
		void output_gnss_sol_and_integ();
		void output_check();
		void output_rtk_debug1();
		void output_system_fault_detection();
		void parse_packet_payload();
		void save_imu_bin();
		void parse_gga();
		int8_t parse_nmea(uint8_t data);		
	public:
		void init();
		void set_base_file_name(char* file_name);
		void set_show_format_time(bool show);
		void set_MI_file_switch(bool write);
		int input_data(uint8_t data);
		int input_ins_save_data(unsigned char data);		
		void finish();
		void ins_save_finish();
	public:
		int get_current_type();
		gnss_sol_t* get_gnss_sol();
		ins_sol_t * get_ins_sol();
		raw_imu_t * get_imu_raw();
	};
};

