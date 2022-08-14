// 2022-08-13
// 1863 스카이라인 쉬운거
// https://www.acmicpc.net/problem/1863
/*
    스택, 그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 가장 낮은 y값을 기준으로 인접한 x축들을 제거하며 올라간다.
    제거하며 올라가던 도중 x축에서 y축이 서로 다른 경우, 즉 높이가 서로 다른 경우 현재까지 제거한 y축이 하나의 빌딩이 된다.
    - 다른 y축의 개수만큼 위 행위를 반복하여 빌딩의 개수를 구한다.
    - 스택을 이용하여 위를 구현한다.
    - 스택 st의 상태에 따라 입력된 y를 넣거나 스택을 비운다.
     - 만약 y가 0이 아니면서, st가 비어있거나 y가 이전에 나온 빌딩의 높이 st.top()보다 크면 넣는다.
      스택에 저장된 값은 빌딩이 될 스카이라인이다. 그러나 0인 경우, 스카이라인이 없으며 이는 빌딩이 될 수 없다. 따라서 넣지 않는다.
      st.top()보다 y가 작은 경우는 이전까지 나온 스카이라인이 하나 이상의 빌딩이 된다.
     - 만약 y가 st.top()보다 작을 경우
      st.top()의 값을 뺀다. 이것이 하나의 빌딩이 된다.
      y가 0이 아니면서, st가 비어있거나 st.top()의 값이 y가 아닐 때 값을 넣는다.
      st.top()과 y가 달라야 하는 이유는, 같은 높이의 인접한 스카이라인은 같은 빌딩이 된다. 즉, 새로운 빌딩을 넣지 않는다.
    etc.) 스택을 이용해야 하는 걸 생각보다 빠르게 깨달음
    - 설명하기 매우 어려운듯
 */

#include <iostream>
#include <stack>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 50'003 // max n
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int ans = 0;
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;

        if (y != 0 && (st.empty() || st.top() < y)) // 0이 아니면서, 스택이 비어있거나 top보다 y가 더 큰 경우
            st.push(y);
        else
        {
            while (st.size() && y < st.top()) // top() < y가 될 때까지
                st.pop(), ans++;
            if (y != 0 && (st.empty() || st.top() != y)) // 0이 아니면서, 스택이 비어있거나 top()이 y와 다를 경우
                st.push(y);
        }
    }

    cout << ans + st.size();
}