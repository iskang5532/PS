// 2023-02-26
// 27522 카트라이더: 드리프트
// https://www.acmicpc.net/problem/27522
/*
    정렬 (14,292KB, 128ms)
    시간 복잡도: ?
    풀이)
    - 입력된 시간과 팀을 v에 저장 후, 시간을 기준으로 오름차순 정렬.
    이후, 첫 번째 값의 팀부터 확인하여 순위에 맞는 점수를 팀 점수에 더함.
    두 팀의 점수를 비교 후, 승리한 팀을 출력.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 8;
    static final int grade[] = { 10, 8, 6, 5, 4, 3, 2, 1 };

    static class P implements Comparable<P> {
        private String t;
        private char team;

        P(String t, char team) {
            this.t = t;
            this.team = team;
        }

        @Override
        public int compareTo(P o) {
            return t.compareTo(o.t);
        };

    };

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        P[] v = new P[MAX];
        for (int i = 0; i < MAX; i++) {
            st = new StringTokenizer(br.readLine());
            v[i] = new P(st.nextToken(), st.nextToken().charAt(0));
        }

        Arrays.sort(v);

        int red = 0, blue = 0;
        for (int i = 0; i < MAX; i++)
            if (v[i].team == 'R')
                red += grade[i];
            else
                blue += grade[i];

        System.out.println((red > blue) ? "Red" : "Blue");
    }
}