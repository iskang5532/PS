// 2023-02-16
// 1766 문제집
// https://www.acmicpc.net/problem/1766
/*
    위상정렬 (46,472KB, 540ms)
    시간 복잡도: ?
    풀이)
    - 입력된 조건을 만족하면서 가능한 쉬운 문제를 우선적으로 출력해야 한다.
    그러므로 쉬운 문제를 먼저 탐색할 수 있도록 우선순위 큐를 사용한다.
    etc.)
    - 다른 식으로 풀다가 WA에 갇힌 문제
    - 기존 문제와 다른 점은 pq를 사용했다는 점.
    pq를 사용함으로 인해 큐에 값을 넣으면서 ret에 값을 넣는게 아닌, 큐에서 빼올 때 값을 추가해야 한다.
    참고)
    - 코드: https://blog.naver.com/jinhan814/222131303518
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 32003; // max n
 
     static int n, m; // 문제의 수 n(1 ≤ n ≤ 32,000), 정보의 개수 m(1 ≤ m ≤ 100,000)
     static ArrayList<Integer>[] adj = new ArrayList[MAX];
     static int[] in_degree = new int[MAX]; // in_degree[i] = k일 경우, i로 가는 정점의 개수는 k개
 
     static ArrayList<Integer> bfs() {
         ArrayList<Integer> ret = new ArrayList<>();
 
         PriorityQueue<Integer> pq = new PriorityQueue<>(); // 오름차순
         for (int i = 0; i < n; i++)
             if (in_degree[i] == 0)
                 pq.add(i);
 
         while (pq.size() > 0) {
             int cur = pq.poll();
             ret.add(cur);
             for (final int nxt : adj[cur])
                 if (--in_degree[nxt] == 0)
                     pq.add(nxt);
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
             int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
             {
                 adj[a - 1].add(b - 1);
                 in_degree[b - 1]++;
             }
         }
 
         StringBuffer ans = new StringBuffer();
         for (final int i : bfs())
             ans.append(i + 1).append(' ');
         System.out.println(ans);
     }
 }