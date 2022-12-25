// 2022-12-25
// 17086 아기 상어 2
// https://www.acmicpc.net/problem/17086
/*
    BFS (14,68KB, 144ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값이 상어일 경우, dist에 INF의 값을 저장.
    - board를 이용하여 bfs.
    이때, dist가 INF일 경우 다음 위치는 1이며 아닐 경우 현재까지의 거리 + 1.
    - dist중 최댓값을 구함.
    주의할 점은 dist에 상어의 위치를 표시하기 위해 INF가 저장되어 있으므로, INF를 제외한 최댓값을 찾아야 함.
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

    static final int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // 북쪽부터 시계방향으로
    static final int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    static final int INF = 0x3f3f3f3f;
    static final int MAX = 53;

    static int n, m; // (2 ≤ N, M ≤ 50)
    static int[][] dist = new int[MAX][MAX]; // dist[y][x] = k일 경우, 가까운 상어로부터 {y, x}까지의 거리는 k (k == INF일 경우, {i, j}에는 상어가 위치)
    static Queue<pii> q = new LinkedList<>(); // 상어의 위치를 저장

    static boolean OOB(int ny, int nx) {
        return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
    }

    static void bfs() {
        while (q.size() > 0) {
            pii p = q.poll();
            int y = p.y, x = p.x;
            for (int d = 0; d < 8; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (OOB(ny, nx))
                    continue;
                if (dist[ny][nx] != 0) // 방문한 적이 있을 경우
                    continue;

                dist[ny][nx] = (dist[y][x] == INF ? 1
                                                  : dist[y][x] + 1);
                q.add(new pii(ny, nx));
            }
        }
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));

        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; j++) {
                int valid = Integer.parseInt(st.nextToken());
                if (valid == 1) // 상어?
                {
                    q.add(new pii(i, j));
                    dist[i][j] = INF;
                }
            }
        }
        
        bfs();

        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (dist[i][j] != INF) // 상어가 아닐 경우
                    ans = Math.max(ans, dist[i][j]);

        System.out.println(ans);
    }
}