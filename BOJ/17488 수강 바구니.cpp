// 2023-03-29
// 17488 수강 바구니
// https://www.acmicpc.net/problem/17488
/*
    구현 (9,444KB, 240ms)
    시간 복잡도: ?
    풀이)
    - 과목을 신청한 학생을 select[]에 저장.
    - select[]의 크기와 cnt[]의 크기를 비교하여 과목을 신청한 학생이 모두 신청에 성공할 수 있는지 확인.
    만약 cnt[]의 크기가 클 경우, 모두 성공이므로 해당 학생들을 ans[]에 저장.
    만약 select[]의 크기가 클 경우, 신청할 수 없음.
    성공 혹은 실패 후 cnt[]는 신청한 학생의 수만큼 값을 뺌.
    - 총 두 번의 수행으로 ans[]를 구함.
    - ans[]에 저장된 값을 출력. (이때, 오름차순 출력이 필요하므로 정렬)
    만약 ans[]가 비었을 경우, 학생은 수강 신청에 실패.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'003 // max n, m

int n, m; // 학생의 수 n, 과목의 수 m(1 ≤ n, m ≤ 1,000)
int cnt[MAX];
vector<int> ans[MAX]; // 학생의 신청 성공 과목을 저장

void get_ans()
{
    vector<int> select[MAX]; // select[i] = {a, b}일 경우, i번 과목을 선택한 학생은 {a, b}
    for (int i = 1; i <= n; i++)
    {
        int p;
        while (cin >> p && p != -1)
            select[p].push_back(i);
    }

    for (int i = 1; i <= m; i++) // i번 과목
    {
        if (cnt[i] >= (int)select[i].size())
            for (const int &people : select[i])
                ans[people].push_back(i);
        cnt[i] -= select[i].size();
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> cnt[i];

    get_ans();
    get_ans();

    for (int i = 1; i <= n; i++, cout << endl)
        if (ans[i].empty())
            cout << "망했어요";
        else
        {
            sort(ans[i].begin(), ans[i].end());
            for (const int &p : ans[i])
                cout << p << ' ';
        }
}