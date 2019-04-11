    import java.io.*;
    import java.math.BigInteger;
    import java.util.*;

    public class F {
        public void solve() throws IOException {
            BigInteger N = new BigInteger(next());

            BigInteger T = sqrt(N);

            if (T.multiply(T).equals(N)) T = T.subtract(BigInteger.ONE);

            BigInteger ost = N.subtract(T.multiply(T));

            T = T.add(BigInteger.ONE);


            if (ost.compareTo(T) <= 0) out.println(ost);
            else out.println(T.add(T).subtract(ost));

            //out.println(sqrt(N).toString());
        }

        BigInteger sqrt(BigInteger n) {
            BigInteger a = BigInteger.ONE;
            BigInteger b = n.shiftRight(5).add(BigInteger.valueOf(8));
            while (b.compareTo(a) >= 0) {
                BigInteger mid = a.add(b).shiftRight(1);
                if (mid.multiply(mid).compareTo(n) > 0) {
                    b = mid.subtract(BigInteger.ONE);
                } else {
                    a = mid.add(BigInteger.ONE);
                }
            }
            return a.subtract(BigInteger.ONE);
        }


        public void run() throws IOException{
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            //br = new BufferedReader(new FileReader("buylow.in"));
            //out = new PrintWriter("buylow.out");
            solve();
            br.close();
            out.close();
        }

        public static void main(String[] args) throws IOException {
            new F().run();
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
            return Double.parseDouble(next());
        }
    }
