// 2022-09-20
// 3460 이진수
// https://www.acmicpc.net/problem/3460
/*
    구현, 비트연산자 (17,376KB, 212ms)
    시간 복잡도: ?
    풀이)
    - 입력된 n의 첫 번째 비트(최우측 비트; LSB)를 확인 후, 비트를 우측으로 한칸 씩 옮김.
    만약 LSB가 1일 경우, 현재 탐색중인 비트의 위치인 i를 출력.
 */

import java.util.*;

public class Main {

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int tc = sc.nextInt();
        while (tc-- > 0) {
            int n = sc.nextInt();

            for (int i = 0; i < 32; i++, n >>= 1)
                if ((n & 1) == 1)
                    System.out.printf("%d ", i);
            System.out.println();
        }
    }
}
