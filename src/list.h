
struct list_element {
    struct list_element *next;
    int data;
};

void list_add(struct list_element *list_head, struct list_element *element);
void list_remove(struct list_element *element);

