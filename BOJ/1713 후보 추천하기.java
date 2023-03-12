// 2023-03-11
// 1713 후보 추천하기
// https://www.acmicpc.net/problem/1713
/*
    구현 (14,852KB, 140ms)
    시간 복잡도: ?
    풀이)
    - 각 후보의 추천 받은 횟수와 사진이 게시된 시간을 v[]에 저장.
    - 사용중인 사진틀의 개수를 cnt에 저장.
    - cnt가 사진틀의 개수를 넘었을 경우, 횟수가 가장 작은 학생 v[i]를 초기화.
    만약 동일할 경우, 시간이 가장 빠른 학생일 초기화.
    이후, 입력된 학생 k의 정보를 v에 저장.
    - v에 0이 아닌 값이 있을 경우, 해당 학생은 사진틀에 게시됨.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int INF = 0x3f3f3f3f;
    static final int MAX = 103; // max m

    static class pii {
        private int cnt, t; // 추천 횟수 cnt, 게시된 시간 t

        private pii() {
            cnt = 0;
            t = 0;
        };

        private pii(int cnt, int t) {
            this.cnt = cnt;
            this.t = t;
        };
    };

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 사진틀의 개수 (1 ≤ n ≤ 20)
        int m = Integer.parseInt(br.readLine()); // 학생의 총 추천 횟수 (m ≤ 1,000)

        StringTokenizer st = new StringTokenizer(br.readLine());
        pii[] v = new pii[MAX];
        for (int i = 0; i < MAX; i++)
            v[i] = new pii();

        int cnt = 0; // 사용한 사진틀의 개수
        for (int t = 0; t < m; t++) {
            int k = Integer.parseInt(st.nextToken()); // 학생의 번호 (1 ≤ k ≤ 100)

            if (v[k].cnt == 0) {
                cnt++;
                v[k].t = t;
            }
            if (cnt > n) // erase
            {
                int mn = INF; // 가장 작은 추천 횟수
                for (int i = 0; i < MAX; i++)
                    if (v[i].cnt != 0)
                        mn = Math.min(mn, v[i].cnt);

                int d = 0; // 제거할 번호
                int mn_t = INF; // 가장 오래된 시간을 저장
                for (int i = 0; i < MAX; i++)
                    if (v[i].cnt == mn && mn_t > v[i].t) {
                        d = i;
                        mn_t = v[i].t;
                    }

                v[d] = new pii(0, 0);
                cnt--;
            }

            v[k].cnt++;
        }

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < MAX; i++)
            if (v[i].cnt != 0)
                ans.add(i);

        Collections.sort(ans);

        StringBuilder sb = new StringBuilder();
        for (Integer i : ans)
            sb.append(i).append(' ');
        System.out.println(sb.toString());
    }
}