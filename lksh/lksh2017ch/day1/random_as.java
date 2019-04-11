import java.util.*;
import java.io.*;
import java.math.*;

public class random_as
{
	public static void main(String[] argv) throws IOException
	{
		new random_as().run();
	}
	Scanner in;
	PrintWriter out;
	int n, k;

	double m0[][];
	double m1[][];

	public void run() throws IOException
	{
		boolean oj = System.getProperty("ONLINE_JUDGE") != null;
		in = oj ? new Scanner(System.in) : new Scanner(new File("input.txt"));
		out = oj ? new PrintWriter(System.out) : new PrintWriter(new File("output.txt"));
		n = in.nextInt();
		k = in.nextInt();
		k -= 2*n;
		m0 = new double[2][n+1];
		m1 = new double[2][n+1];
		int lay = 1;
		for (int i=2; i<=n; i++){
			for (int j=1; j<i; j++){
				m0[lay][j] = (j * (m1[1-lay][j] + 1) + (i-1-j) * m0[1-lay][j]) / (i-1);
				m1[lay][j] = ((j-1) * m1[1-lay][j-1] + (i-j) * (m0[1-lay][j-1] + 1)) / (i-1);
			}
			for (int j = 1; j < i; j++) {
				out.println("m0[" + i + "][" + j + "] = " + m0[lay][j]);
				out.println("m1[" + i + "][" + j + "] = " + m0[lay][j]);
			}
			
			lay = 1-lay;
		}
		double res = (k * m1[1-lay][k] + (n-k) * m0[1-lay][k] + (n-k)) / n;
		out.println(res);		
		out.flush();
	}
}
