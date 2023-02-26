// 2023-02-25
// 10813 공 바꾸기
// https://www.acmicpc.net/problem/10813
/*
    구현 (14,232KB, 128ms)
    시간 복잡도: ?
    풀이)
    - v[]에 값을 넣은 후, 입력된 a와 b에 맞춰 v[a]와 v[b]를 스왑한다.
    이후, 1부터 n까지 v의 값을 출력한다.
    etc.) swap 라이브러리가 없나?
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 103; // max n
 
     static final int[] v = new int[MAX];
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         StringTokenizer st;
 
         st = new StringTokenizer(br.readLine());
         int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()); // 공의 개수 n(1 ≤ n ≤ 100), 스왑 횟수 m(1 ≤ m ≤ 100)
 
         for (int i = 0; i < MAX; i++)
             v[i] = i;
 
         for (int i = 0; i < m; i++) {
             st = new StringTokenizer(br.readLine());
             int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
 
             int temp = v[a];
             v[a] = v[b];
             v[b] = temp;
         }
 
         StringBuffer ans = new StringBuffer();
         for (int i = 1; i <= n; i++)
             ans.append(v[i]).append(' ');
         System.out.println(ans.toString());
     }
 }