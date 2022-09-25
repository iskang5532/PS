// 2022-09-23
// 1107 리모컨
// https://www.acmicpc.net/problem/1107
/*
    완전 탐색 (124,036KB, 556ms)
    시간 복잡도: ?
    풀이)
    - 어떠한 수 l(혹은 r)을 정한 후, 해당 값을 버튼만으로 만들 수 있는지를 확인.
    가능한 경우, 해당 채널에서부터 n까지 몇 개의 채널 이동이 필요한지를 구한 후 누른 버튼의 개수 및 이동 횟수를 ans에 저장. (단, ans와 비교 후 최솟값을 저장)
    - l(혹은 r)이 100이 될 경우, 채널 이동만으로 최소 횟수가 되는지를 확인 후 ans에 저장.
    - n보다 높은 수 혹은 낮은 수가 된 후 채널을 이동하는 방법 또한 가능하므로 l과 r의 초깃값을 n으로 함.
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222086993561
    - 반례: https://www.acmicpc.net/board/view/96380
            https://www.acmicpc.net/board/view/96201
 */

import java.util.*;

public class Main {
    static final int INF = 0x3f3f3f3f;
    static final int MAX = 13; // max btn

    static boolean valid[] = new boolean[MAX]; // valid[i] = false일 경우, 번호 i는 사용할 수 없음

    public static boolean isValid(int k) {
        String s = Integer.toString(k);
        for (char c : s.toCharArray())
            if (!valid[c - '0'])
                return false;
        return true;
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(), m = sc.nextInt(); // 이동하려고 하는 채널 n(0 ≤ n ≤ 500,000) 고장난 버튼의 개수 m(0 ≤ m ≤ 10)

        Arrays.fill(valid, true);
        for (int i = 0; i < m; i++)
            valid[sc.nextInt()] = false;

        int ans = INF;
        for (int l = n, r = n;; l--, r++) {
            if (l == 100 || r == 100) {
                ans = l == 100 ? Math.min(ans, n - l)
                        : Math.min(ans, r - n);
                break;
            }
            if (l >= 0 && isValid(l)) {
                int k = n - l + Integer.toString(l).length();
                ans = Math.min(ans, k);
            }
            if (isValid(r)) {
                int k = r - n + Integer.toString(r).length();
                ans = Math.min(ans, k);
            }
        }

        System.out.println(ans);
    }
}