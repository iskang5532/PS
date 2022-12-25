// 2022-12-22
// 16934 게임 닉네임
// https://www.acmicpc.net/problem/16934
/*
    트라이 (95,988KB, 700ms)
    시간 복잡도: ?
    풀이)
    - 트라이 구조를 이루는 root에 입력된 문자열 s를 추가함.
    s를 추가하는 과정에서 해당 문자가 존재하지 않을 경우, 해당 문자까지의 문자열이 별칭.
    단, 별칭이 s와 같을 경우 s와 같은 문자열이 앞서 몇 번 입력됐는지 확인하여 별칭을 정함. (= 동일한 닉네임의 개수 파악)
    - s의 마지막 문자를 추가한 후, cnt++하여 닉네임의 개수를 늘림.    
    etc.) cnt를 잘못해서 헤맴.
 */

import java.io.*;
import java.util.*;

public class Main {
    static StringBuilder ans = new StringBuilder();

    static class Node {
        private Map<Character, Node> m = new HashMap<>();
        private int cnt = 0; // 동일한 닉네임의 개수

        private void add(final String s, int pos, boolean valid) // s[pos], 별칭을 정했는지를 저장할 valid
        {
            if (pos == s.length()) {
                cnt++;
                if (!valid) // 아직까지 별칭을 구하지 못한 경우
                    ans.append(s + (cnt == 1 ? "" : Integer.toString(cnt)) + '\n');
                return;
            }

            char next = s.charAt(pos);
            if (!m.containsKey(next)) // 해당 문자가 없을 경우
            {
                if (!valid) // 별칭을 구하지 못한 경우, pos까지의 문자열을 별칭으로 사용
                {
                    ans.append(s.substring(0, 1 + pos) + '\n');
                    valid = true;
                }

                m.put(next, new Node());
            }

            m.get(next).add(s, pos + 1, valid);
        }
    };

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));

        int n = Integer.parseInt(br.readLine()); // 유저의 수 (1 ≤ n ≤ 100,000)

        Node root = new Node();

        for (int i = 0; i < n; i++)
            root.add(br.readLine(), 0, false);

        System.out.println(ans.toString());
    }
}