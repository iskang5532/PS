// 2022-11-20
// 16435 스네이크버드
// https://www.acmicpc.net/problem/16435
/*
    그리디, 정렬 (14,420KB, 144ms)
    시간 복잡도: ?
    풀이)
    - 먹은 만큼 길이가 증가하며, 최대한 많이 먹어야 한다.
    - 높이가 낮은 과일 순으로 먹게 될 경우, 길이가 늘어나며 먹을 수 없었던 과일 또한 먹을 수 있게 된다.
    그러므로, 입력된 과일의 높이를 h[]에 저장 후, 오름차순 정렬하여 앞에서부터 과일을 하나씩 먹어가며 l을 늘려간다.
    참고)
    - 정렬: https://codechacha.com/ko/java-sorting-array/
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 1003; // max n

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken()); // 과일의 개수 n(1 ≤ n ≤ 1,000),
        int l = Integer.parseInt(st.nextToken()); // 스네이크버드의 초기 길이 l(1 ≤ l ≤ 10,000)

        st = new StringTokenizer(br.readLine());
        int[] h = new int[MAX];
        for (int i = 0; i < n; i++)
            h[i] = Integer.parseInt(st.nextToken());

        Arrays.sort(h, 0, n);

        for (int i = 0; i < n; i++)
            if (l >= h[i])
                l++;

        System.out.println(l);
    }
}