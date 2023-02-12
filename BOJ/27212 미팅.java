// 2023-02-01
// 27212 미팅
// https://www.acmicpc.net/problem/27212
/*
    DP (22,504KB, 172ms)
    시간 복잡도: ?
    풀이)
    - A와 B를 매칭하여 만들 수 있는 최대 만족도를 구하여 dp에 저장. (A1과 B1, A2와 B1, ... A1과 B2, ...)
    - 모든 A의 값을 이용하여 B와 매칭.
    현재 매칭된 값을 더하더라도 이전 매칭 중에 더 큰 만족도가 존재할 수 있음.
    이전 A값과 현재 B값까지의 만족도, 현재 A값과 이전 B값까지의 만족도, 이전 A와 B의 만족도와 현재 만족도를 비교하여 더 큰 값을 dp에 저장
    etc.)
    - 최적의 풀이인지 모르겠음.
    - 풀었지만 설명이 어려움. 증명을 못해서 그런듯
 */

import java.io.*;
import java.util.StringTokenizer;

public class Main {
    static final int MAX_C = 18; // 최대 배열 크기
    static final int MAX_N = 1003; // 최대 학생수

    static int[][] W = new int[MAX_C][MAX_C]; // 만족도
    static int[] A = new int[MAX_N], B = new int[MAX_N]; // 대학생

    static long max(long a, long b, long c) { return Math.max(a, Math.max(b, c)); }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken()); // 학생의 수 n, m(1 ≤ n, m ≤ 1,000)
        int m = Integer.parseInt(st.nextToken());
        int c = Integer.parseInt(st.nextToken()); // 배열의 크기 c(2 ≤ c ≤ 16)

        for (int i = 1; i <= c; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= c; j++)
                W[i][j] = Integer.parseInt(st.nextToken());
        }
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++)
            A[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < m; i++)
            B[i] = Integer.parseInt(st.nextToken());

        long[][] dp = new long[MAX_N][MAX_N]; // dp[i][j] = k일 경우, A의 i번과 B의 j번까지의 최대 만족도는 k
        for (int i = 1; i <= n; i++) // A
            for (int j = 1; j <= m; j++) // B
                dp[i][j] = max(dp[i - 1][j],                              // A-1과 B
                               dp[i][j - 1],                              // A와 B-1
                               dp[i - 1][j - 1] + W[A[i - 1]][B[j - 1]]); // A-1, B-1과 현재 값

        System.out.println(dp[n][m]);
    }
}