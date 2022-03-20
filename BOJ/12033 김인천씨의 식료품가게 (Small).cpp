// 12033 김인천씨의 식료품가게 (Small)
// https://www.acmicpc.net/problem/12033
/*
    sol.1) 구현, 완전탐색 (2,028KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력된 n*2개의 수 중 n개를 사용하여 나머지 n개의 수를 만들 수 있는지를 확인.
    - 선택된 n개의 수는 만들어진 수에 속하며, 할인된 가격이다.
    - 선택되지 않은 n개의 수는 사용할 수이며, 할인이 되지 않은 가격이다.
    - 할인된 가격의 값과 할인되지 않은 가격으로 만든 값을 맵에 저장.
    이떄, 할인된 가격은 -1, 할인되지 않은 가격으로 만든 값은 +1을 해준다.
    - 맵의 값을 확인.
    만약 음수의 값이 존재한다면 제대로된 값을 선택한 것이 아니다. (할인된 값을 만들 수가 없음)
    그러므로, 선택된 수가 아닌 다른 조합의 수를 사용한다.
    만약 음수의 값이 존재하지 않을 경우(= 모두 0), 할인된 값들을 출력.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
#define MAX 11
#define mul 0.75

void solution(int tc)
{
    int n;
    cin >> n;
    n *= 2;

    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<bool> bit(n, false); // bit[i] = true일 경우, i번째 값은 할인된 값으로 사용
    fill(bit.begin(), bit.begin() + (n >> 1), true);
    do
    {
        unordered_map<int, int> um;
        bool valid = true; // 선택된 값들은 유효한가?

        for (int i = 0; i < n; i++)
            if (bit[i])
                um[v[i]]--;
            else
                um[v[i] * mul]++;

        for (const auto &[idx, k] : um)
            if (k < 0)
                valid = false;

        if (valid)
        {
            cout << "Case #" << tc << ':';
            for (int i = 0; i < n; i++)
                if (bit[i])
                    cout << ' ' << v[i];
            cout << endl;
            return;
        }
    } while (prev_permutation(bit.begin(), bit.end()));
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    for (int cnt = 0; cnt < tc; cnt++)
        solution(cnt + 1);
}

/*
    sol.2) 구현 (2,024KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 입력이 오름차순임을 이용.
    - 첫 번째 값은 할인된 가격.
    이후 들어오는 값은 앞서 입력된 값의 할인을 제외한 값이 아닐 경우 출력.
    또한, 할인된 값은 3으로 나눠지는 값이므로 계산 시 /3 이후 *4를 해줌.
 */

#include <iostream>
#include <unordered_map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'

void solution(int tc)
{
    int n;
    cin >> n;
    n *= 2;

    cout << "Case #" << tc << ':';
    unordered_map<int, int> um;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        if (um[k] == 0)
            um[k / 3 * 4]++, cout << ' ' << k; // 할인을 제외한 원래 가격을 추가
        else
            um[k]--;
    }
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    for (int cnt = 0; cnt < tc; cnt++, cout << endl)
        solution(cnt + 1);
}