// 2022-05-04
// 8896 가위 바위 보
// https://www.acmicpc.net/problem/8896
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 현재 살아있는 로봇의 수를 저장할 cnt.
    - 로봇의 상태(= 죽거나 살거나)를 저장할 dead.
    - 로봇이 낸 패를 저장할 rsp. (rsp['R'] = {0, 2}일 경우, 0번과 2번은 주먹을 냄)
    - rsp의 값을 확인하며 승패를 확인.
     - 가위, 바위, 보 모두 존재할 경우 다음 패를 확인.
     - 그 외의 경우, 두 가지씩 확인. (가위-바위, 바위-보, 보-가위)
     만약 가위와 바위가 존재할 경우, cnt에서 가위의 수만큼 값을 깎음.
     또한, rsp['S']에 존재하는 로봇의 번호를 이용하여 dead = false처리.
    - cnt가 둘 이상, 로봇이 둘 이상 살아남은 경우, 1을 출력.
    그 외의 경우, 살아남은 로봇을 출력.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pcc = pair<char, char>;
#define endl "\n"
#define MAX 13

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 로봇의 수 n,(2 ≤ N ≤ 10)
        cin >> n;

        string s[MAX];
        for (int i = 0; i < n; i++)
            cin >> s[i];

        int cnt = n; // 살아있는 로봇의 수
        bool dead[MAX]{};
        for (int cur = 0; cur < s[0].length() && cnt != 1; cur++)
        {
            vector<int> rsp[100]; // rsp['R'] = {0, 2}일 경우, 0번과 2번은 주먹을 냄
            for (int i = 0; i < n; i++)
            {
                if (dead[i])
                    continue;

                char c = s[i][cur];
                rsp[c].push_back(i);
            }

            if (rsp['R'].size() && rsp['S'].size() && rsp['P'].size())
                continue;
            for (const auto &[a, b] : {pcc{'R', 'S'}, pcc{'S', 'P'}, pcc{'P', 'R'}})
                if (rsp[a].size() && rsp[b].size())
                {
                    cnt -= rsp[b].size();
                    for (const auto &user : rsp[b])
                        dead[user] = true;
                    break;
                }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
            if (!dead[i])
                ans = i + 1;

        cout << (cnt >= 2 ? 0 : ans) << endl;
    }
}