// 2022-10-04
// 1515 수 이어 쓰기
// https://www.acmicpc.net/problem/1515
/*
    완전 탐색, 구현 (16,296KB, 148ms)
    시간 복잡도: ?
    풀이)
    - 수 ans를 1부터 n까지 증가시켜가며 ans에 입력된 문자열 s의 각 문자가 포함되는지 확인 후, 만족하는 최솟값을 구함.
    - ans를 문자열 i로 변환 후, 첫 번째 문자부터 마지막 문자까지 확인.
    i의 현재 확인하고 있는 문자의 위치를 저장할 pos.
    - pos++해가며 i[pos]의 값이 c와 같아지는지 확인.
    만약 같아질 경우, ans는 c를 포함할 수 있음.
    만약 같아지지 않을 경우, ans는 c를 포함하지 않으므로 ans++ 후에 다시 확인.
    - pos를 저장하는 이유는, 두 자릿수 이상의 값이 ans에 포함될 수 있어서임. (ans가 11이며 연속된 c의 값이 11일 경우)
    - 모든 c를 확인한 후, 구해진 ans를 출력.
    etc.)
    - 입력된 수의 길이가 3000자리라 출력 또한 3000자리일줄
    - 문자열 구현에 약한듯
 */

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

    public static void main(String[] args) throws IOException {
        String s = new BufferedReader(new InputStreamReader(System.in)).readLine();

        int ans = 1;
        int pos = 0; // ans의 위치 (pos = 1일 경우, ans[1]과 비교중)
        for (char c : s.toCharArray()) {
            boolean done = false;
            while (true) {
                String i = String.valueOf(ans);
                for (; pos < i.length() && !done; pos++)
                    if (i.charAt(pos) == c)// 현재 값에 숫자가 포함된 경우
                        done = true;

                if (done)
                    break;

                ans++;
                pos = 0;
            }
        }

        System.out.println(ans);
    }
}