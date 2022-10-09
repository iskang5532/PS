// 2022-10-05
// 2852 NBA 농구
// https://www.acmicpc.net/problem/2852
/*
    sol.1) 구현, 문자열 (2,080KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 이기고 있는 구간이란 득점한 팀이 0점이 될 때까지이다.
    - 득점 현황을 저장할 cnt. (양수일 경우 1팀이, 음수일 경우 2팀이 우세)
    - 어느 한 팀의 점수가 앞서게 된 시간을 저장할 prev와 해당 팀의 번호를 저장할 p.
    - 1팀이 이기고 있던 시간 a, 2팀이 이기고 있던 시간 b.
    - 입력된 득점 정보에서 시간을 초로 바꿔 cur에 저장.
    득점 이후에 p가 0일 경우, 앞서고 있던 팀이 없었으므로 p를 해당 팀의 번호로 바꾸며 prev에 cur 저장.
    득점 이후에 cnt가 0일 경우, 동점이 되는 상황임. 즉, 앞서고 있던 팀의 시간을 계산 후 해당 팀에 저장.
     만약 p가 1일 경우, cur - prev의 값을 a에 저장.
     만약 p가 2일 경우, cur - prev의 값을 b에 저장.
    - 마지막 득점 이후 동점이 아니면 p팀에 종료 시간 - prev만큼 시간을 추가.
    참고) 헷갈림
 */

#include <iostream>
#include <sstream> // stringstream

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
    FAST_IO;

    int n; // 골이 들어간 횟수 (1 ≤ n ≤ 100)
    cin >> n;

    int a = 0, b = 0;    // 1팀이 이기고 있던 시간 a, 2팀이 이기고 있던 시간 b
    int cnt = 0;         // 득점 현황 (양수일 경우 1팀이, 음수일 경우 2팀이 우세)
    int prev = 0, p = 0; // 점수가 앞서게 된 시간 prev, 해당 팀 번호 p
    for (int i = 0; i < n; i++)
    {
        int num;
        string t;
        cin >> num >> t;

        stringstream ss(t);
        int m, s;
        char idx;
        ss >> m >> idx >> s;

        int cur = m * 60 + s;

        num == 1 ? cnt++
                 : cnt--;

        if (cnt != 0 && p == 0) // 한 팀이 앞서게 된 경우
            p = num, prev = cur;
        else if (cnt == 0) // 동점이 되었을 경우
        {
            (p == 1 ? a : b) += cur - prev;
            p = 0;
        }
    }
    if (cnt != 0)
        (p == 1 ? a : b) += 48 * 60 - prev;

    cout << (a / 60 < 10 ? "0" : "") << a / 60 << ':' << (a % 60 < 10 ? "0" : "") << a % 60 << endl;
    cout << (b / 60 < 10 ? "0" : "") << b / 60 << ':' << (b % 60 < 10 ? "0" : "") << b % 60 << endl;
}

/*
    sol.2) 정규표현식, 구현, 문자열 (2,176KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 1번 풀이에서 stringstream 대신 정규표현식을 사용
 */

#include <iostream>
#include <regex>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

const regex _REGEX(R"((\d+):(\d+))");

int main()
{
    FAST_IO;

    int n; // 골이 들어간 횟수 (1 ≤ n ≤ 100)
    cin >> n;

    int a = 0, b = 0;    // 1팀이 이기고 있던 시간 a, 2팀이 이기고 있던 시간 b
    int cnt = 0;         // 득점 현황 (양수일 경우 1팀이, 음수일 경우 2팀이 우세)
    int prev = 0, p = 0; // 점수가 앞서게 된 시간 prev, 해당 팀 번호 p
    for (int i = 0; i < n; i++)
    {
        int num;
        string t;
        cin >> num >> t;

        auto it = *sregex_iterator(t.begin(), t.end(), _REGEX);
        int m = stoi(it[1]), s = stoi(it[2]);

        int cur = m * 60 + s;

        num == 1 ? cnt++
                 : cnt--;

        if (cnt != 0 && p == 0) // 한 팀이 앞서게 된 경우
            p = num, prev = cur;
        else if (cnt == 0) // 동점이 되었을 경우
        {
            (p == 1 ? a : b) += cur - prev;
            p = 0;
        }
    }
    if (cnt != 0)
        (p == 1 ? a : b) += 48 * 60 - prev;

    cout << (a / 60 < 10 ? "0" : "") << a / 60 << ':' << (a % 60 < 10 ? "0" : "") << a % 60 << endl;
    cout << (b / 60 < 10 ? "0" : "") << b / 60 << ':' << (b % 60 < 10 ? "0" : "") << b % 60 << endl;
}
