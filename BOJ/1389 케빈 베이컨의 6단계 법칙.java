// 2022-09-19
// 1389 케빈 베이컨의 6단계 법칙
// https://www.acmicpc.net/problem/1389
/*
    BFS (17,948KB, 228ms)
    시간 복잡도: ?
    풀이)
    - 1번부터 n번까지 유저를 선택. 이후 나머지 유저와의 거리를 구하며, 가장 짧은 값이 나온 유저가 정답.
    - 현재 유저를 st라 하며, i번 유저까지의 거리를 dist에 저장.
    - bfs를 이용하여 유저까지의 거리를 구함.
    만약 dist[i] != 0일 경우, i번 유저에게는 이미 도달한 적이 있음.
    - dist에 저장된 1번부터 n번까지의 값을 모두 더하여 sum에 저장.
    - sum과 이전에 구한 mn을 비교.
    만약 sum이 더 작을 경우, st를 ans에 저장.
 */

import java.util.*;

public class Main {

    static int INF = 0x3f3f3f3f;
    static int MAX = 103; // max n

    static ArrayList<Integer>[] path = new ArrayList[MAX];

    public static class pii {
        int pos, l;

        pii(int pos, int l) {
            this.pos = pos;
            this.l = l;
        }
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(), m = sc.nextInt();
        for (int i = 1; i <= n; i++)
            path[i] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            int pos = sc.nextInt(), l = sc.nextInt();

            path[pos].add(l);
            path[l].add(pos);
        }

        int ans = -1;
        int mn = INF;

        for (int st = 1; st <= n; st++) {
            int dist[] = new int[n + 1];
            Arrays.fill(dist, INF);
            dist[st] = 0;

            Queue<pii> q = new LinkedList<>();
            q.add(new pii(st, 0));

            // bfs
            while (q.size() != 0) {
                pii cur = q.poll();

                for (int next : path[cur.pos])
                    if (cur.l < dist[next]) {
                        dist[next] = cur.l + 1;
                        q.add(new pii(next, dist[next]));
                    }
            }

            int sum = 0;
            for (int i = 1; i <= n; i++)
                sum += dist[i];

            if (sum < mn) {
                mn = Integer.min(mn, sum);
                ans = st;
            }
        }

        System.out.println(ans);
    }
}
