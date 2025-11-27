#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef int Status ;
typedef char ElemType;

// 1. struct of the binary tree
typedef struct BiNode {
  ElemType data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


Status InitBiTree(BiTree *T){
  *T = NULL;
}

Status DestroyBiTree(BiTree *T){
  if(*T){
    DestroyBiTree(&(*T)->lchild);
    DestroyBiTree(&(*T)->rchild);
    free(*T);
    *T = NULL;
  }
  return OK;
}

void CreateBiTree(BiTree *T){
  ElemType ch;
  scanf("%c", &ch);
  if(ch == '#') *T = NULL;
  else {
    *T = (BiTree)malloc(sizeof(BiNode));
    if(!*T) exit(ERROR);
    (*T)->data = ch;
    CreateBiTree(&(*T)->lchild);
    CreateBiTree(&(*T)->rchild);
  }
}

Status ClearBiTree(BiTree *T){
  DestroyBiTree(T);
  return OK;
}
