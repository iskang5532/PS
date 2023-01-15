// 2023-01-14
// 27160 할리갈리
// https://www.acmicpc.net/problem/27160
/*
    맵 (2,028KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 과일과 개수를 맵에 저장. (동일한 과일이 입력된 경우, 기존 과일의 개수에 더함)
    - 맵에 저장된 과일과 개수를 확인.
    만약 개수가 5인 과일이 있는 경우, "YES"를 출력.
    만약 개수가 5인 과일이 하나도 없는 경우, "NO"를 출력.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

map<string, int> m; // m[s] = k일 경우, s의 개수는 총 k개

int main()

{
    FAST_IO;

    int n; // 카드의 개수 (1 ≤ n ≤ 100,000)
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s; // 과일의 종류
        int x;    // 과일의 개수 (1 ≤ x ≤ 5)
        cin >> s >> x;

        m[s] += x;
    }

    int valid = false; // 5개인 과일이 있는가?
    for (const auto &[s, x] : m)
        if (x == 5)
            valid = true;
    cout << (valid ? "YES" : "NO");
}