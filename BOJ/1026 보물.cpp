// 2022-04-30
// 1026 보물
// https://www.acmicpc.net/problem/1026
/*
    정렬 (2024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - a[i]*b[i]의 값을 모두 더한 값인 sum이 최솟값이 되어야 한다.
    이는 한 배열의 가장 큰 값이 가장 적게 곱해지면 된다.
    하나의 배열은 오름차순 정렬을, 나머지 하나의 배열은 내림차순 정렬을 해준다.
    이렇게 될 시, i번째 값을 서로 곱해주게 된다면 가장 큰 값을 가장 적게 곱할 수 있다.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

int main()
{
    int n; // 1 ≤ n ≤ 50
    cin >> n;

    vector<int> v1(n), v2(n);
    for (auto &i : v1)
        cin >> i;
    for (auto &i : v2)
        cin >> i;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end(), greater<int>()); // 큰 값이 앞으로

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += v1[i] * v2[i];

    cout << sum;
}