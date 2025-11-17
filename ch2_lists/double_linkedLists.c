#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
typedef int Status;
typedef int ElemType;

typedef struct DuLNode {
    ElemType data;
    struct DuLNode *prior;   // 指向前驱
    struct DuLNode *next;    // 指向后继
} DuLNode, *DuLinkList;      // DuLinkList = указатель на узел (обычно голова)

// 1. 初始化（带头结点）—— 99% экзаменов требуют именно этот
Status InitList(DuLinkList *L) {
    *L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!(*L)) return ERROR;
    (*L)->next = (*L)->prior = NULL;   // 头结点的 next 和 prior 都指向 NULL
    return OK;
}

// 2. 销毁链表
Status DestroyList(DuLinkList *L) {
    DuLinkList p;
    while (*L) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    return OK;
}

// 3. 清空链表（保留头结点）
Status ClearList(DuLinkList L) {
    DuLinkList p = L->next, q;
    L->next = L->prior = NULL;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}

// 4. 判断是否为空
Status ListEmpty(DuLinkList L) {
    return (L->next == NULL) ? OK : ERROR;
}

// 5. 求表长
int ListLength(DuLinkList L) {
    int len = 0;
    DuLinkList p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 6. 取第i个元素（i从1开始）
Status GetElem(DuLinkList L, int i, ElemType *e) {
    DuLinkList p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    *e = p->data;
    return OK;
}

// 7. 按值查找（返回逻辑位序1~n，找不到返回0）
int LocateElem(DuLinkList L, ElemType e, Status (*compare)(ElemType,ElemType)) {
    DuLinkList p = L->next;
    int i = 1;
    while (p && !compare(p->data, e)) {
        p = p->next;
        i++;
    }
    return p ? i : 0;
}

// 8. 在第i个位置之前插入（i=1表示插在第一个数据节点前）
Status ListInsert(DuLinkList L, int i, ElemType e) {
    DuLinkList p = L, s;
    int j = 0;
    while (p && j < i-1) {      // 找到第i-1个节点（p指向要插入位置的前一个）
        p = p->next;
        j++;
    }
    if (!p || j > i-1) return ERROR;

    s = (DuLinkList)malloc(sizeof(DuLNode));
    if (!s) return ERROR;
    s->data = e;

    // 双向链表插入四步法（经典！）
    s->prior = p;
    s->next = p->next;
    if (p->next) p->next->prior = s;   // 如果不是插在末尾
    p->next = s;

    return OK;
}

// 9. 删除第i个元素并用e返回其值
Status ListDelete(DuLinkList L, int i, ElemType *e) {
    DuLinkList p = L;
    int j = 0;
    while (p->next && j < i-1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i-1) return ERROR;

    DuLinkList q = p->next;
    *e = q->data;

    // 双向链表删除三步法（经典！）
    p->next = q->next;
    if (q->next) q->next->prior = p;
    free(q);

    return OK;
}

// 10. 遍历（从前向后）
void ListTraverse(DuLinkList L, void (*visit)(ElemType)) {
    DuLinkList p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

// 11. 反向遍历（从后向前）—— 有时候也考
void ListTraverseBack(DuLinkList L, void (*visit)(ElemType)) {
    DuLinkList p = L;
    while (p->next) p = p->next;   // 找到最后一个节点
    while (p != L) {
        visit(p->data);
        p = p->prior;
    }
    printf("\n");
}