/* 
 * 20440 ๐ต๋๊ฐ ์ซ์ด ์ซ์ด ๋๋ฌด ์ซ์ด ์ซ์ด ์ค์ง ๋ง ๋ด๊ฒ ์ฐ์ฉ๋์ง๋ง๐ต - 1
 * ๋์  ํฉ
 * ์๊ฐ ๋ณต์ก๋: ?
 * ๋ฌธ์ : https://www.acmicpc.net/problem/20440
 * ETC.) ์ฒ์์ pq์ ์์ฅ ์๊ฐ๊ณผ ํด์ฅ ์๊ฐ์ ๋๋์ด ๊ฐ์ ๋ฃ๊ณ  ํด๊ฒฐํ๋ ค๊ณ  ํ์ง๋ง [4 6] - [6 10]๊ณผ ๊ฐ์ ์ด์ด์ง๋ ํํ์ ๊ฒฝ์ฐ๋ฅผ ํด๊ฒฐํ์ง ๋ชปํจ.
 * 1) ์๋ ฅ๋ฐ์ ์๊ฐ๋ค์ ์์์ ๊ธฐ์ค์ผ๋ก ์ค๋ฆ์ฐจ ์ ๋ ฌ ํ, ์์ฐจ์ ์ผ๋ก ์ด์ฉ.
 * 2-1) ํ์ฌ ์๊ฐ๋๊ฐ ์ด์  ์๊ฐ๋์ ๊ฒน์น๋ ๊ตฌ๊ฐ์ด ์๋ ๊ฒฝ์ฐ (= ๋ชจ๊ธฐ๊ฐ ์ด์  ์๊ฐ๋๋ณด๋ค +1)
 * - ๊ฒน์ณ์ง๋ ๊ตฌ๊ฐ์ ์ ์ฅํ๋ฉฐ ๋ชจ๊ธฐ์ ๋ง๋ฆฟ์ +1
 * 2-2) ํ์ฌ ์๊ฐ๋๊ฐ ์ด์  ์๊ฐ๋์ ๊ฒน์น์ง ์์ผ๋ฉด์ ์๋ก ๋ถ์ด์๋ ๊ฒฝ์ฐ (= prev.r == curr.l)
 * - ๊ตฌ๊ฐ์ ๊ธธ์ด๋ฅผ ๋๋ฆผ
 * 2-3) ํ์ฌ ์๊ฐ๋๊ฐ ์ด์  ์๊ฐ๋์ ๊ฒน์น์ง ์์ผ๋ฉด์ ์๋ก ๋จ์ด์ ธ ์๋ ๊ฒฝ์ฐ (= prev.r != curr.l)
 * - ๋๊น
 * ์ฐธ๊ณ : https://velog.io/@bgg01578/%EB%B0%B1%EC%A4%80-20440 (์ฝ๋ ํด์)
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

bool cmp(const pii &a, const pii &b) { return a.l < b.l; } // ์ค๋ฆ์ฐจ์ (์์ฅ ์๊ฐ ๊ธฐ์ค. ๋น ๋ฅธ ๊ฐ์ด ์์ผ๋ก)

struct _greater // ์ค๋ฆ์ฐจ์ (ํด์ฅ ์๊ฐ ๊ธฐ์ค. ๋น ๋ฅธ ๊ฐ์ด ์์ผ๋ก)
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

    // top(): ์๋ ฅ๋ ์๊ฐ๋๋ค ์ค ๋ชจ๊ธฐ๊ฐ ๊ฐ์ฅ ๋ง์ผ๋ฉด์ ์์ฅ ๋ฐ ํด์ฅ ์๊ฐ์ด ๊ฐ์ฅ ๋๋ฆฐ ๊ตฌ๊ฐ
    // size(): ๋ชจ๊ธฐ์ ๋ง๋ฆฟ์
    priority_queue<pii, vector<pii>, _greater> pq;
    pii ans = {0, 0}; // ๋ชจ๊ธฐ๊ฐ ๊ฐ์ฅ ๋ง์ด ์กด์ฌํ๋ ๊ตฌ๊ฐ
    int cnt = 0;      // ๋ชจ๊ธฐ ๋ง๋ฆฟ์ (๊ฐ์ฅ ๋ง์)
    for (const auto &curr : arr)
    {
        while (!pq.empty() && pq.top().r <= curr.l) // i๋ฒ์งธ arr์ ๊ฐ์ด ์ด์  ๊ฐ(= pq.top())๊ณผ ๊ฐ๊ฑฐ๋ ๋ค์ ์๋ ๊ฒฝ์ฐ (= ๊ฐฑ์ ํด์ผ ํจ)
            pq.pop();
        pq.push(curr);

        if (pq.size() > cnt) // ๋ง๋ฆฟ์๊ฐ ๋ง์์ง ๊ฒฝ์ฐ, ๊ฐฑ์ 
        {
            cnt = pq.size();
            ans = pii{curr.l, pq.top().r}; // ์ฌ๊ธฐ์ r์ pq.top().r(= ๊ฐ์ฅ ๋น ๋ฅธ ํด์ฅ ์๊ฐ. ์ฆ, h๊ฐ ๋ฎ์์ง๋ ์ง์ ์)
        }
        else if (cnt == pq.size() && ans.r == curr.l) // ๋ง๋ฆฟ์๊ฐ ๊ฐ์ผ๋ฉฐ ํด์ฅ ์๊ฐ ๋ฐ ์์ฅ ์๊ฐ์ด ๊ฐ์ ๊ฒฝ์ฐ ์๋ก ์ฐ๊ฒฐ
            ans.r = curr.r;
    }

    cout << cnt << endl;
    cout << ans.l << " " << ans.r;
}

// 3
// 2 16
// 4 10
// 5 12

// 1์ฐจ
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