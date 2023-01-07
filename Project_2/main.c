#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define QUIT_MODE -1

typedef int BOOL;

typedef struct Node* Nptr;
typedef struct Node {
    int value, pathsAccount, maxPathsAccount;
    BOOL isVisited;
    Nptr* paths;
} Node;

typedef struct QueueNode* QueueNodePtr;
typedef struct QueueNode {
    Nptr value;
    QueueNodePtr next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

// functions for operating node type
Nptr newNode(int);
void addPath(Nptr, Nptr);

// functions for Queue
Queue* createQueue();
BOOL isEmptyQ(Queue* );
void AddQ(Queue*, Nptr);
Nptr PopQ(Queue* );

// DFS & BFS
void DFS(Nptr);
void BFS(Nptr);

// others
int max(int, int);
void reset(Nptr);

int main(void) {

    int vertexA = -2, vertexB = -2, NodesArraySize = 100, startingVertex = -2;
    Nptr* NodesArray = calloc(NodesArraySize, sizeof(Nptr));
    
    while(TRUE) {

        printf("Enter two vertices to create an edge (Va, Vb separated by space, type -1 -1 to end input)\n> ");
        scanf("%d %d", &vertexA, &vertexB);
        if(vertexA == -1 && vertexB == -1) break;
        
        int biggerVertex = max(vertexA, vertexB);
        if(biggerVertex >= NodesArraySize) {
            int tmp = NodesArraySize;
            NodesArraySize = biggerVertex * 2;
            NodesArray = realloc(NodesArray, NodesArraySize * sizeof(Nptr));
            for(int i = tmp;i < NodesArraySize;i++) NodesArray[i] = NULL;
        }

        if(!NodesArray[vertexA]) NodesArray[vertexA] = newNode(vertexA);
        if(!NodesArray[vertexB]) NodesArray[vertexB] = newNode(vertexB);

        addPath(NodesArray[vertexA], NodesArray[vertexB]);

    }

    while(TRUE) {
        
        printf("Enter the starting vertex to do BFS & DFS (-1 to end the program)\n> ");
        scanf("%d", &startingVertex);
        if(startingVertex == QUIT_MODE) break;
        printf("BFS: "); BFS(NodesArray[startingVertex]); printf("\n");
        reset(NodesArray[startingVertex]);
        printf("DFS: "); DFS(NodesArray[startingVertex]); printf("\n");
        reset(NodesArray[startingVertex]);

    }

    printf("Program Terminated");

    return 0;

}

Nptr newNode(int value) {

    Nptr node = (Nptr) malloc(sizeof(Node));

    node->value = value;
    node->isVisited = FALSE;
    node->pathsAccount = 0;
    node->maxPathsAccount = 1;
    node->paths = (Nptr* ) malloc(sizeof(Nptr));

    return node;

}

void addPath(Nptr node, Nptr neighbor) {

    if(node->pathsAccount == node->maxPathsAccount) {
        node->maxPathsAccount *= 2;
        node->paths = (Nptr* ) realloc(node->paths, node->maxPathsAccount * sizeof(Nptr));
    }
    if(neighbor->pathsAccount == neighbor->maxPathsAccount) {
        neighbor->maxPathsAccount *= 2;
        neighbor->paths = (Nptr* ) realloc(neighbor->paths, neighbor->maxPathsAccount * sizeof(Nptr));
    }
    node->paths[node->pathsAccount++] = neighbor;
    neighbor->paths[neighbor->pathsAccount++] = node;

}

Queue* createQueue() {

    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->front = NULL; queue->rear = NULL;
    return queue;

}

BOOL isEmptyQ(Queue* queue) { if(!queue->front) return TRUE; return FALSE; }

void AddQ(Queue* queue, Nptr value) {

    QueueNodePtr node = (QueueNodePtr ) malloc(sizeof(QueueNode));
    node->value = value;
    node->next = NULL;

    if(!isEmptyQ(queue)) {
        queue->rear->next = node;
        queue->rear = node; 
    }
    else {
        queue->front = node;
        queue->rear = node;
    }

}

Nptr PopQ(Queue* queue) {

    Nptr value;

    if(!isEmptyQ(queue)) {

        QueueNodePtr tmp = queue->front;

        value = queue->front->value;
        if(queue->front == queue->rear) { queue->front = NULL; queue->rear = NULL; }
        else queue->front = queue->front->next;

        free(tmp);
        return value;

    }
    else return NULL;

}

void DFS(Nptr node) {

    node->isVisited = TRUE;
    printf("%d ", node->value);
    for(int i = 0;i < node->pathsAccount;i++) if(!node->paths[i]->isVisited) DFS(node->paths[i]);

}

void BFS(Nptr startingNode) {

    Queue* queue = createQueue();

    startingNode->isVisited = TRUE;
    printf("%d ", startingNode->value);
    for(int i = 0;i < startingNode->pathsAccount;i++) { AddQ(queue, startingNode->paths[i]); startingNode->paths[i]->isVisited = TRUE; }

    while(!isEmptyQ(queue)) {

        Nptr node = PopQ(queue);
        printf("%d ", node->value);
        for(int i = 0;i < node->pathsAccount;i++) if(!node->paths[i]->isVisited) { AddQ(queue, node->paths[i]); node->paths[i]->isVisited = TRUE; }

    }

}

int max(int a, int b) { if(a >= b) return a; return b; }

void reset(Nptr node) {

    node->isVisited = FALSE;
    for(int i = 0;i < node->pathsAccount;i++) if(node->paths[i]->isVisited) reset(node->paths[i]);

}