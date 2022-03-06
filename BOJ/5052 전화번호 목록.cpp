// 5052 전화번호 목록
// https://www.acmicpc.net/problem/5052
/*
    sol.1) 셋 (6,076KB, 240ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 문자열로 만들 수 있는 접두어를 셋에 저장.
    문자열의 길이를 l이라 할 떄, 앞에서부터 1개, 2개, 3개, ... l개를 셋에 저장.
    - 입력받은 문자열이 셋에 존재하는지 확인.
    만약 존재할 경우, 해당 문자열은 입력받은 문자열 중에서 하나의 접두어가 된다.
    즉, 일관성이 없다.
 */

#include <iostream>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 50
    cin >> tc;
    while (tc--)
    {
        int n; // 전화번호의 수 (1 ≤ n ≤ 10,000)
        cin >> n;

        string v[MAX];
        for (int i = 0; i < n; i++)
            cin >> v[i];

        unordered_set<string> us; // 입력된 문자열로 만들 수 있는 접두어를 저장
        for (int i = 0; i < n; i++)
            for (int l = 0; l < v[i].length(); l++) // 문자열을 쪼개어 저장
                us.insert(string(v[i].begin(), v[i].begin() + l));

        bool flag = true;
        for (int i = 0; i < n && flag; i++)
            if (us.find(v[i]) != us.end()) // 해당 문자열이 접두어인 경우
                flag = false;

        cout << (flag ? "YES" : "NO") << endl;
    }
}

/*
    sol.2) 문자열, 정렬 (2,220KB, 56ms)
    시간 복잡도: ?
    풀이)
    - 2중 for문을 이용해 문자열끼리 비교할 경우 TLE.
    - string 정렬 시 문자열의 길이가 아닌 비슷한 문자열로 정렬이 된다는 점을 이용.
    {"1234", "123", "234"} 정렬 시 {"123", "234", "1234"}가 아닌 {"123", "1234", 234"}
    - i번째 문자열을 n-1까지 하나씩 사용하여 다음 문자열과 비교.
    현재 문자열 i가 다음 문자열 i+1보다 짧으면서 i가 i+1에 포함되어 있는지 확인.
    만약 포함될 경우, 일관성이 없음.
    참고)
    - 백준 채점 현황의 사람들 (당시 AC인 분의 코드)
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 10'003

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 50
    cin >> tc;
    while (tc--)
    {
        int n; // 전화번호의 수 (1 ≤ n ≤ 10,000)
        cin >> n;
        string v[MAX];
        for (int i = 0; i < n; i++)
            cin >> v[i];

        sort(v, v + n);

        bool flag = true;
        for (int i = 0; i < n - 1 && flag; i++)
        {
            string s1 = v[i], s2 = v[i + 1];
            if (s1.length() < s2.length() &&
                s1 == string(s2.begin(), s2.begin() + v[i].length()))
                flag = false;
        }

        cout << (flag ? "YES" : "NO") << endl;
    }
}