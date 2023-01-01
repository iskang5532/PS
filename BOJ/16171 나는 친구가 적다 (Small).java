// 2023-01-01
// 16171 나는 친구가 적다 (Small)
// https://www.acmicpc.net/problem/16171
/*
    문자열 (14,312KB, 124ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s에서 숫자를 제거하여 새로운 문자열을 만든다.
    이후, string::find를 이용하여 s에 k가 포함되어 있는지 확인한다.
    만약 포함되어 있을 경우 1을, 아닐 경우 0을 출력한다.
 */

 import java.io.*;

 public class Main {
 
     static String get_s(final String s) {
         StringBuilder ret = new StringBuilder(); // s에서 숫자가 제외된 새로운 문자열
         for (final char c : s.toCharArray())
             if (!('0' <= c && c <= '9'))
                 ret.append(c);
 
         return ret.toString();
     }
 
     public static void main(String[] argm) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
 
         String s = br.readLine(), k = br.readLine();
         s = get_s(s);
 
         System.out.println(s.indexOf(k) != -1 ? 1 // k가 포함되어 있는가?
                                               : 0);
     }
 }