typedef struct {
    ElemType data[MAXSIZE];
    int front;      // 头指针，指向队头元素
    int rear;       // 尾指针，指向队尾元素的下一个位置
} SqQueue;

// 1. 初始化队列
Status InitQueue(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

// 2. 判空
Status QueueEmpty(SqQueue Q) {
    return (Q.front == Q.rear) ? TRUE : FALSE;
}

// 3. 入队
Status EnQueue(SqQueue *Q, ElemType e) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) return ERROR;  // 队满
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

// 4. 出队
Status DeQueue(SqQueue *Q, ElemType *e) {
    if (Q->front == Q->rear) return ERROR;                 // 队空
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

// 5. 取队头元素
Status GetHead(SqQueue Q, ElemType *e) {
    if (Q.front == Q.rear) return ERROR;
    *e = Q.data[Q.front];
    return OK;
}

// 6. 队列长度
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}