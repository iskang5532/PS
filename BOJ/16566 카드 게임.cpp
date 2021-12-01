// sol.1)
/*
    16566 카드 게임
    유니온 파인드(33,276KB, 11,04ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/16566
    풀이)
    - 카드를 제출해야 할 때, 사용 여부 및 대체 카드의 값을 저장할 parent[]. (x의 부모는 x 대신 낼 카드.)
    1) 카드의 번호를 입력받은 후, 정렬시켜줌.
    2) 입력된 카드의 숫자에 맞춰 parent[x] = x를 수행해줌.
    그 외의 값중 하나를 y, y 이상의 값들 중 가장 가까운 값을 x라 했을 때 parent[y] = x로 해줌.
    3) 철수가 내는 카드를 x라고 했을 때, upper_bound를 이용해 x보다 큰 카드(= x`)를 찾아줌.
    4) find_parent(x`)을 통해 카드의 사용 여부 및 사용할 카드를 판별.
    - x`의 카드가 사용됐을 경우, x`을 초과하는 값의 카드를 출력.
    5) x`을 사용했으므로, x`의 부모와 x`+1의 부모를 합쳐줌. (x`+1인 이유는, x`을 내야 할 때, x`보다 큰 수가 x`+1이기 때문)
    etc.)
    - 첫 풀이로는 parent[x]에 arr[x+1]을 넣어 풀려 했으나 실패.
    - sol.2가 대박이므로 앞으로 비슷한 문제를 대비해 sol.2를 기억하자.
    참고)
    - 반례: https://www.acmicpc.net/board/view/74498
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 4'000'000 + 1

int parent[MAX];

int find_parent(int x, bool flag = false)
{
    if (flag)
        return parent[x] != 0 ? x : parent[x] = find_parent(x + 1, true);
    else
        return parent[x] == x || parent[x] == 0 ? x : parent[x] = find_parent(parent[x]);
}
void union_parent(int a, int b)
{
    a = find_parent(a), b = find_parent(b);
    a >= b ? parent[b] = a : parent[a] = b;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m, k; // 카드의 개수 n, 뽑은 카드 개수 m, 제출 카드 개수 k (1 ≤ m ≤ n ≤ 4M, 1 ≤ k ≤ min(m, 10,000))
    cin >> n >> m >> k;

    fill(parent, parent + MAX, 0);
    vector<int> arr(m);
    for (auto &elem : arr)
        cin >> elem, parent[elem] = elem;
    sort(arr.begin(), arr.end());

    for (auto itr = arr.begin(); itr != arr.end() - 1; ++itr)
        find_parent((*itr) + 1, true);

    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        x = *upper_bound(arr.begin(), arr.end(), x);
        x = find_parent(x);
        cout << x << endl;

        union_parent(x, find_parent(x + 1));
    }
}

// sol.2) 카드의 숫자가 아닌 arr의 위치를 이용.
/*
    유니온 파인드 (33,276KB, 736ms)
    풀이)
    - arr를 정렬시킨 후, 카드의 값이 아닌 카드의 순서를 이용. (가능한 이유는 정렬 됐기 때문)
    - upper_bound로 arr에서 x보다 큰 값의 위치를 찾아줌.
    - parent[]에 값의 위치를 저장. 만약 parent[1] == 3일 경우, 1번 카드가 사용될 상황이면 3번 카드를 낸다.
    etc.) 많이 배웠다. 이 풀이가 진짜 유니온 파인드인 느낌.
    참고)
    이론: https://blog.naver.com/jinhan814/222278374131
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 4'000'000 + 1

int parent[MAX];

int find_parent(int x) { return parent[x] == x ? x : parent[x] = find_parent(parent[x]); }
void union_parent(int a, int b)
{
    a = find_parent(a), b = find_parent(b);
    a >= b ? parent[b] = a : parent[a] = b;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m, k; // 카드의 개수 n, 뽑은 카드 개수 m, 제출 카드 개수 k (1 ≤ m ≤ n ≤ 4M, 1 ≤ k ≤ min(m, 10,000))
    cin >> n >> m >> k;

    vector<int> arr(m);
    for (auto &elem : arr)
        cin >> elem;
    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size(); i++)
        parent[i] = i;

    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;

        int pos = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
        pos = find_parent(pos);
        cout << arr[pos] << endl;

        union_parent(pos, pos + 1);
    }
}