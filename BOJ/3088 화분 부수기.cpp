// 2022-07-10
// 3088 화분 부수기
// https://www.acmicpc.net/problem/3088
/*
    그리디 (6,392KB, 92ms)
    시간 복잡도: ?
    풀이)
    - 이전에 부순 화분에 존재했던 수를 저장할 used[]. (used[k] = true일 때, 부순 화분에 수 k가 존재했음)
    - 첫 번째 화분의 수부터 확인.
    만약 현재 화분의 세 수 중 하나가 이전에 부순 화분에 존재했을 경우, 알아서 부숴짐.
    만약 현재 화분의 세 수 중 하나도 이전에 부순 화분에 존재하지 않을 경우, 부서야 함. (= ans++)
 */

#include <iostream>
using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N 300'003   // max n
#define MAX_K 1'000'003 // max ai, bi, ci

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX_N][3];
    for (int i = 0; i < n; i++)
        for (auto &elem : v[i])
            cin >> elem;

    int ans = 0;
    bool used[MAX_K]{}; // used[k] = true일 때, 부순 화문에 수 k가 존재했음
    for (int i = 0; i < n; i++)
    {
        bool be = false; // 이전에 부순 화분에 수가 있었는가
        for (const auto &elem : v[i])
            if (used[elem])
                be = true;
        if (!be)
            ans++;

        for (const auto &elem : v[i])
            used[elem] = true;
    }

    cout << ans;
}