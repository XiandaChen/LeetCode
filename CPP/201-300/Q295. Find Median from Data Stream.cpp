class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    
    void addNum(int num) {
        if (maxHeap.empty() || maxHeap.top() >= num)
            maxHeap.push(num);
        else
            minHeap.push(num);
        
        // balance: maxHeap has same numbers (or one more) of elements than minHeap
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size())
            return (double)maxHeap.top();
        else 
            return (double)(maxHeap.top() + minHeap.top()) / 2.0;
    }
private:
    priority_queue<int> maxHeap; // maxHeap: nums less than median
    priority_queue<int, vector<int>, greater<int>> minHeap; // minHeap: nums larger than median
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */