// 10989 수 정렬하기 3
// https://www.acmicpc.net/problem/10989
/*
    계수 정렬 (Counting Sort) (2,020KB, 1,748ms)
    시간 복잡도: O(n + k) (k는 입력된 값의 최댓값)
    풀이)
    - 메모리 제한이 8MB. int형 값이 10'000'000개 들어올 시 제한을 넘어섬.
    즉, 입력된 값을 저장하는 것은 불가능. (이는 들어오는 값을 즉시 이용해야 함.)
    - 범위가 작으므로 counting sort 이용. (1:10000)
    1) 크기 10001의 배열을 선언한 후, 입력받은 값의 개수를 저장.
    2) 값 1부터 10000까지 개수만큼 출력.
    etc.) 이론을 알아도 막상 사용할 때가 되면 떠오르기가 어려운듯.
 */

#include <iostream>

using namespace std;

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10'000

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 10,000,000
    cin >> n;
    int cnt[MAX + 1] = {0};
    for (int i = 0; i < n; i++)
    {
        int k; // 1 ≤ k ≤ 10,000
        cin >> k;
        cnt[k]++;
    }

    for (int i = 1; i <= MAX; i++) // counting sort
        while (cnt[i])
            cout << i << '\n', cnt[i]--;
}