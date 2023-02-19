// 2023-02-18
// 1516 게임 개발
// https://www.acmicpc.net/problem/1516
/*
    위상정렬 (22,600KB, 276ms)
    시간 복잡도: ?
    풀이)
    - 해당 건물 cur의 건설 시간은 선행 건물의 건설 시간 중 최댓값 + cur의 건설 시간이다.
    그러므로, 각 건물의 최종 건설 시간을 dist에 저장하며, 각각의 건물만을 건설할 때의 시간을 t에 저장하여 사용한다.
    - 선행 건물의 개수를 저장할 in_degree[].
    - 선행 건물의 개수가 없을 경우, t를 dist에 저장한 후 큐에 넣어 탐색한다.
    - 큐에 넣은 값을 선행 건물로 하는 다른 건물을 탐색하여 --in_degree[]한다.
    dist에는 선행 건물의 건설 시간 중 최댓값을 저장한다. (이전 선행 건물 혹은 현재 선행 건물의 최댓값)
    만약 in_degree[] == 0이 될 경우, dist에 현재 건물의 건설 시간인 t를 추가한다.
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 503; // max n
 
     static int n; // 건물의 종류 수 (1 ≤ n ≤ 500)
     static ArrayList<Integer>[] adj = new ArrayList[MAX];
     static int[] t = new int[MAX], in_degree = new int[MAX]; // 건설 시간 t, 선행 개수 in_degree (t[i] = k일 경우, i번 건물만을 만드는데 필요한 시간은 k, in_degree[i] = k일 경우, i번 건물을 위해 필요한 선행 건물의 수는 k개)
 
     static int[] bfs() {
         int[] dist = new int[n];
 
         Queue<Integer> q = new LinkedList<>();
         for (int i = 0; i < n; i++)
             if (in_degree[i] == 0) // 선행 건물이 없을 경우
             {
                 q.add(i);
                 dist[i] = t[i];
             }
 
         while (q.size() > 0) {
             int cur = q.poll();
             for (final int nxt : adj[cur]) {
                 dist[nxt] = Math.max(dist[nxt], dist[cur]); // 선행 건물 중 최대 시간을 저장
                 if (--in_degree[nxt] == 0) {
                     q.add(nxt);
                     dist[nxt] += t[nxt]; // 선행 건물의 시간 + 현재 건물의 건설 시간
                 }
             }
         }
 
         return dist;
     }
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         StringTokenizer st;
 
         st = new StringTokenizer(br.readLine());
         n = Integer.parseInt(st.nextToken());
 
         for (int i = 0; i < n; i++)
             adj[i] = new ArrayList<>();
 
         for (int i = 0; i < n; i++) {
             st = new StringTokenizer(br.readLine());
             t[i] = Integer.parseInt(st.nextToken());
             while (st.hasMoreTokens()) {
                 int nxt = Integer.parseInt(st.nextToken());
                 if (nxt == -1)
                     break;
                 {
                     adj[nxt - 1].add(i);
                     in_degree[i]++;
                 }
             }
         }
 
         int[] dist = bfs();
 
         StringBuffer ans = new StringBuffer();
         for (final int i : dist)
             ans.append(i).append('\n');
         System.out.println(ans.toString());
     }
 }