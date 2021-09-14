/* 
 * 1406 에디터
 * stack
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1406
 * ETC) 스택을 이용한 풀이. 왼쪽과 우측 스택을 사용하며, 왼쪽으로 이동 시 좌측 top()을 오른쪽으로 옮기며, 우측 이동 시 우측 top()을 왼쪽으로 옮김.
 * 여기서 주의사항은, 좌측 스택의 값은 front에서부터 출력해야 하지만, 우측 스택은 top()부터 출력해야 함. (= 오른쪽은 그냥 출력해도 되지만, 왼쪽은 뒤집어 출력해야 함)
 * 때문에 모든 명령이 완료된 후, 좌측 스택을 우측 스택에 쌓은 후(= 뒤집어짐) 우측 스택의 값을 전원 출력하는 형식으로 했음.
 * 참고: https://kih0902.tistory.com/28
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string str; // <= 100k (len)
    cin >> str;

    stack<char> left, right;  // 왼쪽과 우측 스택
    for (const auto &c : str) // 좌측 스택의 값에 모두 넣음
        left.push(c);

    int m; // 1 <= 500k
    cin >> m;
    while (m--)
    {
        char cmd;
        cin >> cmd;
        switch (cmd)
        {
        case 'L': // --
            if (!left.empty()) // 좌측 스택에 값이 있는 경우 (= 우측 스택에 값을 옮길 수가 있는 경우)
            {
                right.push(left.top());
                left.pop(); // 옮기고 나서 제거
            }
            break;
        case 'D': // ++
            if (!right.empty()) // 우측 스택에 값이 있는 경우 (= 좌측 스택에 값을 옮길 수가 있는 경우)
            {
                left.push(right.top());
                right.pop(); // 옮기고 나서 제거
            }
            break;
        case 'B': // pop
            if (!left.empty()) // 좌측 스택에 값이 있는 경우
                left.pop();    // 좌측 스택의 값 제거
            break;
        case 'P': // push
        {
            char c;
            cin >> c;
            left.push(c);
            break;
        }
        }
    }

    // right에 몰빵함 (= left값을 옮김)
    auto moved_to = [&](stack<char> &right, stack<char> &left)
    {
        while (!left.empty())
        {
            right.push(left.top());
            left.pop();
        }
    };

    // 값을 출력함
    auto print = [&](stack<char> &st)
    {
        while (!st.empty())
        {
            cout << st.top();
            st.pop();
        }
    };

    moved_to(right, left);
    print(right);
}