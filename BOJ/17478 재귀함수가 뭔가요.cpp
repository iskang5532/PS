// 17478 재귀함수가 뭔가요?
// https://www.acmicpc.net/problem/17478
/*
    재귀 (2,156KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 재귀 횟수마다 언더바의 개수를 추가시킨 후, 출력에 추가해주면 되는 문제.
    etc.) 오타에 주의해야 하는 문제.
    - 수에는 constexpr, 문자열에는?
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

const string h1 = "\"재귀함수가 뭔가요?\"";
const string h2 = "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.";
const string h3 = "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.";
const string h4 = "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"";
const string ed = "라고 답변하였지."; // end

int n; // 재귀 횟수 (1 ≤ N ≤ 50)

void dfs(int dep, string under_bar = "")
{
    cout << under_bar + h1 << endl;
    if (dep == n)
        cout << under_bar + "\"재귀함수는 자기 자신을 호출하는 함수라네\"" << endl;
    else
    {
        cout << under_bar + h2 << endl;
        cout << under_bar + h3 << endl;
        cout << under_bar + h4 << endl;
        dfs(dep + 1, under_bar + "____");
    }
    cout << under_bar + ed << endl;
}

int main()
{
    FAST_IO;

    cin >> n;

    cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다." << endl;
    dfs(0);
}