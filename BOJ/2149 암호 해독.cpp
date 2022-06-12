// 2022-06-10
// 2149 암호 해독
// https://www.acmicpc.net/problem/2149
/*
    구현 (2,028KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 키 k와 암호문 s가 주어진다.
    암호문을 구하기 위해서는 정렬된 키가 필요하므로, 키를 정렬한다.
    1. 정렬된 키 sk에 암호문을 맞춘다. (= v)
    2. 정렬된 키 sk를 기존 k의 값과 같이 되돌린다. (= ans)
    3. 구한 ans를 출력하되, 열을 먼저 출력한다.
    - 주의할 점은, 문제 설명의 예시와 같이 키에 동일한 문자가 존재할 수 있다.
    ans를 채우기 위해 k와 sk를 비교하는 과정에서 k == sk일 때, 무작정 ans에 값을 넣게 된다면 동일한 값이 들어갈 수 있다.
    etc.) 문제 설명과 같이 암호문을 구하는 문제인줄
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

vector<string> get_ans(const string &k, const string &s)
{
    vector<string> v(k.length());
    for (int i = 0; i < s.length(); i++) // 열을 먼저 채움
        v[i / (s.length() / k.length())].push_back(s[i]);

    vector<string> ans(k.length()); // 평문
    string sk = k;                  // sorted k
    sort(sk.begin(), sk.end());
    for (int i = 0; i < k.length(); i++) // 키에 맞춤
    {
        char cur = sk[i];
        for (int j = 0, flag = true; j < k.length() && flag; j++)
        {
            char next = k[j];
            if (cur == next && ans[j].empty())
                ans[j] = v[i], flag = false;
        }
    }

    return ans;
}

int main()
{
    FAST_IO;

    string k, s;
    cin >> k >> s;

    auto ans = get_ans(k, s);
    for (int j = 0; j < s.length() / k.length(); j++)
        for (int i = 0; i < k.length(); i++)
            cout << ans[i][j];
}