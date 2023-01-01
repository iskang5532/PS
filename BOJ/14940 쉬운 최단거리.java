// 2022-12-27
// 14940 쉬운 최단거리
// https://www.acmicpc.net/problem/14940
/*
    BFS (69,680KB, 740ms)
    시간 복잡도: ?
    풀이)
    - 지도를 board에 저장하며, 시작 지점을 st에 저장.
    - bfs를 이용하여 시작 지점에서 출발하여 도달할 수 있는 위치의 거리를 dist에 저장.
    최단 거리를 구해야 하므로, dist에 저장된 기존 값이 아닐 경우, 거리를 갱신하지 않는다.
    또한, board에 0인 부분은 도달할 수 없는 곳이므로 제외한다.
    - dist에 저장된 값을 출력한다.
    만약 도달한 적이 있을 경우, 값을 출력한다.
    만약 도달한 적이 없으면서 땅인 경우, -1을 출력한다.
    만약 도달한 적이 없으면서 땅이 아닌 경우, 0을 출력한다.
 */

 import java.io.*;
import java.util.*;

public class Main {
    static class pii {
        private int y, x;

        private pii(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    static final int INF = 0x3f3f3f3f;
    static final int MAX = 1003; // max n, m

    static int n, m; // 지도의 크기
    static int[][] board = new int[MAX][MAX];
    static int[][] dist = new int[MAX][MAX]; // dist[i][j] = k일 경우, 시작점에서 {i, j}까지의 거리는 k

    static boolean OOB(int ny, int nx) {
        return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
    }

    static void bfs(final pii st) {
        Queue<pii> q = new LinkedList<>();
        q.add(st);

        for (int[] _dist : dist)
            Arrays.fill(_dist, INF);
        dist[st.y][st.x] = 0; // 시작점의 거리

        final int[] dy = new int[] { -1, 0, 1, 0 }; // 북 서 남 동
        final int[] dx = new int[] { 0, 1, 0, -1 };
        while (q.size() > 0) {
            pii p = q.poll();
            int y = p.y, x = p.x;
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (OOB(ny, nx))
                    continue;
                if (dist[ny][nx] != INF || board[ny][nx] == 0) // 도달한 적이 있거나 갈 수 없는 곳인 경우
                    continue;

                q.add(new pii(ny, nx));
                dist[ny][nx] = dist[y][x] + 1;
            }
        }
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));

        StringTokenizer token = new StringTokenizer(br.readLine());
        n = Integer.parseInt(token.nextToken());
        m = Integer.parseInt(token.nextToken());

        pii st = new pii(-1, -1); // 시작 지점

        for (int i = 0; i < n; i++) {
            token = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; j++) {
                board[i][j] = Integer.parseInt(token.nextToken());
                if (board[i][j] == 2)
                    st = new pii(i, j);
            }
        }

        bfs(st);

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < n; i++, ans.append('\n'))
            for (int j = 0; j < m; j++)
                ans.append(dist[i][j] != INF ? Integer.toString(dist[i][j])     // 도달한 적이 있을 경우
                                             : (board[i][j] != 0 ? "-1" : "0")) // 땅인 부분에 도달할 수 없는 경우
                    .append(' ');

        System.out.println(ans.toString());
    }
}