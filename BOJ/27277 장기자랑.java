// 2023-01-25
// 27277 장기자랑
// https://www.acmicpc.net/problem/27277
/*
    정렬, 그리디 (29,144KB, 464ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 v에 저장하며, v를 새로이 배치한 값을 res에 저장.
    - 첫 번째 순서의 값은 조건에 상관없이 최대 실력만큼 발휘할 수 있다. 즉, 큰 값을 배치한다면 최대한의 이득을 챙길 수 있다.
    그 외의 배치는 실력의 차이가 최대가 나게끔 배치한다.
    - 가장 실력이 있는 자 i를 첫 번째 순서에 두었다면, 두 번째 순서는 가장 실력이 없는 자 j를 둔다.
    다음에는 i 다음으로 실력이 높은 자와 j 다음으로 실력이 낮은 자를 배치한다.
    위와 같이 배치할 경우, (값, 0, 값, 0, ...)과 같이 구할 수가 있으며 이는 실력의 합의 최댓값이 된다.
    - res에 저장할 때 중복된 인원이 저장되지 않게끔 해야 한다.
    etc.) 떠오른 풀이가 정답이라 생각보다 빠르게 풀림
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());

        StringTokenizer st = new StringTokenizer(br.readLine());
        Integer[] v = new Integer[n];
        for (int i = 0; i < n; i++)
            v[i] = Integer.parseInt(st.nextToken());

        Arrays.sort(v, Collections.reverseOrder());

        int[] res = new int[n];
        for (int i = 0, pos = 0; pos < n; i++, pos += 2)
            res[pos] = v[i];
        for (int i = n - 1, pos = 1; pos < n; i--, pos += 2)
            res[pos] = v[i];

        int ans = 0;
        for (int i = 1; i < n; i++)
            ans += Math.max(0, res[i] - res[i - 1]);
        System.out.println(res[0] + ans);
    }
}