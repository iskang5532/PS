// 11004 K번째 수
// https://www.acmicpc.net/problem/11004
/*
    sol.1) 정렬 (21,552KB, 1,048ms)
    시간 복잡도: O(nlogn)
    풀이) 입력된 값들을 벡터에 저장한 후, 오름차순 정렬을 시킴. 이후 원하는 값을 벡터에서 꺼냄.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;
    sort(arr.begin(), arr.end());

    cout << arr[k - 1];
}

/*
    sol.2) nth_element (KB, ms)
    시간 복잡도: O(n)
    풀이) nth_element를 이용해 k번째 수를 [k-1]의 위치로 옮김. (주의할 점은, 그 외의 값들은 정렬된 것이 아님)
    참고)
    - 이론: https://blog.naver.com/jinhan814/222547222163
 */

#include <iostream>
#include <vector>
#include <algorithm> // nth_element

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

int main()
{
    FAST_IO;

    int n, k;
    cin >> n >> k;
    k--; // !

    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;

    nth_element(arr.begin(), arr.begin() + k, arr.end());
    cout << arr[k];
}