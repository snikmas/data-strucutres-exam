#include <stdio.h>
#include <stdlib.h>

// copy a tree;

typedef struct TreeNode {
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void addNode(TreeNode **root, int data){
  if(*root == NULL){
    // insert it here;
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    *root = newNode;
    return;
  }

  if((*root)->data > data){
    // go to the left;
    addNode(&((*root)->left), data);
    return;
  } else {
    addNode(&((*root)->right), data);
    return;

  }

}

TreeNode *copyNode(TreeNode *root){
  if(root== NULL) return NULL;
  TreeNode *newNode = malloc(sizeof(TreeNode));
  newNode->data = root->data;
  newNode->left = copyNode(root->left);
  newNode->right = copyNode(root->right);
}

// 0 - TRUE; 1 - false
int isEqual(TreeNode *root1, TreeNode *root2){
  if(root1 == NULL && root2 == NULL) return 0;
  else if(root1 == NULL || root2 = NULL) return 1;

  if(*(root1)->data != *(root2)->data){
    return 1;
  }
  int left = isEqual(&(root1)->left, &(root2)->left);
  int right = isEqual(&(root1)->right, &(root2)->right);
  return left + right;
}

int main(void){

  TreeNode *root1 = NULL;
  TreeNode *root2 = NULL;
  TreeNode *root3 = NULL;
  addNode(&root1, 12);
  addNode(&root1, 19);
  addNode(&root1, 24);
  addNode(&root1, 5);
  addNode(&root1, 10);

  root2 = copyNode(root1);

  addNode(&root3, 12);
  addNode(&root3, 14);
  addNode(&root3, 24);
  addNode(&root3, 5);
  addNode(&root3, 10);

  int isEqualResp = isEqual(&root1, &root3);
  if(isEqualResp == 1){
    printf("Is not equal");
  } else printf("Is equal");

  return 0;
}