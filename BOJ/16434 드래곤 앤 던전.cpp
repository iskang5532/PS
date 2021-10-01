/* 
 * 16434 드래곤 앤 던전
 * 구현
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/16434
 * etc.) 값의 표현 범위를 신경써야 했던 문제.
 * - 공격당한 만큼 값을 저장(= 필요한 체력). 만약 회복이 있을 경우 저장한 값에서 빼주며, 1 미만이 되지 않게 함. (1 미만은 과도한 회복)
 * - 또한, [공격 - 회복] 후 종료 시 hp와 ans의 값이 다름. (입장할 때의 값을 정해야 하기 때문에 hp의 최댓값을 구해야 함.)
 */

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