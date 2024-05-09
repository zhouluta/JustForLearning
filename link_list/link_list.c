#include <stdio.h>
#include <stdlib.h>

struct Link_Node 
{
    int data;
    struct Link_Node* next;
};


void init_link_list(struct Link_Node* head){
    head->next = NULL;
    head->data = -1;
}
void head_insert(struct Link_Node* head, struct Link_Node* node){
    if(head->next == NULL){
        head->next = node;
        node->next = NULL;
    }else{
        node->next = head->next;
        head->next = node;
    }
}

void tail_insert(struct Link_Node *head, struct Link_Node *node){
    struct Link_Node* p = head;
    while(p->next!= NULL){
        p = p->next;
    }
    p->next = node;
    node->next = NULL;
}

void print_link_list(struct Link_Node* head){
    struct Link_Node* p = head;
    while(p->next != NULL){
        p = p->next;
        printf("%d\t", p->data);
    }
    printf("\n");
}

void update_node(struct Link_Node* head, int old_data, int new_data){
    struct Link_Node* p = head;
    while(p != NULL){
        if(p->data == old_data){
            p->data = new_data;
            break;
        }
        p = p->next;
    }
}

void delete_node(struct Link_Node* head, int data){
    struct Link_Node* p = head;
    struct Link_Node* q = head->next;
    while(q != NULL && q->data != data){
        p = p->next;
        q = q->next;
    }
    if(q != NULL){
        p->next = q->next;
        free(q);
    }
}

void search_node(struct Link_Node* head, int data){
    struct Link_Node* p = head;
    int number = 1;
    while(p->next != NULL){
        p = p->next;
        if(p->data == data){
            break;
        }

        ++number;
    }
    printf("The number of %d is %d.\n", data, number);
}

int main(){
    struct Link_Node* head = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    init_link_list(head);
    struct Link_Node* node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 1;
    head_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 2;
    head_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 3;
    tail_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 4;
    tail_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 5;
    tail_insert(head, node);

    print_link_list(head);
    delete_node(head, 5);
    print_link_list(head);

    update_node(head, 3, 100);
    print_link_list(head);

    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 50;
    head_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 60;
    head_insert(head, node);
    node = (struct Link_Node*)malloc(sizeof(struct Link_Node));
    node->data = 70;
    head_insert(head, node);

    print_link_list(head);
    search_node(head, 100);
    return 0;
}