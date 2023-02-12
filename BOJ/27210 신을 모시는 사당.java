// 2023-01-30
// 27210 신을 모시는 사당
// https://www.acmicpc.net/problem/27210
/*
    누적 합 (23,236KB, 304ms)
    시간 복잡도: ?
    풀이)
    - 각 방향의 최댓값을 구한 후 더 큰 값을 출력한다.
    - 바라보는 방향이 기준 방향 dir과 같을 경우 pSum++, 다를 경우 pSum--하며, 최대 sum값을 저장하여 반환한다.
    만약 음수가 될 경우, 해당 위치까지는 사용하지 않으면 되므로 0으로 대체한다.
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 100003; // max m
     static final int LEFT = 1;
     static final int RIGHT = 2;
 
     static int n;
     static int[] v = new int[MAX]; // 돌상의 개수 n(1 ≤ n ≤ 100,000)
 
     static int get_ans(int dir) {
         int ret = 0, pSum = 0; // 최댓값 ret, 누적 합 pSum
         for (int i = 0; i < n; i++) {
             pSum += (v[i] == dir ? 1 : -1); // 기준 방향과 일치하는가?
             pSum = Math.max(pSum, 0);
 
             ret = Math.max(ret, pSum);
         }
 
         return ret;
     }
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         n = Integer.parseInt(br.readLine());
 
         StringTokenizer st = new StringTokenizer(br.readLine());
         for (int i = 0; i < n; i++)
             v[i] = Integer.parseInt(st.nextToken());
 
         System.out.println(Math.max(get_ans(LEFT), get_ans(RIGHT)));
     }
 }