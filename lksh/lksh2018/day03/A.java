import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class join_vi implements Runnable {
	
	static final int pp = 1000000000;
	
	class Profile {
		public int[] p;
		
		public int hashCode() {
			return Arrays.hashCode(p);
		}
		
		public boolean equals(Object obj) {
			return Arrays.equals(p, ((Profile)obj).p);
		}
		
		Profile(int[] p) {
			this.p = p.clone();
		}
		
		public void norm() {
			int[] tmp = new int[p.length + 1];
			int count = 0;
			Arrays.fill(tmp, -1);
			for (int i = 0; i < p.length; ++i) {
				if (p[i] == -1) {
					continue;
				}
				if (tmp[p[i]] == -1) {
					tmp[p[i]] = count++;
				}
				p[i] = tmp[p[i]];
			}
		}
		
		public boolean end() {
			for (int i = 0; i < p.length; ++i) {
				if (p[i] > 0) {
					return false;
				}
			}
			return true;
		}
		
		int count(int k) {
			int c = 0;
			for (int i = 0; i < p.length; ++i) {
				if (p[i] == k) {
					++c;
				}
			}
			return c;
		}
		
		public String toString() {
			return Arrays.toString(p);
		}
	}
	
	static private void inc(HashMap<Profile, Integer> m, Profile p, int k) {
		if (!m.containsKey(p)) {
			m.put(p, k);
		} else {
			m.put(p, (m.get(p) + k) % pp);
		}
	}
	
	public void solve() throws Exception {
		int n = nextInt();
		int m = nextInt();
		char[][] f = new char[n][];
		for (int i = 0; i < n; ++i) {
			f[i] = nextToken().toCharArray();
		}
		HashMap<Profile, Integer> d = new HashMap<Profile, Integer>();
		Profile tmp = new Profile(new int[m]);
		Arrays.fill(tmp.p, -1);
		d.put(tmp, 1);
		loop: while (n > 0) {
			for (int i = 0; i < m; ++i) {
				if (f[n - 1][i] != '*') {
					break loop;
				}
			}
			--n;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				HashMap<Profile, Integer> t = new HashMap<Profile, Integer>();
				for (Profile p : d.keySet()) {
					int val = d.get(p);
					if (j == 0) {
						if (f[i][j] != '*') {
							if (p.p[j] == -1 || p.count(p.p[j]) != 1) {
								tmp = new Profile(p.p);
								tmp.p[j] = m;
								tmp.norm();
								inc(t, tmp, val);
							}
							if (p.p[j] != -1) {
								tmp = new Profile(p.p);
								inc(t, tmp, val);
							}
						} else {
							if (p.p[j] == -1 || p.count(p.p[j]) != 1) {
								tmp = new Profile(p.p);
								tmp.p[j] = -1;
								tmp.norm();
								inc(t, tmp, val);
							}
						}
					} else {
						if (f[i][j] !='*') {
							if (p.p[j] != p.p[j - 1] && p.p[j] != -1 && p.p[j - 1] != -1) {
								tmp = new Profile(p.p);
								for (int z = 0; z < m; ++z) {
									if (tmp.p[z] == p.p[j - 1]) {
										tmp.p[z] = p.p[j];
									}
								}
								tmp.norm();
								inc(t, tmp, val);
							}
							if (p.p[j] != -1) {
								tmp = new Profile(p.p);
								inc(t, tmp, val);
							}
							if ((p.p[j] == -1 || p.count(p.p[j]) != 1) && p.p[j - 1] != -1) {
								tmp = new Profile(p.p);
								tmp.p[j] = p.p[j - 1];
								tmp.norm();
								inc(t, tmp, val);
							}
							if (p.p[j] == -1 || p.count(p.p[j]) != 1) {
								tmp = new Profile(p.p);
								tmp.p[j] = m;
								tmp.norm();
								inc(t, tmp, val);
							}
						} else {
							if (p.p[j] == -1 || p.count(p.p[j]) != 1) {
								tmp = new Profile(p.p);
								tmp.p[j] = -1;
								tmp.norm();
								inc(t, tmp, val);
							}
						}
					}
				}
				d = t;
			}
		}
		int ans = 0;
		for (Profile p : d.keySet()) {
			if (p.end()) {
				ans += d.get(p);
			}
		}
		out.println(ans);
	}
	
	private BufferedReader in;
	private PrintWriter out;
	private StringTokenizer st;
	
	public void run() {
		try {
			in = new BufferedReader(new InputStreamReader(System.in));
			st = new StringTokenizer("");
			out = new PrintWriter(new OutputStreamWriter(System.out));
			solve();
			out.close();
		} catch (Exception ex) {
			ex.printStackTrace();
			throw new RuntimeException();
		}
	}
	
	public static void main(String[] args) {
		new Thread(new join_vi()).start();
	}
	
	String nextToken() throws Exception {
		while (!st.hasMoreTokens()) {
			String line = in.readLine();
			if (line == null) {
				return null;
			}
			st = new StringTokenizer(line);
		}
		return st.nextToken();
	}
	
	int nextInt() throws Exception {
		return Integer.parseInt(nextToken());
	}
	
	long nextLong() throws Exception {
		return Long.parseLong(nextToken());
	}
	
	double nextDouble() throws Exception {
		return Double.parseDouble(nextToken());
	}

}
