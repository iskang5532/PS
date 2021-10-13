/* 
 * 20440 🎵니가 싫어 싫어 너무 싫어 싫어 오지 마 내게 찝쩍대지마🎵 - 1
 * 누적 합
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/20440
 * ETC.) 처음엔 pq에 입장 시간과 퇴장 시간을 나누어 값을 넣고 해결하려고 했지만 [4 6] - [6 10]과 같은 이어지는 형태의 경우를 해결하지 못함.
 * 1) 입력받은 시간들을 시작을 기준으로 오름차 정렬 후, 순차적으로 이용.
 * 2-1) 현재 시간대가 이전 시간대와 겹치는 구간이 있는 경우 (= 모기가 이전 시간대보다 +1)
 * - 겹쳐지는 구간을 저장하며 모기의 마릿수 +1
 * 2-2) 현재 시간대가 이전 시간대와 겹치지 않으면서 서로 붙어있는 경우 (= prev.r == curr.l)
 * - 구간의 길이를 늘림
 * 2-3) 현재 시간대가 이전 시간대와 겹치지 않으면서 서로 떨어져 있는 경우 (= prev.r != curr.l)
 * - 넘김
 * 참고: https://velog.io/@bgg01578/%EB%B0%B1%EC%A4%80-20440 (코드 해석)
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;

#define endl "\n"

struct pii
{
    int l, r;
};

bool cmp(const pii &a, const pii &b) { return a.l < b.l; } // 오름차순 (입장 시간 기준. 빠른 값이 앞으로)

struct _greater // 오름차순 (퇴장 시간 기준. 빠른 값이 앞으로)
{
    bool operator()(const pii &a, const pii &b) { return a.r > b.r; }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<pii> arr(n);
    for (auto &[l, r] : arr)
        cin >> l >> r;
    sort(arr.begin(), arr.end(), cmp);

    // top(): 입력된 시간대들 중 모기가 가장 많으면서 입장 및 퇴장 시간이 가장 느린 구간
    // size(): 모기의 마릿수
    priority_queue<pii, vector<pii>, _greater> pq;
    pii ans = {0, 0}; // 모기가 가장 많이 존재하는 구간
    int cnt = 0;      // 모기 마릿수 (가장 많은)
    for (const auto &curr : arr)
    {
        while (!pq.empty() && pq.top().r <= curr.l) // i번째 arr의 값이 이전 값(= pq.top())과 같거나 뒤에 있는 경우 (= 갱신해야 함)
            pq.pop();
        pq.push(curr);

        if (pq.size() > cnt) // 마릿수가 많아진 경우, 갱신
        {
            cnt = pq.size();
            ans = pii{curr.l, pq.top().r}; // 여기서 r은 pq.top().r(= 가장 빠른 퇴장 시간. 즉, h가 낮아지는 지점임)
        }
        else if (cnt == pq.size() && ans.r == curr.l) // 마릿수가 같으며 퇴장 시간 및 입장 시간이 같은 경우 서로 연결
            ans.r = curr.r;
    }

    cout << cnt << endl;
    cout << ans.l << " " << ans.r;
}

// 3
// 2 16
// 4 10
// 5 12

// 1차
// #include <iostream>
// #include <queue>

// using namespace std;

// #define endl "\n"

// struct pii
// {
//     int pos, state;
// };

// struct _greater
// {
//     bool operator()(const pii &a, const pii &b)
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

//     priority_queue<pii, vector<pii>, _greater> q;
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
//         pii curr = q.top();
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