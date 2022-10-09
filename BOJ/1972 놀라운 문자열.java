// 2022-10-06
// 1972 놀라운 문자열
// https://www.acmicpc.net/problem/1972
/*
    완전 탐색, 셋 (15,132KB, 164ms)
    시간 복잡도: O(n(n+1)(n+2)/6)??
    풀이)
    - D-쌍을 이루는 문자열 s가 중복되면 안되므로, 중복을 구별할 수 있도록 셋 S를 사용.
    - s가 S에 존재하는지 확인.
    만약 존재하지 않을 경우, 현재까지는 유일한 쌍. 셋에 s를 추가.
    만약 존재할 경우, 유일한 쌍이 아님.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

public class Main {

    static boolean isValid(String word) {
        for (int l = 1; l < word.length() - 1; l++) // 쌍의 길이
        {
            Set<String> S = new HashSet<>();
            for (int st = 0; st < word.length() - l; st++) {
                String s = String.valueOf(new char[] { word.charAt(st), word.charAt(st + l) });
                if (!S.contains(s))
                    S.add(s);
                else
                    return false;
            }
        }
        return true;
    }

    static public void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            String word = br.readLine();
            if (word.equals("*"))
                break;

            System.out.printf("%s is%s surprising.\n", word, (isValid(word) ? "" : " NOT"));
        }
    }
}