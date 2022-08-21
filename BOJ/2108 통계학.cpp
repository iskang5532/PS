// 2022-08-18
// 2108 통계학
// https://www.acmicpc.net/problem/2108
/*
    구현, 정렬 (3,884KB, 76ms)
    시간 복잡도: ?
    풀이)
    1. 산술평균
    - 입력된 n개의 수를 더한 후 n으로 나눔. 이때, 반올림을 수행해야 하므로 더한 값을 double형으로 형변환 후 나눠줘야 함.
    또한, 반올림 시 -0이 나올 수 있으므로 반올림된 값을 int형으로 변환하거나 조건문을 추가하여 0을 출력하도록 해줌.
    2. 중앙값: 입력된 n개의 값 중 중앙의 값을 출력.
    3. 최빈값
    - 입력된 값의 개수를 cnt에 저장한 후, 가장 많이 나온 값을 찾음. (최솟값인 -4,000이 음수이므로, 4,000을 더하여 음수를 없앰)
    만약, 여러개일 경우 두 번째로 작은 값을 찾음.
    - 수 i의 개수 cnt[i]를 확인하며, 만약 이전까지의 최대 개수인 mx보다 많은 경우, 최빈값 ret을 갱신.
    만약 mx == cnt[i]이면서두 번째 값일 경우, ret을 갱신하며 flag = true. (flag가 true일 경우, 이후 mx == cnt[i]여도 ret을 갱신하지 않음)
    4. 범위: 입력된 n개의 수를 정렬한 후 최댓값과 최솟값의 차이를 출력.
 */

#include <iostream>
#include <algorithm> // sort
#include <numeric>   // accumulate
#include <cmath>     // round

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
#define MAX 500'003 // max n
#define MAX_K 8'003 // max k

int get_mode(int cnt[])
{
    int ret = 0;
    int mx = 0, flag = false; // 가장 많이 나온 개수 mx, 두 번쨰 값의 여부 flag
    for (int i = 0; i < MAX_K; i++)
        if (mx < cnt[i])
            mx = cnt[i], ret = i, flag = false;
        else if (mx == cnt[i] && !flag) // 개수가 같으면서 두 번째 값일 경우
            ret = i, flag = true;

    return ret - 4000;
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX]{}, cnt[MAX_K]{}; // |v[i]| ≤ 4,000, cnt[i] = k일 경우, i는 k번 입력받음
    for (int i = 0; i < n; i++)
        cin >> v[i], cnt[4000 + v[i]]++;

    sort(v, v + n);

    cout << (int)round((double)accumulate(v, v + n, 0) / n) << endl; // 산술평균
    cout << v[n / 2] << endl;                                        // 중앙값
    cout << get_mode(cnt) << endl;                                   // 최빈값
    cout << v[n - 1] - v[0];                                         // 범위
}

// ~08-18
// 2108 통계학
// https://www.acmicpc.net/problem/2108
/*
    구현 (4,132KB, 76ms)
    시간 복잡도: ?
    풀이)
    - 입력된 값을 저장할 v와 값의 개수를 저장할 cnt.
    값이 음수일 수도 있으므로 cnt에 저장 시, +4000을 해준 값을 저장.
    - 입력이 끝난 후, v는 오름차순 정렬.
    1. 산술평균 (N개의 수의 합을 N으로 나눈 값. 단, 소수점 이하 첫째 자리에서 반올림한 값을 출력한다.)
    - v에 저장된 모든 값을 더한 후, n으로 나눠줌. 또한, 값은 반올림이 되어야 하므로 round()시켜줌.
    2. 중앙값 (N개의 수을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값)
    - v의 가운데 위치에 존재하는 값, 즉 [n/2]의 값이므로 v[n/2]값을 구해줌.
    3. 최빈값 )N개의 수 중 가장 많이 나타나는 값. 단, 여러 개 있을 때는 최빈값 중 두 번째로 작은 값을 출력한다.)
    - 까다로운 점은 최빈값이 여러 개, 즉 cnt가 가장 높으면서 같은 값이 여러 개일 때이다.
    - 입력될 수 있는 모든 값이 몇 번 입력 됐는지 확인.
    이때 cnt의 뒤에서부터 확인하는데, 이유는 값이 같을 시 저장할 값이 갱신된다. 즉, 갱신될 때마다 저장된 값은 작아짐. (구해야 하는 값은 두 번째로 작은 값)
    - 임의의 값(입력된 값 중에서)이 단 1개만 입력되었다고 가정한 후, cnt 탐색. (= cur = {1, idx})
    만약 현재 탐색 중인 수의 개수가 현재 저장된 개수(= cur.cnt)보다 크거나 같은 경우, prev와 cur 갱신. (주의할 점은, 현재 cur값 먼저 prev에 저장해줘야 함.)
    - cnt 탐색을 마쳐 cur, prev를 구했다면, 두 값의 cnt를 비교한다.
    만약 둘의 cnt가 다른 경우, cur.cnt가 더 큰 값이며 이때는 유일한 최빈값이므로 cur에 저장된 num을 출력한다.
    만약 둘의 cnt가 같은 경우, cnt가 같은 값 중 cur.num이 가장 작을 것이며, prev.num이 두 번째로 작을 것이다.
    그러므로 이때는 prev.num을 출력한다.
    4. 범위 : N개의 수 중 최댓값과 최솟값의 차이
    - 정렬된 v의 가장 앞에 존재하는 값과 뒤에 존재하는 값의 차, 즉 v[n-1] - v[0]을 구한 후 출력.
    etc.) 의외로 시간이 오래걸린 문제.
    - 처음엔 pii 벡터로 구현했음. 이때는 중앙값 구하기가 힘들었음.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <numeric>   // accumulate
#include <cmath>     // round

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX_N 500'000 + 1
#define MAX_K 4'001

struct pii
{
    int cnt, num;
};

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 500,000, n % 1 = 1
    cin >> n;

    vector<int> v(n);
    vector<int> cnt(MAX_K * 2, 0); // cnt[i] = k일 때, 수 i가 k개 존재
    for (int i = 0; i < n; i++)
        cin >> v[i], cnt[v[i] + MAX_K]++; // 0 ≤ v[i] ≤ |4,000|

    sort(v.begin(), v.end());

    pii cur = {1, v[n - 1]}, prev;
    for (int i = MAX_K * 2 - 1; i >= 0; i--)
        if (cur.cnt <= cnt[i])
            prev = cur, cur = {cnt[i], i - MAX_K};

    cout << round(accumulate(v.begin(), v.end(), double(0)) / n) << endl; // 1. 산술평균 : N개의 수들의 합을 N으로 나눈 값
    cout << v[n >> 1] << endl;                                            // 2. 중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
    prev.cnt != cur.cnt ? cout << cur.num << endl
                        : cout << prev.num << endl; // 3. 최빈값 : N개의 수들 중 가장 많이 나타나는 값
    cout << v.back() - v.front();                   // 4. 범위 : N개의 수들 중 최댓값과 최솟값의 차이
}