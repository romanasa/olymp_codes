import java.util.*;
import java.io.*;
import java.math.*;

public class rectangle_di
{
public static void main(String[] argv) throws IOException
{
	new rectangle_di().run();
}

class TB {
	int idx;
	long ans;
	void Assign (TB b) {
		idx = b.idx;
		ans = b.ans;
	}
};

class TNode {
	TB L01;
	TB R01;
	int L;
	int R;
	long ansLR;
	int cnt;
	long sum;
	void Assign (TNode n) {
		L01.Assign (n.L01);
		R01.Assign (n.R01);
		L = n.L;
		R = n.R;
		ansLR = n.ansLR;
	}
};
Scanner in;
PrintWriter out;


TNode Nodes[];
int n;
int root;
int X[], Y[], W[];
int YI[];

long ans;
int ax, aX, ayi, aYi;

void tryit (int x, int X, int yi, int Yi, long sum) {
	if (sum > ans) {
		ax = x;
		aX = X;
		ayi = yi;
		aYi = Yi;
		ans = sum;
	}
}

boolean lsX (int i, int j) {
	return X[i] < X[j];
}
boolean lsY (int i, int j) {
	return Y[i] < Y[j];
}

void Permute(Integer P[], int X[]) {
	int A[] = new int[n];
	for (int i = 0; i < n; ++i)
		A[i] = X[i];
	for (int i = 0; i < n; ++i)
		X[i] = A[P[i]];
}

void update (int n_, int s1_, int s2_) {
	TNode n = Nodes[n_];
	TNode s1 = Nodes[s1_];
	TNode s2 = Nodes[s2_];
	if (s1.cnt == 0 && s2.cnt == 0) {
		if (n.cnt >= 2) {
			n.L = n.R = n.L01.idx;
			n.ansLR = n.L01.ans;
		}
	} else if (s1.cnt == 0) {
		n.Assign (s2);
	} else if (s2.cnt == 0) {
		n.Assign (s1);
	} else {
		n.L01.Assign (s1.L01);
		n.R01.Assign (s2.R01);
		if (s1.sum + s2.L01.ans > n.L01.ans) {
			n.L01.idx = s2.L01.idx;
			n.L01.ans = s1.sum + s2.L01.ans;
		}
		if (s1.R01.ans + s2.sum > n.R01.ans) {
			n.R01.idx = s1.R01.idx;
			n.R01.ans = s1.R01.ans + s2.sum;
		}
		n.L = s1.R01.idx;
		n.R = s2.L01.idx;
		n.ansLR = s1.R01.ans + s2.L01.ans;
		if (s1.cnt >= 2 && s1.ansLR > n.ansLR) {
			n.L = s1.L;
			n.R = s1.R;
			n.ansLR = s1.ansLR;
		}
		if (s2.cnt >= 2 && s2.ansLR > n.ansLR) {
			n.L = s2.L;
			n.R = s2.R;
			n.ansLR = s2.ansLR;
		}
	}
}

void delta (int x, int dw, int di, int s1, int s2, int n, int nodes) {
	Nodes[nodes + x].cnt += di;
	Nodes[nodes + x].sum += dw;
	update (nodes + x, s1, s2);
	if (n == 1)
		return;
	int p = x / 2;
	int np = (n + 1) / 2;
	if (x % 2 == 0)
		delta (p, dw, di, nodes + x, nodes + x + 1, np, nodes + n + 1);
	else
		delta (p, dw, di, nodes + x - 1, nodes + x, np, nodes + n + 1);
}
void deltaLeaf(int x, int dw, int di) {
	TNode n = Nodes[x];
	TB one = new TB ();
	one.idx = x;
	one.ans = n.sum + dw;
	n.L01.Assign (one);
	n.R01.Assign (one);
	delta (x, dw, di, root + 1, root + 1, this.n, 0);
}

void add (int x, int w) {
	deltaLeaf (x, w, 1);
}
void del (int x, int w) {
	deltaLeaf (x, -w, -1);
}

void check (int x, int X) {
	if (Nodes[root].cnt < 2)
		return;
	tryit (x, X, Nodes[root].L, Nodes[root].R, Nodes[root].ansLR);
}

private class ls implements Comparator <Integer> {
	int A[];

	ls (int a[]) {
		A = a;
	}

	public int compare(Integer i, Integer j) {
		if (A[i] == A[j])
			return 0;
		if (A[i] < A[j])
			return -1;
		return 1;
	}
}
public void run() throws IOException
{
	boolean oj = System.getProperty("ONLINE_JUDGE") != null;
	in = oj ? new Scanner(System.in) : new Scanner(new File("input.txt"));
	out = oj ? new PrintWriter(System.out) : new PrintWriter(new File("output.txt"));
	n = in.nextInt();

	for (int nn = n; nn > 1; nn = (nn + 1) / 2)
		root += nn + 1;
	Nodes = new TNode[root + 3];
	for (int i = 0; i < root + 3; ++i) {
		Nodes[i] = new TNode ();
		Nodes[i].L01 = new TB ();
		Nodes[i].R01 = new TB ();
	}
	Integer P[] = new Integer[n];
	X = new int[n];
	Y = new int[n];
	W = new int[n];
	YI = new int[n];
	ans = n * (long)-2E9 - 1;
	for (int i = 0; i < n; ++i) {
		X[i] = in.nextInt ();
		Y[i] = in.nextInt ();
		W[i] = in.nextInt ();
		P[i] = i;
	}
	Arrays.sort (P, new ls (this.X));
	Permute (P, X);
	Permute (P, Y);
	Permute (P, W);
	Arrays.sort (P, new ls (this.Y));
	for (int i = 0; i < n; ++i) {
		YI[P[i]] = i;
	}
	for (int i = 1; i < n; ++i) {
		if (Y[P[i]] == Y[P[i - 1]]) {
			YI[P[i]] = YI[P[i - 1]];
		}
	}
	for (int i = 0; i < n; ) {
		for (int j = i; j < n; ++j) {
			add (YI[j], W[j]);
			if (j + 1 == n || X[j] < X[j + 1]) {
				check (X[i], X[j]);
			}
		}
		for (; i < n; ++i) {
			del (YI[i], W[i]);
			if (i + 1 == n || X[i + 1] > X[i])
				break;
		}
		++i;
		if (i < n) {
			check (X[i], X[n - 1]);
		}
		for (int j = n - 1; j >= i; --j) {
			del (YI[j], W[j]);
			if (j > i && X[j] > X[j - 1]) {
				check (X[i], X[j - 1]);
			}
		}
		for (; i < n; ++i) {
			if (i + 1 == n || X[i + 1] > X[i])
				break;
		}
		++i;
	}
	int y = -1, Y = -1;
	for (int i = 0; i < n; ++i) {
		if (ayi == YI[i])
			y = this.Y[i];
		if (aYi == YI[i])
			Y = this.Y[i];
	}

	out.println(ax + " " + aX);
	out.println(y + " " + Y);
	out.flush();
}
}

