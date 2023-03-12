// 2023-03-11
// 1713 후보 추천하기
// https://www.acmicpc.net/problem/1713
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 각 후보의 추천 받은 횟수와 사진이 게시된 시간을 v[]에 저장.
    - 사용중인 사진틀의 개수를 cnt에 저장.
    - cnt가 사진틀의 개수를 넘었을 경우, 횟수가 가장 작은 학생 v[i]를 초기화.
    만약 동일할 경우, 시간이 가장 빠른 학생일 초기화.
    이후, 입력된 학생 k의 정보를 v에 저장.
    - v에 0이 아닌 값이 있을 경우, 해당 학생은 사진틀에 게시됨.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x3f3f3f3f
#define MAX 103 // max m

struct pii
{
    int cnt, t; // 추천 횟수 cnt, 게시된 시간 t
};

int main()
{
    FAST_IO;

    int n; // 사진틀의 개수 (1 ≤ n ≤ 20)
    cin >> n;
    int m; // 학생의 총 추천 횟수 (m ≤ 1,000)
    cin >> m;

    pii v[MAX]{};
    int cnt = 0; // 사용한 사진틀의 개수
    for (int t = 0; t < m; t++)
    {
        int k; // 학생의 번호 (1 ≤ k ≤ 100)
        cin >> k;

        if (v[k].cnt == 0)
            cnt++, v[k].t = t;
        if (cnt > n) // erase
        {
            int mn = INF; // 가장 작은 추천 횟수
            for (int i = 0; i < MAX; i++)
                if (v[i].cnt)
                    mn = min(mn, v[i].cnt);

            int d;          // 제거할 번호
            int mn_t = INF; // 가장 오래된 시간을 저장
            for (int i = 0; i < MAX; i++)
                if (v[i].cnt == mn && mn_t > v[i].t)
                    d = i, mn_t = v[i].t;

            v[d] = {0, 0}, cnt--;
        }

        v[k].cnt++;
    }

    vector<int> ans;
    for (int i = 0; i < MAX; i++)
        if (v[i].cnt)
            ans.push_back(i);

    sort(ans.begin(), ans.end());

    for (const auto &i : ans)
        cout << i << ' ';
}