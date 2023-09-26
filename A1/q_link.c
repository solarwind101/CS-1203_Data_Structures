#include <stdio.h>
#include <stdlib.h>

#define BADVAL -9999

// Define a structure for a node in the linked list
struct node {
    int info;
    struct node* next;
};

typedef struct node* NODEPTR;

// Function to create a new node and return a pointer to it
NODEPTR createNode(int val) {
    NODEPTR p;
    p = (NODEPTR)malloc(sizeof(struct node));
    p->info = val;
    p->next = NULL;
    return p;
}

// Function to delete the front node of the linked list
int deleteNode(NODEPTR* afront, NODEPTR* arear) {
    NODEPTR temp;
    int val;

    if (*afront == NULL)
        return BADVAL;
    else {
        temp = *afront;
        (*afront) = (*afront)->next;
        val = temp->info;
        free(temp);
        if (*afront == NULL)
            *arear = NULL;
        return val;
    }
}

// Function to insert a new node at the rear of the linked list
void insertNode(NODEPTR* afront, NODEPTR* arear, int elm) {
    NODEPTR temp;
    temp = createNode(elm);

    if (*afront == NULL) {
        *afront = temp;
        *arear = temp;
    } else {
        (*arear)->next = temp;
        *arear = temp;
    }
}

// Function to print the linked list as a queue
void printQueue(NODEPTR front) {
    NODEPTR temp;

    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("F: ");
    for (temp = front; temp != NULL; temp = temp->next)
        printf("%d ", temp->info);
    printf(":R\n");
}

// Define a structure to encapsulate front and rear pointers of a queue
typedef struct queue {
    NODEPTR front, rear;
} QUEUE;

// Function to initialize a QUEUE structure
void init(QUEUE* q) {
    q->front = q->rear = NULL;
}

// Function to check if the QUEUE is empty
int isEmpty(QUEUE* q) {
    return (q->front == NULL);
}

// Function to insert an element at the rear of the queue
void insert(QUEUE* q, int elm) {
    insertNode(&(q->front), &(q->rear), elm);
}

// Function to delete the front element of the queue
int deleteQueue(QUEUE* q) {
    return deleteNode(&(q->front), &(q->rear));
}

// Wrapper function for printing the elements of a queue
void printQueueWrapper(QUEUE* q) {
    printQueue(q->front);
}

int main() {
    QUEUE qq;
    int elm, menu;

    while (1) {
        printf("0. exit, 1. initialize, 2. delete, 3. insert, 4. print. Input Choice: ");
        scanf("%d", &menu);

        switch (menu) {
        case 0:
            exit(0);
        case 1:
            init(&qq);
            break;
        case 2:
            printf("Deleted Value: %d\n", deleteQueue(&qq));
            break;
        case 3:
            printf("Please enter an element: ");
            scanf("%d", &elm);
            insert(&qq, elm);
            break;
        case 4:
            printQueueWrapper(&qq);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
}
