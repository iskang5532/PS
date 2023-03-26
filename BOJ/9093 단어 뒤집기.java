// 2023-03-22
// 9093 단어 뒤집기
// https://www.acmicpc.net/problem/9093
/*
    구현, 문자열 (2,024KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 문장에서 단어를 뽑은 후, 뒤집어 ans에 공백과 함께 저장.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int tc = Integer.parseInt(br.readLine());

        StringBuilder ans = new StringBuilder();
        while (tc-- > 0) {
            StringTokenizer tk = new StringTokenizer(br.readLine());
            while (tk.hasMoreTokens())
                ans.append(new StringBuffer(tk.nextToken()).reverse())
                   .append(' ');
            ans.append('\n');
        }

        System.out.println(ans.toString());
    }
}