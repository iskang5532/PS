// 2022-12-01
// 13022 늑대와 올바른 단어
// https://www.acmicpc.net/problem/13022
/*
    문자열 (14,248KB, 124ms)
    시간 복잡도: ?
    풀이)
    - 단어 wolf중 현재 탐색중인 문자의 위치를 저장할 pos, 연속되는 문자의 개수를 저장할 cnt, 이전 문자의 cnt를 저장할 prev.
    - 현재 문자를 확인.
    만약 이전 문자와 같을 경우, cnt++.
    만약 이전 문자와 다르면서 다음 문자가 wolf 순서와 맞는 경우
     - 이전에 나온 문자의 연속된 개수 prev를 화인.
     만약 prev != cnt일 경우, 개수가 다르므로 false.
     - cnt를 prev에 저장하며, 현재 문자의 개수인 cnt는 1로 변경. (s[pos]의 값)
    만약 이전 문자와 다르면서 다음 문자 또한 wolf 순서와 다른 경우, false.
    - 마지막 단어까지 모두 확인한 경우, 최종적으로 cnt와 prev를 비교 및 마지막 문자가 'f'로 끝났는지 확인.
    만약 아닐 경우, false.
    etc.) 정규표현식으로 풀어볼 것
 */

import java.io.*;

class Main {
    static final char ch[] = { 'w', 'o', 'l', 'f' };

    static boolean isValid(final String s) {
        int pos = 0, cnt = 0, prev = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ch[pos])
                cnt++;
            else if (s.charAt(i) == ch[(pos + 1) % 4]) // next ch
            {
                if (pos != 0 && cnt != prev) // 개수가 다른 경우
                    return false;
                prev = cnt;
                cnt = 1;
                pos = (pos + 1) % 4;
            } else // 순서가 올바르지 않음
                return false;
        }

        return (cnt != prev) || (pos != 3) ? false // 마지막 단어가 개수가 다르거나 순서가 다른 경우
                                           : true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String s = br.readLine();

        System.out.println(isValid(s) ? 1 : 0);
    }
}