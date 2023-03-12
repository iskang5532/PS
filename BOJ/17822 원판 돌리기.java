// 2023-03-09
// 17822 원판 돌리기
// https://www.acmicpc.net/problem/17822
/*
    구현 (18,464KB, 188ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 2차원 공간에 저장.
    입력된 회전 방향 d가 시계 방향일 경우 뒤 값을 앞으로, 반시계 방향일 경우 앞 값을 뒤로 옮긴다.
    - 모든 위치에 대하여 인접한 값이 같은지를 확인한다.
    같은 값이 존재할 경우, 두 값 모두 삭제한다. (삭제란 컨테이너의 크기를 줄이거나 하지는 않음)
    삭제한 값을 한 번에 갱신하기 위하여 del[][]에 해당 위치에 대한 삭제 여부를 저장하며, 현재 회전하는 동안의 삭제 여부를 isDel에 저장.
    - isDel을 이용하여 값을 제거할지, 평균을 구하여 값을 갱신할지 정한다.
    주의할 점은, 나눈 값이 실수형일 수 있으며 평균과 같은 값일 경우 아무것도 하지 않아야 한다.
    etc.) 뒤로 밀거나 앞으로 당기는 로직을 구현하는 것이 헷갈림
    - 평균을 구하는 데에 한 번, nx를 구하는 데에 한 번 데임.
 */

 import java.io.*;
import java.util.*;

public class Main {
    final static int INF = 0x3f3f3f3f;
    final static int MAX = 53; // max n, m

    final static int[] dy = new int[] { -1, 0, 1, 0 }; // 북 서 남 동
    final static int[] dx = new int[] { 0, 1, 0, -1 };

    static int n, m, t; // 원판의 크기 n, 정수의 개수 m(2 ≤ n, m ≤ 50), 회전 횟수 t(1 ≤ t ≤ 50)
    static int[][] board = new int[MAX][MAX];
    static int[] pos = new int[MAX];

    static boolean OOB(int ny, int nx) {
        return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        t = Integer.parseInt(st.nextToken());

        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; j++)
                board[i][j] = Integer.parseInt(st.nextToken()); // 1 ≤ k ≤ 1,000
        }

        for (int ii = 0; ii < t; ii++) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken()); // 회전할 원판 번호 x(2 ≤ n ≤ n)
            int d = Integer.parseInt(st.nextToken()); // 방향 d(0: 시계, 1: 반시계)
            int k = Integer.parseInt(st.nextToken()); // 이동 횟수 k(1 ≤ k ≤ m)

            for (int pos = x; pos <= n; pos += x)
                for (int i = 0; i < k; i++)
                    if (d == 0) // 시계
                    {
                        int tmp = board[pos - 1][m - 1];
                        for (int j = m - 1; j > 0; --j)
                            board[pos - 1][j] = board[pos - 1][j - 1];
                        board[pos - 1][0] = tmp;

                    } else // 반시계
                    {
                        int tmp = board[pos - 1][0];
                        for (int j = 0; j < m - 1; j++)
                            board[pos - 1][j] = board[pos - 1][j + 1];
                        board[pos - 1][m - 1] = tmp;
                    }


            int cnt = 0, sum = 0; // 값의 개수 cnt와 합 sum
            boolean[][] del = new boolean[MAX][MAX];
            boolean isDel = false; // 삭제 여부 del[][], 이번 회전에 삭제한 적이 있는지를 저장할 isDel
            for (int _y = 0; _y < n; _y++)
                for (int _x = 0; _x < m; _x++) {
                    if (board[_y][_x] == INF)
                        continue;

                    int val = board[_y][_x];
                    cnt++;
                    sum += val; // 값을 저장
                    for (int _d = 0; _d < 4; _d++) {
                        int ny = _y + dy[_d];
                        int nx = (m + _x + dx[_d]) % m;
                        if (OOB(ny, nx))
                            continue;
                        if (board[ny][nx] == val) // 인접한 값이 현재 값과 동일한가
                        {
                            del[_y][_x] = del[ny][nx] = true;
                            isDel = true;
                        }
                    }
                }

            if (isDel) // 삭제한 적이 있는가?
            {
                for (int _y = 0; _y < n; _y++)
                    for (int _x = 0; _x < m; _x++)
                        if (del[_y][_x])
                            board[_y][_x] = INF;
            } else {
                double avg = (double) sum / cnt;
                for (int _y = 0; _y < n; _y++)
                    for (int _x = 0; _x < m; _x++) {
                        if (board[_y][_x] == INF)
                            continue;

                        if (board[_y][_x] < avg) // 평균 미만
                            board[_y][_x] += 1;
                        else if (board[_y][_x] > avg) // 평균 초과
                            board[_y][_x] -= 1;
                    }
            }
        }

        int ans = 0;
        for (int _y = 0; _y < n; _y++)
            for (int x = 0; x < m; x++)
                if (board[_y][x] != INF)
                    ans += board[_y][x];
        System.out.println(ans);
    }
}