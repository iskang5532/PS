// 2023-01-13
// 21966 (중략)
// https://www.acmicpc.net/problem/21966
/*
    문자열, 구현 (15.648KB, 148ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s를 이용하여 세 가지 규칙에 맞춰 출력한다.
    1. s의 길이가 25 이하인 경우, s를 출력한다.
    2. s에서 앞과 뒷 부분을 자른 부분 문자열이 모두 같은 문장에 속하는지 확인한다.
    이는, 부분 문자열 안에 존재하는 마침표가 마지막 위치인지 확인하면 된다. (마지막 위치에 존재하지 않을 경우, 서로 다른 문장)
    3. 앞과 뒷 부분을 잘라 출력하되, 중간에 '......'을 같이 출력한다.
 */

import java.io.*;

public class Main {
    static String get_ans(String s, int st, int ed, String dot) { // 정답 문자열 반환
        StringBuilder sb = new StringBuilder();

        sb.append(s.substring(0, st));
        sb.append(dot);
        sb.append(s.substring(s.length() - ed, s.length()));

        return sb.toString();
    }

    static boolean isValid(String s) { // 같은 문장에 속하는지 확인
        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) == '.' && i != s.length() - 1)
                return false;
        return true;
    }

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 글자의 길이 (2 ≤ n ≤ 100,000)
        String s = br.readLine();

        if (s.length() <= 25) // 1.
            System.out.println(s);
        else if (isValid(s.substring(11, s.length() - 11))) // 2.
            System.out.println(get_ans(s, 11, 11, "..."));
        else // 3.
            System.out.println(get_ans(s, 9, 10, "......"));
    }
}