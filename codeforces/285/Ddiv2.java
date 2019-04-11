/**
 * Created by Roman on 11.08.2015.
 */
import java.io.*;
import java.math.*;
import java.util.*;

public class Ddiv2 {

    int MAXN = (int)(2e5 + 7);
    int[] T = new int[MAXN];
    int[] P = new int[MAXN];
    int[] Q = new int[MAXN];
    int[] F1 = new int[MAXN];
    int[] F2 = new int[MAXN];

    public int f(int i) {
        return i & (-i);
    }

    public void update(int pos, int val) {
        pos++;
        for (int i = pos; i < MAXN; i += f(i))
            T[i] += val;
    }

    public int get(int pos) {
        pos++;
        int ans = 0;
        for (int i = pos; i > 0 ; i -= f(i))
            ans += T[i];
        return ans;
    }

    public void solve() throws IOException {
        int n = nextInt();
        for (int i = 0; i < n; i++)
            P[i] = nextInt();
        for (int i = 0; i < n; i++)
            Q[i] = nextInt();

        for (int i = 0; i < n; i++) {
            F1[i] = get(P[i]);
            update(P[i], 1);
        }
        for (int i = 0; i < MAXN; i++)
            T[i] = 0;

        for (int i = 0; i < n; i++) {
            F2[i] = get(Q[i]);
            update(Q[i], 1);
        }
        for (int i = 0; i < n; i++)
            P[i] += Q[i] - F1[i] - F2[i];

        for (int i = n - 1; i >= 0; i--) {
            if (P[i] >= n - i && i > 0)
                P[i - 1]++;
            P[i] %= n - i;
        }

        for (int i = 0; i < MAXN; i++)
            T[i] = 0;

        for (int i = 0; i < n; i++)
            update(i, 1);

        for (int i = 0; i < n; i++) {
            int l = -1, r = n - 1;
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (get(m) >= P[i] + 1)
                    r = m;
                else
                    l = m;
            }
            Q[i] = r;
            update(r, -1);
        }
        for (int i = 0; i < n; i++)
            out.print(Q[i] + " ");
    }

    public void run() throws IOException {
        //br = new BufferedReader(new FileReader("BigInt.in"));
        br = new BufferedReader(new InputStreamReader(System.in));
        out  = new PrintWriter(System.out);
        solve();
        br.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new Ddiv2().run();
    }

    BufferedReader br;
    StringTokenizer str;
    PrintWriter out;

    String next() throws IOException {
        while (str == null || !str.hasMoreTokens()) {
            str = new StringTokenizer(br.readLine());
        }
        return str.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    double nextDouble() throws IOException {
        return Long.parseLong(next());
    }
}
