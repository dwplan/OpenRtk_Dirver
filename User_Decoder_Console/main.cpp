#include <stdio.h>
#include <vector>
#include <io.h>
#include <direct.h>
#include <string.h>
#include "openrtk_user.h"
#include "openrtk_inceptio.h"

#define READ_CACHE_SIZE 4*1024

int getFileSize(FILE* file)
{
	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	return file_size;
}

int makeDir(char* folderPath) 
{
	int ret = -1;
	if (0 != _access(folderPath, 0))
	{
		ret = _mkdir(folderPath);   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
	}
	return ret;
}

void createDirByFilePath(char* filename,char* dirname) {
	char basename[64] = { 0 };
	strncpy(dirname, filename, strlen(filename) - 4);
	char* p = strrchr(dirname, '\\');
	strcpy(basename, p);
	strcat(dirname, "_d");
	makeDir(dirname);
	strcat(dirname, basename);
}

void decode_openrtk_user(char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file) {
		char dirname[256] = { 0 };
		int ret = 0;
		int file_size = getFileSize(file);
		int read_size = 0;
		int readcount = 0;
		char read_cache[READ_CACHE_SIZE] = { 0 };
		std::vector<user_g1_t> gnss_list;
		std::vector<user_i1_t> ins_list;
		set_output_user_file(1);
		set_save_bin(1);
		createDirByFilePath(filename, dirname);
		set_base_user_file_name(dirname);
		while (!feof(file)) {
			readcount = fread(read_cache, sizeof(char), READ_CACHE_SIZE, file);
			read_size += readcount;
			for (int i = 0; i < readcount; i++) {
				ret = input_user_raw(read_cache[i]);
				if (ret == 1) {
					if (get_user_packet_type() == USR_OUT_BESTGNSS) {
						user_g1_t* g1 = get_user_packet_g1();
						gnss_list.push_back(*g1);
					}
					else if (get_user_packet_type() == USR_OUT_INSPVAX) {
						user_i1_t* i1 = get_user_packet_i1();
						ins_list.push_back(*i1);
					}
				}
			}
			double percent = (double)read_size / (double)file_size * 100;
			printf("Process : %4.1f %%\r", percent);
		}
		//gnss kml
		for (int i = 0; i < gnss_list.size(); ++i) {
			if (i == 0) {
				write_gnss_kml_line(&gnss_list[i], 1);
			}
			else if (i == gnss_list.size() - 1) {
				write_gnss_kml_line(&gnss_list[i], -1);
			}
			else {
				write_gnss_kml_line(&gnss_list[i], 0);
			}
		}
		for (int i = 0; i < gnss_list.size(); ++i) {
			if (i == 0) {
				write_gnss_kml_file(&gnss_list[i], 1);
			}
			else if (i == gnss_list.size() - 1) {
				write_gnss_kml_file(&gnss_list[i], -1);
			}
			else {
				write_gnss_kml_file(&gnss_list[i], 0);
			}
		}
		//ins kml
		for (int i = 0; i < ins_list.size(); ++i) {
			if (i == 0) {
				write_ins_kml_line(&ins_list[i], 1);
			}
			else if (i == ins_list.size() - 1) {
				write_ins_kml_line(&ins_list[i], -1);
			}
			else {
				write_ins_kml_line(&ins_list[i], 0);
			}
		}
		for (int i = 0; i < ins_list.size(); ++i) {
			if (i == 0) {
				write_ins_kml_file(&ins_list[i], 1);
			}
			else if (i == ins_list.size() - 1) {
				write_ins_kml_file(&ins_list[i], -1);
			}
			else {
				write_ins_kml_file(&ins_list[i], 0);
			}
		}
		gnss_list.clear();
		ins_list.clear();
		close_user_all_log_file();
		fclose(file);
	}
}

void decode_openrtk_inceptio(char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file) {
		char dirname[256] = { 0 };
		int ret = 0;
		int file_size = getFileSize(file);
		int read_size = 0;
		int readcount = 0;
		char read_cache[READ_CACHE_SIZE] = { 0 };
		std::vector<inceptio_gN_t> gnss_list;
		std::vector<inceptio_iN_t> ins_list;
		set_output_inceptio_file(1);
		createDirByFilePath(filename, dirname);
		set_base_inceptio_file_name(dirname);
		while (!feof(file)) {
			readcount = fread(read_cache, sizeof(char), READ_CACHE_SIZE, file);
			read_size += readcount;
			for (int i = 0; i < readcount; i++) {
				ret = input_inceptio_raw(read_cache[i]);
				if (ret == 1) {
					if (get_inceptio_packet_type() == INCEPTIO_OUT_GNSS) {
						inceptio_gN_t* g1 = get_inceptio_packet_gN();
						gnss_list.push_back(*g1);
					}
					else if (get_inceptio_packet_type() == INCEPTIO_OUT_INSPVA) {
						inceptio_iN_t* i1 = get_inceptio_packet_iN();
						ins_list.push_back(*i1);
					}
				}
			}
			double percent = (double)read_size / (double)file_size * 100;
			printf("Process : %4.1f %%\r", percent);
		}
		//gnss kml
		for (int i = 0; i < gnss_list.size(); ++i) {
			if (i == 0) {
				write_inceptio_gnss_kml_line(&gnss_list[i], 1);
			}
			else if (i == gnss_list.size() - 1) {
				write_inceptio_gnss_kml_line(&gnss_list[i], -1);
			}
			else {
				write_inceptio_gnss_kml_line(&gnss_list[i], 0);
			}
		}
		for (int i = 0; i < gnss_list.size(); ++i) {
			if (i == 0) {
				write_inceptio_gnss_kml_file(&gnss_list[i], 1);
			}
			else if (i == gnss_list.size() - 1) {
				write_inceptio_gnss_kml_file(&gnss_list[i], -1);
			}
			else {
				write_inceptio_gnss_kml_file(&gnss_list[i], 0);
			}
		}
		//ins kml
		for (int i = 0; i < ins_list.size(); ++i) {
			if (i == 0) {
				write_inceptio_ins_kml_line(&ins_list[i], 1);
			}
			else if (i == ins_list.size() - 1) {
				write_inceptio_ins_kml_line(&ins_list[i], -1);
			}
			else {
				write_inceptio_ins_kml_line(&ins_list[i], 0);
			}
		}
		for (int i = 0; i < ins_list.size(); ++i) {
			if (i == 0) {
				write_inceptio_ins_kml_file(&ins_list[i], 1);
			}
			else if (i == ins_list.size() - 1) {
				write_inceptio_ins_kml_file(&ins_list[i], -1);
			}
			else {
				write_inceptio_ins_kml_file(&ins_list[i], 0);
			}
		}
		gnss_list.clear();
		ins_list.clear();
		close_inceptio_all_log_file();
		fclose(file);
	}
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		char* filename = argv[2];
		if (strcmp(argv[1], "-u") == 0) {
			decode_openrtk_user(filename);
		}
		else if (strcmp(argv[1], "-i") == 0) {
			decode_openrtk_inceptio(filename);
		}
		else {
			printf("User_Decoder_Console.exe -u(user)|i(inceptio) <filename> \n");
		}
	}
	else {
		printf("User_Decoder_Console.exe -u(user)|i(inceptio) <filename> \n");
	}
	return 0;
}