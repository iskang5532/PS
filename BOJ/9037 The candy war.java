// 2023-03-15
// 9037 The candy war
// https://www.acmicpc.net/problem/9037
/*
    구현 (14,532KB, 212ms)
    시간 복잡도: ?
    풀이)
    - 홀수개의 사탕을 가진 아이에게 하나의 사탕을 주는 함수 get_candy().
    - 모든 아이가 같은 개수의 사탕을 가지는지 확인하는 함수 is_done().
    - 옆 아이에게 절반의 사탕을 주는 함수 moved().
    - 예제와 같이 첫 입력과 홀수를 짝수로 만드는 함수만으로 답이 나올 수 있음에 주의.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 13; // max n

    static int n; // 인원 (1 ≤ n ≤ 10)
    static int[] v = new int[MAX];

    static boolean is_done() // 모든 아이가 같은 개수의 사탕을 가지는가
    {
        for (int i = 0; i < n - 1; i++)
            if (v[i] != v[i + 1])
                return false;

        return true;
    }

    static void get_candy() // 홀수개의 사탕을 가지고 있는 아이에게 하나의 사탕을 줌
    {
        for (int i = 0; i < n; i++)
            if ((v[i] & 1) == 1)
                v[i]++;
    }

    static void moved() {
        int[] tmp = new int[MAX]; // i에게 줄 1/2개의 사탕
        tmp[0] = v[n - 1] / 2;
        v[n - 1] -= tmp[0];
        for (int i = 1; i < n; i++) {
            tmp[i] = v[i - 1] / 2;
            v[i - 1] -= tmp[i];
        }

        for (int i = 0; i < n; i++)
            v[i] += tmp[i];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringBuilder sb = new StringBuilder();
        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            n = Integer.parseInt(br.readLine());

            StringTokenizer token = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++)
                v[i] = Integer.parseInt(token.nextToken());

            get_candy();

            int ans = 0;
            while (!is_done() && n != 1) {
                ans++;

                moved();
                get_candy();

                if (is_done())
                    break;
            }

            sb.append(ans).append('\n');
        }

        System.out.println(sb.toString());
    }
}