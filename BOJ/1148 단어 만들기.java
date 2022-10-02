// 2022-09-28
// 1148 단어 만들기
// https://www.acmicpc.net/problem/1148
/*
    문자열, 구현 (112,812KB, 556ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 단어 속 문자의 개수를 저장할 words[][]. (word[i]['A'] = k일 때, i번 단어 안에 문자 'A'는 k개 존재)
    - 입력된 퍼즐 속 문자의 개수를 저장할 m[].(m[c] = k일 때, 퍼즐에 문자 c는 k개 존재)
    - 단어를 완성할 때 사용한 문자의 횟수를 저장할 cnt[]. (cnt[c] = k일 때, 문자 c는 단어 완성에 k번 사용)
    - m을 이용하여 현재 문자 word를 만들 수 있는지 확인. (words[][]에 저장된 값을 사용)
    만약 퍼즐에 존재하는 문자의 개수보다 단어에 존재하는 문자의 개수가 많을 경우, 즉 m[c] < word[c]일 경우 만들 수 없음.
    만약 단어를 만들 수 있을 경우, 'A'부터 'Z'까지 확인.
     - 단어 속 문자가 존재할 경우, 즉 word[c]가 0이 아닐 경우 cnt[c]++.
    - 퍼즐 속 문자 c를 이용하여 cnt[c]를 확인하여 최소 개수 mn과 최대 개수 mx를 구함.
    - 최소 개수 mn을 이용한 문자들 s1과 최대 개수 mx를 이용한 문자들 s2를 구함.
    이때, 퍼즐에 존재해야 하므로 m[c]가 0보다 커야 한다.
    etc.)
    - String으로 words를 선언하면 MLE.
    - 제출한 두 코드의 차이는 2차원 배열 선언 시 []['Z']와 [][26] 뿐이지만 메모리 차이는 두 배. why?
 */

import java.util.*;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    static final int INF = 0x3f3f3f3f;
    static final int MAX = 200003; // max words.size()

    static int[][] words = new int[MAX]['Z' + 3]; // word[i]['A'] = k일 때, i번 단어 안에 문자 'A'는 k개 존재

    static boolean isValid(int[] m, int[] word) // 만들 수 있는 단어인가?
    {
        for (char c = 'A'; c <= 'Z'; c++)
            if (m[c] < word[c])
                return false;

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int sz = 0;
        for (;; sz++) /* input word */ {
            String word = br.readLine();
            if (word.equals("-"))
                break;
            for (char c : word.toCharArray())
                words[sz][c]++;
        }

        while (true) /* input puzzle */ {
            String puzzle = br.readLine();
            if (puzzle.equals("#"))
                break;

            int[] m = new int['Z' + 3]; // 퍼즐의 문자의 개수를 저장 (m[c] = k일 때, 퍼즐에 문자 c는 k개 존재)
            for (char c : puzzle.toCharArray())
                m[c]++;

            int[] cnt = new int['Z' + 3]; // 단어를 완성할 때 사용한 문자의 횟수를 저장 (cnt[c] = k일 때, 문자 c는 단어 완성에 k번 사용)
            for (int i = 0; i < sz; i++) {
                int[] word = words[i];

                if (!isValid(m, word))
                    continue;

                for (char c = 'A'; c <= 'Z'; c++)
                    if (word[c] > 0)
                        cnt[c]++;
            }

            int mn = INF, mx = 0;
            for (char c : puzzle.toCharArray()) {
                mn = Math.min(mn, cnt[c]);
                mx = Math.max(mx, cnt[c]);
            }

            String s1 = "", s2 = "";
            for (char c = 'A'; c <= 'Z'; c++) {
                if (m[c] > 0 && cnt[c] == mn)
                    s1 += c;
                if (m[c] > 0 && cnt[c] == mx)
                    s2 += c;
            }

            System.out.printf("%s %d %s %d\n", s1, mn, s2, mx); // mn == mx에 주의
        }
    }
}