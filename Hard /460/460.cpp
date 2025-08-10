class LFUCache {
    struct Node {
        int key, value, freq;
        Node *prev, *next;
        Node(int k, int v) : key(k), value(v), freq(1), prev(nullptr), next(nullptr) {}
    };

    struct DList {
        Node *head, *tail;
        int size;
        DList() : size(0) {
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head->next = tail;
            tail->prev = head;
        }
        void addFront(Node* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
            ++size;
        }
        void remove(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            --size;
        }
        Node* removeLast() {
            if (size == 0) return nullptr;
            Node* node = tail->prev;
            remove(node);
            return node;
        }
        ~DList() {
            delete head;
            delete tail;
        }
    };

    int capacity, minFreq;
    unordered_map<int, Node*> keyNode;
    unordered_map<int, DList*> freqList;

    void update(Node* node) {
        int freq = node->freq;
        freqList[freq]->remove(node);
        if (freq == minFreq && freqList[freq]->size == 0) {
            minFreq++;
        }
        node->freq++;
        if (!freqList.count(node->freq)) freqList[node->freq] = new DList();
        freqList[node->freq]->addFront(node);
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (!keyNode.count(key)) return -1;
        Node* node = keyNode[key];
        update(node);
        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (keyNode.count(key)) {
            Node* node = keyNode[key];
            node->value = value;
            update(node);
        } else {
            if (keyNode.size() == capacity) {
                Node* node = freqList[minFreq]->removeLast();
                keyNode.erase(node->key);
                delete node;
            }
            Node* node = new Node(key, value);
            minFreq = 1;
            if (!freqList.count(1)) freqList[1] = new DList();
            freqList[1]->addFront(node);
            keyNode[key] = node;
        }
    }

    ~LFUCache() {
        for (auto& [_, dl] : freqList) delete dl;
        for (auto& [_, node] : keyNode) delete node;
    }
};
