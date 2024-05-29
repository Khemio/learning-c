#include <stdio.h>
#include <stdlib.h>


// TODO: DEBUG


struct node {
    int value;
    struct node *next;
    struct node *prev;
};
typedef struct node node_t;

void printList(node_t *head) {
    node_t *temp = head;

    while (temp != NULL) {
        printf("%d - ", temp->value);
        temp = temp->next;
    }

    printf("\n");

}

node_t * create_new_node(int value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    result->prev = NULL;

    return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    (*head)->prev = node_to_insert;
    *head = node_to_insert;
    return node_to_insert;
}

void insert_after_node(node_t *node_to_insert_after, node_t *new_node) {
    new_node->next = node_to_insert_after->next;
    if (new_node->next != NULL) {
        new_node->next->prev = node_to_insert_after;
    }
    new_node->prev = node_to_insert_after;
    node_to_insert_after->next = new_node;
}

node_t *find_node(node_t *head, int value) {
    node_t *temp = head;
    while (temp != NULL) {
        if (temp->value == value) return temp;
        temp = temp->next;
    }
    return NULL;
}

void remove_node(node_t **head, node_t *node_to_remove) {
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        return;
    } else {
        node_to_remove->prev->next = node_to_remove->next;

        if ( node_to_remove->next != NULL) {
            node_to_remove->next->prev = node_to_remove->prev;
        }
        // node_t *temp = *head;
        // while (temp != NULL && temp->next != node_to_remove) {
        //     temp = temp->next;
        // }

        // if (temp == NULL) return;
        // temp->next = node_to_remove->next;
        node_to_remove->next = NULL;
        node_to_remove->prev = NULL;
        return;
    }

}

int main(void) {
    node_t *head = NULL;
    node_t *temp;

    for (int i = 0; i < 25; i++) {
        temp = create_new_node(i);
        insert_at_head(&head, temp);
    }

    temp = find_node(head, 13);
    printf("%d\n", temp->value);
    insert_after_node(temp, create_new_node(75));

    printList(head);

    remove_node(&head, temp);
    remove_node(&head, head);

    printList(head);

    return 0;
}