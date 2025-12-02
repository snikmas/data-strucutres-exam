// 1. try to write a tree
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int ElemType;
typedef struct TreeNode {
  ElemType data;
  struct TreeNode *leftCh;
  struct TreeNode *rightCh;
} TreeNode;


TreeNode *root;
void initTree(){
  root = NULL;
};

TreeNode *getNewNode(int data){
  TreeNode *new = (TreeNode*) malloc(sizeof(TreeNode));
  if(!new)return NULL;
  new->data = data;
  new->leftCh = NULL; 
  new->rightCh = NULL; 
  return new;
}

TreeNode *findChildData(TreeNode *cur, int data){
  if(cur == NULL) return NULL; // no results;
  if(cur->leftCh != NULL && cur->leftCh->data == data || cur->rightCh != NULL && cur->rightCh->data == data){
    return cur;
  }


  TreeNode *res = findChildData(cur->leftCh, data); 
  if(res != NULL) return res;
  return findChildData(cur->rightCh, data); 

  
}

TreeNode *insertData(TreeNode *node, int data){

  if(node == NULL){
    return getNewNode(data);
  }

  if (data <= node->data)
    node->leftCh = insertData(node->leftCh, data);
  else
    node->rightCh = insertData(node->rightCh, data);

  return node;
}


void print(TreeNode *node){
  printf("Data: %d\n", node->data);
}

void preOrderTraverse(TreeNode *cur){
  // NODE -> LEFT -> RIGHT
  if(cur == NULL) return;
  print(cur);
  preOrderTraverse(cur->leftCh);
  preOrderTraverse(cur->rightCh);
}
void inOrderTraverse(TreeNode *cur){
  // LEFT -> NODE -> RIGHT
  if(cur == NULL) return;
  inOrderTraverse(cur->leftCh);
  print(cur);
  inOrderTraverse(cur->rightCh);
}
void postOrderTraverse(TreeNode *cur){
  if(cur == NULL) return;
  postOrderTraverse(cur->rightCh);
  print(cur);
  postOrderTraverse(cur->leftCh);
  // RIGHT
}

void delete(int data){
  if(root == NULL) return;
  
  TreeNode *cur = root;
  TreeNode *parent = findChildData(cur, data);
  if(parent == NULL) return;
  if(parent->leftCh->data == data) {
    cur = parent->leftCh;
  } else if(parent->rightCh->data == data) {
    cur = parent->rightCh;
  } else if(parent == NULL){
    printf("No results in parnt");
    return;
  }
  

  if(cur == NULL) return; // no results
  
  if(cur->leftCh == NULL && cur->rightCh == NULL){
    // no child;

    printf("No child:\n");
    // 1. delete link
    if(parent->leftCh == cur) {
      parent->leftCh = NULL;
    } else {
      parent->rightCh = NULL; 
    }

    free(cur);
    // done
  } else if(cur->rightCh != NULL && cur->leftCh != NULL){
    printf("all childs");
    // find the last element in the cur
    // max in the left side is the rightest
    TreeNode *parentLastNode = cur;
    TreeNode *findLastNode = cur->leftCh;
    while(findLastNode->rightCh){
      parentLastNode = findLastNode;
      findLastNode = findLastNode->rightCh;
    }

    cur->data = findLastNode->data;
    parentLastNode->rightCh = NULL;
    free(findLastNode);

  } else if(cur->rightCh == NULL){
    printf("Left child here:\n");
    
    if(parent->data > data){
      parent->leftCh = cur->leftCh;
    } else {
      parent->rightCh = cur->leftCh;
    }
    free(cur);

  } else if(cur->leftCh == NULL){
    printf("no left ch and right child here:\n");
    if(parent->data > data){
      parent->leftCh = cur->rightCh;
    } else {
      parent->rightCh = cur->rightCh;
    }
    free(cur);
  }
  
  

}

// delete node
// case 1: no child -> just free it
// case 2: 1 child -> parent -> child; free the ndoe
// case 3: 2 childs -> 
// 1 way: take the right child data and put to the current node -> remove the right child data (recursion may happen)
// 2 way: in the left childs, take the last child and put in in the current node and remove the last left child
// i think this way is better cuz what if our childs all have 2 childs? too much to change;

int main(void){
  initTree();
  root = insertData(root, 12);
  root = insertData(root, 5);
  root = insertData(root, 15);
  root = insertData(root, 3);
  root = insertData(root, 7);
  root = insertData(root, 13);
  root = insertData(root, 17);
  
  // depth-first traversal;
  printf("Before:\n");
  preOrderTraverse(root);
  // inOrderTraverse(root);
  // postOrderTraverse(root);
  
  // delete
  delete(17);
  printf("After:\n");
  preOrderTraverse(root);
  return 0;
}