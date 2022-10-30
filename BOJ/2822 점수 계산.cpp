// 2022-10-29
// 2822 점수 계산
// https://www.acmicpc.net/problem/2822
/*
    정렬, 구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    1. 입력받은 점수를 번호와 묶은 {점수, 번호}를 v에 저장.
    2. 점수를 기준으로 내림차순 정렬.
    3. 상위 5개의 점수와 번호를 추출한 후, 점수는 sum에 더해주며 번호는 _v에 저장.
    4. 출력할 번호는 오름차순이어야 하므로, _v를 오름차순 정렬.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"

int main()
{
    FAST_IO;

    vector<pii> v(10); // {점수, 번호}
    for (int i = 1; i <= 8; i++)
    {
        int k;
        cin >> k;
        v[i] = {k, i};
    }

    sort(v.begin(), v.end(), greater<>());

    int sum = 0;    // 점수의 합
    vector<int> _v; // 번호 저장
    for (int i = 0; i < 5; i++)
        sum += v[i].first, _v.push_back(v[i].second);

    sort(_v.begin(), _v.end());
    cout << sum << endl;
    for (const auto &i : _v)
        cout << i << ' ';
}