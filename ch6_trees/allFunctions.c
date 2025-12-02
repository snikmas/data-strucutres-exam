#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
typedef char ElemType;

/* ==================== 孩子兄弟表示法（ именно то, что на твоём слайде!）==================== */
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild;   // 指向长子（第一个孩子）
    struct CSNode *nextsibling;  // 指向右兄弟
} CSNode, *Tree;

/* 基本操作 — точно как на слайде! */
Status InitTree(Tree *T) {
    *T = NULL;
    return OK;
}

Status DestroyTree(Tree *T) {
    if (*T) {
        DestroyTree(&(*T)->firstchild);      // 先毁掉所有子树
        DestroyTree(&(*T)->nextsibling);     // 再毁掉所有兄弟
        free(*T);
        *T = NULL;
    }
    return OK;
}

/* CreateTree(&T, definition) — рекурсивное создание по префиксной записи */
void CreateTree(Tree *T) {
    ElemType ch;
    scanf("%c", &ch);
    if (ch == '#') *T = NULL;
    else {
        *T = (CSNode*)malloc(sizeof(CSNode));
        (*T)->data = ch;
        CreateTree(&(*T)->firstchild);   // 创建长子子树
        CreateTree(&(*T)->nextsibling);  // 创建右兄弟
    }
}

/* 示例输入: A B D # # E # # C F # # # #   → 树形如：
       A
      / \
     B   C
    / \   \
   D   E   F
*/

Status ClearTree(Tree *T) { return DestroyTree(T); }

Status TreeEmpty(Tree T) { return T == NULL ? OK : ERROR; }

int TreeDepth(Tree T) {
    if (!T) return 0;
    int childDepth = TreeDepth(T->firstchild);
    int sibDepth   = TreeDepth(T->nextsibling);
    return (childDepth > sibDepth ? childDepth : sibDepth) + 1;
}

Tree Root(Tree T) { return T; }

ElemType Value(Tree T, Tree cur_e) {
    return cur_e ? cur_e->data : '#';
}

Status Assign(Tree T, Tree cur_e, ElemType value) {
    if (cur_e) cur_e->data = value;
    return OK;
}

/* 找双亲 — рекурсия по всему дереву */
Tree Parent(Tree T, Tree cur_e) {
    if (!T || !cur_e || T == cur_e) return NULL;
    
    // 检查当前结点的长子链
    Tree p = T->firstchild;
    while (p) {
        if (p == cur_e) return T;
        Tree found = Parent(p, cur_e);
        if (found) return found;
        p = p->nextsibling;
    }
    return NULL;
}

/* 长子 */
Tree LeftChild(Tree T, Tree cur_e) {
    if (!cur_e) return NULL;
    return cur_e->firstchild;
}

/* 右兄弟 */
Tree RightSibling(Tree T, Tree cur_e) {
    if (!cur_e) return NULL;
    return cur_e->nextsibling;
}

/* 插入第i个孩子（作为p的第i个孩子插入整棵子树c）*/
Status InsertChild(Tree *T, Tree p, int i, Tree c) {
    if (!p || i < 1 || !c) return ERROR;
    
    Tree q = p->firstchild;
    if (i == 1) {                       // 插在最前面
        c->nextsibling = q;
        p->firstchild = c;
    } else {
        int k = 1;
        while (q && k < i-1) {
            q = q->nextsibling;
            k++;
        }
        if (!q) return ERROR;
        c->nextsibling = q->nextsibling;
        q->nextsibling = c;
    }
    return OK;
}

/* 删除p的第i个孩子子树 */
Status DeleteChild(Tree *T, Tree p, int i) {
    if (!p || i < 1) return ERROR;
    
    Tree q = p->firstchild;
    if (i == 1) {
        p->firstchild = q->nextsibling;
    } else {
        int k = 1;
        Tree prev = NULL;
        while (q && k < i) {
            prev = q;
            q = q->nextsibling;
            k++;
        }
        if (!q) return ERROR;
        prev->nextsibling = q->nextsibling;
    }
    DestroyTree(&q);        // 递归销毁被删的子树
    return OK;
}

