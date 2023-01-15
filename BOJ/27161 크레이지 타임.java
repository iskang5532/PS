// 2023-01-14
// 27161 크레이지 타임
// https://www.acmicpc.net/problem/27161
/*
    구현 (14,472KB, 140ms)
    시간 복잡도: ?
    풀이)
    - 현재 부를 시간 t가 입력된 x와 같은지, 혹은 s가 모래시계인지를 비교하여 답을 ans에 저장.
    - 시간은 0부터 11까지 총 12개를 사용. (비교 시, t+1의 값을 사용)
    - 만약 t+1과 x가 같을 경우, 동기화의 법칙으로 인해 게임판 중앙을 내리쳐야 함. (단, 시간 역행의 법칙이 발동되지 않아야 함)
    - 만약 s가 모래시계일 경우, 시간 역행의 법칙이 발동해야 함. (단, 동기화의 법칙이 발동되지 않아야 함)
    - 구한 ans의 값을 출력.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 카드의 개수 (1 ≤ n ≤ 1,000)

        String[] v1 = new String[n];
        int[] v2 = new int[n];
        StringTokenizer st;
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine());

            v1[i] = st.nextToken();
            v2[i] = Integer.parseInt(st.nextToken());
        }

        int[] ans1 = new int[n];
        String[] ans2 = new String[n];
        for (int i = 0, t = -1, rev = 0; i < n; i++) // 시간 t, 반전 상태 rev
        {
            String s = v1[i];
            int x = v2[i];

            t = (12 + t + (rev == 0 ? 1 : -1)) % 12; // 시간 갱신 (반전 상태일 경우, 거꾸로)

            ans1[i] = t + 1;
            if (t + 1 == x && !s.equals("HOURGLASS")) // 시간과 x가 일치하는 경우 (단, 모래시계 아니어야 함)
                ans2[i] = "YES";
            else
                ans2[i] = "NO";

            if (s.equals("HOURGLASS") && t + 1 != x) // 모래시계일 경우, 반전 (단, 시간은 x와 일치하지 않음)
                rev = (rev == 0 ? 1 : 0);
        }

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < n; i++)
            ans.append(ans1[i]).append(' ').append(ans2[i]).append('\n');

        System.out.println(ans.toString());
    }
}