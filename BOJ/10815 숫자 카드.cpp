/* 
 * 10815 숫자 카드
 * 이진 탐색 (binary search)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/10815
 * ETC) 기본적인 이진 탐색 STL을 이용한 문제인 듯.
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

    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &num : arr)
        cin >> num;
    sort(arr.begin(), arr.end()); // 이진 탐색을 위해서는 대상 배열에 대해서 정렬이 필요함
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        cout << binary_search(arr.begin(), arr.end(), num) << endl; // 값을 배열에서 이진 탐색으로 찾은 후, 있으면 true, 없으면 false를 반환
    }
}
