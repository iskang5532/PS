// 18870 좌표 압축
// https://www.acmicpc.net/problem/18870
/*
    18870 좌표 압축 (9,840KB, 460ms)
    시간 복잡도: O(2nlogn + n) (sort + unique + erase: nlogn + n, binary search: nlogn)
    풀이)
    - 현재 값 i가 정렬된 상태의 벡터에서 몇 번째 위치인지를 탐색함.
    1) 벡터 v를 선언한 후, 입력된 값을 저장.
    이후 벡터 idx를 하나 더 만들어 v를 복사.
    2) idx를 오름차순 정렬 및 중복 원소를 제거.
    3) v의 첫 번째 원소(= i)부터 탐색.
    lower_bound를 이용하여 idx에서 i가 몇 번째에 위치하는지 탐색.
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222551512915
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort, unique

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 1 ≤ N ≤ 1,000,000
    cin >> n;
    vector<int> v(n); // -10^9 ≤ vi ≤ 10^9
    for (auto &elem : v)
        cin >> elem;

    vector<int> idx = v;
    sort(idx.begin(), idx.end());
    idx.erase(unique(idx.begin(), idx.end()), idx.end());

    for (const auto &elem : v)
        cout << lower_bound(idx.begin(), idx.end(), elem) - idx.begin() << ' ';
}