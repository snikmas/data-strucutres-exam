// 4. trees

// 1. 二叉树
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

InitTree(&T)
DestroyTree(&T)
CreateTree(&T, definition)
ClearTree(&T)
TreeEmpty(T)
TreeDepth(T)
Root(T)
Value(T, cur_e)
Assign(T, cur_e, value)
Parent(T, cur_e)
LeftChild(T, cur_e)
RightSibling(T, cur_e)
InsertChild(&T, p, i, c)
DeleteChild(&T, p, i)
TraverseTree(T, visit)
