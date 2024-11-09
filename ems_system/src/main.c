#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DESCRIPTION_SIZE 30

typedef enum priority_t {
    PRIORITY_HIGH,
    PRIORITY_NORMAL
} Priority;

typedef struct event_t {
    char description[MAX_DESCRIPTION_SIZE];
    unsigned int time_ms;
    Priority priority;
} Event;

void print_event(const Event *e) {
    printf("Event: %*s | %8d | %6s\n", MAX_DESCRIPTION_SIZE, e->description, e->time_ms, e->priority == PRIORITY_HIGH ? "high" : "normal");
}

void remove_newline(char *string) {
    int string_length = strlen(string);
    if (string_length > 0 && string[string_length - 1] == '\n') {
        string[string_length - 1] = '\0';
    }
}

/* Queue functions start*/

typedef struct node_t Node;

struct node_t {
    Event event;
    Node *next;
};

void add_node_high_normal(Node **head_high, Node **head_normal, Node *new_node) {
    if (new_node->event.priority == PRIORITY_HIGH) {
        if (*head_high == NULL) {
            *head_high = new_node;
        } else {

            Node *current_node = *head_high;
            while(current_node->next != *head_normal) {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
        if (head_normal != NULL) {
            new_node->next = *head_normal;
        }

    } else if (new_node->event.priority == PRIORITY_NORMAL) {
        if (*head_normal == NULL) {
            *head_normal = new_node;
            if (*head_high != NULL) {
                Node *current_node = *head_high;
                while(current_node->next != NULL) {
                    current_node = current_node->next;
                }
                
                current_node->next = *head_normal;
            }
        } else {
            Node *current_node = *head_normal;
            while(current_node->next != NULL) {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
    }
}

void remove_node_high_normal(Node **head_high, Node **head_normal) {
    if (*head_high != NULL) {
        Node *node = *head_high;
        if ((*head_high)->next != NULL) {
            if((*head_high)->next->event.priority == PRIORITY_HIGH) {
                *head_high = (*head_high)->next;
            } else {
                *head_high = NULL;
            }
        } else {
            *head_high = NULL;
        }
        free(node);
    } else if (*head_normal != NULL) {
        Node *node = *head_normal;
        *head_normal = (*head_normal)->next;
        free(node);
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

void print_node(const Node *node) {
    print_event(&node->event);
}

void print_queue_high_normal(const Node *head_high, const Node *head_normal) {
    const Node *current_node = head_high ? head_high : head_normal;
    while (current_node != NULL) {
        print_node(current_node);
        current_node = current_node->next;
    }
    printf("\n");
}

void print_queue(const Node *list_head) {
    const Node *current_node = list_head;
    while (current_node != NULL) {
        print_node(current_node);
        current_node = current_node->next;
    }
    printf("\n");
}

void free_queue_high_normal (Node **head_high, Node **head_normal) {
    Node *aux_node = NULL;
    int all_done = (*head_high != NULL);

    while (*head_high != NULL) {
        aux_node = *head_high;
        *head_high = (*head_high)->next;
        free(aux_node);
    }

    if (all_done) {
        *head_normal = NULL;
        return;
    }

    while (*head_normal != NULL) {
        aux_node = *head_normal;
        *head_normal = (*head_normal)->next;
        free(aux_node);
    }
    return;
}


/* Queue functions end*/

int main() {
    int event_amount = 3;
    //Event *e = malloc(event_amount * sizeof(Event));

    Node *head_normal = NULL;
    Node *head_high = NULL;
    Node *new_node = NULL;

    int event_index = 0;

    char buffer[MAX_DESCRIPTION_SIZE] = "";

    int do_handover = 0;

    while (event_index < event_amount) {

        new_node = malloc(sizeof(Node));
        new_node->next = NULL;

        printf("Descrição: ");
        fgets(new_node->event.description, MAX_DESCRIPTION_SIZE, stdin);
        remove_newline(new_node->event.description);

        printf("Tempo (ms): ");
        fgets(buffer, MAX_DESCRIPTION_SIZE, stdin);
        new_node->event.time_ms = atoi(buffer);

        printf("Prioridade (0: Alta, 1: Normal): ");
        fgets(buffer, MAX_DESCRIPTION_SIZE, stdin);
        new_node->event.priority = atoi(buffer);

        add_node_high_normal(&head_high, &head_normal, new_node);
        print_queue_high_normal(head_high, head_normal);

        event_index++;


        printf("Fazer handover? (y/N): ");
        fgets(buffer, MAX_DESCRIPTION_SIZE, stdin);
        do_handover = buffer[0] == 'y' ? 1 : 0;

        if (do_handover) {
            remove_node_high_normal(&head_high, &head_normal);
            printf("Handover realizado!\n");
            print_queue_high_normal(head_high, head_normal);
        }
        

        /* Event handover start*/

        /*new_node->event.description[0] = '\0';
        new_node->event.time_ms = 0;
        new_node->event.priority = 0;
        print_event(&new_node->event);
        printf("EVENT HANDOVER\n");*/

    }
    free_queue_high_normal(&head_high, &head_normal);
    print_queue_high_normal(head_high, head_normal);
}