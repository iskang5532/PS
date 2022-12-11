// 2022-12-07
// 5582 공통 부분 문자열
// https://www.acmicpc.net/problem/5582
/*
    DP (76,976KB, 252ms)
    시간 복잡도: ?
    풀이)
    - dp를 이용하여 공통 부분 문자열을 구함.
    - 연속된 문자열을 탐색해야 하므로, 이전에 구한 dp값을 계속해서 저장하지 않고 문자열이 같을 때만 값을 저장한다.
    또한, 저장할 값은 대각선 방향에 있는 값으로, 이전에 구한 현재 탐색중인 문자열의 개수 - 1개로 구한 부분 문자열의 길이다.
    etc.) 문제에서 t가 연속으로 나타나는 것이라 해서 헷갈림
    참고)
    - 이론: https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcYlE3S%2FbtqCvxtwlpJ%2FVMcA4jeZFUuPZWsXCaaFpK%2Fimg.png (https://gusdnd852.tistory.com/173)
    - 반례: https://www.ioi-jp.org/joi/2007/FinalRound/index.html
 */

 import java.io.*;

 class Main {
     final static int MAX = 4003; // max s.len
 
     public static void main(String[] argu) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
         String s1 = br.readLine(), s2 = br.readLine();
 
         int ans = 0;
         int[] prev = new int[MAX];
         for (int y = 1; y <= s1.length(); y++) {
             int[] cur = new int[MAX];
             for (int x = 1; x <= s2.length(); x++)
                 if (s1.charAt(y - 1) == s2.charAt(x - 1)) // 문자가 같을 경우, 이전에 구한 부분 문자열의 길이를 가져옴
                     ans = Math.max(ans,
                             cur[x] = prev[x - 1] + 1);
 
             prev = cur;
         }
 
         System.out.println(ans);
     }
 }
 
 // ba
 // aba
 // a b a
 // 0 0 0 0
 // b 0 0 1 0
 // a 0 1 0 2