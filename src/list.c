#include "list.h"

void insert(struct list_element *list_head, struct list_element *new_element, 
    struct list_element *element) {
        struct list_element *cursor = list_head;
        while (cursor->next->next != NULL) {
            if (cursor->next == new_element) {
                new_element->next = cursor->next->next;
            }
            cursor = cursor->next;
        }
    }    
void remove(struct list_element *list_head, struct list_element *element) {
    struct list_element *cursor = list_head;
    while (cursor->next->next != NULL) {
        if (cursor->next == element) {
            cursor->next = cursor->next->next;
        }
    }
    cursor = cursor->next;
}

