class AllOne {
    struct Bucket {
        int count;
        unordered_set<string> keys;
        Bucket* prev;
        Bucket* next;
        Bucket(int c): count(c), prev(nullptr), next(nullptr) {}
    };
    
    unordered_map<string, Bucket*> keyToBucket;
    Bucket* head; // Dummy head (min count)
    Bucket* tail; // Dummy tail (max count)
    
public:
    AllOne() {
        head = new Bucket(INT_MIN);
        tail = new Bucket(INT_MAX);
        head->next = tail;
        tail->prev = head;
    }
    
    ~AllOne() {
        // Clean up all buckets
        Bucket* curr = head;
        while (curr) {
            Bucket* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    
    void inc(string key) {
        if (keyToBucket.count(key) == 0) {
            // Insert new key with count 1
            if (head->next->count != 1) {
                Bucket* b = new Bucket(1);
                insertAfter(head, b);
            }
            head->next->keys.insert(key);
            keyToBucket[key] = head->next;
        } else {
            Bucket* b = keyToBucket[key];
            int newCount = b->count + 1;
            Bucket* next = b->next;
            if (next->count != newCount) {
                Bucket* newBucket = new Bucket(newCount);
                insertAfter(b, newBucket);
            }
            b->next->keys.insert(key);
            keyToBucket[key] = b->next;
            b->keys.erase(key);
            if (b->keys.empty()) remove(b);
        }
    }
    
    void dec(string key) {
        Bucket* b = keyToBucket[key];
        int newCount = b->count - 1;
        if (newCount == 0) {
            keyToBucket.erase(key);
        } else {
            Bucket* prev = b->prev;
            if (prev->count != newCount) {
                Bucket* newBucket = new Bucket(newCount);
                insertAfter(prev, newBucket);
            }
            b->prev->keys.insert(key);
            keyToBucket[key] = b->prev;
        }
        b->keys.erase(key);
        if (b->keys.empty()) remove(b);
    }
    
    string getMaxKey() {
        if (tail->prev == head) return "";
        return *(tail->prev->keys.begin());
    }
    
    string getMinKey() {
        if (head->next == tail) return "";
        return *(head->next->keys.begin());
    }
    
private:
    void insertAfter(Bucket* prev, Bucket* node) {
        node->next = prev->next;
        node->prev = prev;
        prev->next->prev = node;
        prev->next = node;
    }
    
    void remove(Bucket* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
};
