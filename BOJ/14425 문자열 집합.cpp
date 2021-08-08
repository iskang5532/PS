/* 
 * 14425 문자열 집합
 * vector
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/14425
 * ETC.) 저장된 문자열을 정렬 후, 이진탐색으로 문자열의 존재 여부를 확인하여 개수를 추가 (이는 집합에 중복 문자열이 없기 때문에 가능)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> S(n);
    for (auto &str : S)
        cin >> str;

    sort(S.begin(), S.end()); // 이진 탐색을 위해 정렬

    int answer = 0;
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;

        answer += binary_search(S.begin(), S.end(), str); // 문자열이 집합에 존재하는지 이진 탐색을 통해 확인
    }

    cout << answer;
}