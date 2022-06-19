// 2022-06-19
// 10866 덱
// https://www.acmicpc.net/problem/10866
/*
    덱 (2,028KB, 4ms)
    시간 복잡도: ?
 */

#include <iostream>
#include <deque>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

deque<int> dq;

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    while (n--)
    {
        string cmd;
        cin >> cmd;
        int x;

        if (cmd == "push_front")
        {
            cin >> x;
            dq.push_front(x);
        }
        else if (cmd == "push_back")
        {
            cin >> x;
            dq.push_back(x);
        }
        else if (cmd == "pop_front")
            if (dq.size())
            {
                cout << dq.front() << endl;
                dq.pop_front();
            }
            else
                cout << -1 << endl;
        else if (cmd == "pop_back")
            if (dq.size())
            {
                cout << dq.back() << endl;
                dq.pop_back();
            }
            else
                cout << -1 << endl;
        else if (cmd == "size")
            cout << dq.size() << endl;
        else if (cmd == "empty")
            cout << (dq.empty()) << endl;
        else if (cmd == "front")
            cout << (dq.size() ? dq.front() : -1) << endl;
        else if (cmd == "back")
            cout << (dq.size() ? dq.back() : -1) << endl;
    }
}