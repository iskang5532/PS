// 2022-10-23
// 24725 엠비티아이
// https://www.acmicpc.net/problem/24725
/*
    완전 탐색 (15,024KB, 168ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값 중 'E' 혹은 'I'의 위치를 st에 저장.
    이후, st에 저장된 값을 하나씩 완전 탐색에 사용.
    - ch에 각 위치의 MBTI를 저장.
    - 첫 번쨰 MBTI의 값은 st에 저장된 값이므로, 두 번째부터 탐색. (= next == 2)
    만약 다음 위치의 값이 두 번째 MBTI인 'N' 혹은 'S'인 경우, 그 다음 위치를 확인. (= next == 3)
    만약 그 다음 위치의 값이 세 번째 MBTI인 'F' 혹은 'T'인 경우, 그 다음 위치를 확인. (= next == 4)
    만약 그 다음 위치의 값이 네 번째 MBTI인 'P' 혹은 'J'인 경우, 그 다음 위치를 확인. (= next == 5)
    만약 next == 5일 경우, MBTI를 완성한 경우이므로 ans++.
    etc.) 지저분하게 푼듯한 기분
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    public static class pii {
        int y, x;

        pii(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }

    static int MAX = 203; // max n, m

    static final int[] dy = { -1, -1, 0, 1, 1, 1, 0, -1 };
    static final int[] dx = { 0, 1, 1, 1, 0, -1, -1, -1 };
    static final char[][] ch = { {}, {}, { 'N', 'S' }, { 'F', 'T' }, { 'P', 'J' } };

    static int n, m; // 1 ≤ n, m ≤ 200
    static char[][] board = new char[MAX][MAX];
    static ArrayList<pii> v = new ArrayList<>();
    static int ans = 0;

    static final boolean OOB(int ny, int nx) {
        return !(0 <= ny && ny < n) || !(0 <= nx && nx < m);
    }

    static void sol(int i, int j) {
        for (int d = 0; d < 8; d++) {
            int y = i, x = j;
            for (int next = 2; next <= 5; next++) // 다음 위치
            {
                boolean _find = false; // next 위치의 mbti를 찾았는가
                if (next == 5) {
                    ans++;
                    break;
                }

                int ny = y + dy[d], nx = x + dx[d];

                if (OOB(ny, nx))
                    break;

                for (char c : ch[next])
                    if (board[ny][nx] == c) {
                        y = ny;
                        x = nx;
                        _find = true;
                        break;
                    }

                if (!_find) // next번 mbti를 찾지 못했을 경우
                    break;
            }
        }
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        for (int i = 0; i < n; i++) {
            String s = br.readLine();
            for (int j = 0; j < m; j++) {
                board[i][j] = s.charAt(j);
                if (board[i][j] == 'E' || board[i][j] == 'I')
                    v.add(new pii(i, j));
            }
        }

        for (pii cur : v)
            sol(cur.y, cur.x);

        System.out.println(ans);
    }
}