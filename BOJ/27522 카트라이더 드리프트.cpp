// 2023-02-26
// 27522 카트라이더: 드리프트
// https://www.acmicpc.net/problem/27522
/*
    정렬 (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 시간과 팀을 v에 저장 후, 시간을 기준으로 오름차순 정렬.
    이후, 첫 번째 값의 팀부터 확인하여 순위에 맞는 점수를 팀 점수에 더함.
    두 팀의 점수를 비교 후, 승리한 팀을 출력.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 8

vector<pair<string, char>> v;
constexpr int grade[] = {10, 8, 6, 5, 4, 3, 2, 1};

int main()
{
    FAST_IO;

    for (int i = 0; i < MAX; i++)
    {
        string s;
        char c;
        cin >> s >> c;

        v.push_back({s, c});
    }

    sort(v.begin(), v.end());

    int red = 0, blue = 0;
    for (int i = 0; i < MAX; i++)
        ((v[i].second == 'R') ? red : blue) += grade[i];

    cout << ((red > blue) ? "Red" : "Blue");
}