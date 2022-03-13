// 11723 집합
// 문제: https://www.acmicpc.net/problem/11723
/*
    sol.1) 구현 (2,392KB, 760ms)
    시간 복잡도: ?
    풀이)
    - visited 배열을 이용해 집합에 값의 존재 여부를 저장. (visited[3] = true일 경우, 3은 집합에 존재)
    - all 혹은 empty와 같이 visited 배열을 초기화해주는 명령은 나중으로 미룸. (= 시간 초과 방지; 입력되는 명령이 연속적으로 empty or all일 수 있기 때문)
    즉, all 혹은 empty가 아닌, 값에 변동을 주는 명령이 주어지기 전까지는 해당 명령을 보관하다가 명령이 들어올 시에 값을 초기화시킨 후 명령을 수행.
    이렇게 된다면 불필요한 초기화 시간을 줄일 수 있음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 20 + 1

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 3,000,000
    cin >> n;

    bool visited[MAX];
    fill(visited, visited + MAX, false);

    int flag = 2;
    while (n--)
    {
        string cmd;
        cin >> cmd;
        int x; // 1 ≤ x ≤ 20

        if (cmd.front() == 'a' && cmd.back() == 'l') // all
            flag = 1;
        else if (cmd.front() == 'e') // empty
            flag = 0;
        else
        {
            if (flag != 2)
                fill(visited, visited + MAX, flag), flag = 2;

            if (cmd.front() == 'a' && cmd.back() == 'd') // add
                cin >> x, visited[x] = true;
            else if (cmd.front() == 'r') // remove
                cin >> x, visited[x] = false;
            else if (cmd.front() == 'c') // check
                cin >> x, cout << visited[x] << endl;
            else if (cmd.front() == 't') // toggle
                cin >> x, visited[x] = !visited[x];
        }
    }
}

/*
    sol.2) 비트마스킹 (2,024KB, 708ms)
    시간 복잡도: ?
    풀이)
    입력된 값 x가 20 이하의 값이므로, 비트마스크를 이용해 x를 비트로 바꾼 값을 b에 저장하는 식으로 풀이.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 3,000,000
    cin >> n;

    int b = 0;
    while (n--)
    {
        string cmd;
        cin >> cmd;
        int x; // 1 ≤ x ≤ 20

        if (cmd == "add")
            cin >> x, b |= 1 << x;
        else if (cmd == "remove")
            cin >> x, b &= ~(1 << x);
        else if (cmd == "check")
            cin >> x, cout << bool(b & 1 << x) << endl;
        else if (cmd == "toggle")
            cin >> x, b ^= 1 << x;
        else if (cmd == "all")
            b = -1;
        else // empty
            b = 0;
    }
}

/*
    sol.3) 비트셋 (2,024KB, 624ms)
    참고)
    - 비트셋: https://www.crocus.co.kr/549
            https://blog.naver.com/jinhan814/222536104201
*/

#include <iostream>
#include <bitset> // bit

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 3,000,000
    cin >> n;

    bitset<20> bit(0);

    int flag = 2;
    while (n--)
    {
        string cmd;
        cin >> cmd;
        int x; // 1 ≤ x ≤ 20

        if (cmd.front() == 'a' && cmd.back() == 'd') // add
            cin >> x, bit[x - 1] = true;
        else if (cmd.front() == 'r') // remove
            cin >> x, bit[x - 1] = false;
        else if (cmd.front() == 'c') // check
            cin >> x, cout << bit[x - 1] << endl;
        else if (cmd.front() == 't') // toggle
            cin >> x, bit.flip(x - 1);
        else if (cmd.front() == 'a' && cmd.back() == 'l') // all
            bit.set();
        else if (cmd.front() == 'e') // empty
            bit.reset();
    }
}