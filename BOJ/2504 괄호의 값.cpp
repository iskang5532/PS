/* 
 * 2504 괄호의 값
 * stack
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2504
 * ETC.) 온전한 형태인가를 먼저 확인하는 코드을 작성 후, 연산을 수행하는 코드를 작성했음.
 * 여는 괄호가 하나 씩 증가할수록 층(= h)이 높아지며, 층에서 연산이 끝났을 경우(= 닫힌 괄호 입력) 아랫층(= h-1)에 값을 더해줌
 * 이후, 현재 층을 초기화함 (층에 값이 남을 경우, 차후 같은 층이 생성될 경우 기존 값으로 인해 연산된 값이 이상해짐)
 * - 개인적인 이해를 돕기 위한 예제) (()()) => _-ㅁㅁ-_ (각각 2층에서의 연산을 1층에 더해준 후, 1층에서 연산을 수행 후 정답(h == 0)을 산출)
 */

#include <iostream>
#include <stack>

using namespace std;

#define endl "\n"
#define MAX 30 // max len a str

bool is_valid(const stack<char> &st, const char c, bool &flag)
{
    if (st.empty() || st.top() != c) // 값을 제거해야 하는데 스택이 비었거나 온전한 형태가 아닌 경우
    {
        flag = true; // 플래그를 바꿔줌
        return false;
    }
    else
        return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string str;
    cin >> str;

    int num[MAX] = {0}; // num[n]일 때, n층에 존재하는 값 (= 연산이 완료된 값이며, n[0]이 구해야 할 값)
    bool flag = false;  // 유효하지 않을 경우 true로 변환
    stack<char> st;
    for (const auto &c : str)
    {
        int k, h = st.size();
        switch (c)
        {
        case '(':
            st.push('(');
            break;
        case '[':
            st.push('[');
            break;
        case ')':
            if (!is_valid(st, '(', flag))
                break;

            k = num[h] * 2; // 현재 층에 있는 값(기존 값)에 *2를 수행 후 변수에 저장
            if (k == 0)     // 만약 값이 0일 경우 (= h층에 존재하는 값이 없었음)
                k = 2;      // 2로 만듬 (= 연산의 종류는 '(x)'가 아닌 '()')

            num[h] = 0;      // 현재 층 초기화 (= 기존에 위에서 내려온 값들을 모두 사용한 것)
            num[h - 1] += k; // 연산된 값들을 내려 보냄
            st.pop();        // 괄호 사용
            break;
        case ']':
            if (!is_valid(st, '[', flag))
                break;

            k = num[h] * 3;
            if (k == 0)
                k = 3;

            num[h] = 0;
            num[h - 1] += k;
            st.pop();
            break;
        }
    }

    if (flag || !st.empty())
        cout << 0;
    else
        cout << num[0];
}

// ans: 0
// ([)]