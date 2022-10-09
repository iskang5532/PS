// 2022-10-09
// 20291 파일 정리
// https://www.acmicpc.net/problem/20291
/*
    맵 (48,884KB, 1,184ms)
    시간 복잡도: ?
    풀이)
    - 입력되는 문자열이 형식이 존재하며, 점 이후에 나오는 확장자를 필요로 함.
    즉, 입력된 문자열에서 점의 위치를 구한 후, 그 이후에 나오는 문자열은 확장자가 됨.
    - 입력된 확장자의 수를 저장해야 하므로, 맵을 사용.
    또한, 출력할 확장자는 사전순으로 출력해야 하므로, TreeMap 사용.
    - 확장자가 시작되는 위치 pos를 구한 후, s[pos]에서부터 시작되는 문자열을 맵에 저장.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.TreeMap;

public class Main {

    static TreeMap<String, Integer> m = new TreeMap<>();

    static public void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 파일의 개수 (1 ≤ n ≤ 50,000)
        for (int i = 0; i < n; i++) {
            String s = br.readLine();

            int pos = 0; // 확장자가 시작되는 위치
            while (s.charAt(pos++) != '.')
                ;

            String _s = s.substring(pos);
            m.put(_s, (m.containsKey(_s) ? m.get(_s) : 0) + 1);
        }

        m.forEach((s, cnt) -> {
            System.out.println(s + " " + cnt);
        });
    }
}