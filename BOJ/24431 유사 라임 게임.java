// 2023-01-16
// 24431 유사 라임 게임
// https://www.acmicpc.net/problem/24431
/*
    정렬 (15,868KB, 172ms)
    시간 복잡도: ?
    풀이)
    - 공통 접미사를 확인하여 쌍을 이루도록 만드는 문제.
    - 접미사를 확인해야 하므로, 입력된 문자열을 뒤집은 후 v에 저장.
    - 곹통된 분자열을 구해야 하므로 v를 정렬.
    - v에서 v[0], v[1]과 같이 두 개의 문자열을 꺼내 서로 비교하여 f개의 문자가 서로 같은지 확인.
    만약 같을 경우, ans++ 및 다른 두 문자열을 비교. (v[2], v[3])
    만약 다를 경우, 문자열을 하나 바꾼 후 비교. (v[1], v[2])
    etc.) 접미사가 아닌 단순 공통 부분 문자열인줄
    - 만약 공통 부분 문자열이라면?
 */

import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int tc = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        while (tc-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken()); // 문자열의 개수 n(2 ≤ n ≤ 500)
            int l = Integer.parseInt(st.nextToken()); // 길이 l(1 ≤ l ≤ 10)
            int f = Integer.parseInt(st.nextToken()); // 공통 접미사의 길이 f(1 ≤ f ≤ 10)

            String[] v = new String[n];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++)
                v[i] = new StringBuffer(st.nextToken()).reverse().toString(); // 문자열 뒤집기

            Arrays.sort(v);

            int ans = 0;
            for (int pos = 0; pos < n - 1; pos++)
                if (v[pos].substring(0, f).equals(v[pos + 1].substring(0, f))) // f개의 문자가 서로 같을 경우
                {
                    ans++;
                    pos++;
                }

            sb.append(ans).append('\n');
        }

        System.out.println(sb.toString());
    }
}