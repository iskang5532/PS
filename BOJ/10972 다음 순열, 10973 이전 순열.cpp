/*
    10972 다음 순열, 10973 이전 순열
    구현, 조합 (2,180KB, 0ms)
    시간 복잡도: ?
    문제: https://boj.kr/10972 https://boj.kr/10973
    참고)
    - 이론: https://jins-dev.tistory.com/entry/%EB%8B%A4%EC%9D%8C-%EC%88%9C%EC%97%B4-%EC%B0%BE%EA%B8%B0-%EC%A0%84%EC%B2%B4-%EC%88%9C%EC%97%B4-%ED%83%90%EC%83%89-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Next-Permutation
 */

#include <iostream>
#include <vector>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

bool __next_permutation(vector<int> &arr)
{
    int n = arr.size();

    int pos = -1;
    for (int i = n - 1; i >= 1; i++) // 뒤에서부터 확인하여 시간을 줄임
        if (arr[i - 1] < arr[i])
        {
            pos = i - 1;
            break;
        }

    if (pos == -1) // 다음 순열이 존재하지 않는 경우
        return false;

    for (int i = n - 1; i > pos; i--)
        if (arr[pos] < arr[i])
        {
            swap(arr[pos], arr[i]);
            reverse(arr.begin() + pos + 1, arr.end());
            return true;
        }

    return false;
}
bool __prev_permutation(vector<int> &arr)
{
    int n = arr.size();

    int pos = -1;
    for (int i = n - 1; i >= 1; i--)
        if (arr[i - 1] > arr[i])
        {
            pos = i - 1;
            break;
        }

    if (pos == -1)
        return false;

    for (int i = n - 1; i > pos; i--)
        if (arr[pos] > arr[i])
        {
            swap(arr[pos], arr[i]);
            reverse(arr.begin() + pos + 1, arr.end());
            return true;
        }

    return false;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ N ≤ 10,000
    cin >> n;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;

    if (__next_permutation(arr)) // or __prev_permutation() | 다음 순열이 존재하는 경우
        for (const auto &elem : arr)
            cout << elem << " ";
    else
        cout << -1;
}

// 앞에서부터 탐색. (직관적이라 좋음)
// for (int i = 0; i < n - 1; i++)
//     if (arr[i] < arr[i + 1])
//         pos = i;