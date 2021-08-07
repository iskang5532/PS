// 첫 번째 시간 초과..
/* 
 * 21939 문제 추천 시스템 Version 1
 * vector
 * 시간 복잡도: 최악의 경우 O(m * nlogn)??
 * 문제: https://www.acmicpc.net/problem/21939
 * 참고: find 사용. (vector 속 pair에 대한 find)
 * https://www.codegrepper.com/code-examples/cpp/find+in+set+of+pairs+using+first+value+cpp (pair find)
 * https://notepad96.tistory.com/entry/C-Vector-%EA%B0%92-%ED%83%90%EC%83%89-find-%EC%A1%B4%EC%9E%AC-%EC%9C%A0%EB%AC%B4-%ED%99%95%EC%9D%B8 (find)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

struct Info
{
    int P, L;
};

bool cmp(const Info &p1, const Info &p2)
{
    if (p1.L == p2.L)
        return p1.P > p2.P;
    return p1.L > p2.L;
}

int recommended(const vector<Info> &arr)
{
    int answer = 0;

    int x; // 1 or -1
    cin >> x;
    if (x == 1)
        answer = arr.front().P;
    else if (x == -1)
        answer = arr.back().P;

    return answer;
}
void added(vector<Info> &arr)
{
    int p, l; // 1 <= P <= 100k, 1 <= L <= 100
    cin >> p >> l;

    arr.push_back({p, l});
    sort(arr.begin(), arr.end(), cmp);
}
void solved(vector<Info> &arr)
{
    int p;
    cin >> p;

    // vector<Info>::iterator
    auto it = find_if(arr.begin(), arr.end(),
                      [&](const Info &p1)
                      { return p1.P == p; });
    arr.erase(it);

    // arr.erase(find_if(arr.begin(), arr.end(),
    //                   [&](const Info &p1)
    //                   { return p1.L == k; }));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    vector<Info> arr(n);
    for (auto &elem : arr)
        cin >> elem.P >> elem.L; // 1 <= P <= 100k, 1 <= L <= 100
    sort(arr.begin(), arr.end(), cmp);

    int m; // 1 <= 10k
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string cmd;
        cin >> cmd;

        char c = cmd[0];
        if (c == 'r')
            cout << recommended(arr) << endl;
        else if (c == 'a')
            added(arr);
        else if (c == 's')
            solved(arr);
    }
}