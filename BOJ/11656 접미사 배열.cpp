// 2022-05-18
// 11656 접미사 배열
// https://www.acmicpc.net/problem/11656
/*
    문자열, 정렬 (2,580KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열을 i개씩 자른 결과를 벡터에 저장.
    - 벡터를 오름차순 정렬 후, 원소를 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    vector<string> v;
    for (int i = 0; i < s.length(); i++)
        v.push_back(string(s.begin() + i, s.end()));

    sort(v.begin(), v.end());
    for (const auto &s : v)
        cout << s << endl;
}