class SummaryRanges {
    set<pair<int, int>> intervals;
public:
    SummaryRanges() {}

    void addNum(int value) {
        auto it = intervals.lower_bound({value, value});
        int start = value, end = value;

        // Merge with previous interval if needed
        if (it != intervals.begin()) {
            auto itPrev = std::prev(it);
            if (itPrev->second + 1 >= value) {
                start = itPrev->first;
                end = max(end, itPrev->second);
                intervals.erase(itPrev);
            }
        }
        // Merge with next interval if needed
        while (it != intervals.end() && it->first <= end + 1) {
            end = max(end, it->second);
            it = intervals.erase(it);
        }
        intervals.insert({start, end});
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        for (auto& p : intervals)
            res.push_back({p.first, p.second});
        return res;
    }
};
