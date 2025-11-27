#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
typedef int Status;
typedef int ElemType;

typedef struct Node {
    ElemType data;
    struct Node *next;
} LNode, *LinkList;        // LinkList = указатель на узел (часто это голова)

// 1. 初始化（带头结点）—— 99% экзаменов требуют именно этот вариант
Status InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode));   // 创建头结点
    if (!(*L)) return ERROR;
    (*L)->next = NULL;                      // 头结点的next指向空
    return OK;
}

// 2. 销毁链表
Status DestroyList(LinkList *L) {
        // *L IS A POINTER, NOT IS A NODE
    LinkList p;
    while (*L) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
    return OK;
}

// 3. 清空链表（保留头结点）
Status ClearList(LinkList L) {
    LinkList p = L->next, q;
    L->next = NULL;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}

// 4. 判断是否为空
Status ListEmpty(LinkList L) {
    return (L->next == NULL) ? OK : ERROR;
}

// 5. 求表长
int ListLength(LinkList L) {
    int len = 0;
    LinkList p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 6. 取第i个元素（i从1开始）
Status GetElem(LinkList L, int i, ElemType *e) {
    LinkList p = L->next;
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
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType,ElemType)) {
    LinkList p = L->next;
    int i = 1;
    while (p && !compare(p->data, e)) {
        p = p->next;
        i++;
    }
    if (p) return i;
    return 0;
}

// 8. 插入（在第i个位置之前插入，i=1表示插在第一个数据节点前）
Status ListInsert(LinkList L, int i, ElemType e) {
    LinkList p = L, s;
    int j = 0;
    while (p && j < i-1) {      // 找第i-1个节点
        p = p->next;
        j++;
    }
    if (!p || j > i-1) return ERROR;
    
    s = (LinkList)malloc(sizeof(LNode));
    if (!s) return ERROR;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 9. 删除第i个元素并用e返回其值
Status ListDelete(LinkList L, int i, ElemType *e) {
    LinkList p = L, q;
    int j = 0;
    while (p->next && j < i-1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i-1) return ERROR;
    
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

// 10. 求前驱
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e) {
    LinkList p = L->next, q = p ? p->next : NULL;
    while (q) {
        if (q->data == cur_e) {
            *pre_e = p->data;
            return OK;
        }
        p = q;
        q = q->next;
    }
    return ERROR;
}

// 11. 求后继
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
    LinkList p = L->next;
    while (p && p->next) {
        if (p->data == cur_e) {
            *next_e = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

// 12. 遍历
void ListTraverse(LinkList L, void (*visit)(ElemType)) {
    LinkList p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}