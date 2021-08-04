/* 
 * 2304 창고 다각형
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2304
 * ETC.) 가장 높은 기둥이 여러 개인 경우에 대한 고민을 오래 함.. (결국 인터넷 참고)
 * 참고: https://hwan-shell.tistory.com/304 (이론 및 그림)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

struct P
{
    int x, y;
};

bool cmp(const P &p1, const P &p2) { return p1.x < p2.x; }; // 오름차순

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<P> arr(n);
    for (auto &elem : arr)
        cin >> elem.x >> elem.y;
    sort(arr.begin(), arr.end(), cmp);

    int answer = 0;

    // 좌측에서부터 우측으로 이동하며 가장 높은 기둥까지의 면적을 구해줌 (추가로, 가장 높은 기둥이 여러개인 경우, 하나를 제외한 면적을 구해줌)
    int left_pos = 0, left_h = 0; // 선택된 기둥의 가장 왼쪽 부분 및 높이 (= 면적을 구하는 데 사용)
    for (const auto &itr : arr)
        if (left_h <= itr.y) // 현재 기둥의 높이가 이전 기둥보다 높거나 같은 경우, 이전 기둥에서부터 현재 기둥 이전까지의 면적을 구함. (같은 경우가 포함되며, 위 주석에서 언급된 부분)
        {
            answer += (itr.x - left_pos) * left_h;
            left_pos = itr.x, left_h = itr.y;
        }
    // 우측에서부터 좌측으로 이동하며 가장 높은 기둥까지의 크기를 구해줌
    int right_pos = arr.back().x, right_h = 0;
    for (vector<P>::reverse_iterator itr = arr.rbegin(); itr != arr.rend(); itr++)
        if (right_h < (*itr).y)
        {
            answer += (right_pos - (*itr).x) * right_h;
            right_pos = (*itr).x, right_h = (*itr).y;
        }
    answer += right_h; // or += left_h; 하나 남은 가장 높은 기둥의 넓이를 더해줌

    cout << answer;
}
// 예제. (기존 예제에 12, 10(가장 높은 기둥)을 추가)
// ans: 106
// 8
// 2 4
// 11 4
// 15 8
// 4 6
// 5 3
// 8 10
// 13 6
// 12 10