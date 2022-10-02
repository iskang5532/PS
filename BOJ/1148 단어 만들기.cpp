// 2022-09-28
// 1148 단어 만들기
// https://www.acmicpc.net/problem/1148
/*
    문자열, 구현 (14,444KB, 92ms)
    시간 복잡도: ?
    풀이)
    - 입력된 단어들을 저장할 words, 입력된 퍼즐판을 저장할 puzzle.
    - puzzle에 존재하는 문자의 개수를 저장할 m[].  (m[c] = k일 때, 퍼즐에 문자 c는 k개 존재)
    - words에 저장된 단어 word를 완성할 때 사용한 문자의 사용 횟수를 저장할 cnt[]. (cnt[c] = k일 때, 문자 c는 단어 완성에 k번 사용)
    - word에 존재하는 문자의 개수를 저장할 ch[].
    - m에 저장된 값을 이용하여 word가 만들 수 있는 문자인지 확인.
    만약 만들 수 있다면, 만들 때 사용된 문자를 cnt에 저장.
    이때, 중복된 문자는 한 번만 사용한 것으로 간주해야 함.
    - 최소 개수를 만들 수 있는 문자들을 저장할 문자열 s1, 최대 개수를 만들 수 있는 문자들을 저장할 문자열 s2.
    - cnt의 최솟값 mn과 최댓값 mx를 구함.
    이후, puzzle의 각 문자 c를 cnt에서 확인.
    만약 cnt[c] == mn일 경우, s1에 c를 추가.
    만약 cnt[c] == mx일 경우, s2에 문자를 추가.
    동일한 문자가 존재할 수 있으므로 값을 초기화하여 중복을 방지해야 한다.
    - 저장된 s1과 mn, s2와 mx를 출력한다.
    단, mn == mx일 경우 s2 대신 s1을 출력한다. (중복 방지로 인해 mn == mx일 때의 s2는 값이 저장되지 않음. s1으로 가기 때문)
    etc.)
    - 엄청 헷갈린 문제지만 다행히 원트
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 0x3f3f3f3f

vector<string> words; // words.size() ≤ 200,000

int main()
{
    FAST_IO;

    { // input word
        string s;
        while (cin >> s)
        {
            if (s == "-")
                break;
            words.push_back(s);
        }
    }
    { // input puzzle
        string puzzle;
        while (cin >> puzzle)
        {
            if (puzzle == "#")
                break;

            int m['Z' + 3]{}; // 퍼즐의 문자의 개수를 저장 (m[c] = k일 때, 퍼즐에 문자 c는 k개 존재)
            for (const char &c : puzzle)
                m[c]++;

            int cnt['Z' + 3]{}; // 단어를 완성할 때 사용한 문자의 사용 횟수를 저장 (cnt[c] = k일 때, 문자 c는 단어 완성에 k번 사용)
            for (const string &word : words)
            {
                bool valid = true; // 만들 수 있는 단어인가?
                int ch['Z' + 3]{}; // 문자의 개수를 저장
                for (const char &c : word)
                    if (m[c] < ++ch[c])
                        valid = false;

                if (!valid)
                    continue;

                for (const char &c : puzzle)
                {
                    if (ch[c] == -1) // 중복 제외
                        continue;
                    if (ch[c] != 0) // 사용된 문자인가
                        cnt[c]++;
                    ch[c] = -1;
                }
            }

            int mn = INF, mx = 0;
            for (const char &c : puzzle)
                mn = min(mn, cnt[c]), mx = max(mx, cnt[c]);

            string s1, s2;
            for (const char &c : puzzle)
            {
                if (cnt[c] == mn)
                    s1.push_back(c), cnt[c] = -1;
                if (cnt[c] == mx)
                    s2.push_back(c), cnt[c] = -1;
            }

            sort(s1.begin(), s1.end()), sort(s2.begin(), s2.end());
            cout << s1 << ' ' << mn << ' ' << (mn == mx ? s1 : s2) << ' ' << mx << endl; // mn == mx에 주의
        }
    }
}