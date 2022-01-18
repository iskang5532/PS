// 1450 냅색문제
// https://www.acmicpc.net/problem/1450
/*
    이분 탐색, 중간에서 만나기 (2,920KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력된 물건으로 만들 수 있는 무게를 모두 구한 후, c 이하 무게의 개수를 구하면 되는 문제.
    - n = 30일 수도 있음. 이는 경우의 수를 구할 때 LLONG_MAX를 초과. 그러므로 두 개의 공간 v1, v2에 나눠 담아줌.
    - v1과 v2에 존재하는 물건들을 이용하여 만들 수 있는 무게를 a, b에 저장.
    이때, a와 b에는 추가로 '0'이 들어가게 됨.
    반드시 a와 b에서 각각 하나씩 뽑아 가방에 넣는 것이 아님. 즉, a의 물건만 가방에 넣을 수 있음.
    그러므로 a의 물건 하나를 가방에 넣어 무게가 늘어난다면, b의 물건 중에서는 무게가 없는 물건이 존재해야 한다. (이는 a 또한 마찬가지)
    또한, 0과 0이 될 수도 있는데, 이는 물건을 넣지 않는 경우이다.
    - b의 물건을 하나씩 확인. (물건의 무게는 i)
    물건을 가방에 담고 난 후 남은 가방의 무게는 k(= c-i)라고 할 때, k 이하의 물건이 a에 몇 개 있는지를 탐색한 후, ans에 더해줌.
    etc.) 투 포인터?
 */

#include <iostream>
#include <vector>
#include <algorithm> // upper_bound

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
typedef long long ll;

vector<ll> func(const vector<int> &v)
{
    int sz = v.size();
    vector<ll> ret = {0}; // v의 값으로 만들 수 있는 모든 수를 저장

    for (int bits = 1; bits < 1 << sz; bits++)
    {
        ll sum = 0;
        for (int pos = 0; pos < sz; pos++)
            if (bits & 1 << pos)
                sum += v[pos];

        ret.push_back(sum);
    }

    return ret;
}

int main()
{
    FAST_IO;

    int n, c; // 물건의 개수 n(1 ≤ n ≤ 30), 가방의 무게 c(1 ≤ C ≤ 10^9)
    cin >> n >> c;
    vector<int> v1, v2; // 1 ≤ k ≤ 10^9
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (i & 1)
            v1.push_back(k);
        else
            v2.push_back(k);
    }

    vector<ll> a = func(v1);
    vector<ll> b = func(v2);
    sort(a.begin(), a.end());

    ll ans = 0;
    for (const auto &i : b)
        ans += upper_bound(a.begin(), a.end(), c - i) - a.begin(); // c - i 이하 값의 개수를 a에서 탐색

    cout << ans;
}