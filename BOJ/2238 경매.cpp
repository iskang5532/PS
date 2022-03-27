// 2238 경매
// https://www.acmicpc.net/problem/2238
/*
    구현, 맵 (10,296KB, 44ms)
    시간 복잡도: ?
    풀이)
    - 맵에 가격 p와 번호 i, 이름 s를 저장. (m[p][i] = s일 때, p원으로 참가한 i번째 사람의 이름은 s(i 기준 정렬))
    - i원에 제시한  사람의 수 sz. (가장 작은 금액에 투자한 사람을 찾기 위함)
    - 가장 적은 수의 사람이 제시한 가격을 저장할 price.
    - 1원부터 u원까지 탐색하며, 이전 sz보다 더 적은 수가 있는지 탐색.
    만약 더 적을 경우, sz와 price 갱신.
    etc.) 풀리는데로 풀었지만 지저분한 풀이인듯
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 10'003

int main()
{
    FAST_IO;

    int u, n; // 금액의 상한 u(1 ≤ u ≤ 10,000), 경매에 참여한 횟수 n(1 ≤ n ≤ 100,000)
    cin >> u >> n;

    map<int, string> m[MAX]; // m[p][i] = s일 때, p원으로 참가한 i번째 사람의 이름은 s(i 기준 정렬)
    for (int i = 0; i < n; i++)
    {
        string s; // 이름 s(1 ≤ s.len ≤ 10)
        int p;    // 제시한 가격 p(1 ≤ p ≤ u, 정수)
        cin >> s >> p;
        m[p][i] = s;
    }

    int sz = INF; // i원에 제시한 사람의 수
    string s;
    int price;
    for (int i = 1; i <= u; i++)
        if (m[i].size() && m[i].size() < sz)
        {
            s = m[i].begin()->second, price = i;
            sz = m[i].size();
        }

    cout << s << ' ' << price;
}

/*
    sol.2) 구현 (5,932KB, 20ms)
    시간 복잡도: ?
    참고)
    - 코드: https://blog.naver.com/jinhan814/222548351521
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 10'003

struct Info
{
    Info() : s(""), p(INF){};
    string s; // 이름 s(1 ≤ s.len ≤ 10)
    int p;    // 제시한 가격 p(1 ≤ p ≤ u, 정수)
};

int main()
{
    FAST_IO;

    int u, n; // 금액의 상한 u(1 ≤ u ≤ 10,000), 경매에 참여한 횟수 n(1 ≤ n ≤ 100,000)
    cin >> u >> n;

    vector<Info> v(n);
    int cnt[MAX]{}; // cnt[p] = k일 경우, p원에 참여한 수는 k
    for (auto &[s, p] : v)
        cin >> s >> p, cnt[p]++;

    Info ans;
    int mx = INF;
    for (const auto &[s, p] : v)
        if (cnt[p] < mx) // 개수가 더 적은 경우
        {
            ans.s = s, ans.p = p;
            mx = cnt[p];
        }
        else if (mx == cnt[p] && p < ans.p) // 개수는 같으나 가격이 더 낮은 경우
            ans.s = s, ans.p = p;

    cout << ans.s << ' ' << ans.p;
}