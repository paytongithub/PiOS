#include "sd.h"
#include "rprintf.h"
#include "serial.h"
#include "fat.h"
#include <string.h>
#include <ctype.h>

#define SECTOR_SIZE 512

struct boot_sector *bs;
char bootSector[SECTOR_SIZE];
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;


int fatInit() {
    sd_init();
    sd_readblock(0, bootSector, 1);
    bs = bootSector;
    // TODO: Read FAT table from the SD card into array fat_table
    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
    rprintf("\n");
    rprintf("bytes per sector = %d\n", bs->bytes_per_sector);
    rprintf("sectors per cluster = %d\n", bs->num_sectors_per_cluster);
    rprintf("reserved sectors = %d\n", bs->num_reserved_sectors);
    rprintf("number of FATs = %d\n", bs->num_fat_tables);
    rprintf("number of RDEs = %d\n", bs->num_root_dir_entries);
    
    if (bs->boot_signature != 0xaa55) {
        return -1; // invalid boot sig
    }
    if (strcmp(bs->fs_type, "FAT12") != 0) {
        return -1; // invalid file name
    }

    unsigned int fat_start_sector = bs->num_reserved_sectors;
    sd_readblock(fat_start_sector, fat_table, bs->num_sectors_per_fat);

    root_sector = fat_start_sector + (bs->num_fat_tables * bs->num_sectors_per_fat);
    rprintf("FAT Initialized. Root sector: %d\n", root_sector);


}
int fatOpen(char* filepath, struct root_directory_entry *r) {
    char upper_filepath[256];
    struct root_directory_entry *entry;
    
    for (int i = 0; filepath [i] && i < sizeof(upper_filepath) - 1; i++) {
        upper_filepath[i] = toupper((unsigned char)filepath[i]);
    }
    upper_filepath[strlen(filepath)] = '\0';

    while (entry->file_name[0] != 0x00) {
        // Check if this entry matches the upper_filepath
        if (strncmp(entry->file_name, upper_filepath, 8) == 0 &&
            strncmp(entry->file_extension, upper_filepath + 8, 3) == 0) {
            // Copy the matching entry to 'r'
            *r = *entry;
            return 0; // Success
        }
        entry++; // Move to the next entry
    }
    return -1; // File not found
}

int fatRead(char* buf, struct root_directory_entry *r, int n) {
    unsigned int cluster = r->cluster;  // Starting cluster
    unsigned int bytes_read = 0;
    unsigned int cluster_size = bs->num_sectors_per_cluster * bs->bytes_per_sector;

    while (bytes_read < n && cluster < 0xFF8) {
        // Calculate the starting sector for the current cluster
        unsigned int sector = root_sector + ((cluster - 2) * bs->num_sectors_per_cluster);

        // Read each sector in the cluster
        for (int i = 0; i < bs->num_sectors_per_cluster && bytes_read < n; i++) {
            sd_readblock(sector + i, buf + bytes_read, 1);
            bytes_read += bs->bytes_per_sector;
        }

        // Get next cluster from FAT table
        unsigned int fat_offset = (cluster * 3) / 2;
        if (cluster % 2 == 0) {
            cluster = (fat_table[fat_offset] | (fat_table[fat_offset + 1] << 8)) & 0x0FFF;
        } else {
            cluster = ((fat_table[fat_offset] >> 4) | (fat_table[fat_offset + 1] << 4)) & 0x0FFF;
        }
    }

    return bytes_read; // Total bytes read
}

