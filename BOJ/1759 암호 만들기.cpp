/* 
 * 1759 암호 만들기
 * brute-force
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1759
 * etc.) line.45에서 좀 헷갈렸음.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define endl "\n"

int n, m; // 암호의 길이 및 암호 후보 개수 (3 <= n, m <= 15)
string str;

bool isValid(const string &ans)
{
    int a = 0, b = 0; // 자음 및 모음의 개수
    for (const auto &c : ans) // 암호의 문자를 하나씩 검사
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') // 모음일 경우
            b++;
        else // 자음일 경우
            a++;

    if (a >= 2 && b >= 1) // 조건에 만족하는 경우 (자음이 둘 이상, 모음이 하나 이상)
        return true;
    return false;
}

void dfs(const string &ans = "", const int start = 0, const int cnt = 0)
{
    if (ans.length() == n && isValid(ans)) // 원하는 길이 및 적합한 문자열인 경우
    {
        cout << ans << endl;
        return;
    }

    for (int idx = start; idx < m; idx++) // 암호에 넣어볼 문자 탐색. 시작지점 start부터 m - 1까지
    {
        char c = str[idx]; // idx번째 문자
        dfs(ans + c, idx + 1, cnt + 1); // 주의할 점은, start + 1이 아닌 idx + 1 (오름차를 요하기 때문)
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        str.push_back(c);
    }
    sort(str.begin(), str.end()); // 출력이 오름차순을 요하기 때문에 입력값을 정렬시켜 줌

    dfs();
}