// 2022-12-06
// 6443 애너그램
// https://www.acmicpc.net/problem/6443
/*
    백트래킹 (59,304KB, 440ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어의 철자들을 재조합하여 만들 수 있는 모든 단어를 출력해야 한다.
    단, 중복된 단어는 한 번만 출력해야 하며, 오름차순으로 출력해야 한다.
    - 오름차순 출력을 위해, 입력된 문자열 word를 오름차순 정렬한다.
    - dfs를 이용하여 word의 철자로 만들 수 있는 모든 단어를 구하여 ans에 저장하며, visited[]를 이용하여 사용된 문자의 위치를 저장한다.
    - 중복된 단어는 제외해야 한다.
    dfs를 이용하여 단어를 구하는 과정에서 이전에 구한 단어와 동일한 단어가 나올 것 같다면, 더 이상 탐색하지 않고 다음 단어를 구해야 한다.
    이를 알기 위해서는, 현재 s의 마지막 문자를 기억하여 사용한다.
    만약 s[pos]를 추가하는 과정에서 이전 s[pos]와 현재 s[pos]가 같을 경우, 최종적으로 이전에 구한 s와 현재 구해질 s는 같다.
    - s와 word의 길이가 동일한 경우, ans에 s를 저장.
 */

import java.io.*;
import java.util.*;

class Main {
    static boolean[] visited;
    static StringBuilder ans = new StringBuilder();

    static void get_ans(char[] v, String s) {
        if (s.length() == v.length) {
            ans.append(s).append('\n');
            return;
        }

        char prev = '\0';
        for (int pos = 0; pos < v.length; pos++)
            if (!visited[pos] && prev != v[pos]) {
                prev = v[pos];
                visited[pos] = true;
                get_ans(v, s + v[pos]);
                visited[pos] = false;
            }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 단어의 개수
        for (int i = 0; i < n; i++) {
            char[] v = br.readLine().toCharArray();
            Arrays.sort(v);

            visited = new boolean[v.length];
            get_ans(v, "");
        }

        System.out.println(ans.toString());
    }
}