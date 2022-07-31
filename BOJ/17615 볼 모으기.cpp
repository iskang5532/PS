// 2022-07-31
// 17615 볼 모으기
// https://www.acmicpc.net/problem/17615
/*
    그리디 (2,912KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 공의 개수가 많지 않으므로, 빨간색 공을 옮길 떄의 횟수와 파란색 공을 옮길 때의 횟수를 구한 후, 더 작은 값을 출력.
    - 포인트는, 끝에 존재하는 공은 옮길 필요가 없음.
    단, 왼쪽과 오른쪽이 같은 색이라면 둘 중 한쪽은 반대편으로 옮겨야 함.
    이때 옮겨야 하는 쪽은 공의 개수가 더 작은 쪽이다.
    - 왼쪽과 오른쪽의 연속적인 공의 개수를 구한 후, 색에 맞춰 R 혹은 B에 저장. (R과 B는 옮겨야 하는 공이 아님)
    위에서 언급한 것처럼 더 작은 개수를 옮겨야 하면서 R과 B에는 '옮기지 않는' 공을 저장하므로, 연속적인 공의 최대 개수를 R 혹은 B에 저장.
    etc.)
    - 꽤 어려웠음
    - 서로 같은 공 사이에 존재하는 다른 공의 개수를 각각 구하여 값을 더한 후, 더 작은 값을 출력해보려 했으나 이 또한 아이디어 고갈로 실패.
    - 빨간색 공을 옮긴 경우와 파란색 공을 옮긴 경우 두 가지를 구한 후, 더 작은 값을 구해보는 과정에서 끝에 연속되는 공의 개수가 포인트임을 파악.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    string s;
    cin >> s;

    int cnt['Z']{}; // cnt['R'] = k일 경우, 빨간색 볼은 k개
    for (const auto &c : s)
        cnt[c]++;

    int R = 0, B = 0; // 끝에 존재하면서 연속적인 공의 최대 개수 (R = 2일 경우, 왼쪽 혹은 오른쪽에 빨간색 공이 2개 존재하며, 가장 많음)
    for (int l = 1, p = 1; l < n; l++, p++)
        if (s[l] != s[l - 1])
        {
            s[l - 1] == 'R' ? R = max(R, p)
                            : B = max(B, p);
            break;
        }
    for (int r = n - 2, p = 1; r >= 0; r--, p++)
        if (s[r] != s[r + 1])
        {
            s[r + 1] == 'R' ? R = max(R, p)
                            : B = max(B, p);
            break;
        }

    cout << min(cnt['B'] - B, cnt['R'] - R);
}