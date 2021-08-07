// 두 번째 시간 초과..
/* 
 * 21939 문제 추천 시스템 Version 1
 * priority_queue
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/21939
 * ETC.) pq를 선언해 값을 저장.
 * 추가의 경우 pq에 추가
 * 제거의 경우 값을 하나 씩 다른 컨테이너로 옮기며 검사하여 제거
 * 출력의 경우 front는 top을 출력하며, back인 경우 다른 컨테이너로 옮기며 마지막 값을 출력
 * move 사용
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define endl "\n"

struct Info
{
    int P, L;
};

struct cmp
{
    bool operator()(const Info &p1, const Info &p2)
    {
        if (p1.L == p2.L)
            return p1.P < p2.P;
        return p1.L < p2.L;
    }
};

int recommended(const priority_queue<Info, vector<Info>, cmp> &pq)
{
    int x; // 1 or -1
    cin >> x;

    if (x == 1)
        return pq.top().P;
    else // if (x == -1)
    {
        priority_queue<Info, vector<Info>, cmp> temp = pq;
        while (!(temp.size() == 1))
            temp.pop();
        return temp.top().P;
    }
}
void added(priority_queue<Info, vector<Info>, cmp> &pq)
{
    int p, l; // 1 <= P <= 100k, 1 <= L <= 100
    cin >> p >> l;

    pq.push({p, l});
}
void solved(priority_queue<Info, vector<Info>, cmp> &&pq)
{
    priority_queue<Info, vector<Info>, cmp> temp = move(pq);

    int p;
    cin >> p;

    while (!temp.empty())
    {
        if (temp.top().P == p)
        {
            temp.pop();
            continue;
        }
        pq.push(temp.top()), temp.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    priority_queue<Info, vector<Info>, cmp> pq;
    for (int i = 0; i < n; i++)
    {
        int p, l;
        cin >> p >> l;
        pq.push({p, l});
    }

    int m; // 1 <= 10k
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string cmd;
        cin >> cmd;

        char c = cmd[0];
        if (c == 'r')
            cout << recommended(pq) << endl;
        else if (c == 'a')
            added(pq);
        else if (c == 's')
            solved(move(pq));
    }
}