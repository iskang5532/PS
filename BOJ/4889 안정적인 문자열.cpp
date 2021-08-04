/* 
 * 4889 안정적인 문자열
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/4889
 * ETC.) 먼저 일반적인 인풋(ex. {{{})에 대해 고민을 한 이후에 이레귤러 인풋(ex. }}{{)에 대한 처리를 고민하는 것이 좋은 듯
 * 참고: https://blog.naver.com/jinhan814/222130110021 (코드를 보며 이해함)
 */

#include <iostream>
#include <stack>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string str;
    for (int i = 1; cin >> str && str[0] != '-'; i++) // 입력
    {
        int cnt = 0, answer = 0; // cnt는 괄호의 개수를 의미. (양수는 열린 괄호를, 음수는 닫힌 괄호)
        for (const auto &c : str)
        {
            if (cnt == 0 && c == '}') // 첫 번째 값이 닫힌 괄호인 경우, 여는 괄호로 바꿔줌 (= 횟수 +1, 열린 괄호 개수 +1)
                answer++, cnt++;
            else if (c == '{') // 열린 괄호일 경우 +1
                cnt++;
            else if (c == '}') // 닫힌 괄호일 경우 -1
                cnt--;
        }
        answer += cnt / 2; // 열린 괄호의 절반을 닫힌 괄호로 바꿔주면 안정적인 문자열이 되므로, 개수의 절반을 횟수에 더해줌
        cout << i << ". " << answer << endl;
    }
}

// ans: 4
// }}}{{{