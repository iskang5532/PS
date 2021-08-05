/* 
 * 16120 PPAP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/16120
 * ETC.) 문자열이 PPAPPPAP와 같이 여러 개의 PPAP가 있어도 PPAP인 줄 알았는데 아니었음. (덕분에 오래 걸림)
 * 입력받은 문자열에 대해 앞에서부터 문자를 하나 씩 빼내며, 빼낸 문자열이 "PPAP"가 되었을 경우, 'P'로 변경해줌.
 * 참고: 
 */

#include <iostream>

using namespace std;

#define endl "\n"
#define PPAP_len 4

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string str; // len: 1 <= 1M
    cin >> str; // 'P' or 'A'

    string answer = "";
    for (const auto &c : str)
    {
        answer += c;                                                 // 문자를 하나 넣어 줌
        if (answer.length() >= PPAP_len &&                           // PPAP의 길이 이상인 경우
            string(answer.end() - PPAP_len, answer.end()) == "PPAP") // ans의 뒷 네 글자가 PPAP인 경우
        {
            for (int i = 0; i < PPAP_len; i++) // 네 번 빼냄
                answer.pop_back();
            answer += "P"; // 빼낸 자리에 P를 넣어 줌
        }
    }

    cout << (answer == "P" ? "PPAP" : "NP");
}