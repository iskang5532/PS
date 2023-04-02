// 2023-03-26
// 10836 여왕벌
// https://www.acmicpc.net/problem/10836
/*
    구현 (282,900KB, 4,212ms)
    시간 복잡도: ?
    풀이)
    - m^2을 n번 수행할 경우 TLE.
    - 제일 왼쪽 열과 제일 위쪽 행을 제외한 나머지 값은 해당 위치의 첫 번째 행의 값과 동일하다.
    이를 이용하여 m^2의 연산을 하지 않아도 해당 위치의 값을 구할 수 있다.
    etc.) 어려웠던 문제.
    - 삼항연산자 반환값은 뒤에 적어야 함.
    - n번의 반복문 안에서 board의 값을 저장할 때, 작성한 코드에 따라 TLE 여부가 갈림.
 */

import java.io.*;
import java.util.*;

public class Main {
    static int MAX = 703;// max n, m

    static int[][] board = new int[MAX][MAX];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int m = Integer.parseInt(tk.nextToken()); // 크기 m(2 ≤ m ≤ 700)
        int n = Integer.parseInt(tk.nextToken()); // 날짜 수 n(1 ≤ n ≤ 1,000,000)
        for (int i = 0; i < n; i++) {
            int y = m - 1, x = 0;

            tk = new StringTokenizer(br.readLine());

            int cnt;
            for (int j = 0; j < 3; j++) {
                cnt = Integer.parseInt(tk.nextToken());
                while (y > 0 && cnt-- > 0)
                    board[y--][x] += j;
                while (cnt-- > 0)
                    board[y][x++] += j;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < m; y++, sb.append('\n'))
            for (int x = 0; x < m; x++)
                sb.append(1 + board[(x == 0) ? y : 0][x]).append(' '); // 제일 왼쪽 열과 제일 위쪽 행인지 확인하여 값을 출력

        System.out.println(sb.toString());
    }
}