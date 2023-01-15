// 2023-01-11
// 27113 잠입
// https://www.acmicpc.net/problem/27113
/*
    그리디, 구현 (54,688KB, 428ms)
    시간 복잡도: O(n)
    풀이)
    - 최 상병을 쫒아오는 로봇은 레이저의 영향을 받지 않는다.
    즉, 최 상병이 좌측이나 후진, 혹은 멈추는 순간이 존재할 경우, 최 상병은 로봇에게 잡히고 만다.
    그러므로 최 상병은 항상 직진 혹은 우측으로 이동해야 한다.
    - 회상병의 x축 위치를 저장할 pos.
    - x축에서 레이저가 없는 위치를 확인 후, 최 상병이 갈 수 있는 가장 가까운 위치로 최 상병을 이동시킨다. (갈 수 있는 위치란, 현재 위치를 포함한 우측인 위치)
    - 모든 레이절르 통과한 최 상병의 위치를 확인한다.
    최 상병이 목표 지점의 x축 값 이하에 위치한 경우, 최 상병은 탈출할 수 있다. (해당 위치에서 우측으로 이동하면 탈출)
    etc.)
    - 이 문제 또한 질문의 내용을 제대로 읽지 않아서 왜맞틀 외침.
 */

import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken()); // 행의 크기 n(2 ≤ n ≤ 100,000), 열의 크기 m(2 ≤ m ≤ 10^9)
        
        int pos = 1; // 최 상병의 위치 pos
        for (int i = 0; i < n - 1; i++) {
            st = new StringTokenizer(br.readLine());

            int x = Integer.parseInt(st.nextToken());
            if (x == 0)
                continue;
            else if (x == 1) {
                int c = Integer.parseInt(st.nextToken()); // 위치
                char d = st.nextToken().charAt(0); // 방향

                if (d == 'L')
                    pos = (pos <= c ? c + 1
                            : pos);
                else if (d == 'R')
                    pos = (pos < c ? pos
                            : m + 1);
            } else if (x == 2) {
                int c1 = Integer.parseInt(st.nextToken()); // 위치
                char d1 = st.nextToken().charAt(0); // 방향
                int c2 = Integer.parseInt(st.nextToken());
                char d2 = st.nextToken().charAt(0);

                // 지나갈 곳이 없는 경우
                if ((d1 == 'L' && d1 == d2) && c2 == m) // 왼왼
                    pos = m + 1;
                if ((d1 == 'R' && d1 == d2) && c1 == 1) // 오오
                    pos = m + 1;
                if ((d1 == 'L' && d2 == 'R') && c2 - c1 == 1) // 왼오
                    pos = m + 1;
                if ((d1 == 'R' && d2 == 'L') && (c1 == 1 && c2 == m)) // 오왼
                    pos = m + 1;

                if (d1 == 'L' && d2 == 'L') // 왼왼
                    pos = (pos <= c2 ? c2 + 1
                            : pos);
                if (d1 == 'R' && d2 == 'R') // 오오
                    pos = (pos < c1 ? pos
                            : m + 1);
                if (d1 == 'L' && d2 == 'R') // 왼오
                    pos = (pos <= c1 ? c1 + 1
                            : c1 < pos && pos < c2 ? pos
                                    : m + 1);
                if (d1 == 'R' && d2 == 'L') // 오왼
                    pos = ((pos < c1 || c2 < pos) ? pos
                            : c2 + 1);
            }
        }

        System.out.println(pos <= m ? "YES" : "NO");
    }
}