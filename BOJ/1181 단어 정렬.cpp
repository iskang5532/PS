// 1181 단어 정렬
// https://www.acmicpc.net/problem/1181
// 각 풀이 시간 복잡도 참고: https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector (적힌 것과는 다름. 문자열이라?)
/*
    sol.1) 벡터 (4,648KB, 20ms)
    시간 복잡도: O(50 * (nlogn + n)) (sort + unique + erase: O(nlogn + n))
    풀이)
    - 길이가 짧은 것부터 정렬해야 함. 또한, 최대 길이는 50을 넘지 않으므로 문자열의 길이로 분류해 저장.
    1) 문자열을 입력받으며, 길이에 맞춰 벡터에 저장.
    2) 벡터에서 길이가 1인 값부터 확인.
    3) 정렬 후, 중복값을 제거 후에 안에 들어있는 문자열을 출력.
    etc.)
    - 문자열이 인자일 떄의 erase-unique의 시간 복잡도는?
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 50 + 1

int main()
{
    FAST_IO;

    vector<string> v[MAX];

    int n; // 1 ≤ N ≤ 20,000
    cin >> n;
    while (n--)
    {
        string str;
        cin >> str;

        v[str.length()].push_back(str); // 문자열의 길이로 분류
    }

    for (auto &v : v)
    {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (const auto &str : v)
            cout << str << endl;
    }
}

/*
    sol.2) 셋  (4,932KB, 24ms)
    시간 복잡도: ?
    풀이)
    - 길이가 짧은 것부터 정렬해야 함. 또한, 최대 길이는 50을 넘지 않으므로 문자열의 길이로 분류해 저장.
    - 셋을 이용해 정렬 및 중복 문자열 제거,
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 50 + 1

int main()
{
    FAST_IO;

    set<string> s[MAX];

    int n; // 1 ≤ N ≤ 20,000
    cin >> n;
    while (n--)
    {
        string str;
        cin >> str;

        s[str.length()].insert(str);
    }

    for (auto &s : s)
        for (const auto &str : s)
            cout << str << endl;
}