// 1920 수 찾기
// https://www.acmicpc.net/problem/1920
/*
    이분 탐색 (2,292KB, 52ms)
    시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
    풀이)
    1) n개의 값을 입력받아 배열에 저장한 후, 오름차순 정렬.
    2) 입력받은 k값이 배열에 존재하는지 binary_search를 이용해 확인 및 결과를 출력.
 */

#include <iostream>
#include <algorithm> // sort, binary_search

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100'000 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ N ≤ 100,000
    cin >> n;
    int arr[MAX]; // -2^31 ≤ k < 2^31
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);

    int m; //  1 ≤ M ≤ 100,000
    cin >> m;
    while (m--)
    {
        int k; // -2^31 ≤ k < 2^31
        cin >> k;
        cout << binary_search(arr, arr + n, k) << endl;
    }
}