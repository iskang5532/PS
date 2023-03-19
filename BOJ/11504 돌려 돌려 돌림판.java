// 2023-03-18
// 11504 돌려 돌려 돌림판
// https://www.acmicpc.net/problem/11504
/*
    구현 (16,064KB, 176ms)
    시간 복잡도: ?
    풀이)
    - x와 y의 입력이 자릿수로 입력되므로, m개의 입력에 맞춰 수로 만들어주는 함수를 구현하여 사용.
    - 돌림판의 값을 board[]에 저장.
    - 지점 st에서부터 m개의 값을 이용하여 z를 만듦.
    st + i가 돌림판의 크기 n을 넘을 수 있으므로, 나머지 연산을 사용.
    etc.) 재밌는 문제
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 103; // max l

    static int[] board = new int[MAX];

    static int get_z(int st, int n, int m) // 돌림판에서 st의 위치에서 m개의 수를 이어 붙인 값을 반환
    {
        StringBuilder sb = new StringBuilder();

        for (int i = st; i < st + m; i++)
            sb.append(board[i % n]);

        return Integer.parseInt(sb.toString());
    }

    static int in_num(int m, StringTokenizer token) // m개의 수를 받아서 만든 값을 반환
    {
        StringBuilder sb = new StringBuilder();
        while (token.hasMoreElements())
            sb.append(token.nextToken());

        return Integer.parseInt(sb.toString());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringBuilder sb = new StringBuilder();
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            StringTokenizer token;
            token = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(token.nextToken()); // 등분 개수 n(1 ≤ n ≤ 100)
            int m = Integer.parseInt(token.nextToken()); // 수의 길이 m(1 ≤ m ≤ 9, m ≤ n)

            int x = in_num(m, new StringTokenizer(br.readLine()));
            int y = in_num(m, new StringTokenizer(br.readLine()));

            token = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++)
                board[i] = Integer.parseInt(token.nextToken());

            int cnt = 0;
            for (int st = 0; st < n; st++) {
                int z = get_z(st, n, m);
                if (x <= z && z <= y)
                    cnt++;
            }

            sb.append(cnt).append('\n');
        }

        System.out.println(sb.toString());
    }
}