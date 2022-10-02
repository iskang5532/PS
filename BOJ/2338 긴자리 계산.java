// 2022-10-01
// 2338 긴자리 계산
// https://www.acmicpc.net/problem/1411
/*
    완전 탐색 (14,552KB, 144ms)
    시간 복잡도: ?
    풀이)
    - BigInteger를 이용하여 입력된 두 값 a, b를 저장.
    이후, BigInteger의 메소드를 이용하여 연산된 값을 출력.
 */

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        BigInteger a = new BigInteger(br.readLine()), b = new BigInteger(br.readLine());

        System.out.println(a.add(b));
        System.out.println(a.subtract(b));
        System.out.println(a.multiply(b));

    }
}