// 2022-09-16
// 1874 스택 수열
// https://www.acmicpc.net/problem/1874
/*
    스택 (3,308KB, 16ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수를 v[]에 저장하며, 현재 탐색 중인 v의 위치를 저장할 변수 pos.
    - 값의 추가 여부를 저장할 ans.
    - 1부터 n까지의 수를 스택 st에 저장.
    이후 스택의 top()값이 v[pos]와 같을 경우, 스택에서 값을 빼며 pos++ 및 '-' 추가.
    top() != v[pos]가 될 때까지 반복.
    - 입력된 수열을 만들 수 있다면, 스택에 값이 존재해서는 안 됨.
    만약 st.size()가 참일 경우, "NO"를 출력하며, 거짓일 경우 ans를 출력.
 */

#include <iostream>
#include <stack>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 100'003 // max n

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i];

    string ans;
    stack<int> st;
    for (int i = 1, pos = 0; i <= n; i++)
    {
        st.push(i), ans += "+\n";

        while (st.size() && st.top() == v[pos]) // 스택.top()이 수열(v[pos])에 필요한 값인 경우
            st.pop(), pos++, ans += "-\n";
    }

    cout << (st.size() ? "NO" : ans);
}
