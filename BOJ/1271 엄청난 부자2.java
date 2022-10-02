// 2022-09-30
// 1271 엄청난 부자2
// https://www.acmicpc.net/problem/1271
/*
    완전 탐색 (14,340KB, 124ms)
    시간 복잡도: ?
    풀이)
    - BigInteger를 이용하여 입력된 두 값 a, b를 저장.
    이후, BigInteger의 메소드를 이용하여 a/b 및 a%b 출력.
    참고)
    - 코드: https://www.acmicpc.net/board/view/52647
 */

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] v = br.readLine().split(" ");
        BigInteger a = new BigInteger(v[0]), b = new BigInteger(v[1]);

        System.out.println(a.divide(b));
        System.out.println(a.remainder(b));
    }
}