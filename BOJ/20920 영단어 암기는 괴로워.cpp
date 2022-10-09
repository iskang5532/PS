// 2022-10-07
// 20920 영단어 암기는 괴로워
// https://www.acmicpc.net/problem/20920
/*
    맵, 정렬 (17,448KB, 108ms)
    시간 복잡도: ?
    풀이)
    - 단어가 입력된 횟수를 저장할 맵 um.
    - 입력된 단어의 길이가 m 이상일 경우, um에 횟수 저장.
    - 맵에 저장된 값을 정렬해주기 위해 벡터 v를 생성 후 맵에 있는 값들을 옮김.
    - v를 정렬.
    1. 두 단어의 입력 횟수 cnt끼리 비교 후, 큰 값을 리턴. 만약 cnt가 서로 같을 경우, 2번 수행
    2. 두 단어의 길이를 비교 후, 더 긴 값을 리턴. 만약 두 단어의 길이가 같을 경우, 3번 수행
    3. 두 단어를 비교 후, 작은 값을 리턴. (작은 값은 사전 순으로 앞서 있는 단어가 됨)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

unordered_map<string, int> um; // {단어, 횟수}

bool cmp(const pair<string, int> &p1, const pair<string, int> &p2)
{
    const auto &[s1, c1] = p1;
    const auto &[s2, c2] = p2;

    return c1 != c2 ? c1 > c2                                                 // 1. 횟수
                    : (s1.length() != s2.length() ? s1.length() > s2.length() // 2. 길이
                                                  : s1 < s2);                 // 3. 사전 순
}

int main()
{
    FAST_IO;

    int n, m; // 단어의 개수 n(1 ≤ n ≤ 100,000), 기준 길이 m(1 ≤ m ≤ 10)
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        if (s.length() < m)
            continue;

        um[s]++;
    }

    vector<pair<string, int>> v;
    for (const auto &[s, cnt] : um)
        v.push_back({s, cnt});

    sort(v.begin(), v.end(), cmp);

    for (const auto &[s, cnt] : v)
        cout << s << endl;
}
