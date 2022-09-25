// 2022-05-07
// 두 큐 합 같게 만들기 (코딩테스트 연습 > 2022 KAKAO TECH INTERNSHIP > 두 큐 합 같게 만들기)
// https://school.programmers.co.kr/learn/courses/30/lessons/118667
/*
    큐
    시간 복잡도: ?
    풀이)
    - 두 배열의 합을 비교 후, 더 큰 배열의 가장 작은 원소를 다른 배열로 옮김.
    이후, 두 배열의 합이 같아질 때까지 반복.
    - 입력된 두 벡터 v1, v2를 큐 q1, q2에 저장.
    - q1에 저장된 원소의 합을 l, q2에 저장된 원소의 합을 r.
    만약 l == r일 경우, 두 배열의 합은 같으므로 0을 출력.
    만약 l != r일 경우, l과 r의 대소를 확인.
     - 원소의 이동 횟수를 저장할 cnt.
     만약 l > r일 경우, q1의 원소를 q2에 넣음. (이와 동시에 넣은 원소를 r에 추가, l에서 제거)
     만약 r > l일 경우, q2의 원소를 q1에 넣음. (이와 동시에 넣은 원소를 l에 추가, r에서 제거)
     원소의 이동이 끝난 후, l과 r을 비교. 만약 같을 경우, cnt 출력.
    참고)
    - 해설: https://tech.kakao.com/2022/07/13/2022-coding-test-summer-internship/
 */

#include <bits/stdc++.h>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;

int solution(vector<int> v1, vector<int> v2) // (1 < v.len ≤ 300,000, 1 < v[i] ≤ 10^9)
{
    queue<int> q1, q2; // v1의 값을 q1에, v2의 값을 q2에 저장
    ll l = 0, r = 0;   // v1 원소의 합을 저장할 l, v2 원소의 합을 저장할 r
    for (const auto &i : v1)
        l += i, q1.push(i);
    for (const auto &i : v2)
        r += i, q2.push(i);

    if (l == r)
        return 0;

    for (int cnt = 1; cnt < 1'111'111; cnt++) // 238297
    {
        if (l > r) // q1의 원소를 꺼내 p2에 넣음
        {
            int k = q1.front();
            q2.push(k), r += k;
            q1.pop(), l -= k;
        }
        else if (l < r) // p2의 원소를 꺼내 p1에 넣음
        {
            int k = q2.front();
            q1.push(k), l += k;
            q2.pop(), r -= k;
        }

        if (l == r)
            return cnt;
    }

    return -1;
}