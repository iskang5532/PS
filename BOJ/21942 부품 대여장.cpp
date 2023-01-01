// 2022-12-27
// 21942 부품 대여장
// https://www.acmicpc.net/problem/21942
/*
    맵, 파싱 (10,804KB, 302ms)
    시간 복잡도: ?
    풀이)
    - 입력된 날짜와 시간을 분으로 바꿔 계산함.
    - 맵 m에 회원이 빌린 부품의 이름과 시간을 저장하며, 이름과 벌금을 ans에 저장.
    - 모든 정보를 확인.
    만약 저장된 맵에 회원이 빌린 부품 중 현재 정보의 부품이 없을 경우, 부품을 빌리는 정보.
     - 맵에 회원의 이름과 함께 부품의 이름과 시간을 저장.
    만약 저장된 맵에 회원이 빌린 부품 중 현재 정보의 부품가 있을 경우, 부품을 반납하는 정보.
     - 맵에 저장된 시간은 빌린 시간이므로, 해당 시간과 반납한 시간의 차이가 기간을 넘었는지 확인.
     만약 넘었을 경우, ans에 이름과 벌금을 추가.
    - ans에 저장된 값을 출력. (단, 값이 없을 경우, -1을 출력)
    etc.)
    - 변수 사용을 착각 (dp 변수를 안쓰고 DAYS 변수를 쓰다가 데임)
    참고)
    - 맵 속에 맵 넣기: https://www.geeksforgeeks.org/implementing-multidimensional-map-in-c/
 */

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
using ll = long long;

constexpr int DAYS[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // i월의 일수
int dp[13]{};                                                                 // dp[i] = k일 경우, i월 까지의 일수는 k

map<string, map<string, ll>> m; // {name, {p, t}}일 경우, name은 부품 p를 시간 t에 빌림
map<string, ll> ans;            // {name, k}일 경우, name의 벌금은 k

ll t_to_min(const string &s) // 시간을 분으로 바꿈
{
    stringstream ss(s);

    int h, m;
    char idx;
    ss >> h >> idx >> m;

    return h * 60 + m;
}

ll date_to_min(const string &s) // 연도와 월, 일을 분으로 바꿈
{
    stringstream ss(s);
    int y, m, d;
    char idx;
    ss >> y >> idx >> m >> idx >> d;

    return (dp[m - 1] + d) * 24 * 60;
}

int l_to_m(const string &s) // 대여 기간을 분으로 바꿈
{
    stringstream ss(s);
    int d, h, m;
    char idx;
    ss >> d >> idx >> h >> idx >> m;

    return d * 24 * 60 + h * 60 + m;
}

int main()
{
    FAST_IO;
    for (int i = 1; i <= 12; i++)
        dp[i] = DAYS[i] + dp[i - 1];

    int n, f; // 정보의 개수 n (2 ≤ n ≤ 80,000), 벌금 f(1 ≤ f ≤ 4,000)
    string l; // 대여 기간
    cin >> n >> l >> f;
    int _l = l_to_m(l);
    for (int i = 0; i < n; i++)
    {
        string date, t, p, name;
        cin >> date >> t >> p >> name;

        ll cur = date_to_min(date) + t_to_min(t);

        auto itr = m[name].find(p);
        if (itr == m[name].end()) // 해당 부품을 빌린 적이 없는 경우, 빌린 시간을 저장
            m[name][p] = cur;
        else // 해당 부품을 빌린 적이 있는 경우
        {
            ll prev = m[name][p]; // 빌린 시간
            if (cur - prev > _l)
                ans[name] += (cur - prev - _l) * f;
            m[name].erase(p); // 빌린 목록에서 제건
        }
    }

    if (ans.empty())
        cout << "-1";
    else
        for (const auto &[name, cost] : ans)
            cout << name << ' ' << cost << endl;
}