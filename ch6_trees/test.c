#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status ;
typedef char ElemType;

// 1. struct of the binary tree
typedef struct BiNode {
  ElemType data;
  struct BiNode *lchild, *rchild;
} BiNode, *BiTree;


// call: InitTree(&T);
Status InitTree(BiTree *T) {
  // just to null
  *T = NULL;
  return OK;
}
// DestroyTree(&T)
Status DestroyTree(BiTree *T){
  if(*T == NULL) return;
  else {
    DestroyTree(&(*T)->lchild);
    DestroyTree(&(*T)->rchild);
    free(*T);
    *T = NULL;
  }
}

// CreateTree(&T, definition)
Status CreateTree(BiTree *T, ElemType data){
  *T = (BiTree)malloc(sizeof(BiNode));
  if(!(*T)) return ERROR;
  else {
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    (*T)->data = data;
  }
  return OK;
}

// ClearTree(&T)
Status ClearTree(BiTree *T){
  DestroyTree(T); // ? or (*T);
}

// TreeEmpty(T)
Status TreeEmpty(BiTree T){
  return (T == NULL) // not *T.. i guess
}

// TreeDepth(T)
int TreeDepth(BiTree T){
  if(T == NULL) return 0;
  else{
    int l = TreeDepth(T->lchild);
    int r = TreeDepth(T->rchild);
    return (l > r ? l : r) + 1;
  }
}
// Root(T);
BiTree* Root(BiTree T){
  return &T;
}

// Value(T, cur_e)  ifnd? or what for this function? or put new one?
BiTree Value(BiTree T, ElemType cur_e){
  if(T == NULL) return NULL;
  if(T->data == cur_e) return T;
  else{
    // actually, we can just check if current is ok;
    if(T->lchild && T->lchild->data == cur_e) return T->lchild; 
    if(T->rchild && T->rchild->data == cur_e) return T->rchild; 
    Value(T->lchild, cur_e);
    Value(T->rchild, cur_e);
  }
}

// Assign(T, cur_e, value)
BiTree Assign(BiTree T, ElemType cur_e, ElemType value){
  if(T == NULL) return ERROR;
  else {
    if(T->lchild && T->lchild->data == cur_e) return T->lchild->data = value; 
    if(T->rchild && T->rchild->data == cur_e) return T->rchild->data = value; 
    Assign(T->lchild, cur_e, value);
    Assign(T->rchild, cur_e, value);
  }

}