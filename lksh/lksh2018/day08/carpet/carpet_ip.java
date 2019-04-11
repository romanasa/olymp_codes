import java.io.*;
import java.util.Arrays;

/**
 * Created by pva701 on 2/26/15.
 */

public class carpet_ip {
    public static final String TASK = "carpet";
    public static final int INF = 1000000000;
    public static final int K = 30;

    BufferedReader in;
    PrintWriter out;

    public int[] buildSuffixArray(String str) {
        int n = str.length();
        char[] chars = new char[n + 1];
        for (int i = 0; i < n; ++i)
            chars[i] = str.charAt(i);
        chars[n] = 'a' - 1;
        int[] p = buildSuffixArray(chars);
        return p;
    }

    public int[] buildSuffixArray(char[] s) {
        int n = s.length;
        int maxClasses = Math.max(n, K);
        int[] cnt = new int[K];
        int[] color = new int[n];
        int[] h = new int[maxClasses];
        int[] a = new int[n];
        int[] newA = new int[n];
        int[] newColor = new int[n];

        for (int i = 0; i < n; ++i) {
            s[i] = (char)((int)s[i] - (int)'a' + 1);
            cnt[s[i]]++;
            color[i] = s[i];
        }
        for (int i = 1; i < K; ++i)
            h[i] = h[i - 1] + cnt[i - 1];

        for (int i = 0; i < n; ++i)
            a[h[color[i]]++] = i;

        h[0] = 0;
        for (int i = 1; i < K; ++i)
            h[i] = h[i - 1] + cnt[i - 1];
        int l = 1;
        while (l < n) {
            for (int i = 0; i < n; ++i) {
                int j = a[i] - l + n;
                if (j >= n) j -= n;
                newA[h[color[j]]] = j;
                h[color[j]]++;
            }
            newColor[newA[0]] = 0;
            h[0] = 0;
            for (int i = 1; i < n; ++i)
                if (color[newA[i]] == color[newA[i - 1]] && color[(newA[i] + l) % n] == color[(newA[i - 1] + l) % n])
                    newColor[newA[i]] = newColor[newA[i - 1]];
                else {
                    newColor[newA[i]] = newColor[newA[i - 1]] + 1;
                    h[newColor[newA[i]]] = i;
                }
            for (int i = 0; i < n; ++i) {
                a[i] = newA[i];
                color[i] = newColor[i];
            }
            l *= 2;
        }
        return Arrays.copyOfRange(a, 1, a.length);
    }

    public int[] calcLcp(char[] str, int[] p) {
        int n = str.length - 1;
        int[] pos = new int[n];
        int[] lcp = new int[n];
        for (int i = 0; i < n; ++i)
            pos[p[i]] = i;
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (k > 0) --k;
            if (pos[i] == n - 1) {
                lcp[n - 1] = 0;
                k = 0;
            } else {
                int j = p[pos[i] + 1];
                while (str[i + k] == str[j + k]) ++k;
                lcp[pos[i]] = k;
            }
        }
        return lcp;
    }

    static class MinimumStack {
        private int[] stack;
        private int[][] jumps;
        private int[] sizes;
        private int size;

        public MinimumStack(int n) {
            stack = new int[n];
            jumps = new int[n][getMaxLog(n) + 1];
            sizes = new int[n];
        }

        public void clear() {
            size = 0;
        }

        private int back() {
            return stack[size - 1];
        }

        private void pop_back() {
            --size;
        }

        public void add(int lcp, int position) {
            while (size > 0 && lcp <= back()) {
                position = Math.min(position, jumps[size - 1][0]);
                pop_back();
            }
            stack[size] = lcp;
            jumps[size][0] = position;
            ++size;
            sizes[size - 1] = 1;
            for (int j = 1; (1<<j) <= size; ++j) {
                sizes[size - 1] = j + 1;
                jumps[size - 1][j] = Math.min(jumps[size - 1][j - 1], jumps[size - 1 - (1<<j-1)][j - 1]);
            }
        }

        public int getMaxLenOfPrefix(int curPos) {
            int h = getMaxLog(size);
            int posLen = size - 1;
            int minPosOnPrefix = INF;
            for (int j = h; j >= 0 && posLen >= 0; --j)
                if (j < sizes[posLen] && Math.min(minPosOnPrefix, jumps[posLen][j]) + stack[posLen - (1<<j) + 1] > curPos) {
                    minPosOnPrefix = Math.min(minPosOnPrefix, jumps[posLen][j]);
                    posLen = posLen - (1<<j);
                }
            int mx = 0;
            if (posLen != -1)
                mx = Math.max(mx, stack[posLen]);
            mx = Math.max(mx, curPos - minPosOnPrefix);
            return mx;
        }

        private int getMaxLog(int sz) {
            int h = -1;
            while ((1<<h+1) <= sz)
                ++h;
            return h;
        }

    }

    public int[] calcMaxPrefixes(String str) {
        int n = str.length();
        char[] chars = new char[n + 1];
        for (int i = 0; i < n; ++i)
            chars[i] = str.charAt(i);
        chars[n] = 'a' - 1;
        int[] p = buildSuffixArray(chars);
        int[] lcp = calcLcp(chars, p);
        int[] ret = new int[n];

        MinimumStack minimumStack = new MinimumStack(n);
        for (int i = n - 2; i >= 0; --i) {
            minimumStack.add(lcp[i], p[i + 1]);
            int maxLenOfPrefix = minimumStack.getMaxLenOfPrefix(p[i]);
            ret[p[i]] = Math.max(ret[p[i]], maxLenOfPrefix);
        }
        minimumStack.clear();
        for (int i = 1; i < n; ++i) {
            minimumStack.add(lcp[i - 1], p[i - 1]);
            int maxLenOfPrefix = minimumStack.getMaxLenOfPrefix(p[i]);
            ret[p[i]] = Math.max(ret[p[i]], maxLenOfPrefix);
        }
        return ret;
    }


    public void solve() throws IOException {
        String str = in.readLine();
        int[] s = calcMaxPrefixes(str);
        int[] t = calcMaxPrefixes(new StringBuilder(str).reverse().toString());
        for (int i = 0; i < t.length / 2; ++i) {
            int tmp = t[i];
            t[i] = t[t.length - i - 1];
            t[t.length - i - 1] = tmp;
        }
        int n = str.length();
        Fenwick tree = new Fenwick(n + 1);
        long ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] != 0)
                ans += tree.sum(0, i + s[i]);
            if (t[i] != 0)
                tree.upd(i - t[i] + 1, 1);
        }
        out.println(ans);
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(new FileInputStream(TASK + ".in")));
            out = new PrintWriter(new File(TASK + ".out"));
            long l = System.currentTimeMillis();
            solve();
            long r = System.currentTimeMillis();
            System.err.println("time = " + (r - l) / 1000.0);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new carpet_ip().run();
    }

    static class Fenwick {
        private int[] s;
        private int n;
        public Fenwick(int n) {
            this.n = n;
            s = new int[n + 1];
        }

        public int sum(int l, int r) {
            return get(r) - get(l - 1);
        }

        private int get(int v) {
            int sum = 0;
            while (v >= 0) {
                sum += s[v];
                v = (v & (v + 1)) - 1;
            }
            return sum;
        }

        public void upd(int v, int value) {
            while (v <= n) {
                s[v] += value;
                v |= v + 1;
            }
        }
    }
}
