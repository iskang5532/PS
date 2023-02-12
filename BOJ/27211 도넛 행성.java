// 2023-01-31
// 27211 도넛 행성
// https://www.acmicpc.net/problem/27211
/*
    BFS (116,480KB, 588ms)
    시간 복잡도: ?
    풀이)
    - bfs를 이용하여 빈 공간의 개수를 파악.
    기존 문제들과 다른 점은, 영역을 벗어날 경우 반대편으로 넘어가진다는 것이다.
    즉, 다음 위치 {ny, nx}를 구할 때 나머지 연산을 이용하여 반대편 값을 구한다.
    - 모든 위치를 확인하며, 현재 위치가 빈 공간일 경우, ans++하며 인접한 모든 빈 공간을 숲으로 덮는다.
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
    };

    static final int MAX = 1003; // max n, m

    static final int[] dy = new int[] { -1, 0, 1, 0 }; // 북 서 남 동
    static final int[] dx = new int[] { 0, 1, 0, -1 };

    static int n, m; // 2 ≤ n, m ≤ 1,000
    static boolean[][] forest = new boolean[MAX][MAX];

    static void bfs(final int st_y, final int st_x) // 빈 공간과 인접한 모든 빈 공간을 숲으로 채움
    {
        Queue<pii> q = new LinkedList<>();
        q.add(new pii(st_y, st_x));
        forest[st_y][st_x] = true; // 숲으로 덮음

        while (q.size() > 0) {
            pii cur = q.poll();
            for (int d = 0; d < 4; d++) {
                int ny = (n + cur.y + dy[d]) % n;
                int nx = (m + cur.x + dx[d]) % m;
                if (forest[ny][nx]) // 숲일 경우
                    continue;

                q.add(new pii(ny, nx));
                forest[ny][nx] = true;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < m; j++)
                forest[i][j] = Integer.parseInt(st.nextToken()) == 1 ? true : false;
        }

        int ans = 0;
        for (int y = 0; y < n; y++)
            for (int x = 0; x < m; x++)
                if (!forest[y][x]) // 숲이 아닐 경우 (= 빈 공간일 경우)
                {
                    ans++;
                    bfs(y, x);
                }

        System.out.println(ans);
    }
}