/**
 * Created by User on 26.02.2015.
 */
import java.io.*;

/**
 * Created by pva701 on 2/26/15.
 */

public class carpet_ip_n2 {
    public static final String TASK = "carpet";
    public static final int INF = 1000000000;
    public static final int K = 30;

    BufferedReader in;
    PrintWriter out;

    public int[] zFunction(String s) {
        int n = s.length();
        int[] z = new int[n];
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                z[i] = Math.min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i]))
                ++z[i];
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    public int[] calcMaxPrefixes(String str) {
        int n = str.length();
        int[] s = new int[n];
        for (int i = 0; i < n; ++i) {
            int[] z = zFunction(str.substring(i, n));
            for (int j = 0; j < n - i; ++j)
                s[i + j] = Math.max(s[i + j], Math.min(j, z[j]));
        }
        return s;
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

        int ans = 0;
        int n = str.length();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (s[i] != 0 && t[j] != 0 && s[i] + i >= j - t[j] + 1) ++ans;
        out.println(ans);
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(new FileInputStream(TASK + ".in")));
            out = new PrintWriter(new File(TASK + ".out"));
            long l = System.currentTimeMillis();
            solve();
            long r = System.currentTimeMillis();
            System.err.println((r - l) / 1000.0);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new carpet_ip_n2().run();
    }

    static class Fenwick {
        private int[] s;
        private int n;
        public Fenwick(int n) {
            this.n = n;
            s = new int[n];
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
