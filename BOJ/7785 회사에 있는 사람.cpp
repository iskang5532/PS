// 7785 회사에 있는 사람
// 문제: https://www.acmicpc.net/problem/7785
/*
    sol.1) set (9,948KB, 80ms)
    시간 복잡도: ? (insert, erase: O(logN))
    풀이)
    - 출입 기록에 따라 셋에 이름을 넣거나 빼줌.
    - 사전 순의 역순으로 출력해야 하므로, 셋을 내림차순 정렬로 선언.
 */

#include <iostream>
#include <set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 출입 기록의 수 (2 ≤ n ≤ 1M)
    cin >> n;

    set<string, greater<string>> s; // 내림차순 정렬
    // set<string> s;
    for (int i = 0; i < n; i++)
    {
        string name, cmd;
        cin >> name >> cmd;

        if (cmd.front() == 'e') // enter
            s.insert(name);
        else if (cmd.front() == 'l') // leave
            s.erase(name);
    }

    for (auto str : s)
        cout << str << endl;
    // for(auto itr = s.rbegin(); itr != s.rend(); itr++)
    //     cout << *itr << endl;
}

/*
    sol.2) 우선순위 큐 (10,348KB, 96ms)
    시간 복잡도: ?
    풀이)
    - leave를 나중으로 미룸.
    - 두 개의 우선순위 큐(in, out)을 선언. (사전 순의 역순으로 출력해야 하므로 내림차순 정렬)
    - 회사에 들어온 사람은 in에, 나간 사람은 out에 저장.
    이후 출력을 수행하는데, 출력될 사람이 out.top()과 같은 경우 출력하지 않음.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 출입 기록의 수 (2 ≤ n ≤ 1M)
    cin >> n;

    priority_queue<string> in, out; // 들어온 사람을 저장할 in, 나간 사람을 저장할 out
    for (int i = 0; i < n; i++)
    {
        string name, cmd;
        cin >> name >> cmd;

        if (cmd.front() == 'e') // enter
            in.push(name);
        else if (cmd.front() == 'l') // leave
            out.push(name);
    }

    while (in.size())
    {
        while (out.size() && in.top() == out.top()) // 현재 출력될 사람이 나간 사람인 경우
            in.pop(), out.pop();
        if (in.size())
            cout << in.top() << endl, in.pop();
    }
}

/*
    sol.3) vector (5,156KB, 44ms)
    시간 복잡도: ?
    풀이)
    - 들어온 사람 및 나간 사람 모두 동일한 벡터에 저장.
    - 입력이 끝난 벡터는 내림차순 정렬. (사전 순의 역순으로 출력해야 하므로)
    - 출력 시, 만약 현재 출력할 사람이 다음 사람과 같은 경우 출력하지 않음.
    이는 벡터에 존재하는 이름이 하나뿐이라면, 들어온 기록은 있지만 나간 기록이 없다는 뜻.
    또한 만약 들어온 기록과 나간 기록이 서로 떨어져 있더라도 정렬로 인해 서로 붙게 됨.
    그러므로 i번째 기록과 i+1번째 기록을 비교해 만약 같을 경우, 현재 사람은 나간 것이므로 출력하지 않음.
    etc.) 어려운 문제라면 이러한 풀이로 풀게 할듯.
    참고)
    이론: https://blog.naver.com/jinhan814/222088698130
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 출입 기록의 수 (2 ≤ n ≤ 1M)
    cin >> n;

    vector<string> arr(n);
    for (int i = 0; i < n; i++)
    {
        string name, idx;
        cin >> name >> idx;

        arr[i] = name;
    }

    sort(arr.begin(), arr.end(), greater<string>()); // 내림차순 정렬
    for (int i = 0; i < n; i++)
        if (i != n - 1 && arr[i] == arr[i + 1]) // 이름이 같은 경우
            i++;
        else
            cout << arr[i] << endl;
}