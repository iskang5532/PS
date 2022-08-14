// 2022-08-05
// 16206 롤케이크
// https://www.acmicpc.net/problem/16206
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 만들 수 있는 10의 최대 개수를 구한 후 출력하는 문제.
    - 10을 만들기 위해서는 10보다 큰 값을 잘라 10과 나머지 수 k로 나누어야 한다.
    - 나머지 수 k가 10일 경우, 한 번의 횟수로 두 개의 10을 만들게 된다. 즉, 효율이 높다.
    이를 이용해, 10의 배수의 값을 우선으로 자른다.
    또한, 수 20은 1회만으로, 30은 2회, 40은 3회... 값이 커질수록 횟수가 많아진다. 그러므로 작은 값을 우선으로 자른다.
    - 10의 배수가 아닌 값들은 10의 배수가 모두 잘렸으면서 자르는 횟수가 남아 있으면 자른다.
    이들은 자른 횟수만큼 10이 나오므로, 순서를 신경 쓰지 않아도 된다.
    - 이 풀이에서는 값을 배열 v에 저장한 후, 10의 배수를 우선으로, 그중에서도 작은 값을 우선으로 오도록 정렬한 후 풀었다.
    그 외의 풀이는, 10의 배수를 저장할 v1, 그 외의 값을 저장할 v2를 선언한 후 v1을 오름차순 정렬하여 풀어줄 수도 있다. (이게 더 편한 듯)
    etc.) cmp의 원리가 헷갈림.
    참고)
    - 반례: https://www.acmicpc.net/board/view/61964
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

bool cmp(const int a, const int b)
{
    return a % 10 == 0 && b % 10 == 0 ? a < b        // 10의 배수 내림차순 정렬
                                      : a % 10 == 0; // 10의 배수를 우선으로
}

int main()
{
    FAST_IO;

    int n, m; // 롤케이크의 개수 n, 자를 수 있는 횟수 m (1 ≤ N, M ≤ 1,000)
    cin >> n >> m;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n, cmp); // 오름차순 정렬

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        while (m && v[i] > 10) // 횟수가 남았으며 분할이 가능한 경우
            v[i] -= 10, m--, ans++;
        if (v[i] == 10)
            ans++;
    }

    cout << ans;
}
