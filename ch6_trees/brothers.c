// 第二部分：树（普通树）—— 必考：孩子兄弟表示法
// ⭐ 1. 孩子兄弟链表（树的标准存储结构）
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild;  // 第一个孩子
    struct CSNode *nextsibling; // 右兄弟
} CSNode, *CSTree;

// 树的遍历（先根遍历 = 类似前序）
void PreOrder(CSTree T) {
    if (T) {
        visit(T->data);
        PreOrder(T->firstchild);
        PreOrder(T->nextsibling);
    }
}

// 树的高度
int TreeHeight(CSTree T) {
    if (!T) return 0;

    int h_child = 0;
    CSTree c = T->firstchild;
    while (c) {
        int h = TreeHeight(c);
        if (h > h_child) h_child = h;
        c = c->nextsibling;
    }
    return h_child + 1;
}

// 求孩子个数
int ChildCount(CSTree T) {
    int cnt = 0;
    T = T->firstchild;
    while (T) { cnt++; T = T->nextsibling; }
    return cnt;
}

// 兄弟个数
int SiblingCount(CSTree T) {
    int cnt = 0;
    T = T->nextsibling;
    while (T) { cnt++; T = T->nextsibling; }
    return cnt;
}
