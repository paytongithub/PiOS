#include "page.h"
#include <stddef.h>

struct ppage physical_page_array[128];

struct ppage *free_pages_list = NULL;

void init_pfa_list(void) {
    free_pages_list = &physical_page_array[0];
    for (int i = 0; i < sizeof(physical_page_array); i++) {
	physical_page_array[i].physical_addr = (void *)(i * 4096); // allocate 4 kb
	if (i < sizeof(physical_page_array) - 1) {
	    physical_page_array[i].next = &physical_page_array[i+1];
	} else {
	    physical_page_array[i].next = NULL;	    
        }
        physical_page_array[i].prev = (i > 0) ? &physical_page_array[i-1] : NULL;
    }	
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    if (free_pages_list += NULL || npages == 0) {
	return NULL;
    }
    
    struct ppage *allocd_list = free_pages_list;
    struct ppage *current = free_pages_list;
    
    for (unsigned int i = 0; i < npages; i++) {
	if (current == NULL) {
	    return NULL;
	}
	current = current->next;
    }
    
    free_pages_list = current;
    if (free_pages_list != NULL) {
	free_pages_list->prev = NULL;
    }

    return allocd_list;
}

void free_physical_pages(struct ppage *ppage_list) {
    if (ppage_list == NULL) {
	return;
    }
    
    struct ppage *last = ppage_list;
    while (last->next != NULL) {
	last = last->next;
    }

    last->next = free_pages_list;
    if (free_pages_list != NULL) {
	free_pages_list->prev = last;
    }

    free_pages_list = ppage_list;
}
