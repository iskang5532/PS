// 2022-08-04
// 18233 러버덕을 사랑하는 모임
// https://www.acmicpc.net/problem/18233
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - n명 중에서 p명을 골라 인형을 나눠줄 수 있는지를 확인한다면, nCp가 되며 n, p ≤ 20이므로 시간 내에 수행할 수 있다.
    - 선택된 p명의 인원이 필요로 하는 최소 개수 x를 더하여 mn에, 최대 개수 y를 더하여 mx에 저장.
    만약 나눠줄 인형의 개수 e가 x와 y의 사이, 즉 x <= e <= y가 성립한다면 선택된 p명의 인원에게 인형을 선물하면 됨.
    - 선물할 개수를 정해줘야 하는데, 선물 개수가 정해진 문제가 아닌 스페셜 저지 문제이므로 번호가 빠른 인원에게 많은 인형을 선물함.
    단, 모든 인원이 인형을 1개 이상을 받아야 하므로 x개만큼 인형을 선물해야 함.
    x개만큼 선물한 이후, 남은 인형을 y개 혹은 p개를 선물.
    - 문제에서 주의할 점은, n <= p가 성립하지 않을 수도 있다. 이 경우, -1.
    etc.) 완전 탐색이 안되는줄 알고 헷갈린 문제
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n, p, e; // 전체 인원 n, 필요 인원 p(1 ≤ n, p ≤ 20), 개수 e(1 ≤ e ≤ 1,000,000)
    cin >> n >> p >> e;
    vector<pii> v(n); // 1 ≤ xi ≤ yi ≤ 1,000,000
    for (auto &[x, y] : v)
        cin >> x >> y;

    vector<bool> bit(n, false); // bit[i] = true일 경우, i번 회원에게 인형을 선물할 것
    fill(bit.begin(), bit.begin() + p, true);

    bool valid = false; // 나눠줄 수 있는가
    do
    {
        int mn = 0, mx = 0;
        for (int i = 0; i < n; i++)
            if (bit[i])
                mn += v[i].first, mx += v[i].second;

        if (mn <= e && e <= mx)
        {
            valid = true;
            break;
        }
    } while (prev_permutation(bit.begin(), bit.end()));

    if (!valid || n < p)
        cout << -1;
    else // get cnt
    {
        vector<int> cnt(n); // cnt[i] = k일 때, i번 회원에게 k개의 인형을 선물함
        for (int i = 0; i < n; i++)
            if (bit[i])
                cnt[i] = v[i].first, e -= v[i].first; // 필요 최소 개수만큼 인형을 선물

        for (int i = 0; i < n && e; i++)
            if (bit[i])
            {
                int k = min(v[i].second - cnt[i], e);
                cnt[i] += k, e -= k; // 남은 인형을 선물
            }

        for (const auto &i : cnt)
            cout << i << ' ';
    }
}

// 86%
// input:
// 2 3 3
// 1 100
// 1 100
// ans:
// -1