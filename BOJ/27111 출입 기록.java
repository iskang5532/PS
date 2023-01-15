// 2023-01-08
// 27111 출입 기록
// https://www.acmicpc.net/problem/27111
/*
    구현 (57,256KB, 432ms)
    시간 복잡도: ?
    풀이)
    - visited[]에 해당 번호의 방문 여부를 저장.
    - a와 b를 입력받은 후 visited에 저장된 값을 이용하여 ans의 증감 여부를 결정.
    만약 visited[a]가 b와 긑은 경우, 반대되는 출입 기록이 사라졌으므로 ans++.
    - n개의 a와 b를 모두 입력받은 후, visited에 저장된 모든 값을 확인.
    만약 visited[i] == true일 경우, 나간 기록이 사라졌으므로 ans++.
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 200003; // max n
     static int[] visited = new int[MAX];
 
     public static void main(String[] argu) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         int n = Integer.parseInt(br.readLine()); // 기록의 개수 (1 ≤ n ≤ 200,000)
 
         int ans = 0;
         StringTokenizer st;
         for (int i = 0; i < n; i++) {
             st = new StringTokenizer(br.readLine());
 
             int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken()); // 번호 a, 출입 여부 b
 
             if (visited[a] == b) // 출입 여부와 같은 경우 (= 반대되는 출입 기록이 사라짐)
                 ans++;
             visited[a] = b;
         }
 
         for (int i = 0; i < MAX; i++)
             if (visited[i] == 1) // 방문한 상태인 경우 (= 나간 기록이 없는 경우)
                 ans++;
 
         System.out.println(ans);
     }
 }