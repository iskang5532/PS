// 2023-03-05
// 15685 드래곤 커브
// https://www.acmicpc.net/problem/15685
/*
    구현 (14,392KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 세대에 맞는 커브 방향을 curve[]에 모두 구한 후 사용.
    curve에 저장된 기본 방향은 0이며, 입력으로 들어온 방향에 맞춰 curve 방향을 d만큼 회전하여 사용.
    - 이동한 위치는 board[][]에 저장.
    - 구한 board의 모든 위치에 대하여, 현재 위치와 우측, 하단, 우측 하단이 true일 경우 드래곤 커브의 일부이다.
 */

import java.io.*;
import java.util.*;

public class Main {

    final static int MAX = 103; // max size

    final static int[] dy = new int[] { 0, -1, 0, 1 }; // 서 북 동 남
    final static int[] dx = new int[] { 1, 0, -1, 0 };

    static boolean[][] board = new boolean[MAX][MAX];

    static class Info {
        private int x, y, d, g; // 시작 점 (x, y)(0 ≤ x, y ≤ 100), 방향 d(우측부터 반시계), 세대 g(0 ≤ g ≤ 10)

        private Info(int x, int y, int d, int g) {
            this.x = x;
            this.y = y;
            this.d = d;
            this.g = g;
        }
    };

    static ArrayList<Integer> get_curve() {
        ArrayList<Integer> ret = new ArrayList<>();
        ret.add(0);

        for (int i = 0; i < 13; i++) // max g
            for (int pos = ret.size() - 1; pos >= 0; --pos)
                ret.add((ret.get(pos) + 1) % 4);

        return ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 드래곤 커브의 개수 (1 ≤ n ≤ 20)

        ArrayList<Info> v = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            v.add(new Info(Integer.parseInt(st.nextToken()),
                    Integer.parseInt(st.nextToken()),
                    Integer.parseInt(st.nextToken()),
                    Integer.parseInt(st.nextToken())));
        }

        ArrayList<Integer> curve = get_curve();

        for (int i = 0; i < n; i++) {
            Info p = v.get(i);
            int x = p.x, y = p.y, d = p.d, g = p.g;
            board[y][x] = true;

            int ny = y, nx = x;
            for (int pos = 0; pos < (1 << g); pos++) {
                int nd = (curve.get(pos) + d) % 4;

                ny = ny + dy[nd];
                nx = nx + dx[nd];

                board[ny][nx] = true;
            }
        }

        int ans = 0;
        for (int y = 0; y < MAX - 1; y++)
            for (int x = 0; x < MAX - 1; x++)
                if (board[y][x] && board[y][x + 1] && board[y + 1][x] && board[y + 1][x + 1])
                    ans++;
        System.out.println(ans);
    }
}