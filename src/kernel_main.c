#include "list.h"

    


void kernel_main() {
    struct list_element c = {NULL, 0};
    struct list_element b = {&c, 0};
    struct list_element a = {&b, 0};
    struct list_element *head = &a;

    struct list_element new_node = {NULL, 1};
    insert(head, &new_node);
    remove(head);
    while(1){
    }
}
