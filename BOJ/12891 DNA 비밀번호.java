// 2022-10-18
// 12891 DNA 비밀번호
// https://www.acmicpc.net/problem/12891
/*
    슬라이딩 윈도우 (20,088KB, 332ms)
    시간 복잡도: O(n)
    풀이)
    - 일정 길이의 부분문자열을 사용해야 하므로, 슬라이딩 윈도우를 사용.
    - 부분문자열 속 문자의 개수를 저장할 cnt[].
    1. p개만큼 dna에서 부분문자열을 추출 후, 문자를 cnt에 저장.
    이후, isValid() 함수를 사용하여 부문문자열이 조건에 충족하는지 확인.
    만약 조건에 충족하면 ans++.
    2. 새로 추가할 문자의 위치 r은 p+1부터이며, dna[r] 문자를 추가. 또한, p개만큼 문자를 유지해야 하므로 제거할 위치 l은 0부터이며, dna[l] 문자를 제거.
    이후, isValid() 함수를 사용하여 부문문자열이 조건에 충족하는지 확인.
    dna의 마지막 문자까지 확인할 때까지 반복.
    - 충족해야 하는 문자의 개수(pass[])는 cnt와 같아야 하는 것이 아닌 최소 개수임에 주의.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

    static int[] pass = new int['z'], cnt = new int['z']; // 부분문자열 속 문자의 개수를 저장할 cnt

    static boolean isValid() {
        for (int i = 'A'; i < 'Z'; i++)
            if (pass[i] > cnt[i]) // 최소 개수를 충족시키지 못한 경우
                return false;
        return true;
    }

    public static void main(String[] argm) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int s = Integer.parseInt(st.nextToken()); // DNA 길이 |S|
        int p = Integer.parseInt(st.nextToken()); // 비밀번호 길이 |P| (1 ≤ |P| ≤ |S| ≤ 1,000,000)
        String dna = br.readLine();

        st = new StringTokenizer(br.readLine());
        for (char c : new char[] { 'A', 'C', 'G', 'T' })
            pass[c] = Integer.parseInt(st.nextToken());

        for (int i = 0; i < p; i++)
            cnt[dna.charAt(i)]++;

        int ans = 0;
        if (isValid())
            ans++;

        for (int l = 0, r = p; r < dna.length(); l++, r++) {
            cnt[dna.charAt(l)]--;
            cnt[dna.charAt(r)]++;
            if (isValid())
                ans++;
        }

        System.out.println(ans);
    }
}