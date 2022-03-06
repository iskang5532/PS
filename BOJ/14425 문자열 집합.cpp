// 14425 문자열 집합
// https://www.acmicpc.net/problem/14425
/*
    sol.1) 셋 (7,944KB, 68ms)
    시간 복잡도: O(n + m)
    풀이)
    1. 셋에 문자열을 저장. (insert (O(1))
    2. 탐색할 문자열을 입력받은 후, 셋에 존재하는지 탐색. (find (O(1))

 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    unordered_set<string> us;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        us.insert(str);
    }

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;
        if (us.find(str) != us.end())
            ans++;
    }

    cout << ans;
}

/*
    sol.2) 이분 탐색 (7,944KB, 100ms)
    시간 복잡도: ?
    풀이)
    1. 입력된 문자열을 벡터에 저장한 후 오름차순 정렬. (이분 탐색을 위해)
    2. 탐색할 문자열을 입력받은 후, 이분 탐색을 이용해 벡터에 문자열이 존재하는지 확인.
    만약 존재할 경우 1, 없을 경우 0을 반환하므로 반환된 값을 ans에 저장.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n, m; // 집합의 개수 n, 탐색 문자열의 개수 m (1 ≤ N, M ≤ 10,000)
    cin >> n >> m;

    vector<string> v(n);
    for (auto &str : v)
        cin >> str;

    sort(v.begin(), v.end());

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;

        ans += binary_search(v.begin(), v.end(), str);
    }

    cout << ans;
}