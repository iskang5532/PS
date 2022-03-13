/*
    쿠키 구입 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 쿠키 구입)
    시간 복잡도: O(N^2)?
    문제: https://programmers.co.kr/learn/courses/30/lessons/49995
    풀이)
    - 쿠키의 입력은 정렬되어 있음.
    - 기준점에서부터 왼쪽과 오른쪽으로 구역을 나눠 품 (왼쪽의 구역은 오른쪽의 구역보다 값이 낮다는 점을 이용)
    - 기준점에서부터 하나씩 왼쪽 값(= itr_l)과 오른쪽 값(= itr_r)을 읽어 값을 누적.
    만약 누적된 왼쪽 값(= l)과 오른쪽 값(= r)이 같은 경우, ans 갱신.
    - 1부터 2,000까지 모든 기준점을 살펴보며, 두 과자를 비교해야 하므로 itr_r은 기준점에서, itr_l은 기준점의 왼쪽에서부터 시작.
    etc.) 생각보다 빠르게 풀려서 좋았음.
 */

#include <vector>

using namespace std;

int solution(vector<int> cookie)
{
    int ans = 0;
    int len = cookie.size();
    for (int i = 1; i < len; i++) // 왼쪽 값이 0부터 시작될 수 있도록 기준점은 1부터
    {
        auto itr_l = cookie.rbegin() + (len - i);
        auto itr_r = cookie.begin() + i;

        int l = *itr_l, r = *itr_r; // 누적값
        if (l == r)
            ans = max(ans, l);
        while (itr_l != cookie.rend() && itr_r != cookie.end())
        {
            if (l == r)
                ans = max(ans, l);

            if (l <= r) // l값이 작을 시 l 범위를 늘려주며 l값을 추가 (값이 같은 경우 무한루프가 돌 수 있으므로 추가)
                itr_l++, l += *itr_l;
            else if (l > r) // r값이 작을 시 r 범위를 늘려주며 r값을 추가
                itr_r++, r += *itr_r;
        }
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution({1, 1, 2, 3}) << endl; // 3
//     cout << solution({1, 2, 4, 5}) << endl; // 0
// }