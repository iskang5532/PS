// 2022-10-21
// 20365 블로그2
// https://www.acmicpc.net/problem/20365
/*
    그리디, 구현 (19,452KB, 216ms)
    시간 복잡도: ?
    풀이)
    - 연속된 색은 한 번으로 칠할 수 있음.
    - 칠할 색의 개수를 저장할 B, R.
    - 연속된 색임을 확인하기 위해, 이전 색을 prev에 저장.
    만약 이전 색과 다른 경우, 새로운 색이 나온 것이므로 현재 색의 개수를 카운팅한다.
    둘 중 더 많은 색을 전체적으로 칠한 후, 나머지 색을 따로 칠한다.
    즉, 1 + min(B, R)을 출력한다.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 문제의 수 (1 ≤ n ≤ 500,000)
        String s = br.readLine();

        int b = 0, r = 0;
        char prev = ' '; // 이전 색
        for (char c : s.toCharArray()) {
            if (c != prev)
                if (c == 'B')
                    b++;
                else
                    r++;
            prev = c;
        }

        System.out.println(1 + Math.min(b, r));
    }
}