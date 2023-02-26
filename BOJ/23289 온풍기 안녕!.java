// 2023-02-24
// 23289 온풍기 안녕!
// https://www.acmicpc.net/problem/23289
/*
    구현, 시뮬레이션 (16,984KB, 164ms)
    시간 복잡도: ?
    풀이)
    - 조사해야 하는 모든 칸의 온도가 k 이상이 되었을 경우, 반복한 횟수를 출력. 단, 최댓값은 101.
    - 조사해야 하는 칸의 정보를 v에 저장.
    - 입력된 벽을 2진수로 변환하여 2차원 배열 wall[][]에 저장. (wall[y][x] = 0b0011일 경우, (y, x)의 위와 좌측에 벽이 존재)
    - 온풍기에서 바람이 나와 퍼지는 온도는 항상 동일한다. 그러므로, 한 번 퍼졌을 때의 온도를 sum에 저장하여 사용한다.
    bfs()를 이용하여 sum을 구한다. 이때, 벽이 막고 있는지를 확인해야 한다.
     - 직선으로 이동 시에는 해당 위치와 다음 위치 사이에 벽이 있는지를 확인한다.
     - 대각선으로 이동 시에는 바람의 방향에 따른 벽을 고려해야 한다. (수직이 되도록 이동 후 바람의 방향에 맞춰 이동)
     만약 다음 위치가 1사분면일 경우, 우측으로 이동 후 위로 이동하는 과정에서 벽이 없어야 한다.
    - 집 안의 온도를 저장할 temp[][].
    1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
    - temp에 sum값을 더함.
    2. 온도가 조절됨
    - 해당 칸과 인접한 칸의 온도 차가 4 이상일 경우, 인접한 칸에 온도를 나눈다. (나눈 값은 t에 저장)
    - 큰 값에서 작은 값으로 퍼질 수 있는지를 조사한다.
    이는 기준이 되는 위치의 값이 인접한 칸보다 커야 하며, 만약 작을 경우 해당 칸이 기준으로 되었을 때 조절을 시도한다.
    3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
    - 바깥쪽 칸의 온도를 1씩 감소한다. 이때, 칸의 온도는 최소 0이다.
    4. 초콜릿을 하나 먹는다.
    choco++.
    5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
    - v에 저장된 값을 이용하여 칸의 온도가 k 이상인지 확인.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 23; // max n, m

    static class pii {
        private int y, x;

        private pii(int y, int x) {
            this.y = y;
            this.x = x;
        };
    };

    static class Board {
        private final int[] dy = new int[] { -1, 0, 1, 0 };
        private final int[] dx = new int[] { 0, 1, 0, -1 };

        private int r, c, k; // 크기 r, c(2 ≤ r, c ≤ 20), 온도 k(1 ≤ k ≤ 2,000)
        private int[][] board;
        private int[][] wall; // wall[y][x] = 0b0011일 경우, (y, x)의 위와 좌측에 벽이 존재
        private ArrayList<pii> v; // 조사해야 하는 칸을 저장

        private int[][] sum; // 바람이 한 번 나올 때의 온도
        private int[][] temp; // 온도

        Board() {
            board = new int[MAX][MAX];
            wall = new int[MAX][MAX];
            v = new ArrayList<>();

            sum = new int[MAX][MAX];
            temp = new int[MAX][MAX];
        };

        void input() throws IOException {
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            StringTokenizer st;

            st = new StringTokenizer(br.readLine());
            r = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());

            for (int i = 1; i <= r; i++) {
                st = new StringTokenizer(br.readLine());
                for (int j = 1; j <= c; j++) {
                    int p = Integer.parseInt(st.nextToken()); // 0: 빈 칸, 1: 우측, 2: 좌측, 3: 위, 4: 아래, 5: 조사
                    board[i][j] = (p == 0 || p == 5) ? -1
                                : (p == 1)           ?  1
                                : (p == 2)           ?  3
                                : (p == 3)           ?  0
                                :                       2;
                    if (p == 5)
                        v.add(new pii(i, j));
                }
            }

            int w = Integer.parseInt(br.readLine()); // 벽의 개수 (0 ≤ w ≤ r*c)
            for (int i = 0; i < w; i++) {
                st = new StringTokenizer(br.readLine());
                int y = Integer.parseInt(st.nextToken()), x = Integer.parseInt(st.nextToken());// 위치 (y, x)
                int t = Integer.parseInt(st.nextToken()); // 방향 t(0:위, 1:우측)

                wall[y][x] |= (1 << t);
                if (t == 0)
                    wall[y - 1][x] |= (1 << 2);
                else
                    wall[y][x + 1] |= (1 << 3);
            }
        };

        boolean OOB(int ny, int nx) {
            return !(1 <= ny && ny <= r) || !(1 <= nx && nx <= c);
        };

        @FunctionalInterface
        interface _Lambda {
            public boolean func(int y, int x, int ny, int nx, int dir, int d);
        };

        void get_sum() {
            _Lambda _has_wall = (y, x, ny, nx, dir, d) -> { // 해당 위치까지 벽이 있는지 확인
                if (d == 1) // 직선
                    return ((wall[y][x] & 1 << dir) >= 1) ? true : false;
                else if (dir == 0 || dir == 2) // 상하 (= 좌우 이동 후 상하 이동)
                {
                    if ((wall[y][x] & 1 << (d == 0 ? 3 : 1)) >= 1 ||
                            (wall[ny][nx] & 1 << (dir + 2) % 4) >= 1)
                        return true;
                } else if (dir == 1 || dir == 3) // 좌우 (= 상하 이동 후 좌우 이동)
                {
                    if ((wall[y][x] & 1 << (d == 0 ? 0 : 2)) >= 1 ||
                            (wall[ny][nx] & 1 << (dir + 2) % 4) >= 1)
                        return true;
                }
                return false;
            };

            for (int st_y = 1; st_y <= r; st_y++)
                for (int st_x = 1; st_x <= c; st_x++) {
                    if (board[st_y][st_x] == -1) // 빈 공간
                        continue;

                    int dir = board[st_y][st_x]; // 바람의 방향

                    Queue<pii> q = new LinkedList<>();
                    q.add(new pii(st_y + dy[dir], st_x + dx[dir])); // 선풍기의 앞에서부터 시작
                    int dist[][] = new int[MAX][MAX];
                    dist[st_y + dy[dir]][st_x + dx[dir]] = 5; // 초깃값 5

                    final int[][] _dy = new int[][] { { -1, -1, -1 }, { -1, 0, 1 }, { 1, 1, 1 }, { -1, 0, 1 } };
                    final int[][] _dx = new int[][] { { -1, 0, 1 }, { 1, 1, 1 }, { -1, 0, 1 }, { -1, -1, -1 } };
                    while (q.size() > 0) {
                        pii p = q.poll();
                        int y = p.y, x = p.x;

                        sum[y][x] += dist[y][x];

                        for (int d = 0; d < 3; d++) // 이동할 위치
                        {
                            int ny = y + _dy[dir][d], nx = x + _dx[dir][d];
                            if (OOB(ny, nx) || dist[ny][nx] != 0)
                                continue;
                            if (_has_wall.func(y, x, ny, nx, dir, d))
                                continue;

                            dist[ny][nx] = dist[y][x] - 1;
                            if (dist[ny][nx] != 0)
                                q.add(new pii(ny, nx));
                        }
                    }
                }
        }

        void flood() {
            for (int y = 1; y <= r; y++)
                for (int x = 1; x <= c; x++)
                    temp[y][x] += sum[y][x];
        }

        void control_temp() {
            int[][] t = new int[MAX][MAX]; // 조절될 온도
            for (int y = 1; y <= r; y++)
                for (int x = 1; x <= c; x++)
                    for (int d = 0; d < 4; d++) {
                        int ny = y + dy[d], nx = x + dx[d];
                        if (OOB(ny, nx) || (wall[y][x] & 1 << d) >= 1)
                            continue;

                        int k = temp[y][x] - temp[ny][nx]; // 온도 차
                        if (k >= 4) {
                            t[y][x] -= k / 4;
                            t[ny][nx] += k / 4;
                        }
                    }

            for (int y = 1; y <= r; y++)
                for (int x = 1; x <= c; x++)
                    temp[y][x] += t[y][x]; // 조절된 값을 합함
        }

        void decrease_temp() {
            for (int y = 1; y <= r; y++)
                for (int x = 1; x <= c; x++)
                    if (y == 1 || x == 1 || y == r || x == c) // 바깥쪽 칸의 온도 -1
                        temp[y][x] = Math.max(0, temp[y][x] - 1); // 단, 최소 온도는 0
        }

        boolean is_ended() // 조건을 만족한 경우
        {
            for (final pii p : v)
                if (temp[p.y][p.x] < k) // k 미만인 경우, 조건을 만족하지 않음
                    return false;

            return true;
        }

    };

    public static void main(String[] args) throws IOException {
        Board house = new Board();
        house.input();
        house.get_sum();

        int choco = 0;
        while (choco <= 100) {
            house.flood(); // 1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
            house.control_temp(); // 2. 온도가 조절됨
            house.decrease_temp(); // 3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
            choco++; // 4. 초콜릿을 하나 먹는다.

            if (house.is_ended()) // 5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사. 모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
                break;
        }

        System.out.println(choco);
    }
}