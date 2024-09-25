#include "rprintf.c"
#include "rprintf.h"
#include "list.c"
#include "serial.c"

char glbl[128];

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


void kernel_main() {
	
    wait();

    bss();

    esp_printf(putc, "test");

    struct list_element c = { NULL, 3};
    struct list_element b = { &c, 2};
    struct list_element a = { &b, 1};
    struct list_element *head = &a;
    struct list_element test = { NULL, 10};
    list_add(head, &test);
    list_remove(&c);

    while(1) {

    }
}
