// 2022-12-03
// 1015 수열 정렬
// https://www.acmicpc.net/problem/1015
/*
    정렬 (14,388KB, 132ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수가 정렬되었을 때의 위치를 구해야 한다.
    - v1[]에 {입력된 값, 위치} 형식으로 값을 저장.
    이후, 값을 기준으로 오름차순 정렬.
    - 오름차순 정렬된 값을 하나씩 확인해가며, 인덱스의 현재 위치를 ans[]에 저장.
    etc.) 예제 입력과 예제 출력만을 보고 풀어서 지문은 모름
 */

import java.io.*;
import java.util.*;

class Main {
    static class pii implements Comparable<pii> {
        private int val, pos;

        private pii(int val, int pos) {
            this.val = val;
            this.pos = pos;
        }

        @Override
        public int compareTo(pii p) {
            return Integer.compare(this.val, p.val); // 오름차순 정렬
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 원소의 개수 (1 ≤ n ≤ 50)

        StringTokenizer st = new StringTokenizer(br.readLine());
        pii[] v1 = new pii[n];
        for (int i = 0; i < n; i++)
            v1[i] = new pii(Integer.parseInt(st.nextToken()), i);

        Arrays.sort(v1);

        int[] v2 = new int[n]; // 값의 위치를 저장
        for (int i = 0; i < n; i++)
            v2[v1[i].pos] = i;

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < n; i++)
            ans.append(Integer.toString(v2[i]) + ' ');

        System.out.println(ans.toString());
    }
}