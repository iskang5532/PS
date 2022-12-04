// 2022-11-29
// 6146 신아를 만나러
// https://www.acmicpc.net/problem/6146
/*
    BFS (42,888KB, 352ms)
    시간 복잡도: ?
    풀이)
    - 물웅덩이 및 해당 위치까지의 거리를 dist[][]에 저장.
    - 입력이 음수가 있으므로, 배열을 사용하기 위해서는 양수로 만들어야 함. 그러므로 최댓값인 500을 더함.
    - 시작점 (0 + C, 0 + C)를 큐에 넣어 bfs 수행.
    만약 다음 위치가 산이의 위치인 경우, 거리를 출력.
    - 물웅덩이의 값이 dist에서 -1로 사용해도 되는 이유는, bfs에서 반복적인 탐색에 영향을 주지 않기 때문이다.
    큐에 들어가기 위해서는 현재 탐색 중인 거리가 이전에 저장된 dist보다 작은 값이어야 한다.
    그러나, dist가 항상 최솟값이다. 탐색 도중 해당 위치에 도달하는 어떠한 값도 갱신될 일이 없어 큐에 넣어질 일은 없다.
 */


import java.io.*;
import java.util.*;

class Main {
    static class pii {
        private int y, x;

        pii(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    static final int INF = 0x3f3f3f3f;
    static final int MAX = 1003;
    static final int C = 500;
    static final int dy[] = { -1, 0, 1, 0 }; // 북 서 남 동
    static final int dx[] = { 0, 1, 0, -1 };

    static int[][] dist = new int[MAX][MAX];

    static boolean OOB(int ny, int nx) { return !(0 <= ny && ny < MAX) || !(0 <= nx && nx < MAX); };

    static int bfs(int ed_x, int ed_y) {
        Queue<pii> q = new LinkedList<>();
        q.add(new pii(C, C));

        dist[C][C] = 0;

        while (q.size() > 0) {
            pii p = q.poll();
            int y = p.y, x = p.x;

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (OOB(ny, nx))
                    continue;
                if (dist[ny][nx] <= dist[y][x] + 1) // 웅덩이 or 최소 거리가 아닌 경우
                    continue;

                if (ny == ed_y && nx == ed_x) // 목적지(신아의 위치)인 경우
                    return dist[y][x] + 1;

                q.add(new pii(ny, nx));
                dist[ny][nx] = dist[y][x] + 1;
            }
        }

        return dist[ed_y][ed_x];
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int x = Integer.parseInt(st.nextToken());
        int y = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());

        for (int[] row : dist)
            Arrays.fill(row, INF);

        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            int _x = Integer.parseInt(st.nextToken()), _y = Integer.parseInt(st.nextToken());

            dist[_y + C][_x + C] = -1;
        }

        System.out.println(bfs(x + C, y + C));
    }
}