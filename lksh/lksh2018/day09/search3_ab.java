import java.io.*;
import java.util.*;
import java.math.*;

public class search3_ab implements Runnable {

	private void solve() throws IOException {
		String p = checkFormat(in.next());
		String t = checkFormat(in.next());
		
		int[] z1 = getZ(p + t);
		int[] z2 = getZ(reverse(p) + reverse(t));
		
		ArrayList<Integer> ans = new ArrayList<Integer>();
		
		for (int i = 0; i < t.length() - p.length() + 1; ++i) {
			if (z1[i + p.length()] + z2[t.length() - i] >= p.length() - 1) {
				ans.add(i + 1);
			}
		}
		
		out.println(ans.size());
		for (int i = 0; i < ans.size(); ++i) {
			if (i != 0) {
				out.print(" ");
			}
			out.print(ans.get(i));
		}
		out.println();
	}

	String reverse(String s) {
		StringBuilder sb = new StringBuilder(s);
		sb = sb.reverse();
		return sb.toString(); 
	}
	
	
	int[] getZ(String s) {
		int[] z = new int[s.length()];
		z[0] = s.length();
		int l = 0;
		int r = 0;
		for (int i = 1; i < z.length; ++i) {
			z[i] = Math.max(0, Math.min(z[i - l], r - i + 1));
			while (i + z[i] < s.length() && s.charAt(z[i]) == s.charAt(i + z[i])) ++z[i];
			if (i + z[i] - 1 > r) {
				l = i;
				r = i + z[i] - 1;
			}
		}
		return z;
	}
	
	final int MAXN = 1000000;
	
	String checkFormat(String s) {
		if (s.length() > MAXN) throw new Error();
		for (char c : s.toCharArray()) {
			if (!('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')) throw new Error();
		}
		return s;
	}
	
	final String FILE_NAME = "inexact-matching";

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
		new Thread(new search3_ab()).start();
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
