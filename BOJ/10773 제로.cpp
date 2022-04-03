// 10773 제로
// https://www.acmicpc.net/problem/10773
/*
    스택 (2,548KB, 8ms)
    시간 복잡도: ?
    풀이)
    - FILO 형식으로 값을 저장할 스택 st.
    - 입력된 값 k가 0일 경우, st에서 값을 빼줌. (조건에 의해 k가 0인 경우는 스택에 값이 존재함이 보장됨)
    - 입력된 값 k가 자연수일 경우, st에 값을 넣음.
    - n개의 입력을 마친 경우, st에 존재하는 값의 합을 출력.
    etc.) 기본적인 스택 문제인듯
 */

#include <iostream>
#include <stack>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n; // 1 ≤ ㅜ ≤ 100,000
    cin >> n;

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        int k; // 1 ≤ k ≤ 1,000,000
        cin >> k;
        if (k == 0)
            st.pop();
        else
            st.push(k);
    }

    int ans = 0;
    while (st.size())
        ans += st.top(), st.pop();

    cout << ans;
}