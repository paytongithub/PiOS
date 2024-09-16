#include "list.h"
#include <stddef.h>

void list_add(struct list_element *list_head, struct list_element *element) {
    struct list_element *temp = list_head;
    
    while (temp->next) {
	temp = temp->next;
    }
    temp->next = element;
    
}

void list_remove(struct list_element *element) {
    element->data = element->next->data;
    element->next = element->next->next;
	// Add memory freeing after this, store pointer to removed point
}
