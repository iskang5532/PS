// 2022-11-21
// 14567 선수과목 (Prerequisite)
// https://www.acmicpc.net/problem/14567
/*
    위상정렬 (130m888KB, 792ms)
    시간 복잡도: ?
    풀이)
    - cnt[]에 과목을 이수하기까지 필요한 학기의 수를 저장.
    - in_degree[]에 각 과목마다 필요한 선행 과목의 개수를 저장.
    수행하여 in_degree의 값이 0이 된 정점부터 큐에 넣어 bfs를 수행.
    만약 인접한 다음 정점의 in_degree가 0이 될 경우, cnt는 현재 정점의 cnt + 1의 값을 가지게 된다.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 1003; // max n

    static ArrayList<Integer> adj[] = new ArrayList[MAX];
    static int[] in_degree = new int[MAX]; // 필요한 선행 과목의 개수 (in_degree[i] = k일 경우, i번 과목의 선행 과목은 k개)
    static int[] cnt = new int[MAX]; // 필요한 학기 저장 (cnt[i] = k일 경우, i번 과목은 k학기에 이수할 수 있음)

    static void bfs(int n) {
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            if (in_degree[i] == 0) {
                q.add(i);
                cnt[i] = 1;
            }

        while (q.size() > 0) {
            int cur = q.poll();
            for (final int next : adj[cur])
                if (--in_degree[next] == 0) {
                    q.add(next);
                    cnt[next] = cnt[cur] + 1;
                }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken()); // 과목의 수 n(1 ≤ n ≤ 1,000)
        int m = Integer.parseInt(st.nextToken()); // 조건의 수 m(0 ≤ m ≤ 500,000)
        for (int i = 0; i < n; i++)
            adj[i] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());

            adj[a - 1].add(b - 1);
            in_degree[b - 1]++;
        }

        bfs(n);

        for (int i = 0; i < n; i++)
            System.out.printf("%d ", cnt[i]);
    }
}