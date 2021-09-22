/* 
 * 2026 소풍
 * backtracking
 * 시간 복잡도: O(nCk)
 * 문제: https://www.acmicpc.net/problem/2026
 * etc.) 어떻게 dfs를 짜야 하는지 감도 안잡혔음.
 * 추가로, ans를 string으로 만들었을 때는 런타임 에러가 나왔음. why?
 * 참고: https://blog.naver.com/jinhan814/222303601866 (이론 및 코드)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 900 + 1 // 주어질 번호의 최댓값

int K, N, F; // 학생 (1 <= K <= 62), 번호 (K <= N <= 900), 정보 (1 <= F <= 5.6k)
bool path[MAX][MAX];
// string ans;
vector<int> ans; // 문제에 적합한 인원들의 모음

void dfs(int r)
{
    if (ans.size() == K) // 원하는 인원의 수가 모였을 경우
    {
        for (const auto &c : ans)
            cout << c << endl;
        exit(0); // 종료
    }

    for (int i = r + 1; i <= N; i++) // 두 번째 번호부터 (= 다음 번호)
    {
        bool flag = true;            // 다음 번호 i가 적합한지 (기본값은 true)
        for (const auto &elem : ans) // 이전에 입력된 값
            // if (!path[static_cast<int>(elem)][i]) // 런타임 에러. why?
            if (!path[elem][i]) // 이전 번호와 다음 번호 간에 관계가 없는 경우 (= 다음 번호는 올 수 없음)
            {
                flag = false;
                break;
            }
        if (!flag) // 적합하지 않은 경우
            continue;

        ans.push_back(i);
        dfs(i);
        ans.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> K >> N >> F;

    for (int i = 0; i < F; i++)
    {
        int a, b;
        cin >> a >> b;

        path[a][b] = path[b][a] = true; // 양방향
    }

    for (int i = 1; i <= N; i++) // 첫 번째 번호
    {
        ans.push_back(i);
        dfs(i);
        ans.pop_back();
    }
    cout << "-1"; // 적합한 관계를 찾지 못한 경우 (여기까지 온 경우, 프로그램 종료가 없었다는 것)
}