/* 
 * 2143 두 배열의 합
 * 이분 탐색
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2143
 * ETC.) 문제를 제대로 확인 못해서 오래 걸림. (풀이의 시간 복잡도가 (2^n - 1)*2인줄)
 * 참고: https://blog.naver.com/jinhan814/222121948810 (equal_range)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t; // -1G <= 1G
    cin >> t;

    int n; // 1 <= 1k
    cin >> n;
    vector<int> arr_a(n), sum_x; // 배열 및 부 배열을 저장할 벡터
    for (auto &elem : arr_a)
        cin >> elem; // -1M <= 1M
    for (int i = 0; i < n; i++)
    {
        int sum = 0; // 시작점 i부터 n까지의 합(= 부 배열)을 구할 때 사용할 변수
        for (int j = i; j < n; j++)
            sum += arr_a[j], sum_x.push_back(sum); // 부 배열을 구한 후 넣어 줌
    }

    int m; // 1 <= 1k
    cin >> m;
    vector<int> arr_b(m), sum_y;
    for (auto &elem : arr_b)
        cin >> elem; // -1M <= 1M
    for (int i = 0; i < m; i++)
    {
        int sum = 0;
        for (int j = i; j < m; j++)
            sum += arr_b[j], sum_y.push_back(sum);
    }

    sort(sum_y.begin(), sum_y.end()); // 탐색을 위해 정렬
    long long answer = 0;
    for (const auto &elem : sum_x)
    {
        auto [lo, hi] = equal_range(sum_y.begin(), sum_y.end(), t - elem); // t-elem이 배열(sum_y)에서 찾아야 하는 값
        answer += hi - lo;
    }
    cout << answer;
}