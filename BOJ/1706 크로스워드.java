// 2022-10-26
// 1706 크로스워드
// https://www.acmicpc.net/problem/1706
/*
    구현 (14,432KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 입력된 퍼즐의 모든 세로 단어를 확인 후, 사전식 순으로 가장 앞서 있는 낱말을 s1에 저장.
    - 퍼즐을 시계방향으로 90도 회전.
    이후, 회전된 퍼즐에서 모든 세로 단어를 확인 후, 사전식 순으로 가장 앞서 있는 낱말을 s2에 저장.
    - s1과 s2를 비교 후 사전식 순으로 앞서 있는 낱말을 출력.
    - 단어 확인 중에 '#'을 만날 경우, 그전에 나온 문자들을 모아놓은 문자열 s를 단어로 취급.
    주의할 점은, s의 길이가 1일 수 있음. 이때는 단어로 취급하지 않음.
    etc.) 가로 단어와 세로 단어를 확인하는 식으로 풀려다가, 배열 회전이 떠올라 풀이를 바꿈
 */

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class Main {

    static String get_ans(char[][] board) { // 세로 단어 확인

        String ret = String.valueOf((char) ('z' + 1)); // 첫 단어가 항상 사전순으로 앞설 수 있도록
        int r = board.length, c = board[0].length;

        for (int x = 0; x < c; x++) {
            ArrayList<Character> v = new ArrayList<>();
            for (int y = 0; y < r; y++)
                if (board[y][x] != '#')
                    v.add(board[y][x]);
                else {
                    String s = v.stream().map(String::valueOf).collect(Collectors.joining());
                    if (v.size() >= 2 && s.compareTo(ret) < 0)
                        ret = s;
                    v.clear();
                }

            String s = v.stream().map(String::valueOf).collect(Collectors.joining());
            if (v.size() >= 2 && s.compareTo(ret) < 0)
                ret = s;
        }

        return ret;
    }

    static char[][] rotate(char[][] board) { // 시계 방향 회전

        int r = board.length, c = board[0].length;

        char[][] ret = new char[c][r];
        for (int y = 0; y < c; y++)
            for (int x = 0; x < r; x++)
                ret[y][x] = board[r - 1 - x][y];

        return ret;
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int r = Integer.parseInt(st.nextToken()), c = Integer.parseInt(st.nextToken()); // (2 ≤ R, C ≤ 20)
        char[][] board = new char[r][c];
        for (int i = 0; i < r; i++)
            board[i] = br.readLine().toCharArray();

        String s1 = get_ans(board);
        board = rotate(board);
        String s2 = get_ans(board);

        System.out.println(s1.compareTo(s2) < 0 ? s1 : s2);
    }
}