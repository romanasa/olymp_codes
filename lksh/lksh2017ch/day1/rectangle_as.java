import java.util.*;
import java.io.*;
import java.math.*;

public class rectangle_as
{
	public static void main(String[] argv) throws IOException
	{
		new rectangle_as().run();
	}

	public static final long INF = (1L << 62);

	Scanner in;
	PrintWriter out;
	
	public class Point{
		int coords[];
		int ny;
		long w;

		Point(int x, int y, long ww){
			coords = new int[2];
			coords[0] = x;
			coords[1] = y;
			ny = y;
			w = ww;
		}

		public int getX(){
			return coords[0];
		}

		public int getY(){
			return coords[1];
		}
	}

	private class PointsCompare implements Comparator <Point>{
		int cnum;

		PointsCompare(int coord){
			cnum = coord;
		}

		public int compare(Point p1, Point p2){
			int x1 = p1.coords[cnum];
			int x2 = p2.coords[cnum];
			if (x1 < x2) return -1;
			if (x1 > x2) return 1;
			return 0;
		}
	}

	int n;
	Point points[];	
	int real_y[];


	int nn, ts;
	long lans[], rans[], mans[];
	long total[];
	int quant[];
	int lx[], rx[], mlx[], mrx[];

	public void initTree(){
		for (nn=1; nn<n; nn<<=1);
		ts = 2*nn;
		lans = new long[ts];
		rans = new long[ts];
		mans = new long[ts];
		total = new long[ts];
		quant = new int[ts];
		lx = new int[ts];
		rx = new int[ts];
		mlx = new int[ts];
		mrx = new int[ts];
	}

	public void clearTree(){
		Arrays.fill(lans, -INF);
		Arrays.fill(rans, -INF);
		Arrays.fill(mans, -INF);
		Arrays.fill(total, 0);
		Arrays.fill(quant, 0);
		for (int i=nn; i<ts; i++){
			lx[i] = rx[i] = mlx[i] = mrx[i] = i-nn;
		}
	}

	public void addPoint(int x, long val){
		x += nn;

		total[x] += val;
		quant[x]++;
		lans[x] = rans[x] = total[x];
		if (quant[x] >= 2){
			mans[x] = total[x];
		}

		x >>= 1;
		while (x > 0){
			
			int ls = 2*x;
			int rs = 2*x + 1;
			
			total[x] = total[ls] + total[rs];
			quant[x] = quant[ls] + quant[rs];

			lans[x] = lans[ls];
			lx[x] = lx[ls];
			if (lans[rs] > -INF){
				long tmp = lans[rs] + total[ls];
				if (lans[x] < tmp){
					lans[x] = tmp;
					lx[x] = lx[rs];
				}
			}

			rans[x] = rans[rs];
			rx[x] = rx[rs];
			if (rans[ls] > -INF){
				long tmp = rans[ls] + total[rs];
				if (rans[x] < tmp){
					rans[x] = tmp;
					rx[x] = rx[ls];
				}
			}

			if (mans[ls] < mans[rs]){
				mans[x] = mans[rs];
				mlx[x] = mlx[rs];
				mrx[x] = mrx[rs];
			}			
			else{
				mans[x] = mans[ls];
				mlx[x] = mlx[ls];
				mrx[x] = mrx[ls];
			}
			if (rans[ls] > -INF && lans[rs] > -INF){
				long tmp = rans[ls] + lans[rs];
				if (mans[x] < tmp){
					mans[x] = tmp;
					mlx[x] = rx[ls];
					mrx[x] = lx[rs];
				}
			}

			x >>= 1;
		}
	}

	long bw;
	int bx, by, BX, BY;

	public void relax_answer(int cx, int CX){
		if (mans[1] > bw){
			bw = mans[1];
			bx = cx;
			BX = CX;
			by = real_y[mlx[1]];
			BY = real_y[mrx[1]];
		}
	}

	public void run() throws IOException
	{
		boolean oj = System.getProperty("ONLINE_JUDGE") != null;
		in = oj ? new Scanner(System.in) : new Scanner(new File("input.txt"));
		out = oj ? new PrintWriter(System.out) : new PrintWriter(new File("output.txt"));
		n = in.nextInt();

		points = new Point[n];

		for (int i=0; i<n; i++){
			int x = in.nextInt();
			int y = in.nextInt();
			long w = in.nextLong();
			points[i] = new Point(x, y, w);
		}

		Arrays.sort(points, new PointsCompare(1));
		
		real_y = new int[n];
		real_y[0] = points[0].getY();
		points[0].ny = 0;
		for (int i=1; i<n; i++){
			points[i].ny = points[i-1].ny;
			if (points[i].getY() != points[i-1].getY()){
				points[i].ny++;
				real_y[points[i].ny] = points[i].getY();
			}
		}

		Arrays.sort(points, new PointsCompare(0));
		
		bw = -INF;

		initTree();
		for (int i=0; i<n; i++){
			if (i>0 && points[i].getX() == points[i-1].getX()){
				continue;
			}
			clearTree();
			for (int j=i; j<n; j++){
				addPoint(points[j].ny, points[j].w);
				if (j==n-1 || points[j].getX() != points[j+1].getX()){
					relax_answer(points[i].getX(), points[j].getX());
				}
			}
		}

		out.println(bx + " " + BX);
		out.println(by + " " + BY);
		out.flush();
	}
}
