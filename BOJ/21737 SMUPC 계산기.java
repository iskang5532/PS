// 2022-12-02
// 21737 SMUPC 계산기
// https://www.acmicpc.net/problem/21737
/*
    문자열 (85,548KB, 636ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열에서 숫자와 연산을 추출하여 각각 v, oper에 저장.
    - 연산된 결과를 res에 저장하며, 첫 번째 수인 v[0]은 연산의 대상이 되므로 res에 저장한다.
    - v에 저장된 수의 위치를 저장할 pos. (res에 수를 하나 사용하였으므로 초깃값은 1)
    - oper에 저장된 연산 c와 v[pos]의 값을 이용하여 res를 구함.
    만약 c가 'C'일 경우, res를 ans에 저장.
    만약 c가 연산 수행 알파벳일 경우, res에 v[pos]를 이용하여 올바른 연산 수행.
    주의할 점은, 마지막 문자가 연산일 수 있음.
    더 이상 연산에 사용할 수가 없지만 연산이 진행될 수 있으며, v[pos]를 참조하게 될 경우 에러가 발생.
    그러므로, v[pos]에 값이 있는지 확인하여 에러를 예방해야 함.
    - ans에 값이 저장되어 있을 시 값을 출력하지만, 없을 시 "NO OUTPUT" 출력.
 */

import java.io.*;
import java.util.*;

class Main {

    static ArrayList<Integer> v = new ArrayList<>(); // 추출된 수를 저장
    static ArrayList<Character> oper = new ArrayList<>(); // 추출된 연산을 저장

    static void _extract(String s) // 문자열 속 수와 연산을 구함
    {
        StringBuilder num = new StringBuilder();
        for (final char c : s.toCharArray()) {
            if ('0' <= c && c <= '9')
                num.append(c);
            else // 연산일 경우, 이전까지의 수를 저장
            {
                if (num.length() > 0) // 단, 이전에 나온 문자열이 수일 경우 (= 연속된 'C'가 아닐 경우)
                {
                    v.add(Integer.valueOf(num.toString()));
                    num = new StringBuilder();
                }
                oper.add(c);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 기호의 개수 (1 ≤ n ≤ 500,000)
        String s = br.readLine();

        _extract(s);

        ArrayList<Integer> ans = new ArrayList<>();
        int res = v.get(0); // 연산이 완료된 수를 저장
        int pos = 1; // 문자열 속 pos번째 수
        for (final char c : oper) {
            if (c == 'C')
                ans.add(res);
            else if (v.size() <= pos) // 마지막 문자면서 'C'가 아닌 경우, 종료
                break;
            else if (c == 'S')
                res -= v.get(pos++);
            else if (c == 'M')
                res *= v.get(pos++);
            else if (c == 'U')
                res /= v.get(pos++);
            else if (c == 'P')
                res += v.get(pos++);
        }

        if (ans.size() > 0) {
            StringBuilder sb = new StringBuilder();
            for (int i : ans)
                sb.append(i + " ");

            System.out.println(sb);
        } else
            System.out.println("NO OUTPUT");
    }
}