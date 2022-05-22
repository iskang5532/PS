// 2022-05-17
// 11637 인기 투표
// https://www.acmicpc.net/problem/11637
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 표의 수와 최대 득표수를 저장.
    - 후보가 받은 표가 최대 득표수인 경우, cnt++ 및 ans에 후보의 번호를 저장.
    만약 cnt가 2 이상, 즉 최대 득표수를 받은 인원이 둘 이상인 경우 "no winner"
    만약 cnt가 1, 즉 최대 득표수를 받은 인원이 한명일 경우
     - 해당 인원이 과반수 득표를 하였을 경우 "majority winner"
     - 해당 인원이 절반 이하의 득표를 하였을 경우 "minority winner"
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 13

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 500
    cin >> tc;
    while (tc--)
    {
        int v[MAX];

        int n;
        cin >> n;
        int sum = 0, mx = 0;
        for (int i = 0; i < n; i++)
            cin >> v[i], sum += v[i], mx = max(mx, v[i]);

        int cnt = 0, ans;
        for (int i = 0; i < n; i++)
            if (mx == v[i])
                cnt++, ans = i;

        if (cnt == 1)
            cout << (v[ans] > sum / 2 ? "majority winner " : "minority winner ") << ans + 1 << endl;
        else
            cout << "no winner" << endl;
    }
}