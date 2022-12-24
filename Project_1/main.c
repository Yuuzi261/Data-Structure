#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct Node* nptr;
typedef struct Node {
    int value, leftSize;
    struct Node *left, *right;
} Node;

Node* createNode();
void insertNode(nptr*, int);
void inorderTraversal(nptr);
nptr searchNode(nptr, int);
nptr NthKey(nptr, int);

void addNewKey(nptr* );
void queryKey(nptr* );
void findNthKey(nptr* );
void showInorderResult(nptr);
void showModesList();

int main(void) {

    FILE* fp;
    int mode = 0;
    char filename[50];
    Node* root = createNode();

    printf("File name of BST keys value queue: ");
    scanf("%s", filename);
    strcat(filename, ".txt");

    fp = fopen(filename, "r");

    int num;
    printf("INFO: Loading data to program...\n");
    while(fscanf(fp, "%d", &num) != -1) { insertNode(&root, num);}
    fclose(fp);

    printf("\n");
    showInorderResult(root);
    
    while(mode != 6) {
        showModesList();
        printf("\nSelect the mode: ");
        scanf("%d", &mode);
        if(mode == 1) { addNewKey(&root); showInorderResult(root); }
        else if(mode == 3) queryKey(&root);
        else if(mode == 4) findNthKey(&root);
        else if(mode == 5) showInorderResult(root);
    }

    printf("INFO: Terminating program...");

    return 0;

}

Node* createNode() { return NULL; }

void insertNode(nptr* rptr, int value) {

    nptr node = (nptr) malloc(sizeof(Node));
    node->value = value, node->leftSize = 1;
    node->left = NULL, node->right = NULL;

    if(!(*rptr)) (*rptr) = node;
    else {
        nptr* tmp = rptr;
        while(*tmp) {
            if((*tmp)->value > value) { (*tmp)->leftSize++; tmp = &(*tmp)->left; }
            else if((*tmp)->value < value) tmp = &(*tmp)->right;
            else { printf("WARNING: Failed to add data, duplicate value.\n"); return; }
        }
        (*tmp) = node;
        printf("INFO: Added %d successfully.\n", value);
    }

}

void inorderTraversal(nptr node) {

    if(node) {
        inorderTraversal(node->left);
        printf("%d ", node->value);
        inorderTraversal(node->right);
    }

}

nptr searchNode(nptr root, int value) {

    int from;

    while(root) {
        from = root->value;
        if(root->value == value) return root;
        if(root->value > value) {
            root = root->left;
            if(root) printf("(%d) go left -> (%d)\n", from, root->value);
            else printf("(%d) go left -> (NULL)\n", from);
        }
        else {
            root = root->right; 
            if(root) printf("(%d) go right -> (%d)\n", from, root->value);
            else printf("(%d) go right -> (NULL)\n", from); 
        }
    }
    return NULL;

}

nptr NthKey(nptr root, int nth) {

    BOOL isGoRight = FALSE;
    int nowNth = root->leftSize;
    
    while(root) {
        if(nowNth == nth) return root;
        if(nowNth > nth) {
            root = root->left;
            if(isGoRight) nowNth -= root->leftSize;
            else nowNth = root->leftSize;
        }
        else {
            isGoRight = TRUE;
            root = root->right;
            if(root) nowNth += root->leftSize;
            else break;
        }
    }
    return NULL;

}

void addNewKey(nptr* root) {

    int value;

    printf("Enter value: ");
    scanf("%d", &value);
    printf("\n");
    insertNode(root, value);
    printf("\n");

}

void queryKey(nptr* rptr) {

    int value;

    printf("Enter value: ");
    scanf("%d", &value);

    if(searchNode(*rptr, value)) { printf("\nINFO: Find the key(%d).\n\n", value); showInorderResult(*rptr); }
    else printf("\nINFO: CAN'T find the key(%d).\n", value);

}

void findNthKey(nptr* rptr) {

    int nth;
    nptr result;

    printf("Enter nth: ");
    scanf("%d", &nth);
    
    result = NthKey(*rptr, nth);
    if(result) printf("\nINFO: %dth small key in BST is %d.\n", nth, result->value);
    else printf("\nERROR: CAN'T find %dth small key in BST.\n", nth);

}

void showInorderResult(nptr root) {

    printf("Here is the result of inorder traversal on BST:\n");
    inorderTraversal(root);
    printf("\n");

}

void showModesList() {

    printf("\n--------Modes List--------\n");
    printf("(1) Add an new key\n");
    printf("(2) Delete a key\n");
    printf("(3) Query a key\n");
    printf("(4) Query nth small key\n");
    printf("(5) Show the sorted list of keys\n");
    printf("(6) Quit\n");
    printf("--------------------------\n");

}
