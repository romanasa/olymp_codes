import java.io.*;
import java.util.*;
import java.math.*;

public class search4_ab implements Runnable {

	private void solve() throws IOException {
		int n = in.nextInt();
		int[] rmap = new int[n];
		AhoCorasik ac = new AhoCorasik(MAXN + 1);
		int sl = 0;
		for (int i = 0; i < n; ++i) {
			String s = checkFormat(in.next());
			sl += s.length();
			rmap[i] = ac.addWord(s);
		}
		if (sl > MAXN) throw new Error();
		ac.makeSuf();
		String t = checkFormat(in.next());
		if (t.length() > MAXN) throw new Error();
		ac.process(t);
		for (int i = 0; i < n; ++i) {
			if (ac.f[rmap[i]]) {
				out.println("YES");
			} else {
				out.println("NO");
			}
		}
	}

	final int MAXN = 1000000;
	
	String checkFormat(String s) {
		for (char c : s.toCharArray()) {
			if (!('a' <= c && c <= 'z')) throw new Error();
		}
		return s;
	}
	
	final int ALPHA_SIZE = 26;
	int toInt(char c) {
		return c - 'a';
	}
	
	
	class AhoCorasik {
		int[][] go;
		int[] suf;
		boolean[] f;
		int free;
	
		public AhoCorasik(int n) {
			free = 1;
			go = new int[n][ALPHA_SIZE];
			for (int[] t : go) Arrays.fill(t, -1);
			suf = new int[n];
			Arrays.fill(suf, -1);
			f = new boolean[n];
		}
		
		int addWord(String s) {
			int p = 0;
			for (int i = 0; i < s.length(); ++i) {
				int c = toInt(s.charAt(i));
				if (go[p][c] == -1) {
					go[p][c] = free++;
				}
				p = go[p][c];
			}
			return p;
		}
		
		void makeSuf() {
			int[] q = new int[free];
			int head = 0;
			int tail = 1;
			q[0] = 0;
			while (head != tail) {
				int u = q[head++];
				for (int c = 0; c < go[u].length; ++c) {
					if (go[u][c] == -1) continue;
					int v = suf[u];
					while (v >= 0 && go[v][c] == -1) {
						v = suf[v];
					}
					if (v < 0) {
						suf[go[u][c]] = 0;
					} else {
						suf[go[u][c]] = go[v][c];
					}
					q[tail++] = go[u][c];
				}
			}
		}
		
		void process(String s) {
			int p = 0;
			for (int i = 0; i < s.length(); ++i) {
				int c = toInt(s.charAt(i));
				while (p >= 0 && go[p][c] == -1) {
					p = suf[p];
				}
				if (p < 0) {
					p = 0;
				} else {
					p = go[p][c];
				}
				int v = p;
				while (v >= 0 && !f[v]) {
					f[v] = true;
					v = suf[v];
				}
			}
		}
		
		@Override
		public String toString() {
			String ans = "";
			for (int i = 0; i < free; ++i) {
				ans += i + ": suf " + suf[i] + "\n";
				for (int c = 0; c < 26; ++c) {
					if (go[i][c] >= 0) {
						ans += ((char)('a' + c)) + " -> " + go[i][c] + "; ";
					}
				}
				ans += "\n";
			}
			return ans;
		}
	}
	
	
	final String FILE_NAME = "search4";

	SimpleScanner in;
	PrintWriter out;

	@Override
	public void run() {
		try {
			in = new SimpleScanner(new FileReader(FILE_NAME + ".in"));
			out = new PrintWriter(FILE_NAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(-1);
		}
	}

	public static void main(String[] args) {
		new Thread(new search4_ab()).start();
	}

	class SimpleScanner extends BufferedReader {

		private StringTokenizer st;
		private boolean eof;

		public SimpleScanner(Reader a) {
			super(a);
		}

		String next() {
			while (st == null || !st.hasMoreElements()) {
				try {
					st = new StringTokenizer(readLine());
				} catch (Exception e) {
					eof = true;
					return "";
				}
			}
			return st.nextToken();
		}

		boolean seekEof() {
			String s = next();
			if ("".equals(s) && eof)
				return true;
			st = new StringTokenizer(s + " " + st.toString());
			return false;
		}

		private String cnv(String s) {
			if (s.length() == 0)
				return "0";
			return s;
		}

		int nextInt() {
			return Integer.parseInt(cnv(next()));
		}

		double nextDouble() {
			return Double.parseDouble(cnv(next()));
		}

		long nextLong() {
			return Long.parseLong(cnv(next()));
		}
	}
}
