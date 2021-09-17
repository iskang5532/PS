/* 
 * 10971 외판원 순회 2
 * brute-force
 * 시간 복잡도: O(n!)
 * 문제: https://www.acmicpc.net/problem/10971
 * etc.) 궁금한 점이 있음.
 * a - c - b로 이동한 후 b - a로 돌아오도록 작성했는데 돌아오는 길의 경우 중 b - c - a의 비용이 더 낮은 경우는 없는가?
 * 혹은 b - a로 돌아오도록 문제에 주어진건가?
 * 후자의 경우, 외판원 문제 자체가 사이트 https://hsp1116.tistory.com/40 에서의 첫 번째 사진과 같다고 생각.
 * 참고: https://www.acmicpc.net/board/view/7210 (시작점 및 사이클에 대한 질문)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define INF 987654321

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 도시의 수 (2 <= 10)
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(n)); // arr[i][j]는 도시 i에서 도시 j로 가기 위한 비용
    for (auto &col : arr)
        for (auto &row : col)
            cin >> row;

    vector<int> path(n); // 순회할 도시들의 순서를 저장. 처음은 0 to n
    for (int i = 0; i < n; i++)
        path[i] = i;

    int ans = INF; // 외판원 순회에 필요한 최소 비용. 초깃값은 INF
    do
    {
        int sum = 0;       // 목적지까지 도달했을 때의 비용 합
        bool valid = true; // 현재 순회 순서의 유효함 (만약 i to j 이동이 불가능한 경우 false)
        for (int i = 0; i < n - 1; i++)
        {
            int l = path[i], r = path[i + 1]; // 현재 위치 l과 다음 위치 r
            if (arr[l][r]) // 만약 i to j에 대한 길이 존재하는 경우
                sum += arr[l][r];
            else // i to j에 대한 길이 없는 경우
                valid = false;
            // break;
        }

        if (valid && arr[path.back()][path.front()] != false) // 마지막 도시에서 출발 도시로 돌아올 길이 있는 경우
            ans = min(ans, sum + arr[path.back()][path.front()]); // 마지막 - 출발지의 비용도 추가
    } while (next_permutation(path.begin() + 1, path.end())); // +1이 없어도 정답이긴 함.

    cout << ans;
}