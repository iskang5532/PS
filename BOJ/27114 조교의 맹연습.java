// 2023-01-10
// 27114 조교의 맹연습
// https://www.acmicpc.net/problem/27114
/*
    DP (84,692KB, 336ms)
    시간 복잡도: ?
    풀이)
    - 2차원 dp를 이용하여 에너지와 방향에 따른 최소 횟수를 저장
    - 입력된 좌로 돌아 l, 뒤로 돌아 b, 우로 돌아 r의 에너지를 2차원 dp인 cnt[][]에 에너지와 방향에 맞는 횟수 1을 저장.
    이후, 사용 에너지를 1씩 늘려가며 cnt를 갱신.
    - 세 가지의 행동인 l, r, b에 맞춰 행동을 수행한 이후의 에너지와 방향에 맞는 횟수가 최소가 되게끔 저장.
    좌로 돌아를 수행하면ㅅ 현재 방향을 d, cnt[i][d] = cur라 할 때,
    i+l의 에너지를 소모하여 다음으로 바라보는 방향인 d+LEFT에 최소 횟수를 저장.
    횟수는 기존에 구한 값인 cnt[i+l][d+LEFT]와 cur+1을 비교. (단, 기존에 구한 값이 업을 수 있음)
    etc.)
    - 풀이가 잘못된줄 알고 한참을 헤맸는데 cnt 초기화를 잘못함 (MAX + 4로 해놨었음)
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int MAX = 2000003; // max k
    final static int INF = 0x3f3f3f3f;

    final static int FRONT = 0, RIGHT = 1, BACK = 2, LEFT = 3;
    static int cnt[][] = new int[MAX][4];

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int l = Integer.parseInt(st.nextToken()); // LEFT
        int r = Integer.parseInt(st.nextToken()); // RIGHT
        int b = Integer.parseInt(st.nextToken()); // BACK
        int k = Integer.parseInt(st.nextToken()); // 에너지 소모량

        for (int i = 0; i < MAX; i++)
            Arrays.fill(cnt[i], INF);

        cnt[l][LEFT] = cnt[r][RIGHT] = cnt[b][BACK] = 1;
        for (int i = 1; i < k; i++)
            for (int d = 0; d < 4; d++) {
                int cur = cnt[i][d];
                if (cur != INF) {
                    cnt[i + l][(d + LEFT) % 4] = Math.min(cnt[i + l][(d + LEFT) % 4], cur + 1); // LEFT
                    cnt[i + b][(d + BACK) % 4] = Math.min(cnt[i + b][(d + BACK) % 4], cur + 1); // BACK
                    cnt[i + r][(d + RIGHT) % 4] = Math.min(cnt[i + r][(d + RIGHT) % 4], cur + 1); // RIGHT
                }
            }

        int ans = cnt[k][FRONT];
        System.out.println(ans != INF ? ans : -1);
    }
}