// 2022-05-01
// 3048 개미
// https://www.acmicpc.net/problem/3048
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 구조체 배열 v를 선언한 후, 입력된 문자와 방향을 저장.
    - 이후, t초간 v를 탐색.
    만약 인접한 두 값의 방향이 정방향이면서 서로 다른 경우, 두 값을 바꾸며 i++. (i+1번째 값을 이용했으므로)
    - 주의할 점은, 방향에 맞게 바꿔줘야 한다는 것이다.
    오른쪽으로 가는 A와 왼쪽으로 가는 B가 있을 때, 1초에는 BA가 될 것이다.
    2초에는 BA 그대로여야 한다. B와 A가 서로 방향이 다르다고 해서 AB로 만들지 않도록 해야 한다. (둘 다 정방향이며, 앞에 서로 다른 방향을 가진 문자가 없음)
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define RIGHT 0
#define LEFT 1

struct pii
{
    int ch, pos;
};

int main()
{
    FAST_IO;

    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    int t; // 시간 (0 ≤ T ≤ 50)
    cin >> t;

    int sz = n + m;
    vector<pii> v(sz);
    int pos = 0;
    for (int i = n - 1; i >= 0; i--)
        v[pos] = {s1[i], RIGHT}, pos++;
    for (int i = 0; i < m; i++)
        v[pos] = {s2[i], LEFT}, pos++;

    while (t--)
        for (int i = 0; i < sz - 1; i++)
            if (v[i].pos == RIGHT && v[i + 1].pos == LEFT) // 방향이 다르면서 정방향인 경우
                swap(v[i + 1], v[i]), i++;

    for (const auto &elem : v)
        cout << (char)elem.ch;
}

// while (t--)
// {
//     vector<pii> temp(l);
//     for (int i = 0; i < l - 1; i++)
//         if (v[i].pos == 0 && v[i + 1].pos == 1)
//             temp[i] = v[i + 1], temp[i + 1] = v[i], i++;
//         else
//             temp[i] = v[i];
//     if (v[l - 2].pos == v[l - 1].pos || v[l - 2].pos == 1 && v[l - 1].pos == 0)
//         temp[l - 1] = v[l - 1];

//     v = temp;
// }