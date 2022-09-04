// 2022-08-26
// 19639 배틀로얄
// https://www.acmicpc.net/problem/19639
/*
    그리디 (5,256KB, 40ms)
    시간 복잡도: ?
    풀이)
    - 체력이 회복되는 양과 감소하는 양 모두 최대 m의 절반이다.
    이는 체력이 0에 근접하여도 어느 회복을 하든 최대 체력을 넘지 않는다.
    즉, 아무 아이템을 사용하여도 된다.
    1. 최대 체력을 넘지 않는 선에서 체력을 회복한다.
    2. 0이 되지 않을 때까지 공격한다.
    이때, 회복 여부와 상관없이 적을 공격하지 않을 수가 있다.
    이는 공격하면 체력이 0 이하가 되는 순간이다.
    즉, 적이 남아 있으면서 공격하지 않고 넘어간다면, 게임에서 이길 방법이 없다.
    - 사용한 아이템 혹은 처치한 적의 번호를 ans[]에 저장한다.
    - 적을 모두 처치하게 된다면, ans를 출력한다.
    이때, 적의 처치 여부와 상관없이 아이템이 남아 있을 수 있으므로 사용하지 않고 남은 아이템 또한 모두 출력한다.
    etc.) 정렬이나 pii를 이용해야 하는줄 알았으나 필요없었음
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

vector<int> ans;
int mx_hp;
bool valid = true;

int main()
{
    FAST_IO;

    int x, y, m; // 사람의 수 x, 아이템의 개수 y, 체력 m (0 ≤ x, y ≤ 100,000, 2 ≤ m ≤ 100,000)
    cin >> x >> y >> m, mx_hp = m;

    vector<int> atk(x), item(y);
    for (int i = 0; i < x; i++)
        cin >> atk[i];
    for (int i = 0; i < y; i++)
        cin >> item[i];

    int a = 0, b = 0; // 현재 atk의 위치 a, 현재 item의 위치 b
    while (a < x && valid)
    {
        while (b < y && m + item[b] <= mx_hp)
        {
            ans.push_back(b + 1);
            m += item[b];
            b++;
        }

        bool flag = false; // 플레이어를 공격한 적이 있는가
        while (a < x && m - atk[a] > 0)
        {
            ans.push_back(-(a + 1));
            m -= atk[a];
            a++, flag = true;
        }

        if (!flag)
            valid = false;
    }

    if (valid)
    {
        for (const int &i : ans)
            cout << i << endl;
        while (b < y)
            cout << ++b << endl;
    }
    else
        cout << 0;
}