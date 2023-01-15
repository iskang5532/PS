// 2023-01-12
// 27115 통신소
// https://www.acmicpc.net/problem/27115
/*
    BFS 426,988KB, 2,792ms)
    시간 복잡도: ?
    풀이)
    - bfs를 이용하여 전파가 닿는 구역을 구함.
    이때, 전파 세기가 강한 값이 우선적으로 탐색이 되어야 중복 탐색을 막을 수 있음.
    - 해당 위치에 도달한 전파의 남은 거리를 저장할 visited.
    - 입력된 통신소의 정보를 v에 저장한 후 세기 p를 기준으로 내림차순 정렬.
    - v에서 전파가 가장 센 값인 v.get(0)을 큐에 넣어 bfs 수행.
    이후, 나머지 값은 큐에 저장된 값과 비교하며 사용하거나 넘김. (v의 인덱스를 저장할 pos)
    큐에서 전파가 가장 센 값인 f.front()의 p와 v.get(pos).p를 비교.
    만약 두 전파가 같을 경우, 큐에 넣을지 판단.
    bfs를 이용하여 v.get(pos)의 위치에 도달한 적이 없을 경우 큐에 넣으며, 있을 경우 v.get(pos)의 p가 더 약하므로 넣지 않음.
    - 큐에 저장된 위치와 p를 이용하여 다음 위치를 구함.
    다음 위치의 visited와 p를 비교하며, 갱신이 가능한 경우 큐에 넣음.
    etc.)
    - 핵심은 v에 저장된 값을 큐에 한꺼번에 넣는게 아닌, 큐에 저장된 값을 봐가며 값을 넣어 항상 최대 p가 선택될 수 있게끔 해주는 것.
    이는 priority_queue와 같은 효과인듯 하며, 속도는 더 빠름. (= pq 사용시 TLE)
    참고)
    - 풀이: https://upload.acmicpc.net/4f56c116-3464-467c-8a59-f4aab43da360/
 */

import java.io.*;
import java.util.*;

public class Main {
    static class P {
        private int y, x, p;

        private P(int y, int x, int p) {
            this.y = y;
            this.x = x;
            this.p = p;
        }

        private Integer get_p() {
            return this.p;
        }
    };

    static final int MAX = 3003; // max n, m

    static final int[] dy = new int[] { -1, 0, 1, 0 }; // 북 서 남 동
    static final int[] dx = new int[] { 0, 1, 0, -1 };

    static int n, m, k; // 세로 및 가로 크기 n, m(1 ≤ n, m ≤ 3,000), 통신소의 개수 k(1 ≤ k ≤ 300,000)
    static int[][] visited = new int[MAX][MAX]; // visited[y][x] = k일 경우, (y, x)에서 전달할 수 있는 최대 거리는 k (2일 경우 전파가 전달된 곳이면서 2만큼 전달 가능하며, -1일 경우 전파가 전달되지 않은 곳)

    static boolean OOB(int ny, int nx) {
        return !(1 <= ny && ny <= n) || !(1 <= nx && nx <= m);
    }

    static void bfs(final ArrayList<P> v) {
        for (int i = 0; i < MAX; i++)
            Arrays.fill(visited[i], -1);

        Queue<P> q = new LinkedList<>();
        q.add(v.get(0));
        visited[v.get(0).y][v.get(0).x] = v.get(0).p; // 전파가 가장 센 값

        int pos = 1; // v의 인덱스
        while (q.size() > 0) {
            P cur = q.poll();
            int y = cur.y, x = cur.x, p = cur.p;
            while (pos != v.size() && v.get(pos).p == p) // v의 전파가 q의 전파와 동일한 경우 (= 큐에 넣음)
            {
                P _cur = v.get(pos);
                int _y = _cur.y, _x = _cur.x, _p = _cur.p;
                if (visited[_y][_x] < _p) // 현재 전파가 더 강한 경우 (= 해당 위치에 존재하는 전파보다 강함)
                {
                    q.add(new P(_y, _x, _p));
                    visited[_y][_x] = _p;
                }
                pos++;
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (OOB(ny, nx))
                    continue;
                if (visited[ny][nx] >= p - 1) // 해당 위치에 더 강한 전파가 존재할 경우
                    continue;

                visited[ny][nx] = p - 1;
                q.add(new P(ny, nx, p - 1));
            }
        }
    }

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());

        ArrayList<P> v = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            st = new StringTokenizer(br.readLine());

            int y = Integer.parseInt(st.nextToken()); // 세로
            int x = Integer.parseInt(st.nextToken()); // 가로
            int p = Integer.parseInt(st.nextToken()); // 전파 세기

            v.add(new P(y, x, p));
        }

        v.sort(Comparator.comparing(P::get_p).reversed()); // p를 기준으로 내림차순 정렬

        bfs(v);

        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (visited[i][j] != -1)
                    ans++;
        System.out.println(ans);
    }
}