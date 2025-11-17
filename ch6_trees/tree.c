typedef char ElemType;

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 前序 / 中序 / 后序 遍历（递归）——考试必背三函数
void PreOrder(BiTree T) {
    if (T) {
        visit(T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {
    if (T) {
        InOrder(T->lchild);
        visit(T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T->data);
    }
}

// 层序遍历（需要队列）——考试 90% 出现
void LevelOrder(BiTree T) {
    SqQueue Q; InitQueue(&Q);
    BiTree p;

    if (T) EnQueue(&Q, T);

    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &p);
        visit(p->data);
        if (p->lchild) EnQueue(&Q, p->lchild);
        if (p->rchild) EnQueue(&Q, p->rchild);
    }
}

// 二叉树创建（根据前序+空节点）——考试超高频
// 输入： A B # # C D # # E # #
void CreateBiTree(BiTree *T) {
    char ch;
    scanf(" %c", &ch);

    if (ch == '#') *T = NULL;
    else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}

// 求二叉树深度（高度）——100% 考试题
int TreeDepth(BiTree T) {
    if (!T) return 0;
    int l = TreeDepth(T->lchild);
    int r = TreeDepth(T->rchild);
    return (l > r ? l : r) + 1;
}

// 统计节点数 / 叶子数
// 总结点数
int CountNodes(BiTree T) {
    if (!T) return 0;
    return CountNodes(T->lchild) + CountNodes(T->rchild) + 1;
}

// 叶子节点数
int CountLeaves(BiTree T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return CountLeaves(T->lchild) + CountLeaves(T->rchild);
}

// 7. 求第j层节点数
int CountLevelK(BiTree T, int k) {
    if (!T) return 0;
    if (k == 1) return 1;
    return CountLevelK(T->lchild, k-1) + CountLevelK(T->rchild, k-1);
}

// 根据前序 + 中序构建二叉树
BiTree Build(char *pre, char *in, int n) {
    if (n <= 0) return NULL;

    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = pre[0];

    int k = 0;
    while (in[k] != pre[0]) k++;

    T->lchild = Build(pre+1, in, k);
    T->rchild = Build(pre+k+1, in+k+1, n-k-1);

    return T;
}

// 9. 二叉树拷贝
BiTree Copy(BiTree T) {
    if (!T) return NULL;
    BiTree p = (BiTree)malloc(sizeof(BiTNode));
    p->data = T->data;
    p->lchild = Copy(T->lchild);
    p->rchild = Copy(T->rchild);
    return p;
}

// 10. 判断是否同构 (Isomorphic)
int Isomorphic(BiTree T1, BiTree T2) {
    if (!T1 && !T2) return 1;
    if (!T1 || !T2) return 0;
    if (T1->data != T2->data) return 0;

    return (Isomorphic(T1->lchild, T2->lchild) &&
            Isomorphic(T1->rchild, T2->rchild)) ||
           (Isomorphic(T1->lchild, T2->rchild) &&
            Isomorphic(T1->rchild, T2->lchild));
}


