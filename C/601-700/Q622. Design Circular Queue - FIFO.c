typedef struct {
    int *data;
    int head, tail, cnt, size;
} MyCircularQueue;
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
  return obj->cnt == 0;
}
bool myCircularQueueIsFull(MyCircularQueue* obj) {
  return obj->cnt == obj->size;
}
void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj);
}
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* q = malloc(sizeof(MyCircularQueue));
    q->data = malloc(k * sizeof(int));
    q->head = q->tail = q->cnt = 0;
    q->size = k;
    return q;
}
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj)) return false;
    obj->data[obj->tail] = value;
    obj->tail = (obj->tail + 1) % obj->size;    // NOTE
    obj->cnt++;
    return true;
}
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return false;
    obj->head = (obj->head + 1) % obj->size;
    obj->cnt--;
    return true;
}
int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    return obj->data[obj->head];
}
int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) return -1;
    return obj->data[(obj->tail - 1 + obj->size) % obj->size];  // NOTE
}
/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/
