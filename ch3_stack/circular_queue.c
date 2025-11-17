typedef struct {
    ElemType data[MAXSIZE];
    int front;     // points to the head element
    int rear;      // points to the next position after the tail
} SqQueue;

Status InitQueue(SqQueue *Q)  { Q->front = Q->rear = 0; return OK; }
Status EnQueue(SqQueue *Q, ElemType e) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) return ERROR;  // full ← circular judgment
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}
Status DeQueue(SqQueue *Q, ElemType *e) {
    if (Q->front == Q->rear) return ERROR;                 // empty
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}