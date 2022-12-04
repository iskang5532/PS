// 2022-12-04
// 14906 스러피
// https://www.acmicpc.net/problem/14906
/*
    재귀, 구현 (14,212KB, 128ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열이 스러피인지 확인. (이때, 입력받은 문자열 s에 임의의 문자를 추가하여 StringIndexOutOfBounds를 방지)
    스러피란, 스림프와 스럼프로 구성된 문자열이다.
    또한, 스림프 혹은 스럼프 속에 또다른 스림프 혹은 스럼프가 존재할 수 있다.
    그러므로, 해당 구간이 스림프 혹은 스럼프인지 확인하는 함수를 구현하여 사용한다.
    - 함수에서 확인중인 문자열 속 문자의 위치를 저장할 pos, 탐색 이전의 위치를 저장할 prev. (탐색 과정에서 pos가 변하며, 다른 형식을 비교할 때 이전 값이 필요)
    - isSlimp()
    1. 첫 문자가 'A'가 아닐 경우, 스림프가 아님. (= 스러피가 아님)
    맞을 경우, pos++.
    2. 복원 지점을 만듦. (prev = pos)
    3. 조건을 만족하는지 확인하며, 만족할 경우 pos++ 및 true 반환.
    3-1. s[pos] == 'H', 즉 스림프인가?
    3-2. s[pos] == 'B'면서 뒤에 스럼프가 오는가?
    만족하지 않을 경우, 탐색 과정에서 옮겨진 pos를 복원하며 false 반환.
    - isSlump()
    1. 첫 문자가 'D' 혹은 'E'가 아닐 경우, false 반환.
    2. 연속된 'F' 이후의 위치를 찾아 pos에 옮김.
    3. 스럼프 혹은 'G'로 끝나는가?
    3-1. 스럼프일 경우, true 반환.
    3-2. 'G'일 경우, pos++ 및 true 반환. (더 이상의 스럼프가 없음. pos++를 적용하여 다음 조건 탐색에 사용)
    만약 스럼프 혹은 'G'가 아닐 경우, 탐색 과정에서 옮겨진 pos를 복원하며 false 반환. (이 때의 prev는 스림프에서 초기화된 값)
    - isSlimp()와 isSlump()가 true를 반환하게 될 경우, pos++가 적용된다.
    etc.) 깔끔하지 못해서 아쉬움
 */

import java.io.*;

class Main {
    static int pos, prev; // 문자의 위치 pos, 이전 탐색 문자의 위치 prev

    static boolean isSlump(final String s) {
        if (!(s.charAt(pos) == 'D' || s.charAt(pos) == 'E'))
            return false;

        while (s.charAt(++pos) == 'F')
            ;

        if (isSlump(s) || (s.charAt(pos) == 'G' && ++pos >= 0))
            return true;

        pos = prev;
        return false;
    }

    static boolean isSlimp(final String s) {
        if (s.charAt(pos++) != 'A') // 스러피가 아니면 탐색이 종료되므로, pos++를 되돌리지 않아도 됨
            return false;

        prev = pos;
        if (s.charAt(pos) == 'H') // == 2
        {
            pos++;
            return true;
        } else if ((s.charAt(pos) == 'B' && (++pos >= 0 && isSlimp(s)) && s.charAt(pos) == 'C') ||
                isSlump(s) && s.charAt(pos) == 'C') // >= 3
        {
            pos++;
            return true;
        }

        pos = prev;
        return false;
    }

    static boolean isSlurpy(final String s) {
        pos = 0;
        if (s.length() < 4 || !isSlimp(s) || !isSlump(s) || pos != s.length() - 1)
            return false;

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 문자열의 개수 (1 ≤ n ≤ 10)

        StringBuilder ans = new StringBuilder();
        ans.append("SLURPYS OUTPUT\n");
        for (int i = 0; i < n; i++)
            ans.append(isSlurpy(br.readLine() + '\0') ? "YES" : "NO").append('\n');  // 임의의 문자를 추가하여 확인
        ans.append("END OF OUTPUT");

        System.out.println(ans.toString());
    }
}