// 2023-02-08
// 11048 이동하기
// https://www.acmicpc.net/problem/11048
/*
    DP (78,512KB, 540ms)
    시간 복잡도: ?
    풀이)
    - dp를 이용하여 (y, x)에 도달할 때 모을 수 있는 사탕 개수의 최댓값을 저장.
    - 현재 위치가 (y, x)일 때, 다음에 도달할 수 있는 세 위치에 놓인 각각의 사탕을 이용하여 최댓값을 구함.
    (y, x)까지의 최댓값 dp[y][x]와 (ny, nx)에 놓인 사탕을 더한 값과 이전에 구한 최댓값 dp[ny][nx]를 비교하여 dp에 저장.
 */

 import java.io.*;
 import java.util.StringTokenizer;
 
 public class Main {
     static final int[] dy = new int[] { 0, 1, 1 };
     static final int[] dx = new int[] { 1, 1, 0 };
     static final int MAX = 1003; // max m, n
 
     static int n, m; // 1 ≤ n, m ≤ 1,000
     static int[][] board = new int[MAX][MAX];
     static int[][] dp = new int[MAX][MAX];
 
     static boolean OOB(int ny, int nx) {
         return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
     }
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         StringTokenizer st;
 
         st = new StringTokenizer(br.readLine());
         n = Integer.parseInt(st.nextToken());
         m = Integer.parseInt(st.nextToken());
         for (int i = 0; i < n; i++) {
             st = new StringTokenizer(br.readLine());
             for (int j = 0; j < m; j++)
                 board[i][j] = Integer.parseInt(st.nextToken());
         }
 
         dp[0][0] = board[0][0];
         for (int y = 0; y < n; y++)
             for (int x = 0; x < m; x++)
                 for (int d = 0; d < 3; d++) {
                     int ny = y + dy[d], nx = x + dx[d]; // 다음 위치
                     if (OOB(ny, nx))
                         continue;
 
                     dp[ny][nx] = Math.max(dp[ny][nx], dp[y][x] + board[ny][nx]); // 이전에 구한 최댓값과 비교
                 }
 
         System.out.println(dp[n - 1][m - 1]);
     }
 }