class CountIntervals {
    map<int, int> intervals; // left -> right
    int total = 0;
public:
    CountIntervals() {}

    void add(int left, int right) {
        auto it = intervals.lower_bound(left);
        // Merge with previous interval if overlapping
        if (it != intervals.begin()) {
            --it;
            if (it->second < left - 1) ++it;
        }
        // Merge all overlapping intervals
        while (it != intervals.end() && it->first <= right + 1) {
            left = min(left, it->first);
            right = max(right, it->second);
            total -= (it->second - it->first + 1);
            it = intervals.erase(it);
        }
        intervals[left] = right;
        total += (right - left + 1);
    }

    int count() {
        return total;
    }
};
