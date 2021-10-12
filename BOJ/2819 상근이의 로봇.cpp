/* 
 * 2819 상근이의 로봇 
 * 이분 탐색 (2808KB, 88ms)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2819
 * etc.) 진짜 너무너무 헷갈려서 스트레스 받은 문제. 좌표를 이용한 문제에 약한가보다. 
 * 이해가 안가는 부분은 (y++, x--), (y--, x++) 쌍인 줄 알았는데 ++, --끼리였음. (y++는 아래로 향하는 듯함)
 * - 명령마다 모든 좌표에 대한 거리를 구할 경우 TLE. 때문에 다른 방식으로 접근.
 * - 장소보다 낮은 위치 혹은 높은 위치의 조사점의 개수를 이용.
 * 현재 위치 이하의 조사점(= curr)의 개수와 이동한 위치 이상의 조사점(= next)의 개수를 구한 뒤 비교하여 각 조사점과의 거리의 합을 구함.
 * 여기서 이하란 이동 방향의 반대편이며, 이상이란 이동 방향, 즉 정방향이다.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
typedef long long ll;

const int dim_col[4] = {1, -1, 0, 0}; // S, J, I, Z
const int dim_row[4] = {0, 0, 1, -1};

struct pii
{
    int x, y;
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 조사점의 수 (1 ≤ n ≤ 100k), 명령의 수 (1 ≤ m ≤ 300k)
    cin >> n >> m;

    vector<int> v1(n), v2(n); // x값 및 y값을 저장 (|K| ≤ 1M)
    for (int i = 0; i < n; i++)
        cin >> v1[i] >> v2[i];

    pii p = {0, 0}; // 로봇의 위치
    ll k = 0;       // 각 조사점과의 거리의 합
    for (int i = 0; i < n; i++)
    {
        int row = v1[i] - p.x;
        int col = v2[i] - p.y;

        k += abs(col) + abs(row);
    }
    sort(v1.begin(), v1.end()), sort(v2.begin(), v2.end());

    for (int i = 0; i < m; i++)
    {
        char c;
        cin >> c;

        int curr, next; // 현재 위치 이하의 조사점 개수, 다음 위치 이상의 조사점 개수
        if (c == 'S')   // y++
        {
            curr = upper_bound(v2.begin(), v2.end(), p.y) - v2.begin();
            next = v2.size() - curr;
            p.x += dim_row[0], p.y += dim_col[0]; // 로봇의 좌표 갱신
        }
        else if (c == 'J') // y--
        {
            curr = v2.end() - lower_bound(v2.begin(), v2.end(), p.y);
            next = v2.size() - curr;
            p.x += dim_row[1], p.y += dim_col[1];
        }
        else if (c == 'I') // x++
        {
            curr = upper_bound(v1.begin(), v1.end(), p.x) - v1.begin();
            next = v1.size() - curr;
            p.x += dim_row[2], p.y += dim_col[2];
        }
        else if (c == 'Z') // x--
        {
            curr = v1.end() - lower_bound(v1.begin(), v1.end(), p.x);
            next = v1.size() - curr;
            p.x += dim_row[3], p.y += dim_col[3];
        }

        k += curr - next;

        cout << k << endl;
    }
}

// [1, 2, 3, 3, 4, 5, 6], x = 3이며 명령은 x++('I')일 때
// curr = [1, 2, 3, 3] = 4 // 현재 위치(= 3) 이하의 개수
// next = [4, 5, 6] = 3    // 다음 위치(= 4) 이상의 개수
// => curr - next = 1
// 결과적으로 위치의 변동은 +1이 된다.