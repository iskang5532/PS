/* 
 * 2632 피자판매
 * 이분 탐색
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2632
 * ETC.) [2143 두 배열의 합]과 비슷한 문제.
 * 추가적인 조건으로 부분 배열이 (... + a[n - 1] + a[n])뿐만 아니라 (... + a[n - 1] + a[n] + a[0] + ...)와 같이 반대편으로 돌아와 값을 이용할 수 있다.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int sum = 0; // 배열의 합을 저장할 변수
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int S; // <= 2M
    cin >> S;
    int n, m; // 3 <= 1k
    cin >> n >> m;

    vector<int> a(n), sum_a; // 값을 저장할 a와 a의 부 배열을 저장할 sum_a
    for (auto &elem : a)
        cin >> elem;                           // <= 1k
    a.insert(a.end(), a.begin(), a.end() - 1); // 마지막을 제외한 값을 추가함(= a의 처음과 끝을 이어줌. a1, a2, a3, a1, a2)
    sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i], sum_a.push_back(sum); // 부분 배열 저장
    for (int left = 1; left < n; left++)   // 두 번째 값부터 (첫 번째 값은 위에서)
    {
        sum = 0;
        for (int j = left; j < n + left - 1; j++) //  값들을 이용한 합을 저장. 이 때, 값을 한 개 제외. (n번째 값을 제외하지 않을 경우, 동일 값(전체 값의 합)이 들어감)
            sum += a[j], sum_a.push_back(sum);    // = [a2, a2 + a3, a3, a3 + a1], [a3, a3 + a1, ...], ...
    }

    vector<int> b(m), sum_b;
    for (auto &elem : b)
        cin >> elem; // <= 1k
    b.insert(b.end(), b.begin(), b.end() - 1);
    sum = 0;
    for (int i = 0; i < m; i++)
        sum += b[i], sum_b.push_back(sum);
    for (int left = 1; left < m; left++)
    {
        sum = 0;
        for (int j = left; j < m + left - 1; j++)
            sum += b[j], sum_b.push_back(sum);
    }

    sort(sum_a.begin(), sum_a.end());
    sort(sum_b.begin(), sum_b.end());

    int answer = 0;
    answer += upper_bound(sum_a.begin(), sum_a.end(), S) - // 각 부분 배열에서 S의 개수를 찾음
              lower_bound(sum_a.begin(), sum_a.end(), S);
    answer += upper_bound(sum_b.begin(), sum_b.end(), S) -
              lower_bound(sum_b.begin(), sum_b.end(), S);
    for (const auto &elem : sum_a)
    {
        auto [lo, hi] = equal_range(sum_b.begin(), sum_b.end(), S - elem); // a의 부분 배열을 기준으로 b의 부분 배열을 이용해 S를 만들 수 있는 값의 개수를 찾음
        answer += hi - lo;
        // 위 코드와 같음
        // answer += upper_bound(sum_b.begin(), sum_b.end(), S - elem) -
        //           lower_bound(sum_b.begin(), sum_b.end(), S - elem);
    }

    cout << answer;
}