// 2022-11-28
// 14247 나무 자르기
// https://www.acmicpc.net/problem/14247
/*
    그리디, 정렬 (27,724KB, 380ms)
    시간 복잡도: ?
    풀이)
    - 나무가 최대로 컸을 때를 비교하여 가장 큰 나무부터 나중에 잘라주면 된다.
    이때, 나무의 성장 길이만을 이용해야 하며, 초기에 주어지는 값은 제외한다.
    - 자란 나무를 잘라 값을 더해줄 때, 초기에 주어진 값은 나무의 길이에 포함되므로 같이 더해준다.
    - 위와 같이 자르게 될 경우, 맨 처음에 자를 나무는 증가하지 않은 초기 길이가 된다.
    etc.) 문제를 이해하지 못해서 예제를 보고 문제를 유추해서 풂.
    - 자바 배열, 범위 내림차순 정렬 어떻게?
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 100003; // max n

    static long[] v1 = new long[MAX], v2 = new long[MAX];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 나무의 개수 (1 ≤ n ≤ 100,000)

        StringTokenizer st;
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++)
            v1[i] = Long.parseLong(st.nextToken());
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++)
            v2[i] = Long.parseLong(st.nextToken());

        Arrays.sort(v2, 0, n);

        long ans = 0;
        for (int i = 0; i < n; i++)
            ans += v2[i] * i; // 나중에 자르는 나무일수록 성장한 횟수 추가
        for (int i = 0; i < n; i++)
            ans += v1[i];

        System.out.println(ans);
    }
}