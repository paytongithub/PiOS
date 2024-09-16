#include "list.c"
#include <stddef.h>
#include <stdio.h>



void main() {    
    struct list_element c = { NULL, 3};
    struct list_element b = { &c, 2};
    struct list_element a = { &b, 1};
    struct list_element *head = &a;
    struct list_element test = { NULL, 10};
/* //test cases  
    list_add(head, &test);
    printf("%d %d %d %d\n",a.data,a.next->data,a.next->next->data,a.next->next->next->data);   
    list_remove(&c);
    printf("%d %d %d\n",a.data,a.next->data,a.next->next->data);
*/
}
/*
void kernel_main() {
    extern int __bss_start, __bss_end;

    char *bssstart = (char *)&__bss_start;
    char *bssend = (char *)&__bss_end;

    while (bssstart < bssend) {
	*bssstart = 0;
	bssstart++;
    }
    while(1) {
    }
}
*/
