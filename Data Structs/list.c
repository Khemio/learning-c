#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *Node;
typedef struct list *List;

struct node {
    Node prev;
    Node next;
    int value;
};

struct list {
    Node head;
    Node tail;
    size_t length;
};

Node createNode(int v) {
    Node n;
    n = malloc(sizeof(Node));

    n->prev = n->next = NULL;
    n->value = v;

    return n;

}

void destroyNode(Node n) {
    n->prev = n->next = NULL;
    n = NULL;
    free(n);
}

List createList() {
    List l;
    l = malloc(sizeof(List));
    l->head = l->tail = NULL;
    l->length = 0;

    // printf("create: %p\n", l->head);

    return l;
}

void destroyList(List l) {
    while(l->length) {
        l->tail = l->tail->prev;
        destroyNode(l->tail->next);
        l->length--;
    }

    l->head = l->tail = NULL;
    l = NULL;
    free(l);
}

void append(List l, int v) {
    Node n = createNode(v);

    if(!n) {
        return;
    }


    if(l->length == 0) {
        l->head = l->tail = n;
        l->length++;
        return;
    }

    l->tail->next = n;
    n->prev = l->tail;
    l->tail = n;

    l->length++;

    return;
}

void prepend(List l, int v) {
    Node n = createNode(v);

    if(!n) {
        return;
    }

    if(l->length == 0) {
        l->head = l->tail = n;
        l->length++;
        return;
    }

    l->head->prev = n;
    n->next = l->head;
    l->head = n;

    l->length++;

    return;
}

int pop(List l) {
    int out;

    if(l->length == 1) {
        out = l->head->value;
        destroyNode(l->head);
        l->head = l->tail = NULL;
        l->length--;
        return out;
    }

    out = l->tail->value;

    l->tail = l->tail->prev;
    destroyNode(l->tail->next);
    // l->tail->next = NULL;

    l->length--;

    return out;
}

int unshift(List l) {
    int out;

    if(l->length == 1) {
        out = l->head->value;
        destroyNode(l->head);
        l->head = l->tail = NULL;
        l->length--;
        return out;
    }

    out = l->head->value;

    l->head = l->head->next;
    destroyNode(l->head->prev);
    // l->head->prev = NULL;

    l->length--;

    return out;

    // return false;
}

void traverse(List l) {
    if (l->length == 0) {
        return;
    }

    Node n;
    n = l->head;

    for(int i = 0; i < l->length; i++) {
        printf("%d ", n->value);

        n = n->next;
    }

    printf("\n");
}

void insert(List l, int idx, int v) {
    if (idx > l->length + 1) {
        return;
    }

    if (idx == 0) {
        prepend(l, v);
        return;

    } else if (idx == l->length) {
        append(l, v);
        return;
    } 

    Node n = createNode(v);
    Node temp;

    if (idx < (l->length / 2)) {
        temp = l->head;
        
        for (int i = 0; i < idx; ++i) {
            temp = temp->next;
        }

        n->prev = temp->prev;
        n->next = temp->prev->next;
        n->prev->next = n;
        n->next->prev = n;


    } else {
        temp = l->tail;
        // printf("%d\n", idx);

        for (int i = l->length; i > idx; --i) {
            temp = temp->prev;
        }

        n->prev = temp->prev;
        n->next = temp->prev->next;
        n->prev->next = n;
        n->next->prev = n;

    }

    l->length++;

    temp = NULL;

}

int find(List l, int v) {
    if (l->length == 0) {
        return false;
    }

    Node n;
    n = l->head;

    for(int i = 0; i < l->length; i++) {
        if (n->value == v) {
            n = NULL;
            return i;
        }

        n = n->next;
    }

    n = NULL;
    return -1;
}

int get(List l, int idx) {

    if (idx > l->length) {
        return false;
    }

    int i = 0;
    int out;
    Node temp;
    temp = l->head;

    while (i < idx) {
        // if (temp->value == v) {
        //     temp = NULL;
        //     return true;
        // }

        temp = temp->next;
        i++;
    }

    out = temp->value;
    temp = NULL;


    return out;
}

int delete(List l, int v) {
    if (l->length == 0) {
        return false;
    }

    int i = 0;
    int out;
    Node temp;
    temp = l->head;

    for(int i = 0; i < l->length; i++) {
        if (temp->value == v) {

            if (i == 0) {
                out = unshift(l);
            } else if (i == l->length - 1) {
                out = pop(l);
            } else {
                out = temp->value;

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                destroyNode(temp);
                l->length--;
            }

            // temp = NULL;
            return out;
        }

        temp = temp->next;
    }

    return out;
}

int deleteAt(List l, int idx) {
    if (idx > l->length) {
        return false;
    } 
    
    if (idx == 0) {
        return unshift(l);
    } else if (idx == l->length - 1) {
        return pop(l);
    }

    int i = 0;
    int out;
    Node temp;
    temp = l->head;

    while (i < idx) {
        temp = temp->next;
        i++;
    }

    out = temp->value;

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    destroyNode(temp);
    l->length--;

    return out;
}

void concat(List l1, List l2) {

}




int main(void) {
    List iList;
    iList = createList();

    append(iList, 3);
    append(iList, 5);
    append(iList, 7);
    append(iList, 9);

    insert(iList, 1, 1);
    insert(iList, 3, 11);

    traverse(iList);
    printf("%d\n", deleteAt(iList, 0));
    traverse(iList);

    destroyList(iList);


    return EXIT_SUCCESS;
}