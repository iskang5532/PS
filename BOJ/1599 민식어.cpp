// 2022-11-03
// 1599 민식어
// https://www.acmicpc.net/problem/1599
/*
    맵, 정렬 (2,176KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 민식어의 순서에 대응하는 영어를 m[]에 저장.
    - 민식어로 이루어진 문자열 s를 영어로 변환. (= get_str())
    문자열을 변환할 때, 문자를 하나씩 확인하여 m에서 그에 대응하는 영어를 가져와 저장함.
    주의할 점은, 민식어에서 "ng"와 같이 길이 2의 문자열로 이루어져 있다.
    그러므로, 탐색중인 문자의 위치가 마지막 문자가 아닐 경우, 항상 다음 문자와 함께 "ng"인지를 확인해야 한다.
    - 변환된 문자열과 s를 v에 저장.
    이후, 변환된 문자열을 기준으로 오름차순 정렬.
    v에 저장된 순서대로 s를 출력.
    etc.) 다른 풀이가 있을 수 있지만 생각나지 않음
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

const map<string, char> m = {
    {"a", 'a'},
    {"b", 'b'},
    {"k", 'c'},
    {"d", 'd'},
    {"e", 'e'},
    {"g", 'f'},
    {"h", 'g'},
    {"i", 'h'},
    {"l", 'i'},
    {"m", 'j'},
    {"n", 'k'},
    {"ng", 'l'},
    {"o", 'm'},
    {"p", 'n'},
    {"r", 'o'},
    {"s", 'p'},
    {"t", 'q'},
    {"u", 'r'},
    {"w", 's'},
    {"y", 't'},
};

string get_str(const string &s) // 민식어를 영어로 변환
{
    string ret;

    for (int l = 0; l < s.length(); l++)
        if (l != s.length() - 1 && string({s[l], s[l + 1]}) == "ng")
            ret += m.at("ng");
        else
            ret += m.at(string({s[l]}));

    return ret;
}

int main()
{
    FAST_IO;

    int n; // 민식어의 개수 (1 ≤ n ≤ 50)
    cin >> n;

    vector<pair<string, string>> v;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        v.push_back({get_str(s), s});
    }

    sort(v.begin(), v.end());

    for (const auto &[i, s] : v)
        cout << s << endl;
}