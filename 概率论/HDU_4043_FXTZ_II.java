import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static BigInteger fz[] = new BigInteger[510], fm[] = new BigInteger[510];
    static Scanner cin = new Scanner(new BufferedInputStream(System.in));
    static int n, nCase;

    private static void init() {
        fz[1] = BigInteger.ONE;
        fm[1] = BigInteger.valueOf(2);
        for (int i = 2; i <= 500; i++) {
            fz[i] = fz[i-1].multiply(BigInteger.valueOf(2*i-1));
            fm[i] = fm[i-1].multiply(BigInteger.valueOf(2*i));
            BigInteger gcd = fz[i].gcd(fm[i]);
            fz[i] = fz[i].divide(gcd);
            fm[i] = fm[i].divide(gcd);
        }
    }

    public static void main(String[] args) {
        init();
        nCase = cin.nextInt();
        cin.nextLine();
        while (nCase-- > 0) {
            n = cin.nextInt();
            System.out.println(fz[n] + "/" + fm[n]);
        }
    }
}
