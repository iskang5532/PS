// 2022-12-16
// 4900 7 더하기
// https://www.acmicpc.net/problem/4900
/*
    문자열 (2,032KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 7 세그먼트로 수를 만들 수 있는 2진수를 맵에 저장하여 사용. (여기서 2진수란, 7 세그먼트로 만드는 수에 필요한 값)
    - 입력된 문자열에서 '+', '='를 포함하지 않는 문자열을 3개씩 뽑아 한 자릿수의 10진수로 변환하여 값을 num에 저장.
    - '+' 혹은 '='가 나온 경우, num에 저장된 값을 sum에 더함.
    - sum에 저장된 10진수를 문자열로 변환 후, 각 숫자를 2진수로 변환.
    변환된 2진수는 세 자릿수여야 함. 부족한 경우, 앞에서부터 '0'을 채움.
    변환된 값을 ans에 추가.
    - 처음에 입력된 문자열 s과 s를 이용하여 구한 ans를 출력.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

constexpr int l = 3; // 탐색할 문자열의 길이 (= 10진수 코드의 길이)

const map<int, int> conv = { // conv[d] = b일 경우, 2진수 d는 10진수 b, conv[b] = d일 경우 10진수 b는 2진수 d
    // d to b
    {0b0111111, 0},
    {0b0001010, 1},
    {0b1011101, 2},
    {0b1001111, 3},
    {0b1101010, 4},
    {0b1100111, 5},
    {0b1110111, 6},
    {0b0001011, 7},
    {0b1111111, 8},
    {0b1101011, 9},

    // b to d
    {0, 0b0111111},
    {1, 0b0001010},
    {2, 0b1011101},
    {3, 0b1001111},
    {4, 0b1101010},
    {5, 0b1100111},
    {6, 0b1110111},
    {7, 0b0001011},
    {8, 0b1111111},
    {9, 0b1101011},
};

int _sum(const string &s)
{
    int ret = 0;

    string num;
    for (int pos = 0; s[pos] != '=';)
    {
        if (s[pos] == '+')
            ret += stoi(num), num.clear(), pos++;
        else // num
        {
            int k = conv.at(stoi(s.substr(pos, l)));
            num += k + '0';

            pos += l;
        }
    }

    return ret + stoi(num);
}

int main()
{
    FAST_IO;

    string s;
    while (cin >> s)
    {
        if (s == "BYE")
            break;

        int sum = _sum(s); // 입력된 문자열 속 수를 더함

        string ans;
        for (const char &c : to_string(sum)) // 10진수를 2진수로 변환
        {
            string num = to_string(conv.at(c - '0'));
            for (int i = 0; i < l - num.length(); i++) // '0' 채우기
                ans += '0';
            ans += num;
        }

        cout << s << ans << endl;
    }
}