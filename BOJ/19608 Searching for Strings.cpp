// 2022-12-08
// 19608 Searching for Strings
// https://www.acmicpc.net/problem/19608
/*
    라빈 카프 (39,452KB, 164ms)
    시간 복잡도: O(26nlogn) (맵 nlogn, 알파벳 26)
    풀이)
    - h에서 n의 길이만큼의 문자열이 n의 수열 중 하나인지를 확인하는 방법은, 문자의 개수가 서로 동일한지 확인하면 된다. (문자의 개수는 배열에 저장)
    주의할 점은, 중복은 허용하지 않는다는 점이다. 즉, 수열 중 하나를 발견하여 카운팅했을 경우, 이후에 나온 같은 수열은 카운팅하지 않는다.
    - 중복을 제거하기 위해 맵을 이용한다.
    이때, 맵에 {문자열, 배열} 형태로 저장하게 될 경우 MLE. (TLE도 포함일 것으로 생각됨)
    이를 위해 라빈 카프를 이용하여 문자열을 long long 형태의 해시 값으로 변환하여 저장한다.
    - cnt[]에 문자열 n의 문자의 개수를 저장한다.
    이후, 맵에 저장된 배열을 가져와 cnt와 비교한다.
    만약 모두 동일한 경우, ans++.
    참고)
    - 라빈 카프 이론: https://yjg-lab.tistory.com/218
    - 라빈 카프 이론 및 코드: https://blog.naver.com/p_ce1052/222569288095
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pii = pair<int, int>;

string n, h; // 탐색 문자열 n, 대상 문자열 h (1 ≤ n.len, h.len ≤ 200,000)

map<ll, vector<int>> get_map(const vector<ll> &v1, const vector<ll> &v2)
{
    map<ll, vector<int>> m;

    vector<int> cnt(26, 0); // 알파벳의 개수를 저장 (h에서 n의 길이만큼의 문자열)
    for (int i = 0; i < n.length(); i++)
        cnt[h[i] - 'a']++;
    m[v1[n.length() - 1] << 32 | v2[n.length() - 1]] = cnt;

    for (int l = 0, r = n.length(); r < h.length(); l++, r++) 
    {
        cnt[h[l] - 'a']--, cnt[h[r] - 'a']++;

        m[v1[r] << 32 | v2[r]] = cnt;
    }

    return m;
}

vector<ll> get_hash(const pii &info) // 라빈 카프
{
    int mod = info.first, c = info.second;

    vector<ll> ret(h.length()); // n의 길이만큼의 해시를 저장

    ll sum = 0, k = 1;
    for (int i = n.length() - 1; i >= 0; --i)
    {
        sum += (h[i] - 'a' + 1) * k, sum %= mod;
        (i != 0 ? k *= c : '\0'), k %= mod;
    }
    ret[n.length() - 1] = sum;

    for (int l = 0, r = n.length(); r < h.length(); l++, r++)
    {
        sum -= (h[l] - 'a' + 1) * k;
        sum *= c, sum %= mod;
        sum += h[r] - 'a' + 1, sum %= mod;

        if (sum < 0) // 음수가 됐을 경우 (나머지 연산으로 작아진 sum에서 값을 제거하게 될 경우, 음수가 됨)
            sum += mod;
        ret[r] = sum;
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> h;

    constexpr pii p1 = {1e9 + 7, 3}, p2 = {1e9 + 9, 5};
    vector<ll> v1 = get_hash(p1), v2 = get_hash(p2);

    map<ll, vector<int>> m = get_map(v1, v2); // {해시, 배열(알파벳 개수)}

    vector<int> cnt(26, 0); // 문자열 n의 알파벳 개수를 저장
    for (const char &c : n)
        cnt[c - 'a']++;

    int ans = 0;
    for (const auto &[temp, v] : m)
    {
        bool valid = true;
        for (int i = 0; i < 26 && valid; i++) // 알파벳 개수를 비교
            if (v[i] != cnt[i])
                valid = false;
        ans += valid;
    }

    cout << ans;
}