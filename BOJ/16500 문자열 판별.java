// 2023-01-03
// 16500 문자열 판별
// https://www.acmicpc.net/problem/16500
/*
    DP (14,488KB, 128ms)
    시간 복잡도: ?
    풀이)
    - 입력된 n개의 단어를 셋 A에 저장.
    - 문자열 s의 i까지의 부분 문자열을 만들 수 있는지의 여부를 dp[]에 저장.
    - s[0]부터 부분 문자열이 A에 저장되어 있는지 확인.
    만약 있을 경우, dp의 값을 바꿈.
    - s[i]부터는 dp[i-1]이 true인지 확인 후 진행.
    만약 dp[i-1] == true일 경우, 이전까지의 부분 문자열은 만들 수 있는 문자열이므로, i부터 다시 구하면 됨.    
    etc.)
    - 맵, 트라이, dp를 섞어서 풀었다가 실패. (dp를 2차원으로 이래 저래 구현했지만 실패)
    - 설명이 어려움
    참고)
    - 이론: https://www.acmicpc.net/board/view/45056
 */

 import java.io.*;
 import java.util.*;
 
 class Main {
     static final int MAX = 103; // max s.length
 
     static Set<String> A = new HashSet<>();
 
     public static void main(String[] args) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
         String s = br.readLine(); // s.length() ≤ 100
         int n = Integer.parseInt(br.readLine()); // 문자열의 개수 (1 ≤ n ≤ 100)
         for (int i = 0; i < n; i++) {
             String word = br.readLine();
             A.add(word);
         }
 
         boolean[] dp = new boolean[MAX]; // dp[i] = true일 경우, s의 0부터 i까지의 부분 문자열은 만들 수 있음 (= s.substr(0, i+1)가 A에 포함됨)
         for (int st = 0; st < s.length(); st++) {
             if (st != 0 && !dp[st - 1]) // 이전까지의 부분 문자열을 만들 수 없을 경우
                 continue;
             for (int l = 1; st + l <= s.length(); l++) // l개의 문자
                 if (A.contains(s.substring(st, st + l)))
                     dp[st + l - 1] = true;
         }
 
         System.out.println(dp[s.length() - 1] ? "1" : "0");
     }
 }