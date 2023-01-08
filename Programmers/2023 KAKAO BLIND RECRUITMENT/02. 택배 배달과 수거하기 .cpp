// 2023-01-07
// 택배 배달과 수거하기 (코딩테스트 연습 > 2023 KAKAO BLIND RECRUITMENT > 택배 배달과 수거하기)
// https://school.programmers.co.kr/learn/courses/30/lessons/150369
/*
    구현, 그리디
    시간 복잡도: ?
    풀이)
    - 최단 거리를 위해 방문한 집을 구할 get_pos(). (배달 혹은 수거)
    - get_pos()를 이용하여 배달 혹은 수거에 대한 값을 구하여 v1, v2에 저장.
    - v1과 v2에 저장된 값을 이용.
    v1과 v2 각각 가장 먼 집의 위치를 a와 b에 저장.
    이후, a와 b를 비교하여, 더 먼 집의 거리를 사용.
    만약 a가 멀 경우 a에 배달 후 돌아가며 b를 수거하며 b가 멀 경우 a에 배달 후 b로 이동 후 b를 수거한다.
    - 배달 혹은 수거가 완료되어 a 혹은 b가 0이 될 수 있음.
    etc.)
    참고)
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> get_pos(vector<int> &v, int cap) // 최단 거리를 위해 방문한 집을 구함
{
    vector<ll> ret;

    int pos = v.size() - 1;
    int sz = cap, prev = -1; // 집을 수 있는 택배의 개수 sz, 가장 거리가 먼 방문한 집의 거리 prev
    while (pos >= 0)
    {
        if (v[pos] == 0) // 더 이상 없을 경우 (= 방문할 필요가 없음)
        {
            pos--;
            continue;
        }
        if (prev == -1) // 첫 출발 (= 첫 배달 혹은 첫 수거한 집의 위치를 저장)
            prev = pos;

        int cur = min(sz, v[pos]); // 해당 집에서의 택배의 개수
        sz -= cur, v[pos] -= cur;
        if (sz == 0) // 모두 배달했거나 싣은 경우
            ret.push_back(prev + 1), sz = cap, prev = -1;
    }
    if (prev != -1) // 마지막 수행에서 싣었던, 혹은 배달한 집의 위치
        ret.push_back(prev + 1);

    return ret;
}

ll solution(int cap, int n, vector<int> deliveries, vector<int> pickups)
{
    ll ans = 0;

    vector<ll> v1 = get_pos(deliveries, cap),
               v2 = get_pos(pickups, cap);

    int l = 0, r = 0;
    while (l < v1.size() || r < v2.size())
    {
        int a = (l < v1.size() ? v1[l] : 0);
        int b = (r < v2.size() ? v2[r] : 0);

        ans += max(a, b) * 2; // 왕복이므로 *2

        l++, r++;
    }
    return ans;
}

int main()
{
    cout << solution(4, 5,
                     {1, 0, 3, 1, 2},
                     {0, 3, 0, 4, 0});
}