#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
typedef char ElemType;

/* ==================== 1. 二叉树 BiTree ==================== */
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/* 1. 初始化 */
Status InitBiTree(BiTree *T) { *T = NULL; return OK; }

/* 2. 销毁 */
Status DestroyBiTree(BiTree *T) {
    if (*T) {
        DestroyBiTree(&(*T)->lchild);
        DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
    return OK;
}

/* 3. 按前序创建二叉树（#表示空）—— 100% будет на экзамене! */
void CreateBiTree(BiTree *T) {
    ElemType ch;
    scanf("%c", &ch);
    if (ch == '#') *T = NULL;
    else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T) exit(ERROR);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

/* 4. 清空 */
Status ClearBiTree(BiTree *T) {
    DestroyBiTree(T);
    return OK;
}

/* 5. 判空 */
Status BiTreeEmpty(BiTree T) { return T == NULL ? OK : ERROR; }

/* 6. 深度 */
int BiTreeDepth(BiTree T) {
    if (!T) return 0;
    int l = BiTreeDepth(T->lchild);
    int r = BiTreeDepth(T->rchild);
    return (l > r ? l : r) + 1;
}

/* 7. 返回根 */
BiTNode *Root(BiTree T) { return T; }

/* 8. 结点值 */
ElemType Value(BiTNode *p) { return p->data; }

/* 9. 赋值 */
Status Assign(BiTNode *p, ElemType value) { p->data = value; return OK; }

/* 10–13. 找双亲、左孩子、右孩子、兄弟（递归版） */
BiTNode *Parent(BiTree T, ElemType e) {
    if (!T || T->data == e) return NULL;
    if ((T->lchild && T->lchild->data == e) || (T->rchild && T->rchild->data == e))
        return T;
    BiTNode *p = Parent(T->lchild, e);
    if (p) return p;
    return Parent(T->rchild, e);
}

BiTNode *LeftChild(BiTree T, ElemType e) {
    BiTNode *p = T;
    while (p && p->data != e) {
        if (p->lchild && p->lchild->data == e) return p->lchild;
        if (p->rchild && p->rchild->data == e) return p->rchild;
        // 继续往下找
    }
    return NULL;
}
BiTNode *RightChild(BiTree T, ElemType e) { /* аналогично */ return NULL; }
BiTNode *LeftSibling(BiTree T, ElemType e) { /* по родителю */ return NULL; }
BiTNode *RightSibling(BiTree T, ElemType e) { return NULL; }

/* 14–15. 插入/删除子树 */
Status InsertChild(BiTree p, int LR, BiTree c) {
    if (LR == 0) { DestroyBiTree(&p->lchild); p->lchild = c; }
    else { DestroyBiTree(&p->rchild); p->rchild = c; }
    return OK;
}
Status DeleteChild(BiTree p, int LR) {
    if (LR == 0) DestroyBiTree(&p->lchild);
    else DestroyBiTree(&p->rchild);
    return OK;
}

/* 16–19. 四种遍历（100% будут!） */
void PreOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) { visit(T->data); PreOrderTraverse(T->lchild, visit); PreOrderTraverse(T->rchild, visit); }
}
void InOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) { InOrderTraverse(T->lchild, visit); visit(T->data); InOrderTraverse(T->rchild, visit); }
}
void PostOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) { PostOrderTraverse(T->lchild, visit); PostOrderTraverse(T->rchild, visit); visit(T->data); }
}
void LevelOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (!T) return;
    BiTree q[1000]; int f = 0, r = 0;
    q[r++] = T;
    while (f < r) {
        BiTree p = q[f++];
        visit(p->data);
        if (p->lchild) q[r++] = p->lchild;
        if (p->rchild) q[r++] = p->rchild;
    }
}

/* ==================== 2. 线索二叉树 ==================== */
typedef enum {Link, Thread} PointerTag;
typedef struct BiThrNode {
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag, rtag;
} BiThrNode, *BiThrTree;

BiThrTree pre;  // глобальная переменная

void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild);
        if (!p->lchild) { p->ltag = Thread; p->lchild = pre; }
        if (!pre->rchild) { pre->rtag = Thread; pre->rchild = p; }
        pre = p;
        InThreading(p->rchild);
    }
}

Status InOrderThreading(BiThrTree *Thrt, BiTree T) {
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    (*Thrt)->ltag = Link; (*Thrt)->rtag = Thread;
    (*Thrt)->rchild = *Thrt;
    if (!T) (*Thrt)->lchild = *Thrt;
    else {
        (*Thrt)->lchild = T; pre = *Thrt;
        InThreading(T);
        pre->rchild = *Thrt; pre->rtag = Thread;
        (*Thrt)->rchild = pre;
    }
    return OK;
}

void InOrderTraverse_Thr(BiThrTree T, void (*visit)(ElemType)) {
    BiThrTree p = T->lchild;
    while (p != T) {
        while (p->ltag == Link) p = p->lchild;
        visit(p->data);
        while (p->rtag == Thread && p->rchild != T) { p = p->rchild; visit(p->data); }
        p = p->rchild;
    }
}

/* ==================== 3. 普通树（父指针表示） ==================== */
#define MAX_TREE_SIZE 100
typedef struct PTNode {
    ElemType data;
    int parent;
} PTNode;
typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int r, n;
} PTree;

/* ==================== 4. 二叉搜索树 ==================== */
Status SearchBST(BiTree T, ElemType key, BiTree f, BiTree *p) {
    if (!T) { *p = f; return ERROR; }
    if (key == T->data) { *p = T; return OK; }
    else if (key < T->data) return SearchBST(T->lchild, key, T, p);
    else return SearchBST(T->rchild, key, T, p);
}

Status InsertBST(BiTree *T, ElemType e) {
    BiTree p;
    if (!SearchBST(*T, e, NULL, &p)) {
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e; s->lchild = s->rchild = NULL;
        if (!p) *T = s;
        else if (e < p->data) p->lchild = s;
        else p->rchild = s;
        return OK;
    }
    return ERROR;
}

/* ==================== 5. 哈夫曼树 ==================== */
typedef struct {
    int weight, parent, lchild, rchild;
} HTNode, *HuffmanTree;

void Select(HuffmanTree HT, int n, int *s1, int *s2) {
    int m1 = 999999, m2 = 999999;
    *s1 = *s2 = 0;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < m1) { m2 = m1; *s2 = *s1; m1 = HT[i].weight; *s1 = i; }
            else if (HT[i].weight < m2) { m2 = HT[i].weight; *s2 = i; }
        }
    }
}

void HuffmanCoding(HuffmanTree *HT, int *w, int n) {
    int m = 2*n - 1;
    *HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for (int i = 1; i <= n; i++) {
        (*HT)[i].weight = w[i-1];
        (*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = 0;
    }
    for (int i = n+1; i <= m; i++) {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1; (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}