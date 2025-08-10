import java.util.*;

class Fancy {
    static final int MOD = 1_000_000_007;
    List<Long> seq;
    List<Long> add;
    List<Long> mul;
    long addAll;
    long mulAll;

    public Fancy() {
        seq = new ArrayList<>();
        add = new ArrayList<>();
        mul = new ArrayList<>();
        addAll = 0;
        mulAll = 1;
    }

    public void append(int val) {
        // Store value with inverse of current global mul and add
        seq.add((long)val);
        mul.add(mulAll);
        add.add(addAll);
    }

    public void addAll(int inc) {
        addAll = (addAll + inc) % MOD;
    }

    public void multAll(int m) {
        mulAll = (mulAll * m) % MOD;
        addAll = (addAll * m) % MOD;
    }

    public int getIndex(int idx) {
        if (idx >= seq.size()) return -1;
        long val = seq.get(idx);
        long m0 = mul.get(idx);
        long a0 = add.get(idx);

        // Calculate the effect of global operations since append
        // v' = ((val * (mulAll / m0)) % MOD + (addAll - a0 * (mulAll / m0)) % MOD) % MOD
        long m = mulAll * modInverse(m0, MOD) % MOD;
        long a = (addAll - a0 * m % MOD + MOD) % MOD;
        return (int)((val * m % MOD + a) % MOD);
    }

    // Modular inverse using Fermat's little theorem (MOD is prime)
    private long modInverse(long x, int mod) {
        return pow(x, mod - 2, mod);
    }

    private long pow(long x, long y, int mod) {
        long res = 1;
        x = x % mod;
        while (y > 0) {
            if ((y & 1) == 1) res = (res * x) % mod;
            x = (x * x) % mod;
            y >>= 1;
        }
        return res;
    }
}
