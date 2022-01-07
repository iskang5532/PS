// 11650 좌표 정렬하기
// https://www.acmicpc.net/problem/11650
/*
    정렬 (2,808KB, 48ms)
    시간 복잡도: O(nlogn)
    풀이)
    - 두 정수를 pair로 받은 후 정렬.
    정렬 기준은 pair의 첫 번째 값을 기준으로 오름차순 정렬을 시켜줌.
    만약 첫 번째 값이 같을 경우, 두 번째 값을 기준으로 오름차순 정렬.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
typedef pair<int, int> pii;

bool cmp(const pii &p1, const pii &p2) { return p1.first != p2.first ? p1.first < p2.first : p1.second < p2.second; }

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<pii> v(n);
    for (auto &[a, b] : v)
        cin >> a >> b;
    sort(v.begin(), v.end(), cmp);

    for (const auto &[a, b] : v)
        cout << a << " " << b << endl;
}

// 11651 좌표 정렬하기
// https://www.acmicpc.net/problem/11651
/*
    정렬 (2,808KB, 48ms)
    시간 복잡도: O(nlogn)
    풀이)
    - 두 정수를 pair로 받은 후 정렬.
    정렬 기준은 pair의 두 번째 값을 기준으로 오름차순 정렬을 시켜줌.
    만약 두 번째 값이 같을 경우, 첫 번째 값을 기준으로 오름차순 정렬.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
typedef pair<int, int> pii;

bool cmp(const pii &p1, const pii &p2) { return p1.second != p2.second ? p1.second < p2.second : p1.first < p2.first; }

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    vector<pii> v(n);
    for (auto &[a, b] : v)
        cin >> a >> b;
    sort(v.begin(), v.end(), cmp);

    for (const auto &[a, b] : v)
        cout << a << " " << b << endl;
}