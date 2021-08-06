/* 
 * 2696 중앙값 구하기
 * priority_queue (우선순위 큐)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2696
 * ETC.) top()과 동일한 값이 입력으로 들어왔을 때에 대한 처리를 안해줘서 하루종일 해맴.
 * - 풀이 -
 * 1) 좌측과 우측 큐가 있으며, 왼쪽은 작은 값 및 내림차순, 우측은 큰 값 및 오름차순이다.
 * 2) 좌측 큐의 크기는 우측 큐보다 같거나 +1이어야 한다.
 * 3) 들어오는 값이 좌측 큐의 top(= 중앙값)보다 작은 경우 좌측으로, 그 외(= 같거나 큼)의 경우 우측으로 넣어 줌.
 * 3-1) 만약 넣은 직후 2번에 위배되는 경우, 수를 맞춰줌. (좌측이 많을 경우 좌측 top값을 우측으로 넘기며, 우측이 많은 경우 우측 top값을 좌측으로 넘겨줌)
 * 이후 반복하며, 자동으로 중앙값은 좌측 큐의 top값이 된다.
 * TC: http://acmgnyr.org/year2009/problems.shtml (문제가 백준과 다른 점이 있기 때문에, TC 입력 시 주의)
 */

#include <iostream>
#include <queue>
using namespace std;

#define endl "\n"

struct cmp
{
    bool operator()(const int a, const int b) { return a > b; }; // 큰 값이 앞으로 (= 내림차순)
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        cout << (n >> 1) + 1 << endl;

        int cnt = 0;                             // 출력 횟수
        priority_queue<int> l;                   // top(): 작은 값들 중 최댓값
        priority_queue<int, vector<int>, cmp> r; // top(): 큰 값들 중 최솟값
        for (int i = 1; i <= n; i++)
        {
            int k;
            cin >> k;

            if (l.empty() || k < l.top()) // 첫 입력 or 중앙값보다 작은 값일 경우, 왼쪽에 넣어 줌
                l.push(k);
            else // 그 외 (= 좌측 top과 동일 or 큰 값)
                r.push(k);

            int cmp_size = l.size() - r.size(); // ?? if문 안에 변수가 아닌 직접 넣으면 제대로된 결과가 나오지 않음. 왜??
            if (cmp_size > 1)
                r.push(l.top()), l.pop();
            else if (cmp_size < 0)
                l.push(r.top()), r.pop();

            if (i & 1) // 입력 횟수가 홀수인 경우, 출력
            {
                cout << l.top() << " ";
                if (++cnt == 10) // 출력 횟수를 세며, 10번째일 경우 개행문자 출력
                    cnt = 0, cout << endl;
            }
        }
        cout << endl;
    }
}