// 18111 마인크래프트
// https://www.acmicpc.net/problem/18111
/*
    sol.1) 완전 탐색 (3,000KB, 64ms)
    시간 복잡도: O(256nm)
    풀이)
    - 2차원 블럭을 1차원 배열로 저장.
    - 모든 블럭의 높이를 가장 낲은 높이 0에서부터 가장 높은 높이 256까지 모두 수행해보며 값을 구함.
    - 각 땅을 조사하며 블록을 파악하며, 남는 블록의 개수를 p에, 부족한 블록의 개수를 q에 저장.
    이후 p와 q를 이용해 시간을 계산. 만약 이전 시간보다 작거나 같을 시, 시간 및 높이 갱신. (같을 때도 갱신하는 이유는 최대 높이를 찾기 위함)
    etc.) 주어진 블럭의 높이로만 맞추려다가 WA.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222579884777
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX_h 256

struct pii
{
    int cnt, sum; // 땅 및 블럭의 개수
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif
    // deleted a 2s, added a 1s.

    int n, m, b; // 1 ≤ M, N ≤ 500, 0 ≤ B ≤ 64'000'000
    cin >> n >> m >> b;
    int SZ = n * m, blocks = 0;
    vector<int> arr(SZ); // 0 ≤ k ≤ 256
    for (auto &h : arr)
        cin >> h, blocks += h;

    int ans_h = 0, t = INF;
    for (int h = 0; h <= MAX_h; h++)
    {
        int p = 0, q = 0; // 남는 블록의 개수 p, 부족한 블록의 개수 q
        for (const auto &cur : arr)
            cur > h ? p += cur - h : q += h - cur;

        if (b + p - q < 0) // 블록이 부족할 시
            break;

        if (p * 2 + q * 1 <= t) // 최소 시간인 경우 ('='가 있는 이유는 시간이 같을 경우 높이를 갱신해주기 위함)
        {
            t = min(t, p * 2 + q * 1);
            ans_h = h;
        }
    }

    cout << t << ' ' << ans_h;
}

/*
    sol.2) 완전 탐색 (3,000KB, 28ms)
    시간 복잡도: O(256 * 2 + a)?
    풀이)
    - 2차원 블록을 1차원 배열로 저장한 후, 오름차순 정렬.
    이후 가장 낮은 값에서부터 가장 큰 값까지 하나씩 기준 높이로 잡음.
    - 기준 높이 h보다 낮은 값은 l에, 큰 값은 r에 저장. (항상 SZ만큼 연산을 수행하지 않고 l, r의 값을 참고하여 2회 연산 수행)
    - 현재 보유중인 블록의 개수 b, h보다 낮아 부족한 블록의 개수 p, h보다 높아서 남는 블록의 개수 q를 연산시켜 0보다 작을 경우, 현재 h를 만들 수 없음.
    - p와 q를 이용해 시간을 계산. 만약 이전 시간보다 작거나 같을 시, 시간 및 높이 갱신. (같을 때도 갱신하는 이유는 최대 높이를 찾기 위함)
    - 만약 현재 높이와 같은 블록이 존재할 경우, l에 추가. (+ r에서 빼냄)
    etc.) 첫 번째 풀이.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890

struct pii
{
    int cnt, sum; // 땅 및 블록의 개수
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif
    // deleted a 2s, added a 1s.

    int n, m, b; // 1 ≤ M, N ≤ 500, 0 ≤ B ≤ 64'000'000
    cin >> n >> m >> b;
    int SZ = n * m, blocks = 0;
    vector<int> arr(SZ); // 0 ≤ k ≤ 256
    for (auto &h : arr)
        cin >> h, blocks += h;
    sort(arr.begin(), arr.end());

    int ans_h = 0, t = INF;
    pii l = {0, 0}, r = {SZ, blocks}; // 좌측과 우측 구역
    int pos = 0;                      // h보다 높은 블록의 위치 (가장 가까운)
    for (int h = arr.front(); h <= arr.back(); h++)
    {
        int p = (l.cnt * h - l.sum); // 좌측에서의 부족한 블록 개수
        int q = r.sum - (r.cnt * h); // 우측에서의 남는 블록 개수
        if (b + q - p < 0)
            break;

        if (p * 1 + q * 2 <= t) // 최소 시간인 경우 ('='가 있는 이유는 시간이 같을 경우 높이를 갱신해주기 위함)
        {
            t = min(t, p * 1 + q * 2);
            ans_h = h;
        }

        while (pos != SZ && arr[pos] == h)
        {
            l.cnt++, l.sum += arr[pos];
            r.cnt--, r.sum -= arr[pos];
            pos++;
        }
    }

    cout << t << ' ' << ans_h;
}

// 2 1 1
// 0 5
// ans: 7 3