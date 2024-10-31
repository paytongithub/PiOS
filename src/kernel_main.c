#include "rprintf.h"
#include "list.h"
#include "serial.h"
#include "page.h"
#include "getEL.c"
#include "mmu.h"
#include "fatfs.c"
#include "rprintf.h"

char glbl[128];
/*
unsigned long get_timer_count() {
    unsigned long *timer_count_register = 0x3f003004;
    return *timer_count_register;
}


void wait() {
    int start = get_timer_count();
    while(get_timer_count() - start < 1000) {
    }
}

void bss() {
    extern int __bss_start, __bss_end;
    char *bssstart, *bssend;
    bssstart = &__bss_start;
    bssend = (char *)&__bss_end;

    for (int i = 0; i <= bssend - bssstart; i++) {
	bssstart[i] = 0;
    }
}

int getEL() {
    unsigned int el;
    asm("mrs %0,CurrentEL"
	: "=r"(el)
	:
	:);
    return (el>>2);
}
*/
void kernel_main() {
    if (fatInit() != 0) {
        rprintf("Failed to initialize FAT filesystem.\n");
        return;
    }
    rprintf("FAT filesystem initialized successfully.\n");

    // Define the file path to open and a buffer to store the file's data
    char *file_to_open = "TESTFILE.TXT";  // Example file to look for
    struct root_directory_entry file_entry;

    // Attempt to open the file
    if (fatOpen(file_to_open, &file_entry) != 0) {
        rprintf("File %s not found.\n", file_to_open);
        return;
    }
    rprintf("File %s opened successfully.\n", file_to_open);

    // Read the file's contents into a buffer
    char file_buffer[1024];  // Adjust buffer size as needed
    int bytes_read = fatRead(file_buffer, &file_entry, sizeof(file_buffer));

    // Print the contents or indicate a successful read
    if (bytes_read > 0) {
        rprintf("Read %d bytes from %s:\n%s\n", bytes_read, file_to_open, file_buffer);
    } else {
        rprintf("Failed to read from %s.\n", file_to_open);
    }

    /*
    mapPages(0,0);

    init_pfa_list();
    struct ppage *process = allocate_physical_pages(10);
    free_physical_pages(process);
    // wait();

    //  bss();

    esp_printf(putc, "Current Execution Level is %d\r\n", getEL());
    */
    /*
    struct list_element c = { NULL, 3};
    struct list_element b = { &c, 2};
    struct list_element a = { &b, 1};
    struct list_element *head = &a;
    struct list_element test = { NULL, 10};
    list_add(head, &test);
    list_remove(&c);
    */
    while(1) {
    
    }
}


