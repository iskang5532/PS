// 7662 이중 우선순위 큐
// 문제: https://www.acmicpc.net/problem/7662
/*
    sol.1) multiset (48,884KB, 740ms)
    시간 복잡도: ? (입력 및 삭제: O(logN))
    풀이)
    - 멀티셋에 값을 저장한 후, 삭제 명령에 맞춰 값을 제거.
    최댓값을 제거할 떄 셋의 마지막 iterator에 접근해야 하는데, end() - 1이 불가능하므로 --end를 이용해 접근.
    - 중복된 값이 들어올 수 있으므로 멀티셋을 이용. (추가로, 중복된 값이 모두 삭제되지 않도록 주의)
    etc.)
    - 궁금점: rbegin()은 왜 erase()가 안되는걸까
    참고)
    - iterator: https://blog.naver.com/jinhan814/222078822637
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

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; //  연산의 개수 (n ≤ 1,000,000)
        cin >> n;

        multiset<int> ms;
        for (int i = 0; i < n; i++)
        {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'I')
                ms.insert(k);
            else if (c == 'D' && ms.size())
                if (k == 1) // 최댓값 제거
                    ms.erase(--ms.end());
                else if (k == -1) // 최솟값 제거
                    ms.erase(ms.begin());
        }

        if (ms.empty())
            cout << "EMPTY" << endl;
        else
            cout << *(ms.rbegin()) << " " << *ms.begin() << endl;
    }
}

/*
    sol.2) map (48,884KB, 740ms)
    시간 복잡도: ?
    풀이)
    - 맵에 입력된 값과 개수를 저장. (m[4] = 2일 경우, 4의 개수는 2개)
    - 값을 제거 시, 맵에 존재하는 최댓값 혹은 최솟값의 key를 가져와 key의 value--.
    만약 value가 0 이하가 된 경우, 맵에서 제거.
    - 값을 제거 시 해당 값이 존재하지 않을 수 있으므로 예외 처리에 주의.
 */

#include <iostream>
#include <map>

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

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; //  연산의 개수 (n ≤ 1,000,000)
        cin >> n;

        map<int, int> m;
        for (int i = 0; i < n; i++)
        {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'I')
                m[k]++;
            else if (c == 'D' && m.size())
                if (k == 1) // 최댓값 제거
                {
                    auto key = m.rbegin()->first;
                    m[key]--;
                    if (m[key] <= 0)
                        m.erase(key);
                }
                else if (k == -1) // 최솟값 제거
                {
                    auto key = m.begin()->first;
                    m[key]--;
                    if (m[key] <= 0)
                        m.erase(key);
                }
        }

        if (m.empty())
            cout << "EMPTY" << endl;
        else // print key
            cout << m.rbegin()->first << " " << m.begin()->first << endl;
    }
}

/*
    sol.3) 우선순위 큐 (16,312KB, 756ms)
    시간 복잡도: ?
    풀이)
    - 오름차순 정렬 및 내림차순 정렬이 되어 있는 우선순위 큐를 2개 선언하여 값을 저장.
    - 최댓값 혹은 최솟값 제거 시
     하나의 큐에서는 값을 즉시 제거(= top)하며, 나머지 큐에서는 제거할 값을 저장함. (대기)
     값을 저장 시, 큐에 제거된 값을 저장해야 함. (즉, 저장-제거 순)
    etc.) pop()을 최소한으로 사용시켜 최적화가 가능할 듯 싶은데 잘 안보인다..
    - pop() 명령 또한 해당 큐의 top()을 drop에 넣지 않고 즉시 제거시키는게 더 좋아보이는데, 구현이 떠오르지 않음.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

struct _less // 내림차순
{
    bool operator()(const int a, const int b) { return a < b; }
};
struct _greater // 오름차순
{
    bool operator()(const int a, const int b) { return a > b; }
};

template <typename Func = _less>
struct pq_set
{
    priority_queue<int, vector<int>, Func> in, out;

    void push(int k) { in.push(k); }
    void drop(int k) { out.push(k); }
    void pop()
    {
        while (out.size() && out.top() == in.top())
            in.pop(), out.pop();
    }
    int top()
    {
        pop();
        return in.top();
    }
    bool empty()
    {
        pop();
        return in.empty();
    }
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; //  연산의 개수 (n ≤ 1,000,000)
        cin >> n;

        pq_set mx;
        pq_set<_greater> mn;
        for (int i = 0; i < n; i++)
        {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'I')
                mx.push(k), mn.push(k);
            else if (c == 'D')
                if (k == 1)
                {
                    if (!mx.empty())
                    {
                        int temp = mx.top();
                        mn.drop(temp), mx.drop(temp);
                    }
                    mx.pop();
                }
                else if (k == -1)
                {
                    if (!mn.empty())
                    {
                        int temp = mn.top();
                        mx.drop(temp), mn.drop(temp);
                    }
                    mn.pop();
                }
        }

        if (mx.empty())
            cout << "EMPTY" << endl;
        else
            cout << mx.top() << " " << mn.top() << endl;
    }
}

// 3%
// 1
// 3
// I 100
// I 100
// D 1
// ans: 100 100