typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;   // 队头指针
    QNode *rear;    // 队尾指针
} LinkQueue;

// 初始化（带头结点） OK
Status InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
    Q->front->next = NULL;
    return OK;
}

// 入队 OK
Status EnQueue(LinkQueue *Q, ElemType e) {
    QNode *p = (QNode*)malloc(sizeof(QNode));
    p->data = e;  p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

// 出队
Status DeQueue(LinkQueue *Q, ElemType *e) {
    if (Q->front == Q->rear) return ERROR;
    QNode *p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) Q->rear = Q->front;  // 如果是最后一个元素
    free(p);
    return OK;
}