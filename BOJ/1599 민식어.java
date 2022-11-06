// 2022-11-03
// 1599 민식어
// https://www.acmicpc.net/problem/1599
/*
    sol.1) 맵, 정렬 (14,472KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 민식어의 순서에 대응하는 영어를 m[]에 저장.
    - 민식어로 이루어진 문자열 s를 영어로 변환. (= get_str())
    문자열을 변환할 때, 문자를 하나씩 확인하여 m에서 그에 대응하는 영어를 가져와 저장함.
    주의할 점은, 민식어에서 "ng"와 같이 길이 2의 문자열로 이루어져 있다.
    그러므로, 탐색중인 문자의 위치가 마지막 문자가 아닐 경우, 항상 다음 문자와 함께 "ng"인지를 확인해야 한다.
    - 변환된 문자열과 s를 v에 저장.
    이후, 변환된 문자열을 기준으로 오름차순 정렬.
    v에 저장된 순서대로 s를 출력.
    etc.) 다른 풀이가 있을 수 있지만 생각나지 않음
	참고)
	- Map: https://memo-the-day.tistory.com/28 
 */

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    static class Pair implements Comparable<Pair> {
        String s1, s2;

        Pair(String s1, String s2) {
            this.s1 = s1;
            this.s2 = s2;
        }

        @Override
        public int compareTo(final Pair p) {
            return s1.compareTo(p.s1);
        }
    }

    static Map<String, Character> m = Map.ofEntries(
            new AbstractMap.SimpleEntry<String, Character>("a", 'a'),
            new AbstractMap.SimpleEntry<String, Character>("b", 'b'),
            new AbstractMap.SimpleEntry<String, Character>("k", 'c'),
            new AbstractMap.SimpleEntry<String, Character>("d", 'd'),
            new AbstractMap.SimpleEntry<String, Character>("e", 'e'),
            new AbstractMap.SimpleEntry<String, Character>("g", 'f'),
            new AbstractMap.SimpleEntry<String, Character>("h", 'g'),
            new AbstractMap.SimpleEntry<String, Character>("i", 'h'),
            new AbstractMap.SimpleEntry<String, Character>("l", 'i'),
            new AbstractMap.SimpleEntry<String, Character>("m", 'j'),
            new AbstractMap.SimpleEntry<String, Character>("n", 'k'),
            new AbstractMap.SimpleEntry<String, Character>("ng", 'l'),
            new AbstractMap.SimpleEntry<String, Character>("o", 'm'),
            new AbstractMap.SimpleEntry<String, Character>("p", 'n'),
            new AbstractMap.SimpleEntry<String, Character>("r", 'o'),
            new AbstractMap.SimpleEntry<String, Character>("s", 'p'),
            new AbstractMap.SimpleEntry<String, Character>("t", 'q'),
            new AbstractMap.SimpleEntry<String, Character>("u", 'r'),
            new AbstractMap.SimpleEntry<String, Character>("w", 's'),
            new AbstractMap.SimpleEntry<String, Character>("y", 't'));

    static String get_str(final String s) { // 민식어를 영어로 변환
        ArrayList<Character> ret = new ArrayList<>();

        for (int l = 0; l < s.length(); l++)
            if (l != s.length() - 1 && (s.charAt(l) == 'n' && s.charAt(l + 1) == 'g'))
                ret.add(m.get("ng"));
            else
                ret.add(m.get(Character.toString(s.charAt(l))));

        return ret.stream().map(String::valueOf).collect(Collectors.joining());
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 민식어의 개수 (1 ≤ n ≤ 50)
        ArrayList<Pair> v = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            String s = br.readLine();

            v.add(new Pair(get_str(s), s));
        }

        Collections.sort(v);
        for (int i = 0; i < n; i++)
            System.out.println(v.get(i).s2);
    }
}

/*
    sol.2) 정렬, 구현 (16,252KB, 168ms)
    시간 복잡도: ?
    풀이)
    - 입력된 민식어를 replaceAll을 이용하여 영어로 변환.
    이때 주의할 점은, ng는 n과 g가 합쳐진 문자열이다. 즉, n 혹은 g가 다른 문자로 변환될 수 있다.
    그러므로 먼저 ng를 임의의 문자로 변환 후에 민식어를 영어로 변환하고 난 후 임의의 문자를 다시 영어로 변환해준다.
    참고)
    - audrn6689님 코드 (48973798): https://www.acmicpc.net/source/48973798
 */

import java.io.*;
import java.util.*;

public class Main {
    static class Pair implements Comparable<Pair> {
        String s1, s2;

        Pair(String s1, String s2) {
            this.s1 = s1;
            this.s2 = s2;
        }

        @Override
        public int compareTo(final Pair p) {
            return s1.compareTo(p.s1);
        }
    }

    static final String[] eng___ = { "-", "a", "b", "c", "d", "e", "g", "h", "i", "j", "k", "l", "n", "o", "p", "q", "r", "s", "t", "u", "m" };
    static final String[] minsic = { "ng", "a", "b", "k", "d", "e", "g", "h", "i", "l", "m", "n", "o", "p", "r", "s", "t", "u", "w", "y", "-" };

    static String get_str(final String s) { // 민식어를 영어로 변환

        String ret = s;
        for (int pos = 0; pos < eng___.length; pos++)
            ret = ret.replaceAll(minsic[pos], eng___[pos]);

        return ret;
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine()); // 민식어의 개수 (1 ≤ n ≤ 50)
        ArrayList<Pair> v = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            String s = br.readLine();

            v.add(new Pair(get_str(s), s));
        }

        Collections.sort(v);
        for (int i = 0; i < n; i++)
            System.out.println(v.get(i).s2);
    }
}