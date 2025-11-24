#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType data[MAXSIZE];
    int top;                // 栈顶指针（指向栈顶元素），空栈时 top = -1
} SqStack;

// 1. 初始化栈
Status InitStack(SqStack *S) {
    S->top = -1;
    return OK;
}

// 2. 判空
Status StackEmpty(SqStack S) {
    return (S.top == -1) ? TRUE : FALSE;
}

// 3. 入栈
Status Push(SqStack *S, ElemType e) {
    if (S->top == MAXSIZE - 1) return ERROR;  // 栈满
    S->top++;
    S->data[S->top] = e;
    // 也可以写成： S->data[++S->top] = e;
    return OK;
}

// 4. 出栈 OK
Status Pop(SqStack *S, ElemType *e) {
    if (S->top == -1) return ERROR;           // 栈空
    *e = S->data[S->top];
    S->top--;
    // 也可以写成： *e = S->data[S->top--];
    return OK;
}

// 5. 取栈顶元素（不删除）
Status GetTop(SqStack S, ElemType *e) {
    if (S.top == -1) return ERROR;
    *e = S.data[S.top];
    return OK;
}

// 6. 清空栈（考试一般不要求写DestroyStack，因为是静态的）
void ClearStack(SqStack *S) {
    S->top = -1;
}