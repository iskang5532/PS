// 2022-11-07
// 9519 졸려
// https://www.acmicpc.net/problem/9519
/*
    시뮬레이션 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 원래 단어 word가 주어지는 것이 아닌, x번 섞인 문자열 s를 word를 구하는 문제.
    - 입력된 x는 10억이며, 문자열 s의 길이는 1'000이다. 즉, 완전 탐색을 이용하면 TLE.
    그러나 10억번 반복하는 도중 입력된 문자열로 돌아오는 경우가 생긴다. 즉, 일정 횟수부터는 반복되므로 횟수를 감소시킬 수 있다.
    - word의 문자 위치를 저장할 v[]. (v[i] = {0, 3, 1, 2}이며 원래 단어가 word일 경우, word[1] == s[3])
    - v의 기본값은 {0, 1, 2, ...}.
    만약 i번 섞었을 때의 v가 기본값과 같아질 경우, x %= i.
    이후, 최대 i번 반복하여 v[]를 구함.
    - v에 저장된 값을 이용하여 s에서 문자를 추출하여 출력.
    참고)
    - 댓글: https://www.acmicpc.net/board/view/25714
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

vector<int> get_v(int x, int sz)
{
    auto isDefault = [](const vector<int> &v) -> bool // 기본값과 같은가
    {
        for (int i = 0; i < v.size(); i++)
            if (v[i] != i)
                return false;
        return true;
    };

    vector<int> prev(sz);
    for (int i = 0; i < sz; i++)
        prev[i] = i;
    for (int i = 0; i < x; i++)
    {
        vector<int> cur(sz);
        for (int pos = 0, l = 0, r = sz - 1; l <= r; pos += 2, l++, r--)
            cur[l] = prev[pos], (l != r ? cur[r] = prev[pos + 1] : 0);
        if (isDefault(cur))
            x %= i + 1, i = -1; // 횟수를 감소시킨 후, 처음부터 다시 탐색.

        prev = cur;
    }

    return prev;
}

int main()
{
    FAST_IO;

    int x; // 눈을 깜박이는 횟수 (1 ≤ X ≤ 1,000,000,000)
    cin >> x;
    string s; // 3 ≤ s.length() ≤ 1'000
    cin >> s;

    vector<int> v = get_v(x, (int)s.length()); // 원래 단어의 문자 위치를 저장 (v[i] = {0, 3, 1, 2}이며 원래 단어가 word일 경우, word[1] == s[3])

    for (int i = 0; i < s.length(); i++)
        cout << s[v[i]];
}