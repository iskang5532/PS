// 2022-10-27
// 2290 LCD Test
// https://www.acmicpc.net/problem/2290
/*
    구현 (22,452KB, 352ms)
    시간 복잡도: ?
    풀이)
    - 입력된 숫자를 영역별로 나눠 생각함. (x축으로 3개(0번부터 2번), y축으로 5개(0번부터 4번))
    - 반복되는 구간, 즉 확장해야 하는 구간은 x축에서는 1번, y축에서는 1번과 3번이다.
    - ch에 숫자의 영역에 따른 문자를 저장하여 출력. (ch[y][k][x] = '|'일 경우, y번 k의 x번은 '|')
    - 위에서 언급한 것처럼, x == 1 혹은 y == 1, y == 3일 경우 s번만큼 출력해야 한다.
    etc.) 노가다
 */

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.BufferedReader;

public class Main {
    static final char[][][] ch = {
            // 0 to 9
            { { ' ', '-', ' ' }, { ' ', ' ', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', ' ', ' ' },
                    { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' } },
            { { '|', ' ', '|' }, { ' ', ' ', '|' }, { ' ', ' ', '|' }, { ' ', ' ', '|' }, { '|', ' ', '|' },
                    { '|', ' ', ' ' }, { '|', ' ', ' ' }, { ' ', ' ', '|' }, { '|', ' ', '|' }, { '|', ' ', '|' } },
            { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' },
                    { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', ' ', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' } },
            { { '|', ' ', '|' }, { ' ', ' ', '|' }, { '|', ' ', ' ' }, { ' ', ' ', '|' }, { ' ', ' ', '|' },
                    { ' ', ' ', '|' }, { '|', ' ', '|' }, { ' ', ' ', '|' }, { '|', ' ', '|' }, { ' ', ' ', '|' } },
            { { ' ', '-', ' ' }, { ' ', ' ', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', ' ', ' ' },
                    { ' ', '-', ' ' }, { ' ', '-', ' ' }, { ' ', ' ', ' ' }, { ' ', '-', ' ' }, { ' ', '-', ' ' } },
    };

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int s = Integer.parseInt(st.nextToken());
        String n = st.nextToken();

        for (int y = 0; y < 5; y++)
            for (int _y = (y == 1 || y == 3) ? 0 : s - 1; _y < s; _y++, System.out.println()) // y 확장 (1 혹은 3일 경우)
                for (char c : n.toCharArray()) {
                    int k = c - '0';
                    for (int x = 0; x < 3; x++)
                        for (int _x = (x == 1) ? 0 : s - 1; _x < s; _x++) // x 확장 (1일 경우)
                            System.out.printf("%c", ch[y][k][x]);
                    System.out.print(' ');
                }
    }
}