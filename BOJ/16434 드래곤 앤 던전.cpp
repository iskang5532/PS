/* 
 * 16434 드래곤 앤 던전
 * 구현, 파라메트릭 서치
 * 문제: https://www.acmicpc.net/problem/16434
 * etc.) 값의 표현 범위를 신경써야 했던 문제.
 */

// sol.1) 구현 (36ms)
// - 공격당한 만큼 값을 저장(= 필요한 체력). 만약 회복이 있을 경우 저장한 값에서 빼주며, 1 미만이 되지 않게 함. (1 미만은 과도한 회복)
// - 또한, [공격 - 회복] 후 종료 시 hp와 ans의 값이 다름. (입장할 때의 값을 정해야 하기 때문에 hp의 최댓값을 구해야 함.)
#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    ll hp = 1, ans = 1; // 임시적인 체력 및 필요 최소 체력 (default: 1)
    ll n, atk;          // 방의 개수 (1 ≤ n ≤ 123,456), 초기 공격력 atk (1 ≤ atk ≤ 1M)
    cin >> n >> atk;
    while (n--)
    {
        ll t, a, h; // 방의 정보 t ∈ {1, 2}, 공격력 및 체력 (1 ≤ a, h ≤ 1M)
        cin >> t >> a >> h;

        if (t == 1)
        {
            if (h % atk == 0) // 공격이 체력에 딱 맞게 떨어져서 한 대 덜맞는 경우
                h -= atk;
            hp += a * (h / atk);
            ans = max(ans, hp);
        }
        else if (t == 2)
        {
            atk += a, hp -= h;
            if (hp < 1) // 1 미만은 될 수 없기 때문에 1로 고정
                hp = 1;
        }
    }

    cout << ans;
}

// sol.2) 파라메트릭 서치 (196ms)
// 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
// - 결정 문제로 바꾸어 풀었음.
// - 던전을 클리어할 수 있는 '최소' 체력을 구해야 함.
#include <iostream>
#include <vector>
#include <limits.h> // LLONG_MAX

using namespace std;

#define endl "\n"
typedef long long ll;

struct P
{
    int t, a, h; // 방의 정보 t ∈ {1, 2}, 공격력 및 체력 (1 ≤ a, h ≤ 1M)
};

ll solution(const vector<P> &arr, const int _atk)
{
    ll l = 1, r = LLONG_MAX - 1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        ll hp = mid, atk = _atk; // 값이 수정되기 때문에 따로 선언

        for (auto [t, a, h] : arr)
        {
            if (t == 1)
            {
                if (h % atk == 0) // 공격이 체력에 딱 맞게 떨어져서 한 대 덜맞는 경우
                    h -= atk;
                hp -= a * (h / atk);
            }
            else if (t == 2)
            {
                atk += a, hp += h;
                if (hp > mid)
                    hp = mid;
            }

            if (hp <= 0) // 체력이 다 닳은 경우
                break;
        }

        if (hp < 1) // 현재 기준값(= mid)이 부족한 경우
            l = mid + 1;
        else // hp >= 1
            r = mid - 1;
    }

    return l;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    ll n, atk; // 방의 개수 (1 ≤ n ≤ 123,456), 초기 공격력 atk (1 ≤ atk ≤ 1M)
    cin >> n >> atk;

    vector<P> arr(n); // 입력된 값을 저장할 공간
    for (auto &[t, a, h] : arr)
        cin >> t >> a >> h;

    cout << solution(arr, atk);
}

// 후 회복 (회복 후 몬스터를 만나지 않음)
// ans: 20
// 2
// 1
// 1 1 20
// 2 3 10

// 선 회복 (최대 hp를 넘지 못함)
// ans: 21
// 3 1
// 2 9 10
// 2 10 10
// 1 20 40