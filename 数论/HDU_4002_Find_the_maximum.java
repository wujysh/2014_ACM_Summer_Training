import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    static int prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};
    static BigInteger sum[] = new BigInteger[55];
    static Scanner cin = new Scanner(new BufferedInputStream(System.in));
    static BigInteger n;
    static int nCase;

    private static void init() {
        sum[0] = BigInteger.valueOf(1);
        for (int i = 1; i < 55; i++) {
            sum[i] = sum[i - 1].multiply((BigInteger.valueOf(prime[i])));
        }
    }

    public static void main(String[] args) {
        init();
        nCase = cin.nextInt();
        cin.nextLine();
        while (nCase-- > 0) {
            String line = cin.nextLine();
            n = new BigInteger(line);

            int l = 1, r = 54;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (sum[mid].compareTo(n) > 0) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }

            if (sum[r].compareTo(n) <= 0) {
                System.out.println(sum[r]);
            } else {
                System.out.println(sum[l]);
            }
        }
    }
}
