// 2022-11-23
// 14676 영우는 사기꾼?
// https://www.acmicpc.net/problem/14676
/*
    위상정렬 (72,904KB, 560ms)
    시간 복잡도: ?
    풀이)
    - 건물을 건설하기 위해 필요한 건물 종류의 개수를 저장할 in_degree[]
    - 건물의 건설된 개수를 저장할 cnt[].
    - a == 1일 경우
     - in_degree[cur] == 0일 경우, 해당 건물의 건설 조건이 충족되었으므로 건물을 건설.
     이때, cnt[cur] == 0일 경우, 해당 건물을 필요로 하는 건물들의 조건을 하나 충족하게 됨.
     그러므로 in_degree[next]--.
     건물을 건설하였으므로 cnt[cur]++.
     - in_degree[cur] != 0일 경우, 해당 건물의 건설 조건이 불충족이므로 건설할 수 없음.
    - a == 2일 경우
     건물을 파괴하므로 cnt[cur]--.
      - cnt[cur] == 0일 경우, cur을 필요로 하는 건물들의 조건을 하나 불충족하게 됨.
      그러므로 in_degree[next]--.
      - cnt[cur] < 0일 경우, 치트 사용. (건물의 개수가 음수)
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 100003; // max n

    static ArrayList<Integer>[] adj = new ArrayList[MAX]; // adj[i] = {a, b}일 경우, i번 건물을 건설하기 위해서는 a, b가 필요
    static int[] in_degree = new int[MAX];                // 선행 건물의 개수 (in_degree[i] = k일 경우, i번 건물을 건설하기 위해 필요한 건물의 종류가 k개)
    static int[] cnt = new int[MAX];                      // 건설된 횟수 (cnt[i] = k일 경우, i번 건물은 k번 건설됨)

    static boolean isValid(int a, int cur) // 건설 혹은 파괴가 가능한가?
    {
        if (a == 1) // create
            if (in_degree[cur] == 0) {
                if (cnt[cur] == 0) // 건설이 처음인 경우, 인접한 건물의 조건을 충족
                    for (final int next : adj[cur])
                        in_degree[next]--;
                cnt[cur]++;
            } else
                return false;
        else if (a == 2) // destroy
        {
            --cnt[cur];
            if (cnt[cur] == 0) // 모든 건물이 파괴된 경우, 불충족
                for (final int next : adj[cur])
                    in_degree[next]++;
            else if (cnt[cur] < 0) // 파괴할 건물이 없는데 파괴된 경우
                return false;
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken()); // 종류의 개수 n
        int m = Integer.parseInt(st.nextToken()); // 관계의 개수 m
        int k = Integer.parseInt(st.nextToken()); // 정보의 개수 k (1 ≤ n, m, k ≤ 100,000)

        for (int i = 0; i < MAX; i++)
            adj[i] = new ArrayList<>();
            
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken()), y = Integer.parseInt(st.nextToken()); // x를 건설해야 y를 건설할 수 있음 (1 ≤ x, y ≤ n)

            adj[x].add(y);
            in_degree[y]++;
        }

        boolean valid = true;
        for (int i = 0; i < k && valid; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken()), cur = Integer.parseInt(st.nextToken()); // 건설 혹은 파괴 여부 a, 건물의 번호 cur

            valid = (isValid(a, cur) ? true : false);
        }

        System.out.println(valid ? "King-God-Emperor" : "Lier!");
    }
}