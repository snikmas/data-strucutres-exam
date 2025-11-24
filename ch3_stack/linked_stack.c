typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

// 初始化 OK
Status InitStack(LinkStack *S) {
    *S = NULL;
    return OK;
}

// 入栈（头插法）OK
Status Push(LinkStack *S, ElemType e) {
    StackNode *p = (StackNode*)malloc(sizeof(StackNode));
    p->data = e;
    p->next = *S;
    *S = p;
    return OK;
}

// 出栈
Status Pop(LinkStack *S, ElemType *e) {
    if (*S == NULL) return ERROR;
    *e = (*S)->data;
    StackNode *p = *S;
    *S = (*S)->next;
    free(p);
    return OK;
}