// 2022-12-12
// 13417 카드 문자열
// https://www.acmicpc.net/problem/13417
/*
    sol.1) 그리디 (41,104KB, 322ms)
    시간 복잡도: O(n)
    풀이)
    - 문자열의 앞 부분을 저장할 pre, 뒷 부분을 저장할 suf.
    - 현재 넣어야 될 문자 c를 이전에 만든 문자열과 비교하여 앞 혹은 뒤에 넣음.
    만약 c가 pre에 저장된 마지막 문자보다 사전 순으로 빠른 경우, pre에 추가.
    만약 c가 pre에 저장된 마지막 문자보다 사전 순으로 느린 경우, suf에 추가.
    - pre는 내림차순이므로, reverse시킨 후 suf와 같이 출력.
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int MAX = 1003; // max n

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
        int tc = Integer.parseInt(br.readLine());
        for (int idx = 0; idx < tc; idx++) {
            int n = Integer.parseInt(br.readLine()); // 카드의 수(1 ≤ n ≤ 1,000)

            StringTokenizer st = new StringTokenizer(br.readLine());
            char[] c = new char[MAX];
            for (int i = 0; i < n; i++)
                c[i] = st.nextToken().charAt(0);

            StringBuilder pre = new StringBuilder(), suf = new StringBuilder();
            for (int i = 0; i < n; i++)
                if (pre.toString().isEmpty() || c[i] <= pre.charAt(pre.length() - 1))
                    pre.append(c[i]);
                else
                    suf.append(c[i]);

            System.out.println(pre.reverse().toString() + suf.toString());
        }
    }
}


/*
    sol.2) 그리디 (96,112KB, 524ms)
    시간 복잡도: ?
    풀이)
    - 현재 넣어야 될 문자 c를 이전에 만든 문자열 anㄴ와 비교하여 앞 혹은 뒤에 넣음.
    만약 c가 ans의 첫 번째 문자보다 사전 순으로 빠른 경우, ans의 앞에 추가.
    만약 c가 ans의 첫 번째 문자보다 사전 순으로 느린 경우, ans의 뒤에 추가.
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int MAX = 1003; // max n

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
        int tc = Integer.parseInt(br.readLine());
        for (int idx = 0; idx < tc; idx++) {
            int n = Integer.parseInt(br.readLine()); // 카드의 수(1 ≤ n ≤ 1,000)

            StringTokenizer st = new StringTokenizer(br.readLine());
            char[] c = new char[MAX];
            for (int i = 0; i < n; i++)
                c[i] = st.nextToken().charAt(0);

            String ans = new String();
            for (int i = 0; i < n; i++)
                if (ans.isEmpty() || c[i] <= ans.charAt(0))
                    ans = c[i] + ans;
                else
                    ans += c[i];

            System.out.println(ans);
        }
    }
}