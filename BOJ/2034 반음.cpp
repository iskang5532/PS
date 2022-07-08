// 2034 반음
// https://www.acmicpc.net/problem/2034
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 해당 건반이 칠 수 있는 흰 건반인지를 저장할 배열 check.
    A부터 G까지 검은 건반을 포함하여 수를 메긴 후, 흰 건반의 위치에 true를 넣어 저장.
    - i번째 건반의 알파벳이 무엇인지를 저장할 배열 c.
    - 흰 건반의 위치를 첫 음으로 잡아 완전 탐색을 수행.
    만약 악보를 치는 중에 검은 건반이 나올 경우, 다음 흰 건반의 위치를 사용.
    만약 악보를 치는 중에 검은 건반이 안나온 경우, 첫 음과 마지막에 친 끝 음을 저장.
    - 주의할 점은, 시작 음에서 악보를 치는 도중 값이 음수가 되거나 건반의 수를 넘을 수 있음.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 10'003
#define mod 12

bool check[] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0};                          // i번째 건반의 여부
char c[] = {'A', '\0', 'B', 'C', '\0', 'D', '\0', 'E', 'F', '\0', 'G', '\0'}; // i번째 건반의 값

int solution(int v[], int n, int cur)
{
    for (int i = 0; i < n; i++)
    {
        cur = (cur + v[i]) % mod;
        if (cur < 0)
            cur += mod;

        if (!check[cur])
            return -1;
    }

    return cur;
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<pii> ans; // 첫 음 st와 끝 음 ed를 저장
    for (const int st : {0, 2, 3, 5, 7, 8, 10})
    {
        int ed = solution(v, n, st);
        if (ed != -1)
            ans.push_back({st, ed});
    }

    for (const auto &[st, ed] : ans)
        cout << c[st] << ' ' << c[ed] << endl;
}