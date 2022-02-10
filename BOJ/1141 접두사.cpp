// 1141 접두사
// https://www.acmicpc.net/problem/1141
/*
    문자열, 구현 (2,028KB, 0ms)
    시간 복잡도: O(n^3) (substr: O(n))
    풀이)
    - 접두사가 아닌 문자열의 개수 ans를 찾음.
    - 문자열을 하나 선택한 후, 나머지 문자열과 비교하여 기준 문자열이 접두사가 아닌지를 확인.
    만약 기준 문자열이 비교 문자열의 접두사인 경우, 비교를 종료한 후 기준 문자열을 바꿈.
    만약 기준 문자열이 모든 문자열과 비교 후에 접두사가 아님이 확인됐을 경우, ans++.
    - 기준 문자열이 비교 문자열보다 길이가 길 수 있으므로, 정렬을 통해 항상 기준 문자열이 비교 문자열의 길이 이하로 되게끔 만들어줌.
    etc.) 조합, dfs로 해결 하려다가 망함.
    - 문제 이해 및 삽질로 시간을 많이씀
    참고)
    - 이론: https://godzz.tistory.com/41 (코드 해석해서 참고함)
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 50 + 1

bool cmp(const string &s1, const string &s2) // 길이로 정렬
{
    return s1.length() < s2.length();
}

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 50
    cin >> n;
    vector<string> v(n); // s.len ≤ 50
    for (auto &s : v)
        cin >> s;
    sort(v.begin(), v.end(), cmp); // 문자열의 길이로 정렬

    int ans = 1; // 접두사로 사용되지 않는 문자열의 개수
    for (int i = 0; i < n - 1; i++)
    {
        bool isPrefix = false;
        for (int j = i + 1; j < n; j++)
        {
            string s1 = v[i], s2 = v[j];
            if (s1 == s2.substr(0, s1.length()))
            {
                isPrefix = true;
                break;
            }
        }

        if (!isPrefix)
            ans++;
    }

    cout << ans;
}

// 11
// h xi hio run hcc runn runc hipo runni running running
// ans: 6
// h [xi] [hio] run [hcc] [runn] [runc] [hipo] runni running running