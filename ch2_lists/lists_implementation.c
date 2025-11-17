#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define OK      1
#define ERROR   0
#define OK 1
#define ERROR 0
typedef int Status;
typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType data[MAXSIZE];     // 静态分配（最常见考试版本）
    int length;                 // 当前长度
} SqList;

// 1. 初始化
Status InitList(SqList *L) {
    L->length = 0;
    return OK;
}

// 2. 销毁（静态分配其实不用free，但考试要写）
Status DestroyList(SqList *L) {
    L->length = 0;              // 静态版只需置0即可
    return OK;
}

// 3. 清空
Status ClearList(SqList *L) {
    L->length = 0;
    return OK;
}

// 4. 判断是否为空
Status ListEmpty(SqList L) {
    return (L.length == 0) ? OK : ERROR;
}

// 5. 求线性表长度
int ListLength(SqList L) {
    return L.length;
}

// 6. 取第i个元素（i从1开始！）
Status GetElem(SqList L, int i, ElemType *e) {
    if (i < 1 || i > L.length) return ERROR;
    *e = L.data[i-1];
    return OK;
}

// 7. 查找第一个满足compare()的元素位置（从1开始计数）
int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    for (int i = 0; i < L.length; i++) {
        if (compare(L.data[i], e)) {
            return i + 1;       // 返回逻辑位序（1开始）
        }
    }
    return 0;                   // 未找到返回0
}

// 8. 插入（在第i个位置之前插入）
Status ListInsert(SqList *L, int i, ElemType e) {
    if (L->length >= MAXSIZE) return ERROR;   // 存储空间已满
    if (i < 1 || i > L->length + 1) return ERROR;
    
    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}

// 9. 删除第i个元素并用e返回其值
Status ListDelete(SqList *L, int i, ElemType *e) {
    if (L->length == 0) return ERROR;
    if (i < 1 || i > L->length) return ERROR;
    
    *e = L->data[i-1];
    for (int j = i; j < L->length; j++) {
        L->data[j-1] = L->data[j];
    }
    L->length--;
    return OK;
}

// 10. 求前驱
Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e) {
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] == cur_e) {
            *pre_e = L.data[i-1];
            return OK;
        }
    }
    return ERROR;
}

// 11. 求后继
Status NextElem(SqList L, ElemType cur_e, ElemType *next_e) {
    for (int i = 0; i < L.length-1; i++) {
        if (L.data[i] == cur_e) {
            *next_e = L.data[i+1];
            return OK;
        }
    }
    return ERROR;
}

// 12. 遍历
void ListTraverse(SqList L, void (*visit)(ElemType)) {
    for (int i = 0; i < L.length; i++) {
        visit(L.data[i]);
    }
    printf("\n");
}

// 示例visit函数
void print(ElemType e) {
    printf("%d ", e);
}