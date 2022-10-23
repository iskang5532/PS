// 2022-10-17
// 2607 비슷한 단어
// https://www.acmicpc.net/problem/2607
/*
    구현 (14,172KB, 120ms)
    시간 복잡도: ?
    풀이)
    - 기준이 되는 문자열 속 문자의 개수를 저장할 c1[], 비교할 문자열 속 문자의 개수를 저장할 c2[].
    - 문자는 더하거나, 빼거나, 하나의 문자를 다른 문자로 바꿀 수 있다.
    즉, 다음과 같다.
    1. c1과 c2를 비교할 때, c1 혹은 c2의 차이가 1이 한 번 발생하였을 경우, 문자를 더하거나 빼서 맞출 수 있다.
    2. c1과 c2를 비교할 때, c1과 c2가 각각 1씩 더 큰 상황이 한 번 발생하였을 경우, 문자를 바꾸어 맞출 수 있다.
    - c1과 c2를 비교.
    만약 c1 > c2일 경우, l에 c1 - c2를 저장.
    만약 c1 < c2일 경우, r에 c2 - c1을 저장.
    l과 r 모두 2 미만일 경우, 비교 문자열은 기준 문자열과 비슷한 단어이다.
    etc.)
    - 문제를 잘못 이해함.
    참고)
    - if문: https://gyong0117.tistory.com/m/89
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    static int[] c1 = new int['z']; // 기준 문자열 속 문자의 개수를 저장

    static boolean isValid(String s) {

        int[] c2 = new int['z']; // 비교 문자열 속 문자의 개수를 저장
        for (char c : s.toCharArray())
            c2[c]++;

        int l = 0, r = 0; // 초과된 문자의 개수를 저장
        for (int i = 'A'; i < 'Z'; i++)
            if (c1[i] > c2[i]) // 기준 문자열의 문자가 더 많은 경우
                l += c1[i] - c2[i];
            else if (c1[i] < c2[i]) // 입력 문자열의 문자가 더 많은 경우
                r += c2[i] - c1[i];

        return (l < 2 && r < 2) ? true : false;
        // if (l - 1 == 0 && r - 1 == 0) // trans
        // return true;
        // if ((l == 1 && r == 0) || (l == 0 && r == 1)) // del
        // return true;
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 단어의 개수 (1 ≤ n ≤ 100)
        String s = br.readLine(); // 기준 문자열

        for (char c : s.toCharArray())
            c1[c]++;

        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            String _s = br.readLine(); // 비교 문자열
            if (isValid(_s))
                ans++;
        }

        System.out.println(ans);
    }
}