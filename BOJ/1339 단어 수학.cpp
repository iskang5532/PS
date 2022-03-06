// 22-03-02
// 1339 단어 수학
// https://www.acmicpc.net/problem/1339
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 해당 문자의 자릿수에 맞춰 10의 거듭제곱을 cnt에 저장함.
    이후 cnt를 내림차순 정렬 후에 가장 큰 값에 9부터 값을 할당한 후, 총 합을 출력.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222609762108
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 단어의 개수 (1 ≤ N ≤ 10)
    cin >> n;

    int cnt[26]; // cnt[c] = k일 떄, 문자 c의 우선도는 k (k가 높을수록 다른 문자에 비해 높은 값을 받을 수 있음)
    fill(cnt, cnt + 26, 0);
    while (n--)
    {
        string s;
        cin >> s;
        reverse(s.begin(), s.end()); // 1의 자리부터 10의 거듭제곱 값을 부여
        for (int i = 0, l = 1; i < s.length(); i++)
            cnt[s[i] - 'A'] += l, l *= 10;
    }

    sort(cnt, cnt + 26, [&](int a, int b)
         { return a > b; }); // 내림차순 정렬

    int ans = 0;
    for (int i = 0; i < 10; i++) // 10개의 문자에 값을 부여
        ans += cnt[i] * (9 - i);

    cout << ans;
}

// 3
// ABB
// BAA
// BAA
// ans: 2875

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

/* 21-10-24
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

int ALPHABET[26]; // 알파벳의 변환된 숫자를 저장

int to_num(const string &str)
{
    string ret;

    for (const auto &c : str)
        ret += ALPHABET[c - 'A'] + '0';

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

    fill(ALPHABET, ALPHABET + 26, -1);
    int t = 9; // 알파벳에 부여할 숫자
    for (const auto &[cnt, c] : vec)
        if (ALPHABET[c - 'A'] == -1) // 만약 현재 알파벳에 부여된 수가 없을 경우
            ALPHABET[c - 'A'] = t, t--;

    int ans = 0;
    for (const auto &str : arr)
        ans += to_num(str);
    cout << ans;
}