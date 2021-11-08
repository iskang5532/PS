/*
    지형 편집 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 지형 편집)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12984?language=cpp
    풀이)
    - 2차원 블록들을 1차원으로 바꿨으며, 블록들을 저장한 배열 arr를 오름차순으로 정렬.
    - 모든 칸에 대해 조사하며, 현재 조사중(= pos)인 블록의 높이(= h)과 같도록 모든 위치에서 블록들의 높이를 맞춤.
    - pos보다 작은 범위에서는 블록들의 높이가 h보다 낮을 것이며, 반대로 pos보다 큰 범위에서는 블록들의 높이가 h보다 높을 것이다.
    - 작은 범위에서 부족한 블록의 개수(= l)를, 큰 범위에서 초과한 블록의 개수(= r)를 파악한 후, 제거 비용과 추가 비용을 이용해 계산해줌.
    etc.)
    - 파라메트릭 서치로 풀려다가 실패.
    - accumulate의 반환값이 int값이며 long long 반환을 위해서는 0LL을 넣어야 한다는 점을 배움.
    참고)
    - 이론: https://ydeer.tistory.com/78
 */

#include <vector>
#include <algorithm> // sort
#include <numeric>   // accumulate
#include <limits.h>  // LLONG_MAX

using namespace std;

typedef long long ll;

ll solution(vector<vector<int>> land, int P, int Q) // P: add, Q: pop
{

    vector<int> arr;
    for (const auto &row : land)
        for (const auto &col : row)
            arr.push_back(col);
    sort(arr.begin(), arr.end());

    ll ans = LLONG_MAX;
    ll last = arr.size() - 1; // 마지막 위치
    ll prev_blocks = arr.front(), post_blocks = accumulate(arr.begin() + 1, arr.end(), 0LL); // 기준점 이전의 블록 개수, 기준점 이후의 블록 개수를 저장
    for (ll pos = 0; pos <= last; pos++)
    {
        ll h = arr[pos]; // 기준점의 높이
        ll l = 0, r = 0; // 왼쪽에서의 부족한 블록 개수 l, 오른쪽에서의 초과한 블록 개수
        if (pos)
        {
            l = ((h * pos) - prev_blocks) * P; // h기준의 전체 크기 - 현재 블록 = 부족한 블록
            prev_blocks += arr[pos];
        }
        if (pos != last)
        {
            r = (post_blocks - (h * (last - pos))) * Q; // 현재 블록 - h 기준의 전체 크기 = 초과한 블록
            post_blocks -= arr[pos + 1];
        }

        ans = min(ans, l + r);
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     //  배열의 크기 (1 ≤ N ≤ 300 )
//     //  블록의 수 (0 ≤ Ai ≤ 10^9)
//     //  추가 및 제거 (1 ≤ P, Q ≤ 100)
//     cout << "1. 5?\t" << solution({{1, 2}, {2, 3}}, 3, 2) << endl;                   // 5
//     cout << "2. 33?\t" << solution({{4, 4, 3}, {3, 2, 2}, {2, 1, 0}}, 5, 3) << endl; // 33
//     cout << "3. 6?\t" << solution({{1, 1}, {1, 3}}, 1, 5) << endl;                   // 6
//     cout << "4. 0?\t" << solution({{1}}, 1, 5) << endl;                              // 0
//     cout << "5. 60?\t" << solution({{3, 3}, {3, 1}}, 1000, 10) << endl;              // 60
//     cout << "6. 0?\t" << solution({{1000000000, 1000000000}, {1000000000, 1000000000}}, 1, 1000);
// }