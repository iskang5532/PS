/*
    1339 단어 수학
    그리디, 맵 (2,032KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1339
    etc.) 쉬운 문제라고 생각했지만, 꽤 헤맴..
    - 문자열의 길이가 긴 입력부터 앞에서부터 수를 부여하면 될 줄 알았지만, 아니었음.
    - 길이가 같은 문자열이 존재하면서 맨 앞의 문자가 같을 수가 있으므로 고려하며 풀었지만, 이 또한 틀림. (밑에 적어둔 반례와 같이 문자열이 길다고 반드시 값이 큰 것은 아님)
    - 반례를 해결하기 위해, 입력된 문자열의 모든 문자와 위치에 대한 값을 저장.
    - 구해진 문자에 대한 값을 이용하며, 큰 값부터 큰 수를 부여.
    참고:
    - 반례에 대한 해결법 https://excited-hyun.tistory.com/145
    - '그리디'란? https://www.acmicpc.net/board/view/63716
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int NUMBER[26]; // 알파벳의 변환된 숫자를 저장

int to_num(const string &str)
{
    string ret;

    for (const auto &c : str)
        ret += NUMBER[c - 'A'] + '0';

    return stoi(ret);
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 단어의 개수 (1 ≤ N ≤ 10)
    cin >> n;
    vector<string> arr(n); // 입력된 문자열을 저장 (문자열을 수로 변환할 때 사용)
    map<char, int> m;      // 입력된 알파벳이 몇 번째 위치에 몇 개가 왔는지를 저장
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        arr[i] = str;

        int len = 1; // 1의 자리부터
        for (auto itr = str.rbegin(); itr != str.rend(); itr++)
            m[*itr] += len, len *= 10;
    };

    vector<pair<int, char>> vec;
    for (const auto &[c, cnt] : m) // value 기준 정렬
        vec.push_back({cnt, c});
    sort(vec.begin(), vec.end(), greater<pair<int, char>>());

    fill(NUMBER, NUMBER + 26, -1);
    int t = 9; // 알파벳에 부여할 숫자
    for (const auto &[cnt, c] : vec)
        if (NUMBER[c - 'A'] == -1) // 만약 현재 알파벳에 부여된 수가 없을 경우
            NUMBER[c - 'A'] = t, t--;

    int ans = 0;
    for (const auto &str : arr)
        ans += to_num(str);
    cout << ans;
}

// input:
// 3
// ABB
// BAA
// BAA
// ans: 2875

// input:
// 10
// ABB
// BB
// BB
// BB
// BB
// BB
// BB
// BB
// BB
// BB
// ans: 1790