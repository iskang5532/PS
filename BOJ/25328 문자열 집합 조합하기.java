// 2022-12-30
// 25328 문자열 집합 조합하기
// https://www.acmicpc.net/problem/25328
/*
    맵, 백트래킹 (39,468KB, 568ms)
    시간 복잡도: ?
    풀이)
    - 문자열의 최대 길이는 17이므로, 부분 문자열을 구할 때는 3만번의 연산으로 구할 수 있다. (17C8 (k = 8일 경우))
    - 구한 부분 문자열을 횟수와 함께 맵에 저장하여 관리한다.
    - 부분 문자열을 구하는 과정에서, 해당 부분 문자열이 두 번 이상 나타난 경우 valid의 값을 true로 바꾼다.
    - valid에 맞춰 출력을 나눈다.
    만약 valid == false인 경우, -1을 출력한다. (두 번 이상 나온 부분 문자열이 없으므로)
    만약 valid == true인 경우, 맵을 이용하여 값을 출력한다.
    맵에서 꺼낸 문자열이 두 번 이상 나타난 경우, 문자열을 출력한다.
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 21; // max string length
     static Map<String, Integer> m = new TreeMap<>(); // {부분 문자열, 만든 횟수}
     static boolean valid; // 두 번 이상 나타나는 부분 문자열이 존재하는가?
     static boolean[] bits = new boolean[MAX];
 
     static void get_subs(final String s, int k, int dep, int pos) { // 백트래킹
         if (dep == k) {
             StringBuilder sb = new StringBuilder();
             for (int i = 0; i < bits.length; i++)
                 if (bits[i] == true)
                     sb.append(s.charAt(i));
 
             String subs = sb.toString();
             m.put(subs, (m.containsKey(subs) ? m.get(subs) : 0) + 1);
             if (m.get(subs) >= 2) // 두 번 이상인 경우
                 valid = true;
 
             return;
         }
 
         for (int i = pos; i < s.length(); i++) {
             bits[i] = true;
             get_subs(s, k, dep + 1, i + 1);
             bits[i] = false;
         }
     }
 
     public static void main(String[] argm) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
 
         String s1 = br.readLine(), s2 = br.readLine(), s3 = br.readLine();
         int k = Integer.parseInt(br.readLine());
 
         get_subs(s1, k, 0, 0);
         get_subs(s2, k, 0, 0);
         get_subs(s3, k, 0, 0);
 
         if (!valid)
             System.out.println(-1);
         else {
             StringBuilder ans = new StringBuilder();
             m.forEach((s, cnt) -> {
                 if (cnt >= 2)
                     ans.append(s).append('\n');
             });
             System.out.println(ans.toString());
         }
     }
 }