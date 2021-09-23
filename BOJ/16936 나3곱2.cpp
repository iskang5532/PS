/* 
 * 16936 나3곱2
 * DFS
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/16936
 * etc.) next_permutation을 이용한 풀이를 실패함. (시간초과)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 100 + 1 // 수열의 최대 크기
typedef long long ll;

int n;             // 수열의 크기 (2 <= n <= 100)
bool visited[MAX]; // i번째 원소 사용 여부
vector<ll> ans;    // 만들어질 수열을 저장할 공간

void dfs(const vector<ll> &arr)
{
    if (ans.size() == n) // 만들어진 수열의 길이가 원하는 길이인 경우, 출력
    {
        for (const auto &elem : ans)
            cout << elem << " ";
        exit(0);
    }

    for (int i = 0; i < n; i++) // 두 번째부터 올 값
    {
        if (visited[i]) // 만약 i번쨰 원소를 사용한 적이 있는 경우
            continue;
        if (ans.back() % 3 == 0 && ans.back() / 3 == arr[i] || // 나3
            (ans.back() * 2 == arr[i]))                        // 곱2
        {
            ans.push_back(arr[i]), visited[i] = true;
            dfs(arr);
            ans.pop_back(), visited[i] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;
    vector<ll> arr(n); // 수열 (<= 10^18)
    for (auto &elem : arr)
        cin >> elem;

    for (int i = 0; i < n; i++) // 첫 번째 값 선정. 값은 arr[n-1]까지
    {
        ans.push_back(arr[i]), visited[i] = true;
        dfs(arr);
        ans.pop_back(), visited[i] = false;
    }
}