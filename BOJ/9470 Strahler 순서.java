// 2022-11-22
// 9470 Strahler 순서
// https://www.acmicpc.net/problem/9470
/*
    위상정렬 (14,532KB, 136ms)
    시간 복잡도: ?
    풀이)
    - in_degree[]에 해당 노드에 들어오는 간선의 개수를 저장.
    - 맵 m에 해당 노드의 정보를 저장. (m[i] = {order, cnt}일 경우, i번 노드로 들어오는 간선의 가장 큰 순서는 order이며, 총 cnt개)
    - bfs를 이용하여 n번 노드의 정보를 구함.
    - 현재 노드 cur에서 갈 수 있는 다음 노드 next와 비교.
    만약 cur의 순서(m[cur].order)가 next보다 높은 경우, next의 순서를 변경.
    만약 cur의 순서와 next의 순서가 같을 경우, next의 횟수(m[next].cnt) +1
    만약 in_degree[next]가 0이 될 경우, next의 순서를 갱신할 수 있는지 확인.
     next의 횟수가 1일 경우, 순서는 그대로 유지.
     next의 횟수가 2 이상일 경우, 순서는 +1.
    - m[n]에 저장된 order를 출력.
    etc.)
    - 재밌었음. 초기화에 주의
    - 테케가 굉장히 약해보임
    참고)
    - 맵: https://wakestand.tistory.com/112
 */

import java.io.*;
import java.util.*;

public class Main {
    static class pii {
        int order, cnt;

        private pii(int order, int cnt) {
            this.order = order;
            this.cnt = cnt;
        }
    }

    static final int MAX = 1003; // max n

    static ArrayList<Integer>[] adj = new ArrayList[MAX];
    static int[] in_degree = new int[MAX];        // 노드로 들어오는 간선의 개수를 저장 (in_degree[i] = k일 경우, i번 노드에 들어오는 간선의 개수는 k개)
    static Map<Integer, pii> m = new HashMap<>(); // 노드의 정보를 저장 (m[i] = {order, cnt}일 경우, i번 노드로 들어오는 간선의 가장 큰 순서는 order이며, cnt개)

    static void bfs(int n) {
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            if (in_degree[i] == 0) {
                q.add(i);
                m.put(i, new pii(1, 1));
            }

        while (q.size() > 0) {
            int cur = q.poll();
            for (final int next : adj[cur]) {
                int a = m.getOrDefault(cur, new pii(0, 0)).order, b = m.getOrDefault(next, new pii(0, 0)).order;
                if (a > b) // 더 높은 순서일 경우, 순서를 변경함
                    m.put(next, new pii(a, 1));
                else if (a == b) // 같은 순서일 경우, 순서의 개수 +1
                    m.getOrDefault(next, new pii(0, 0)).cnt++;

                if (--in_degree[next] == 0) {
                    q.add(next);
                    if (m.getOrDefault(next, new pii(0, 0)).cnt >= 2) // next 노드의 순서를 정함
                        m.getOrDefault(next, new pii(0, 0)).order++;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int tc = Integer.parseInt(br.readLine()); // 1 ≤ tc ≤ 1000
        while (tc-- > 0) {
            for (int i = 0; i < MAX; i++)
                adj[i] = new ArrayList<>();
            Arrays.fill(in_degree, 0, MAX, 0);
            m.clear();

            StringTokenizer st = new StringTokenizer(br.readLine());
            int k = Integer.parseInt(st.nextToken()); // tc의 번호 k
            int n = Integer.parseInt(st.nextToken()); // 노드의 수 n(2 ≤ n ≤ 1,000)
            int p = Integer.parseInt(st.nextToken()); // 간선의 수 p

            for (int i = 0; i < p; i++) {
                st = new StringTokenizer(br.readLine());
                int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken()); // a에서 b로 흐름

                adj[a - 1].add(b - 1);
                in_degree[b - 1]++;
            }

            bfs(n);

            System.out.printf("%d %d\n", k, m.get(n - 1).order);
        }
    }
}