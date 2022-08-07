// 2022-08-02
// 1946 신입 사원
// https://www.acmicpc.net/problem/1946
/*
    그리디 (2,920KB, 500ms)
    시간 복잡도: ?
    풀이)
    - 서류심사 성적 a, 면접 성적 b를 입력받은 후 a를 기준으로 오름차순 정렬.
    - a가 오름차순이므로, 앞선 인원에 비해 성적이 떨어짐.
    - b를 비교. 만약 b 또한 다른 인원에게 떨어질 경우, 해당 인원은 선발되지 않음.
    v[0]부터 b를 탐색하며, 앞서 나온 가장 높은 성적을 변수 mn에 저장. (가장 높은 성적이라 함은, 값이 작음)
    만약 v[i].b가 mn보다 클 경우, 즉 성적이 낮을 경우 v[i]는 탈락.
    만약 v[i].b가 mn보다 작을 경우, 즉 성적이 높을 경우 v[i]는 합격하며, mn에 v[i].b의 값을 저장.
    etc.) 일단 정렬해본 후 생각해보자는 식으로 정렬해보니 풀이가 보였음
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl '\n'
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 지원자의 수(1 ≤ n ≤ 100,000)
        cin >> n;
        vector<pii> v(n);
        for (auto &[a, b] : v)
            cin >> a >> b;

        sort(v.begin(), v.end());

        int ans = 0;
        int mn = n + 1; // i까지 b의 최솟값을 저장
        for (const auto &[a, b] : v)
            if (b < mn)
                ans++, mn = b;

        cout << ans << endl;
    }
}