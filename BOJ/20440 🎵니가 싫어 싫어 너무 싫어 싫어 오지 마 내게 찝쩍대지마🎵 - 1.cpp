/* 
 * 20440 🎵니가 싫어 싫어 너무 싫어 싫어 오지 마 내게 찝쩍대지마🎵 - 1
 * 누적 합
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/20440
 * ETC.) 처음엔 pq에 입장 시간과 퇴장 시간을 나누어 값을 넣고 해결하려고 했지만,
 * [4 6] - [6 10]과 같은 이어지는 형태의 경우를 해결하지 못함
 * 참고: https://velog.io/@bgg01578/%EB%B0%B1%EC%A4%80-20440 (코드 해석)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl "\n"

struct P
{
    int l, r;
};

bool cmp(const P &a, const P &b) { return a.l < b.l; } // 입장 시간 기준 오름차순 (= 빠른 값이 앞으로)

struct _greater // 퇴장 시간 기준 오름차순 (= 빠른 값이 앞으로)
{
    bool operator()(const P &a, const P &b) { return a.r > b.r; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<P> arr(n);
    for (auto &elem : arr)
        cin >> elem.l >> elem.r;
    sort(arr.begin(), arr.end(), cmp);

    P answer = {0, 0};
    // pq.top(): 입력된 시간대들 중 모기가 가장 많으면서 입장 및 퇴장 시간이 가장 느린 구간
    // pq.size(): 모기의 마릿수
    priority_queue<P, vector<P>, _greater> pq;
    int h = 0; // 가장 많이 있는 시간대의 모기 마릿수
    for (int i = 0; i < n; i++)
    {
        // i번째 arr의 값이 이전 값(= pq.top())과 같거나 뒤에 있는 경우 (= 갱신해야 함)
        while (!pq.empty() && pq.top().r <= arr[i].l)
            pq.pop();
        pq.push(arr[i]);

        if (pq.size() > h) // 마릿수가 많아진 경우, 갱신
        {
            h = pq.size();
            answer = {arr[i].l, pq.top().r}; // 여기서 r은 pq.top().r(= 가장 빠른 퇴장 시간. 즉, h가 낮아지는 지점임)
        }
        else if (h == pq.size() && answer.r == arr[i].l) // 높이가 같으며 퇴장 시간 및 입장 시간이 같은 경우, 연결해줌
            answer.r = arr[i].r;
    }

    cout << h << endl;
    cout << answer.l << " " << answer.r;
}

// 3
// 2 16
// 4 10
// 5 12

/* ___ unresolved ___ */
// 1차
// #include <iostream>
// #include <queue>

// using namespace std;

// #define endl "\n"

// struct P
// {
//     int pos, state;
// };

// struct _greater
// {
//     bool operator()(const P &a, const P &b)
//     {
//         if (a.pos == b.pos)
//             return a.state > b.state;
//         return a.pos > b.pos;
//     }
// };

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL), cout.tie(NULL);

//     int n;
//     cin >> n;

//     priority_queue<P, vector<P>, _greater> q;
//     for (int i = 0; i < n; i++)
//     {
//         int l, r;
//         cin >> l >> r;
//         q.push({l, 1});
//         q.push({r, -1});
//     }

//     int l, r;
//     int _max = 0, _min = 0, cnt = 0;
//     while (!q.empty())
//     {
//         P curr = q.top();
//         q.pop();

//         if (curr.state == 1)
//         {
//             if (++cnt > _max)
//             {
//                 _max = cnt;
//                 l = curr.pos;
//             }
//         }
//         else if (curr.state == -1)
//         {
//             if (cnt > _min)
//             {
//                 _min = cnt;
//                 r = curr.pos;
//             }
//             cnt--;
//         }
//     }

//     cout << _max << endl;
//     cout << l << " " << r;
// }