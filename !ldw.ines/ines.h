#ifndef __INES_H__
#define __INES_H__

#define MAX_NAME 16

#pragma pack(push)
#pragma pack(1)
struct ines_hdr {
	ulong	signature;
	unsigned char	prg_banks;
	unsigned char	chr_banks;
	unsigned char	map_byte0;
	unsigned char	map_byte1;
	char	dummy[8];
};

struct ines_vect {
	unsigned short nmi_vect;
	unsigned short res_vect;
	unsigned short irq_vect;
};

struct fds_disk_hdr {
//	unsigned char block_code;	// 1
	unsigned char signature[14];
	unsigned char manufacturer;
	unsigned char name[4];
	unsigned char revision;
	unsigned char side_num;
	unsigned char disk_num;
	unsigned char disk_type;
	unsigned char unknown0;
	unsigned char boot_read;	// WHAT I NEEDED HERE FOR THE FIRT PLACE!
	unsigned char filler[5];
	unsigned char man_date[3];
	unsigned char country_code;
	unsigned char unimportant[21];
};

struct fds_file_amount {
//	unsigned char block_code;	// 2
	unsigned char amount;
};

struct fds_file_header {
	unsigned char num;
	unsigned char code;
	unsigned char name[8];
	unsigned short addr;
	unsigned short size;
	unsigned char type;
};

//struct fds_file_data {
//	unsigned char block_code;	// 4
//};
#pragma pack(pop)

#endif