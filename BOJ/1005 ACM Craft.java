// 2022-11-16
// 1005 ACM Craft
// https://www.acmicpc.net/problem/1005
/*
    위상정렬 (238,292KB, 832ms)
    시간 복잡도: ?
    풀이)
    - 단순하게 BFS로 구현할 시 TLE.
    i번 정점에 도달할 수 있는 정점들이 모두 도달했을 때, 비로소 i번 정점을 큐에 넣음. (반복적인 탐색을 방지; TLE 해결)
    - 해당 정점으로 올 수 있는 정점의 개수를 저장할 in_degree.
    - 해당 정점까지의 거리를 저장할 dist[]. (시간을 거리로 표현)
    in_degree[i] == 0이 되어야 i번 정점을 탐색할 수 있다.
    그러므로, dist[i]를 구할 때 이전 정점 prev의 dist 중에서 최댓값을 이용한다. (결국 i를 건설하기 위해서는 가장 큰 값을 거쳐야 하기 때문)
    - in_degree가 0인 정점들을 큐에 넣은 후 bfs.
    etc.) ed에서부터 역으로 탐색해도 될 줄 알았으나 WA.
    - 태그는 위상정렬과 DP인데 사용한건지 잘 모르겠다.
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222088685430
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 1003; // max n

    static int[] c = new int[MAX]; // 건물의 건설 시간
    static ArrayList<Integer>[] adj = new ArrayList[MAX];
    static int[] in_degree = new int[MAX]; // in_degree[i] = k일 경우, i번 건물을 건설하기 위해서는 인접한 k개의 건물이 완성되어야 함

    static int bfs(int n, int k, int ed) {
        int[] dist = new int[MAX];

        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            if (in_degree[i] == 0) {
                q.add(i);
                dist[i] = c[i];
            }

        while (q.size() > 0) {
            int cur = q.poll();

            for (final int next : adj[cur]) {
                dist[next] = Math.max(dist[next], dist[cur] + c[next]);

                if (--in_degree[next] == 0) // 더 이상 필요로 하는 건물이 없을 경우
                    q.add(next);
            }
        }
        return dist[ed];
    }

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            StringTokenizer st;

            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken()); // 건물의 개수 n(2 ≤ n ≤ 1,000),
            int k = Integer.parseInt(st.nextToken()); // 규칙의 개수 k(1 ≤ k ≤ 100,000)
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++)
                c[i] = Integer.parseInt(st.nextToken());

            for (int i = 0; i <= n; i++) { // 초기화
                adj[i] = new ArrayList<>();
                in_degree[i] = 0;
            }

            for (int i = 0; i < k; i++) {
                st = new StringTokenizer(br.readLine());
                int x = Integer.parseInt(st.nextToken()), y = Integer.parseInt(st.nextToken()); // 출발지 x, 도착지 y
                adj[x - 1].add(y - 1);

                in_degree[y - 1]++;
            }

            st = new StringTokenizer(br.readLine());
            int w = Integer.parseInt(st.nextToken()); // 필요 건물 w

            System.out.println(bfs(n, k, w - 1));
        }

    }
}