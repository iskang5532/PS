// 2022-08-06
// 20311 화학 실험
// https://www.acmicpc.net/problem/20311
/*
    그리디, 우선순위 큐 (10,340KB, 88ms)
    시간 복잡도: ?
    풀이)
    - 여러 색깔 중에서 시험관의 개수가 많은 두 개를 선택한 후, 출력해줌. 단, 시험관이 더 많은 색을 먼저 출력.
    만약 남은 색깔의 수가 하나일 경우
     - 시험관이 하나 남았을 경우, 시험관을 출력.
     - 시험관이 둘 이상 남았을 경우, -1 출력.
    - 현재 색깔과 이전 색깔이 같을 수 있으므로, 이전 색깔을 저장한 후 현재 색깔을 비교함.
    만약 같을 경우 -1 출력.
    - 출력할 색깔을 ans에 저장한 후 조건을 만족할 경우 저장된 값을 출력.
    etc.) 어려웠음
    참고)
    - 이론: https://blog.naver.com/dsyun96/222697847210
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n, k; // 시험관의 개수 n, 색깔의 종류 k(1 ≤ k, n ≤ 300,000)
    cin >> n >> k;
    priority_queue<pii> pq; // 남은 개수를 기준으로 정렬
    for (int i = 0, t; i < k; i++)
        cin >> t, pq.push({t, i + 1});

    vector<int> ans;
    int prev = 0, valid = true; // 이전에 나온 수 prev, 연속적으로 나온 적이 있는지를 저장할 valid
    while (pq.size() >= 2 && valid)
    {
        auto [cnt_a, i_a] = pq.top();
        pq.pop();
        auto [cnt_b, i_b] = pq.top();
        pq.pop();

        if (prev == i_a)
            valid = false;
        prev = i_b;

        if (cnt_a - 1)
            pq.push({cnt_a - 1, i_a});
        if (cnt_b - 1)
            pq.push({cnt_b - 1, i_b});
        ans.push_back(i_a);
        ans.push_back(i_b);
    }

    if (pq.size() && valid)
    {
        auto [cnt, i] = pq.top();
        pq.pop();

        if (prev == i || cnt - 1)
            valid = false;
        ans.push_back(i);
    }

    if (valid)
        for (const auto &i : ans)
            cout << i << ' ';
    else
        cout << -1;
}