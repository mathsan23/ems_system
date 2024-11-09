#include <stdio.h>
#include <stdlib.h>

typedef struct node_t Node;

struct node_t {
    int value;
    Node *next;
};

void add_node(Node **list_head, Node *new_node) {
    if (*list_head == NULL) {
        *list_head = new_node;
    } else {
        Node *current_node = *list_head;
        while(current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}

void remove_node(Node **list_head) {
    if (*list_head == NULL) {
        return;
    }

    Node *node = *list_head;
    *list_head = (*list_head)->next;
    free(node);
}

void print_queue(const Node *list_head) {
    const Node *current_node = list_head;
    while (current_node != NULL) {
        printf("%d -> ", current_node->value);
        current_node = current_node->next;
    }
    printf("\n");
}

void print_node(const Node *node) {
    printf("%d\n", node->value);
}



int main() {
    Node *head = NULL;
    Node *new_node = NULL;

    for (int i = 0; i < 5; i++)
    {
        new_node = malloc(sizeof(Node));
        new_node->value =  i*i;
        new_node->next = NULL;
        add_node(&head, new_node);
        print_queue(head);
    }

    remove_node(&head);
    print_queue(head);

    // freeing up list
    Node *current_node = NULL;

    while (head != NULL) {
        current_node = head;
        head = head->next;
        print_queue(head);
        free(current_node);
    }
    
    return 0;
}