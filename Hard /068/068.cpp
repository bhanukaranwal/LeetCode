class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0, n = words.size();
        
        while (i < n) {
            int count = words[i].length();
            int last = i + 1;
            while (last < n && count + words[last].length() + (last - i) <= maxWidth) {
                count += words[last].length();
                last++;
            }
            
            string line;
            int gaps = last - i - 1;
            
            if (last == n || gaps == 0) {
                for (int j = i; j < last; j++) {
                    line += words[j];
                    if (j < last - 1) line += " ";
                }
                line += string(maxWidth - line.length(), ' ');
            } else {
                int spaces = (maxWidth - count) / gaps;
                int extra = (maxWidth - count) % gaps;
                for (int j = i; j < last; j++) {
                    line += words[j];
                    if (j < last - 1) {
                        line += string(spaces + (j - i < extra ? 1 : 0), ' ');
                    }
                }
            }
            
            result.push_back(line);
            i = last;
        }
        
        return result;
    }
};
