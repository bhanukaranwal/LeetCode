class Solution {
public:
    bool isRationalEqual(string s, string t) {
        auto f1 = toDouble(s);
        auto f2 = toDouble(t);
        // Allow a small epsilon for floating-point comparison
        return fabs(f1 - f2) < 1e-12;
    }

    double toDouble(const string& s) {
        int intPart = 0;
        string nonRepeat, repeat;
        int dot = s.find('.');
        int leftParen = s.find('(');
        int rightParen = s.find(')');

        if (dot == string::npos) {
            intPart = stoi(s);
        } else {
            intPart = stoi(s.substr(0, dot));
            if (leftParen == string::npos) {
                nonRepeat = s.substr(dot + 1);
            } else {
                nonRepeat = s.substr(dot + 1, leftParen - dot - 1);
                repeat = s.substr(leftParen + 1, rightParen - leftParen - 1);
            }
        }

        double res = intPart;
        if (!nonRepeat.empty()) {
            res += stod("0." + nonRepeat);
        }
        if (!repeat.empty()) {
            // 0.00(repeat) = repeat / (10^len(nonRepeat) * (10^len(repeat) - 1))
            double base = pow(10, nonRepeat.size());
            double repBase = pow(10, repeat.size()) - 1;
            double repVal = stod(repeat) / (base * repBase);
            res += repVal;
        }
        return res;
    }
};
