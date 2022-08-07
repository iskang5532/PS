// 2022-08-01
// 18310 안테나
// https://www.acmicpc.net/problem/18310
/*
    그리디 (2,680KB, 92ms)
    시간 복잡도: ?
    풀이)
    - 안테나가 세워진 곳 v[i]를 기준으로 왼쪽에 있는 집의 개수를 l, 오른쪽에 있는 집의 개수를 r이라 할 때, l == r이 된다면 v[i]가 답이 됨.
    만약 집의 개수가 짝수개라면, 구간으로 표시가 됨. (v[a], v[b])
    이 중 더 작은 v[a]를 출력.
    - 위에 적힌 이론을 모두 충족시키는 풀이는 입력된 집의 위치 중 가운데에 해당하는 집 혹은 두 집 중 더  작은 집을 구하여 출력하면 됨.
    etc.) 안테나는 집이 위치한 곳에만 설치할 수 있음에 주의
    참고)
    - 이론: https://blog.naver.com/jinhan814/222534711709
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 200'003 // max n

int main()
{
    int n;
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    cout << v[(n - 1) / 2];
}