// 2022-10-19
// 15886 내 선물을 받아줘 2
// https://www.acmicpc.net/problem/15886
/*
    구현 (15,092KB, 124ms)
    시간 복잡도: ?
    풀이)
    - 반복되는 구간을 탐색 후 t[]에 저장.
    - 방문한 위치를 visited[]에 저장 후, 재방문 시 반복되는 구간임을 확인.
    - 모든 문자에 관하여 확인. 이전에 찾은 반복되는 구간이 이후에 나올 수도 있으므로, 찾은 구간을 t[]에 저장.
    - t에 저장된 반복되는 구간의 개수를 ans에 저장.
    출력 시, ans/2의 값을 출력.
    etc.) 바로 못풀고 일주일 후에 떠오름
 */

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {

    static int MAX = 1003; // max n

    public static void main(String[] argm) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 길이 (2 ≤ N ≤ 1,000)
        String s = br.readLine(); // 지도

        int[] t = new int[MAX]; // 반복되는 구간 (t[i] == t[i + 1] == true일 경우, i와 i+1에서 반복)
        for (int i = 0; i < n; i++) {
            boolean[] visited = new boolean[MAX];
            int pos = i; // 현재 탐색중인 문자의 위치
            while (!visited[pos]) {
                visited[pos] = true;
                if (s.charAt(pos) == 'E')
                    pos++;
                else
                    pos--;
            }

            t[pos] = 1;
        }

        int ans = Arrays.stream(t).sum();
        System.out.println(ans >> 1);
    }
}