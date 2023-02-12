// 2023-02-04
// 2294 동전 2
// https://www.acmicpc.net/problem/2294
/*
    DP (14,416KB, 140ms)
    시간 복잡도: ?
    풀이)
    - i개의 동전을 이용하여 만든 금액이면서 사용한 동전의 최소 개수를 저장할 dp.
    - i번 동전을 이용하여 구한 최소 개수를 이용하여 i+1번과 함께 만들 수 있는 최소 개수를 구함.
    금액 m에서 i+1번 동전의 가치만큼 뺀 dp값이 존재할 경우, 현재 dp값과 이전 dp값+1과 비교하여 최솟값을 저장.
    - 해당 금액을 만들 수 없을 경우, -1을 출력.
    etc.) 설명이 어려움
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int INF = 0x3f3f3f3f;
     static final int MAX = 103; // max n
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         StringTokenizer st = new StringTokenizer(br.readLine());
         int n = Integer.parseInt(st.nextToken());// 동전의 개수 n(1 ≤ n ≤ 100)
         int k = Integer.parseInt(st.nextToken()); // 원하는 가치 k(1 ≤ k ≤ 10,000)
 
         int[] v = new int[MAX];
         for (int i = 0; i < n; i++)
             v[i] = Integer.parseInt(br.readLine());
 
         int[] dp = new int[k + 1];
         Arrays.fill(dp, INF);
         dp[0] = 0;
         for (int i = 0; i < n; i++)
             for (int m = v[i]; m <= k; m++)
                 dp[m] = Math.min(dp[m], dp[m - v[i]] + 1);
 
         System.out.println(dp[k] == INF ? -1 : dp[k]);
     }
 }