// 2023-02-15
// 2623 음악프로그램
// https://www.acmicpc.net/problem/2623
/*
    위상정렬 (15,044KB, 148ms)
    시간 복잡도: ?
    풀이)
    - 가수의 번호를 하나의 정점으로 생각하며, 정점 간 연결된 값을 ans에 저장하여 출력한다.
    이때, ans 원소의 개수가 n개가 아니면 사이클이 존재한다는 것이므로 0을 출력한다.
    - in_degree[]에 해당 정점이 도착지인 정점의 개수를 저장하며, 탐색 도중 0이 되었을 경우 큐 및 ret에 추가.
    etc.)
    - 출력이 n개의 줄로 이뤄져야 함. 즉, 입력에 존재하지 않는 가수 또한 출력에 있어야 함.
 */

 import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 1003; // max n

    static int n, m; // 가수의 수 n(1 ≤ n ≤ 1,000), PD의 수 m(1 ≤ m ≤ 100)
    static ArrayList<Integer>[] adj = new ArrayList[MAX];
    static int[] in_degree = new int[MAX]; // in_degree[i] = k일 경우, i로 도착하는 정점은 k개

    static ArrayList<Integer> bfs() {
        ArrayList<Integer> ret = new ArrayList<>();

        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++)
            if (in_degree[i] == 0) {
                q.add(i);
                ret.add(i);
            }

        while (q.size() > 0) {
            int cur = q.poll();
            for (final int nxt : adj[cur])
                if (--in_degree[nxt] == 0) {
                    q.add(nxt);
                    ret.add(nxt);
                }
        }

        return ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        for (int i = 0; i < n; i++)
            adj[i] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());

            int p = Integer.parseInt(st.nextToken());
            { // 입력된 값들을 이용하여 정점 간 간선을 연결
                int[] v = new int[MAX];
                for (int j = 0; j < p; j++) {
                    v[j] = Integer.parseInt(st.nextToken());
                    v[j]--;
                }

                for (int j = 0; j < p - 1; j++) {
                    adj[v[j]].add(v[j + 1]);
                    in_degree[v[j + 1]]++;
                }
            }
        }

        ArrayList<Integer> v = bfs();

        StringBuffer ans = new StringBuffer();
        if (v.size() != n)
            ans.append(0);
        else
            for (final int i : v)
                ans.append(i + 1).append('\n');
        System.out.println(ans.toString());
    }
}