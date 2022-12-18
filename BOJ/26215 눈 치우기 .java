// 2022-12-11
// 26215 눈 치우기
// https://www.acmicpc.net/problem/26215
/*
    sol.1) 그리디, 투 포인터? (16,248KB, 144ms)
    시간 복잡도: ?
    풀이)
    - 가장 큰 값과 가장 작은 값을 찾은 후, -1씩 수행.
    만약, 남은 수가 하나일 경우 남아 있는 값만 -1.
    - 항상 가장 큰 값과 가장 작은 값을 사용해야 하므로, 값을 제거할 때마다 정렬함.
    etc.) 여러 풀이를 이용했지만 엄청난 수의 WA. 결국 무지성 구현으로 성공
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int MAX = 103; // max n

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());

        StringTokenizer st = new StringTokenizer(br.readLine());
        int[] v = new int[MAX];
        for (int i = 0; i < n; i++)
            v[i] = Integer.parseInt(st.nextToken());

        Arrays.sort(v, 0, n);

        int ans = 0;

        for (int l = 0, r = n - 1; l <= r; ans++) {
            if (l == r)
                v[l]--;
            else {
                v[l]--;
                v[r]--;
            }

            Arrays.sort(v, 0, n);
            while (l < n && v[l] == 0)
                l++;
        }

        System.out.println(ans <= 1440 ? ans : -1);
    }
}


/*
    sol.2) 수학 (14,220KB, 128ms)
    시간 복잡도: ?
    참고)
    - 수식: https://gall.dcinside.com/mgallery/board/view/?id=ps&no=30748&page=1
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine());

        StringTokenizer st = new StringTokenizer(br.readLine());
        int mx = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            int k = Integer.parseInt(st.nextToken());
            mx = Math.max(mx, k);
            sum += k;
        }

        int ans = Math.max(mx, (int) Math.ceil((double) sum / 2));
        System.out.println(ans <= 1440 ? ans : -1);
    }
}