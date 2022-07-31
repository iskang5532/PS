// 2022-07-26
// 1092 배
// https://www.acmicpc.net/problem/1092
/*
    그리디, 정렬 (2,184KB, 56ms)
    시간 복잡도: ?
    풀이)
    - 입력된 크레인과 박스를 내림차순 정렬.
    - 각각의 크레인이 몇 개의 박스를 옮기는지를 저장할 cnt[].
    - i번 박스가 옮겨졌는지를 저장할 used[].
    - 시간마다 크레인은 하나의 박스를 옮긴다고 가정.
    현재 시간대에 박스를 옮기지 않은 크레인의 번호를 cur, 옮기지 않은 박스를 i라 할 때
    만약 크레인이 박스를 들 수 있다면, cnt[cur]++ 및 cur++(다음 크레인), used[i] = true(박스 옮겨짐)
    모든 박스를 탐색.
    - 크레인을 이용해 옮길 수 있는 박스를 모두 옮긴 후, used[]를 확인하며 옮기지 못한 박스가 있는지 확인.
    만약 모든 박스를 옮겼을 경우, 크레인이 옮긴 박스의 개수 중 가장 많이 옮긴 개수를 출력.
    만약 모든 박스를 옮기지 못하였을 경우, -1 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort, max_element

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N 53
#define MAX_M 10'003

int main()
{
    FAST_IO;

    int n; // 크레인 개수
    cin >> n;
    vector<int> crane(n); // 크레인 정보
    for (auto &i : crane)
        cin >> i;
    int m; // 박스의 개수
    cin >> m;
    vector<int> box(m); // 박스의 정보
    for (auto &i : box)
        cin >> i;

    sort(crane.begin(), crane.end(), greater<int>());
    sort(box.begin(), box.end(), greater<int>());

    int cnt[MAX_N]{};  // cnt[i] = k일 때, i번 크레인은 k개의 박스를 옮김
    int used[MAX_M]{}; // used[i] = true일 때, i번 박스는 옮겨짐
    for (int st = 0; st < m; st++)
    {
        if (used[st])
            continue;

        for (int i = st, cur = 0; i < m && cur < n; i++) // 선택된 박스 i, 선택된 크레인 cur
            if (!used[i] && crane[cur] >= box[i])
                cnt[cur++]++, used[i] = true;
    }

    bool valid = true;
    for (int i = 0; i < m; i++)
        if (!used[i]) // 옮기지 못한 박스가 있는가
            valid = false;

    cout << (valid ? *max_element(cnt, cnt + n) : -1);
}