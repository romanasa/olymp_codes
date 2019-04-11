import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.StringTokenizer;

public class TaskD {
    private final InputReader reader;
    private final OutputWriter writer;

    public TaskD(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new TaskD(reader, writer).run();
        writer.writer.flush();
    }

    final int C = 62;
    final int CC = C * C;

    int ordByChar(char c) {
        return 'a' <= c && c <= 'z' ? (int)(c - 'a') : 'A' <= c && c <= 'Z' ? (int)(c - 'A' + 26) : (int)(c - '0' + 52);
    }

    char charByOrd(int x) {
        return x < 26 ? (char)('a' + x) : x < 52 ? (char)('A' + x - 26) : (char)('0' + x - 52);
    }

    int numByStr(String s) {
        assert s.length() == 2;
        return ordByChar(s.charAt(0)) * C + ordByChar(s.charAt(1));
    }

    String strByNum(int x) {
        StringBuilder sb = new StringBuilder(2);
        sb.append(charByOrd(x / C));
        sb.append(charByOrd(x % C));
        return sb.toString();
    }

    List<Integer>[] E;
    int[] in, out;

    int[] eul;
    int ept = 0;

    void go(int x) {
        while (!E[x].isEmpty()) {
            int y = E[x].get(E[x].size() - 1);
            E[x].remove(E[x].size() - 1);
            go(y);
            eul[ept++] = y;
        }
    }

    public void run() {
        int n = reader.nextInt();
        String[] S = new String[n];

        E = new ArrayList[CC];
        in = new int[CC];
        out = new int[CC];
        eul = new int[n + 1];
        for (int i = 0; i < CC; i++)
            E[i] = new ArrayList<Integer>();

        for (int i = 0; i < n; i++) {
            S[i] = reader.next();
            int a = numByStr(S[i].substring(0, 2));
            int b = numByStr(S[i].substring(1, 3));
            E[a].add(b);
            out[a]++;
            in[b]++;
        }
        int start = -1, end = -1, any = -1;
        boolean bad = false;
        for (int i = 0; i < CC && !bad; i++) {
            if (out[i] != 0 || in[i] != 0)
                any = i;
            if (Math.abs(out[i] - in[i]) >= 2)
                bad = true;
            else if (out[i] == in[i] + 1) {
                if (start != -1)
                    bad = true;
                else
                    start = i;
            } else if (in[i] == out[i] + 1) {
                if (end != -1)
                    bad = true;
                else
                    end = i;
            }
        }
        if (bad) {
            writer.printf("NO\n");
            return;
        }
        if (start == -1)
            start = any;
        go(start);
        if (ept != n) {
            writer.printf("NO\n");
            return;
        }
        writer.printf("YES\n");
        writer.printf("%s", strByNum(start));
        for (int i = ept - 1; i >= 0; i--)
            writer.printf("%c", strByNum(eul[i]).charAt(1));
        writer.printf("\n");
    }


    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    static class OutputWriter {
        public PrintWriter writer;

        OutputWriter(OutputStream stream) {
            writer = new PrintWriter(stream);
        }

        public void printf(String format, Object... args) {
            writer.print(String.format(Locale.ENGLISH, format, args));
        }
    }
}

