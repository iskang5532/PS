// 2023-02-06
// 17070 파이프 옮기기 1
// https://www.acmicpc.net/problem/17070
/*
    DP (14,356KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 파이프는 (n, n)으로 이동해야 하므로, (0, 0)에서부터 (n, n)까지 각 위치에서 파이프의 방향의 개수를 저장하여 답을 구한다.
    dp[y][x][d] = k일 경우, (y, x)에서 방향 d인 파이프의 개수는 k개.
    - 파이프의 방향인 가로, 세로, 대각선에 따라 다음으로 이동할 수 있는 위치가 달라지므로, 상황에 맞게 구한다.
 */

 import java.io.*;
import java.util.StringTokenizer;

public class Main {
    static final int MAX = 20; // max n
    static final int R = 0, RD = 1, D = 2; // 가로 R, 대각선 RD, 세로 D

    static int n; // 집의 크기 (3 ≤ n ≤ 16)
    static boolean[][] wall = new boolean[MAX][MAX];
    static int[][][] dp = new int[MAX][MAX][3]; // dp[y][x][d] = k일 경우, (y, x)에서 방향 d인 파이프의 개수는 k개

    static boolean OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < n); }

    static void get_dp(int y, int x) {
        for (final int cur_dir : new int[] { R, RD, D }) // 파이프의 현재 방향
        {
            int k = dp[y][x][cur_dir];

            final int d[][] = { { R, RD }, { R, RD, D }, { RD, D } }; // 파이프가 바라볼 수 있는 방향
            for (final int nxt_dir : d[cur_dir]) // 파이프의 다음 방향
            {
                if (nxt_dir == R)
                    if (!OOB(y, x + 1) && !wall[y][x + 1])
                        dp[y][x + 1][nxt_dir] += k;
                if (nxt_dir == RD)
                    if (!OOB(y, x + 1) && !OOB(y + 1, x + 1) && !(OOB(y + 1, x)) &&
                            !wall[y][x + 1] && !wall[y + 1][x + 1] && !wall[y + 1][x])
                        dp[y + 1][x + 1][nxt_dir] += k;
                if (nxt_dir == D)
                    if (!OOB(y + 1, x) && !wall[y + 1][x])
                        dp[y + 1][x][nxt_dir] += k;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        n = Integer.parseInt(br.readLine());

        StringTokenizer st;
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < n; j++)
                wall[i][j] = (Integer.parseInt(st.nextToken()) == 0 ? false : true);
        }

        dp[0][1][R] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!wall[i][j])
                    get_dp(i, j);

        System.out.println(dp[n - 1][n - 1][R] +
                dp[n - 1][n - 1][RD] +
                dp[n - 1][n - 1][D]);
    }
}