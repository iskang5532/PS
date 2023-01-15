// 2023-01-14
// 27160 할리갈리
// https://www.acmicpc.net/problem/27160
/*
    맵 (40,300KB, 432ms)
    시간 복잡도: ?
    풀이)
    - 입력된 과일과 개수를 맵에 저장. (동일한 과일이 입력된 경우, 기존 과일의 개수에 더함)
    - 맵에 저장된 과일과 개수를 확인.
    만약 개수가 5인 과일이 있는 경우, "YES"를 출력.
    만약 개수가 5인 과일이 하나도 없는 경우, "NO"를 출력.
 */

import java.io.*;
import java.util.*;

public class Main {
    static Map<String, Integer> m = new LinkedHashMap<>();

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 카드의 개수 (1 ≤ n ≤ 100,000)

        StringTokenizer st;
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());
            String s = st.nextToken(); // 과일의 종류
            int x = Integer.parseInt(st.nextToken()); // 과일의 개수 (1 ≤ x ≤ 5)

            m.put(s, m.getOrDefault(s, 0) + x);
        }

        boolean valid = false; // 5개인 과일이 있는가?
        for (String s : m.keySet())
            if (m.get(s) == 5)
                valid = true;

        System.out.println(valid ? "YES" : "NO");
    }
}