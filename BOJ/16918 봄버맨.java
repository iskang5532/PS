
// 2023-03-13
// 16918 봄버맨
// https://www.acmicpc.net/problem/16918
/*
    구현 (15,236KB, 228ms)
    시간 복잡도: ?
    풀이)
    - 0초: 폭탄이 설치된 시간을 저장할 board[][]. 단, 설치된 폭탄이 없을 경우 -1로 표시. (= EMPTY)
    - 1초: 아무것도 하지 않음.
    - 2초: 설치되지 않은 모든 공간에 폭탄을 설치.
    - 3초: 3초 전에 설치된 모든 폭탄을 터트림.
     현재 위치의 폭탄이 3초 전에 설치된 폭탄일 경우, 인접한 네 방향의 폭탄을 터트림
     단, 인접한 폭탄 또한 3초 전에 설치된 폭탄일 경우 제외. (터트릴 경우 탐색에서 제외되므로 해당 폭탄과 인접한 폭탄을 터트릴 수 없음)
    - 4초 이후부터는 2초와 3초를 반복.
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int[] dy = new int[] { -1, 0, 1, 0 }; // 북 서 남 동
    final static int[] dx = new int[] { 0, 1, 0, -1 };

    final static int MAX = 203; // max r, c
    final static int EMPTY = -1;

    static int r, c, n; // 크기 r, c, 시간 n (1 ≤ r, c, n ≤ 200)
    static int[][] board = new int[MAX][MAX]; // board[y][x] = t일 경우, (y, x)의 폭탄은 t초에 설치됨 (단, -1일 경우 폭탄은 존재하지 않음)

    static boolean OOB(int ny, int nx) {
        return !(0 <= ny && ny < r) || !(0 <= nx && nx < c);
    }

    static void created_bomb(int t) // 빈 공간에 폭탄 생성
    {
        for (int y = 0; y < r; y++)
            for (int x = 0; x < c; x++)
                if (board[y][x] == EMPTY)
                    board[y][x] = t;
    }

    static void boom(int t) // 3초 전에 설치된 폭탄을 터트림
    {
        int k = t - 3;
        for (int y = 0; y < r; y++)
            for (int x = 0; x < c; x++)
                if (board[y][x] == k) // 터트려야 하는 폭탄일 경우, 인접한 네 방향의 폭탄을 터트림 (단, k와 같을 경우 제외)
                {
                    board[y][x] = EMPTY;
                    for (int d = 0; d < 4; d++) {
                        int ny = y + dy[d], nx = x + dx[d];
                        if (OOB(ny, nx) || board[ny][nx] == k) // k초를 가진 폭탄을 제외. 그래야 해당 폭탄과 인접한 다른 폭탄을 터트릴 수 있음
                            continue;
                        board[ny][nx] = EMPTY;
                    }
                }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());
        r = Integer.parseInt(st.nextToken());
        c = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());

        for (int i = 0; i < r; i++) {
            String s = br.readLine();
            for (int j = 0; j < c; j++) {
                char c = s.charAt(j);
                board[i][j] = (c == 'O') ? 0 // 0초
                        : EMPTY;
            }
        }

        for (int t = 2; t <= n; t++)
            if ((t & 1) == 0)
                created_bomb(t); // 짝수 시간
            else
                boom(t); // 홀수 시간

        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < r; y++) {
            for (int x = 0; x < c; x++)
                sb.append((board[y][x] == EMPTY) ? '.' : 'O');
            sb.append('\n');
        }

        System.out.println(sb.toString());
    }
}