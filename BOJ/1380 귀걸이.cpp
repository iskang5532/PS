// 1380 귀걸이
// https://www.acmicpc.net/problem/1380
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 여학생의 이름이 공백을 포함하므로, getline()을 이용하여 입력을 받아줌.
    - i번째 여학생의 이름을 저장할 v. (v[i] = "name"일 경우, i+1번째 여학생의 이름은 "name")
    - 귀걸이 압수 및 회수 여부를 저장할 cnt. (cnt[i] = 1일 경우 압수, 2일 경우 회수)
    - 여학생의 번호 k를 받은 후, cnt의 값을 올린다.
    이후 모든 여학생의 cnt를 탐색하며, 만약 값이 1일 경우, 즉 압수된 상태(이며 회수되지 않음)인 여학생을 찾으면 여학생의 이름을 출력한다.
    etc.)
    - getline(cin, )을 사용할 경우, cin.ignore()를 필요로 할 수 있음.
    - 입력 'A'와 'B'는 어디에 사용하는 것인가?
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 103 // max n

int main()
{
    FAST_IO;

    for (int n, tc = 1; cin >> n; tc++, cout << endl) // 여학생의 수 (1 ≤ n ≤ 100)
    {
        if (n == 0) // exit
            return 0;

        cin.ignore();

        vector<string> v(n); // v[i] = "name"일 경우, i+1번째 여학생의 이름은 "name"
        for (int i = 0; i < n; i++)
        {
            string s;
            getline(cin, s);
            v[i] = s;
        }

        int cnt[MAX]; // 여학생의 귀걸이 압수 및 회수 여부를 저장. (cnt[i] = 1일 경우 압수, 2일 경우 회수)
        fill(cnt, cnt + MAX, 0);
        for (int i = 0; i < 2 * n - 1; i++)
        {
            int k;
            char idx;
            cin >> k >> idx;

            cnt[k - 1]++;
        }

        for (int i = 0; i < n; i++)
            if (cnt[i] == 1) // 압수당한 상태일 경우
            {
                cout << tc << ' ' << v[i];
                break;
            }
    }
}