class MyCircularDeque {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        data.resize(k);
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull()) return false;
        head = (head - 1 + data.size()) % data.size();
        data[head] = value;
        ++cnt;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull()) return false;
        data[(head + cnt) % data.size()] = value;
        ++cnt;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty()) return false;
        head = (head + 1) % data.size();
        --cnt;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) return false;
        --cnt;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return isEmpty() ? -1 : data[head];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return isEmpty() ? -1 : data[(head + cnt - 1) % data.size()];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return cnt == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return cnt == data.size();
    }
private:
    vector<int> data;
    int cnt = 0, head = 0;
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */