class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) return false;
        data[(head + cnt) % data.size()] = value;
        ++cnt;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % data.size();
        --cnt;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return isEmpty() ? -1 : data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return isEmpty() ? -1 : data[(head + cnt - 1) % data.size()];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return cnt == 0;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return cnt == data.size();
    }
private:
    vector<int> data;
    int cnt = 0, head = 0; // cnt: num of element in queue
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */