import java.lang.*;
import java.math.*;
import java.io.*;
public class D {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String a = in.readLine();
        String b = in.readLine();
        BigInteger ba = new BigInteger(a);
        BigInteger bb = new BigInteger(b);
        BigInteger res = ba.multiply(bb);
        System.out.print(res.toString());
    }

}