
// 2023-03-22
// 15874 Caesar Cipher
// https://www.acmicpc.net/problem/15874
/*
    구현, 문자열 (16,204KB, 176ms)
    시간 복잡도: ?
    풀이)
    - c가 시작점인 'a' 혹은 'A'에서부터 얼마나 떨어져 있는지를 구함.
    이후, 해당 값에 k를 더한 후, 26을 나누게 된다면 최종적으로 시작점에서부터 얼마나 떨어졌는지 구할 수 있음.
 */

import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tk = new StringTokenizer(br.readLine()); // idx
        int k = Integer.parseInt(tk.nextToken());

        StringBuilder sb = new StringBuilder();
        String s = br.readLine();
        for (final char c : s.toCharArray())
            if ('a' <= c && c <= 'z')
                sb.append((char) ('a' + (c - 'a' + k) % 26));
            else if ('A' <= c && c <= 'Z')
                sb.append((char) ('A' + (c - 'A' + k) % 26));
            else
                sb.append(c);

        System.out.println(sb.toString());
    }
}