class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        if (lower.empty() || num <= lower.top()) {
            lower.push(num);
        } else {
            upper.push(num);
        }
        // Balance the heaps
        if (lower.size() > upper.size() + 1) {
            upper.push(lower.top());
            lower.pop();
        } else if (upper.size() > lower.size()) {
            lower.push(upper.top());
            upper.pop();
        }
    }

    double findMedian() {
        if (lower.size() == upper.size()) {
            return (lower.top() + upper.top()) / 2.0;
        } else {
            return lower.top();
        }
    }

private:
    priority_queue<int> lower; // max-heap
    priority_queue<int, vector<int>, greater<int>> upper; // min-heap
};
