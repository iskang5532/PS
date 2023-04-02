// 2023-04-02
// 27922 현대모비스 입사 프로젝트
// https://www.acmicpc.net/problem/27922
/*
    그리디, 정렬 (155,004KB, 1,460ms)
    시간 복잡도: ?
    풀이)
    - 두 개의 역량을 골라 최댓값을 만들어야 하므로, 입력된 역량을 더해 만든 값을 기준으로 정렬하여 값을 구함.
    - 입력된 세 개의 역량 중 두 개의 역량을 더하여 만든 세 개의 값을 v에 넣음. (a+b, a+c, b+c)
    - 각 역량을 기준으로 내림차순 정렬.
    이후, 상위 k개의 값을 더하여 ans에 최댓값을 저장.
    etc.) 어려웠음. 첫 풀이의 반례를 모르겠음. 풀이 자체가 잘못된 것인가?
    - 풀이 설명이 어려움.
    참고)
    - 해설: https://upload.acmicpc.net/3f195577-cf7d-4abc-ac2b-f56fda68da67/
 */

import java.io.*;
import java.util.*;

public class Main {
    static class P {
        private int a, b, c;

        private P(int a, int b, int c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        private int get_a() { return a; }
        private int get_b() { return b; }
        private int get_c() { return c; }
    }

    static int get_ans(ArrayList<P> v, int k) {
        int a = 0, b = 0, c = 0;
        for (int i = 0; i < k; i++) {
            a += v.get(i).a;
            b += v.get(i).b;
            c += v.get(i).c;
        }

        return Math.max(a, Math.max(b, c));
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tk = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(tk.nextToken()), k = Integer.parseInt(tk.nextToken()); // 강의의 개수 n, 수강 개수 k (1 ≤ k ≤ n ≤ 100,000)

        ArrayList<P> v = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tk = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(tk.nextToken());
            int b = Integer.parseInt(tk.nextToken());
            int c = Integer.parseInt(tk.nextToken());

            v.add(new P(a + b, a + c, b + c));
        }

        int ans = 0;

        v.sort(Comparator.comparing(P::get_a).reversed());
        ans = Math.max(ans, get_ans(v, k));
        v.sort(Comparator.comparing(P::get_b).reversed());
        ans = Math.max(ans, get_ans(v, k));
        v.sort(Comparator.comparing(P::get_c).reversed());
        ans = Math.max(ans, get_ans(v, k));

        System.out.println(ans);
    }
}