// 2023-03-02
// 27659 Queue skipping (Easy) 
// https://www.acmicpc.net/problem/27659
/*
    덱 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - n개의 수가 순서대로 들어 있는 덱을 생성 후, 입력된 k를 찾아 제거 후 앞에 삽입.
    이후, 덱에 존재하는 마지막 원소를 출력.
 */

#include <iostream>
#include <deque>

using namespace std;

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, e;
        cin >> n >> e;

        deque<int> dq;
        for (int i = 1; i <= n; i++)
            dq.push_back(i);

        for (int i = 0; i < e; i++)
        {
            int k;
            cin >> k;
            int pos = 0;
            while (dq[pos] != k)
                pos++;
            dq.erase(dq.begin() + pos), dq.push_front(k);
        }

        cout << dq.back() << '\n';
    }
}