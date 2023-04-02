// 2023-03-28
// 8892 팰린드롬
// https://www.acmicpc.net/problem/8892
/*
    완전 탐색, 문자열 (68,956KB, 404ms)
    시간 복잡도: ?
    풀이)
    - 두 단어를 합쳐 만든 단어가 팰린드롬인지를 확인.
    - 단어의 개수는 최대 100 만들어진 단어의 길이는 최대 10,000이므로 최대 1억의 연산을 필요로 한다.
    즉, 완전 탐색을 이용하여 팰린드롬인 단어을 찾는다.
 */

import java.io.*;

public class Main {
    static int MAX = 103;// max k

    static String[] v = new String[MAX];

    static boolean isPalindrome(final String s) {
        for (int i = 0; i < s.length() >> 1; i++)
            if (s.charAt(i) != s.charAt(s.length() - 1 - i))
                return false;
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringBuilder sb = new StringBuilder();
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            int k = Integer.parseInt(br.readLine());
            for (int i = 0; i < k; i++)
                v[i] = br.readLine();

            String ans = "0";
            for (int i = 0; i < k; i++)
                for (int j = 0; j < k; j++)
                    if (i != j && isPalindrome(v[i] + v[j]))
                        ans = v[i] + v[j];

            sb.append(ans).append('\n');
        }
        System.out.println(sb.toString());
    }
}