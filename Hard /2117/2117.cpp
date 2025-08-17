class Solution {
public:
	string abbreviateProduct(int left, int right) {
		long long suf = 1;
		int zeros = 0, org_digits = 0;
		double prod = 1.0;
		for (int n = left; n <= right; n ++) {
			prod *= n;
			while (prod >= 1.0) { 
				prod /= 10.0;
				org_digits ++; 
			}
			suf *= n;
			while (suf % 10 == 0) { 
				zeros ++;
				suf /= 10;
			}
			if (suf > pow(10, 14)) suf %= (long long)pow(10, 14);
		}
		if (org_digits - zeros <= 10) {
			return to_string((long long)(prod * pow(10, org_digits - zeros) + 0.5)) + 'e' + to_string(zeros);
		} else {

			
			string str_suf = "0000" + to_string(suf);
			return to_string((int)(prod * 100000)) + "..." + str_suf.substr(str_suf.length() - 5) + 'e' + to_string(zeros);
		}
	}
};
