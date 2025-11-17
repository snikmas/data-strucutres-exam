#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  struct Node *left;
  struct Node *right;
  int data;
} Node;

Node *root = NULL;

void insert(int userData);
void run();
Node* createNewNode(int userData);
Node* search(Node *cur, int data);

void run(){
  int userData;
  printf("Input Data:\n");
  scanf("%i", &userData);
  root = insert(userData);
}

Node* createNewNode(int userData){
  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = userData;

  return newNode;
}


Node* insert(int userData){
  // 1. if root is null
  Node *cur = root;
  if(root == NULL){
    return root = createNewNode(userData);
  } else if(data < root->data){
    cur->left = insert(root->left, userData);
  } else if(data > root->data){
    cur->right = insert(root->right, userData);
  }

  return cur;
}

int main(void){

  int input = 0;


  printf("1 >> Input Data\n2 >> Exit");
  scanf("%i", &input);
  while(input != 2){
    run();
    scanf("%i", &input);
  }

  return 0;
}
