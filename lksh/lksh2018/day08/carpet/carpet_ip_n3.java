/**
 * Created by User on 26.02.2015.
 */
import java.io.*;

/**
 * Created by pva701 on 2/26/15.
 */

public class carpet_ip_n3 {
    public static final String TASK = "carpet";
    public static final int INF = 1000000000;
    public static final int K = 30;

    BufferedReader in;
    PrintWriter out;

    public void solve() throws IOException {
        String str = in.readLine();
        int n = str.length();
        boolean[][] pref = new boolean[n][n];
        boolean[][] suff = new boolean[n][n];
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                int ind = str.indexOf(str.substring(i, j + 1));
                if (ind != -1) pref[i][j] = ind + j - i < i;
                suff[i][j] = str.lastIndexOf(str.substring(i, j + 1)) > j;
            }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                boolean found = false;
                for (int k = i; k < j && !found; ++k)
                    found = pref[i][k] && suff[k + 1][j];
                if (found) ++ans;
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
            System.err.println((r - l) / 1000.0);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new carpet_ip_n3().run();
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
