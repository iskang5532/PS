// 2023-02-10
// 1065 한수
// https://www.acmicpc.net/problem/1065
/*
    완전 탐색 (14,228KB, 124ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 수의 길이가 크지 않으므로, 문자열로 변환 후 두 수의 차이를 구하여 한수의 개수를 구함.
    - 수의 길이가 1일 경우, 한수.
    - 수의 길이가 2 이상일 경우, 해당 문자열이 한수인지 확인.
    첫 번째와 두 번째의 수의 차이를 p에 저장한 후, 나머지 두 수의 차이를 확인.
    만약 p와 다른 경우, 해당 수는 한수가 아님.
 */

 import java.io.*;

 public class Main {
     static boolean isHansoo(int k) { // 한수인가?
         String s = Integer.toString(k);
         if (s.length() >= 2) {
             int p = (s.charAt(0) - '0') - (s.charAt(1) - '0'); // 기준 차이 값
             for (int i = 1; i < s.length() - 1; i++)
                 if ((s.charAt(i) - '0') - (s.charAt(i + 1) - '0') != p)
                     return false;
         }
 
         return true;
     }
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         int n = Integer.parseInt(br.readLine());
 
         int ans = 0;
         for (int k = 1; k <= n; k++)
             if (isHansoo(k))
                 ans++;
         System.out.println(ans);
     }
 }