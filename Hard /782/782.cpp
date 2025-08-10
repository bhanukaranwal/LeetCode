class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        int rowMask = 0, colMask = 0;
        for (int i = 0; i < n; ++i) {
            rowMask |= board[0][i] << i;
            colMask |= board[i][0] << i;
        }
        int reverseRowMask = ((1 << n) - 1) ^ rowMask;
        int reverseColMask = ((1 << n) - 1) ^ colMask;
        int rowCnt = 0, colCnt = 0;
        for (int i = 0; i < n; ++i) {
            int currRowMask = 0, currColMask = 0;
            for (int j = 0; j < n; ++j) {
                currRowMask |= board[i][j] << j;
                currColMask |= board[j][i] << j;
            }
            if (currRowMask != rowMask && currRowMask != reverseRowMask) return -1;
            if (currColMask != colMask && currColMask != reverseColMask) return -1;
            if (currRowMask == rowMask) ++rowCnt;
            if (currColMask == colMask) ++colCnt;
        }
        int rowMoves = getMoves(rowMask, rowCnt, n);
        int colMoves = getMoves(colMask, colCnt, n);
        if (rowMoves == -1 || colMoves == -1) return -1;
        return rowMoves + colMoves;
    }
    int getMoves(int mask, int count, int n) {
        int ones = __builtin_popcount(mask);
        int minSwaps = INT_MAX;
        if (n % 2 == 0) {
            int swaps0 = __builtin_popcount(mask ^ 0xAAAAAAAA & ((1 << n) - 1));
            int swaps1 = __builtin_popcount(mask ^ 0x55555555 & ((1 << n) - 1));
            if (ones == n / 2) minSwaps = min(minSwaps, swaps0 / 2);
            if (ones == n / 2) minSwaps = min(minSwaps, swaps1 / 2);
        } else {
            if (ones == n / 2) minSwaps = min(minSwaps, __builtin_popcount(mask ^ 0xAAAAAAAA & ((1 << n) - 1)) / 2);
            if (ones == n / 2 + 1) minSwaps = min(minSwaps, __builtin_popcount(mask ^ 0x55555555 & ((1 << n) - 1)) / 2);
        }
        return minSwaps == INT_MAX ? -1 : minSwaps;
    }
};
