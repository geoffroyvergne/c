#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node_t;

void testInsert(node_t* head);
void printList(node_t* head);
void push(node_t* head, int data);
void pushFirst(node_t** head, int data);
int pop(node_t** head);
int removeLast(node_t* head);
int removeByIndex(node_t** head, int index);
int removeByValue(node_t** head, int data);

int main(void) {
    node_t* head = NULL;
    head = (node_t*) malloc(sizeof(node_t));

    testInsert(head);
    push(head, 5);
    pushFirst(&head, 0);
    //removeLast(head);
    //pop(&head);

    //removeByIndex(&head, 1);
    int val = removeByValue(&head, 3);
    printf("%i\n", val);

    printList(head);

    return 0;
}

void push(node_t* head, int data) {
    node_t* current = head;

    while(current->next != NULL) {
        current = current->next;
    }

    current->next = (node_t*) malloc(sizeof(node_t));
    current->next->data = data;
    current->next->next = NULL;
}

void pushFirst(node_t** head, int data) {
    // Create a new item and set its value
    node_t* newNode;
    newNode = (node_t*) malloc(sizeof(node_t));
    newNode->data = data;

    // Link the new item to point to the head of the list
    newNode->next = *head;

    // Set the head of the list to be our new item
    *head = newNode;
}

int pop(node_t** head) {

    if(*head == NULL) {
        return -1;
    }

    int retval = -1;
    
    // Take the next item that the head points to and save it
    node_t* nextNode = NULL;
    nextNode = (*head)->next;
    retval = (*head)->data;

    // Free the head item
    free(*head);

    // Set the head to be the next item that we've stored on the side
    *head = nextNode;

    return retval;
}

int removeLast(node_t* head) {
    int retval = 0;

    // if there is only one item in the list, remove it
    if(head->next == NULL) {
        retval = head->data;
        free(head);
        return retval;
    }

    // get to the second to last node in the list
    node_t* current = head;
    while(current->next->next != NULL) {
        current = current->next;
    } 

    // now current points to the second to last item of the list, so let's remove current->next
    retval = current->next->data;
    free(current->next);
    current->next = NULL;
    
    return retval;
}

int removeByIndex(node_t** head, int index) {

    if(index == 0) {
        return pop(head);
    }

    int i = 0;
    int retval = -1;

    node_t* current = *head;
    node_t* tempNode = NULL;

    // Iterate to the node before the node we wish to delete
    for(i=0; i<index-1; i++) {
        if(current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    // Save the node we wish to delete in a temporary pointer
    tempNode = current->next;
    retval = tempNode->data;

    // Set the previous node's next pointer to point to the node after the node we wish to delete
    current->next = tempNode->next;

    // Delete the node using the temporary pointer
    free(tempNode);

    return retval;
}

int removeByValue(node_t** head, int data) {
    int retval = -1;
    
    node_t* current = *head;
    node_t* temp = NULL;

    if(current != NULL && current->data == data) {
        *head = current->next;
        retval = current->data;
        free(current);
        return retval;
    }

    while(current != NULL && current->data != data) {
        temp = current;
        current = current->next;
    }

    if(current == NULL) return -1;

    retval = current->data;
    temp->next = current->next;
    free(current);
    
    return retval;
}

void printList(node_t* head) {
    node_t* current = head;

    while(current != NULL) {
        printf("Data -> %d \n", current->data);
        current = current->next;
    }
}

void testInsert(node_t* head) {
    node_t* current = head;

    while(current->next != NULL) {
        current = current->next;
    }

    node_t* second = NULL;
    node_t* third = NULL;

    // Allocate 3 nodes in the Heap
    second = (node_t*) malloc(sizeof(node_t));
    third = (node_t*) malloc(sizeof(node_t));

    // Assign values to datas
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    head->next->next->next = (node_t*) malloc(sizeof(node_t));
    head->next->next->next->data = 4;
    head->next->next->next->next = NULL;
}