// 4. trees

// 1. 二叉树
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// Основные операции, которые ОБЯЗАТЕЛЬНО спрашивают:
Status InitBiTree(BiTree *T);                    // 初始化
Status DestroyBiTree(BiTree *T);                 // 销毁
Status CreateBiTree(BiTree *T);                  // 按前序建树（输入格式: ABD##E#C##）
Status ClearBiTree(BiTree *T);                   // 清空
Status BiTreeEmpty(BiTree T);                    // 判空
int BiTreeDepth(BiTree T);                       // 求深度（高度）
BiTNode *Root(BiTree T);                         // 返回根结点
ElemType Value(BiTNode *p);                      // 返回结点值
Status Assign(BiTNode *p, ElemType value);       // 给结点赋值
BiTNode *Parent(BiTree T, ElemType e);           // 找双亲
BiTNode *LeftChild(BiTree T, ElemType e);        // 左孩子
BiTNode *RightChild(BiTree T, ElemType e);       // 右孩子
BiTNode *LeftSibling(BiTree T, ElemType e);      // 左兄弟
BiTNode *RightSibling(BiTree T, ElemType e);     // 右兄弟
Status InsertChild(BiTree p, int LR, BiTree c);  // 插入子树（LR=0左，1右）
Status DeleteChild(BiTree p, int LR);            // 删除左/右子树

// Три обхода — 100% будут на экзамене:
void PreOrderTraverse(BiTree T, void (*visit)(ElemType));
void InOrderTraverse(BiTree T, void (*visit)(ElemType));
void PostOrderTraverse(BiTree T, void (*visit)(ElemType));
void LevelOrderTraverse(BiTree T, void (*visit)(ElemType));  // 层序



// 2. 线索二叉树
typedef enum {Link, Thread} PointerTag;   // Link=0指针, Thread=1线索

typedef struct BiThrNode {
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag, rtag;
} BiThrNode, *BiThrTree;

// Самые частые функции:
Status InOrderThreading(BiThrTree *Thrt, BiTree T);  // 中序线索化（最经典）
void InOrderTraverse_Thr(BiThrTree T, void (*visit)(ElemType)); // 用线索遍历

// 3. 树（普通树)
#define MAX_TREE_SIZE 100
typedef struct PTNode {
    ElemType data;
    int parent;                 // 父结点位置（-1表示根）
} PTNode;

typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int r;      // 根的位置
    int n;      // 结点数
} PTree;

// Часто просят:
int Parent(PTree T, int i);
int LeftChild(PTree T, int i);
int RightSibling(PTree T, int i);

// 4. 二叉搜索树
Status SearchBST(BiTree T, ElemType key, BiTree f, BiTree *p);
Status InsertBST(BiTree *T, ElemType e);
Status DeleteBST(BiTree *T, ElemType key);


// 5. 平衡二叉树
// В узле добавляются:
int bf;                     // balance factor
BiTree avl_insert(BiTree T, ElemType e, int *taller);
void R_Rotate(BiTree *p);
void L_Rotate(BiTree *p);
void LeftBalance(BiTree *T);
void RightBalance(BiTree *T);

// 6. 哈夫曼树 Huffman Tree

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n);
void Select(HuffmanTree HT, int n, int *s1, int *s2);   // 选两个最小的