/* 先根遍历 */
void TraverseTree(Tree T, void (*visit)(ElemType)) {
    if (T) {
        visit(T->data);
        TraverseTree(T->firstchild, visit);
        TraverseTree(T->nextsibling, visit);
    }
}

void print(ElemType c) { printf("%c ", c); }    

// BINARY TREE
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
typedef char ElemType;

/* ==================== 二叉树的抽象数据类型定义 ==================== */
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;           // BiTree = указатель на узел (корень)

/* ====================== 基本操作实现 ====================== */

/* 1. 初始化 */
Status InitBiTree(BiTree *T) {
    *T = NULL;
    return OK;
}

/* 2. 销毁二叉树 */
Status DestroyBiTree(BiTree *T) {
    if (*T) {
        DestroyBiTree(&(*T)->lchild);
        DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
    return OK;
}

/* 3. 按前序序列创建二叉树（#表示空）—— 100% будет на экзамене */
void CreateBiTree(BiTree *T) {
    ElemType ch;
    scanf("%c", &ch);
    if (ch == '#') *T = NULL;
    else {
        *T = (BiTNode*)malloc(sizeof(BiTNode));
        if (!*T) exit(ERROR);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

/* 4. 插入子树：将c作为p的第LR个孩子（LR=0左，1右） */
Status InsertChild(BiTree p, int LR, BiTree c) {
    if (!p || !c) return ERROR;
    if (LR == 0) {                     // 插入左子树
        c->rchild = p->lchild;         // c的右孩子指向原来p的左子树
        p->lchild = c;
    } else {                           // 插入右子树
        c->rchild = p->rchild;
        p->rchild = c;
    }
    return OK;
}

/* 5. 删除p的第LR个孩子子树 */
Status DeleteChild(BiTree p, int LR) {
    if (!p) return ERROR;
    if (LR == 0) DestroyBiTree(&(p->lchild));
    else         DestroyBiTree(&(p->rchild));
    return OK;
}

/* 6. 清空 */
Status ClearBiTree(BiTree *T) {
    return DestroyBiTree(T);
}

/* 7. 判断空 */
Status BiTreeEmpty(BiTree T) {
    return T == NULL ? OK : ERROR;
}

/* 8. 求深度 */
int BiTreeDepth(BiTree T) {
    if (!T) return 0;
    int l = BiTreeDepth(T->lchild);
    int r = BiTreeDepth(T->rchild);
    return (l > r ? l : r) + 1;
}

/* 9. 返回根结点 */
BiTNode *Root(BiTree T) {
    return T;
}

/* 10. 返回结点值（e为结点指针） */
ElemType Value(BiTree e) {
    return e ? e->data : '#';
}

/* 11. 给结点赋值 */
Status Assign(BiTree e, ElemType value) {
    if (e) e->data = value;
    return OK;
}

/* 12. 找双亲 */
BiTNode *Parent(BiTree T, BiTree e) {
    if (!T || T == e) return NULL;
    if (T->lchild == e || T->rchild == e) return T;
    BiTNode *found = Parent(T->lchild, e);
    if (found) return found;
    return Parent(T->rchild, e);
}

/* 13. 左孩子 */
BiTNode *LeftChild(BiTree T, BiTree e) {
    return (e && e->lchild) ? e->lchild : NULL;
}

/* 14. 右兄弟（二叉树中右兄弟就是右孩子） */
BiTNode *RightSibling(BiTree T, BiTree e) {
    if (!e) return NULL;
    BiTNode *p = Parent(T, e);
    if (p && p->lchild == e && p->rchild) return p->rchild;
    return NULL;
}

/* 15. 四种遍历（100% будут на экзамене） */
void PreOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
}

void InOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
    }
}

void PostOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T->data);
    }
}

void LevelOrderTraverse(BiTree T, void (*visit)(ElemType)) {
    if (!T) return;
    BiTree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while (front < rear) {
        BiTree p = queue[front++];
        visit(p->data);
        if (p->lchild) queue[rear++] = p->lchild;
        if (p->rchild) queue[rear++] = p->rchild;
    }
}

/* 辅助打印函数 */
void Print(ElemType e) { printf("%c ", e); }