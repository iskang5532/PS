/*
    수식 최대화 (코딩테스트 연습 > 2020 카카오 인턴십 > 수식 최대화)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/67257
    풀이)
    1) 주어진 문자열 expression을 숫자와 연산을 나눠 저장(= v) (숫자-연산-숫자-연산..)
    2) 연산자를 만들 수 있는 경우의 수를 모두 만듦. (= 조합)
    3) 문자열과 현재 사용할 연산자를 이용해 연산을 수행할 함수를 만들어 사용.
     - 문자열의 탐색은 [1]부터 하며, 값의 추가는 [i-1]을 추가한다. 추가로, 마지막 값은 for문의 밖에서 if문을 통해 넣어준다. (수행할 연산이 남아있거나 마지막 값이 사용되지 않은 경우)
     - 만약 현재 연산자가 사용될 연산자일 경우
      - 현재 연산자가 다음의 연산자와 같을 경우, 그다음의 연산자 또한 같은지 계속 확인하며 cnt++
      이는 현재 연산자가 사용할 연산자일 경우, 문자열의 숫자가 아닌 연산 된 숫자인 값을 넣어야 하므로 cnt를 이용해 제외할 문자열의 수를 세어줌.
     - 만약 현재 연산자가 사용될 연산자가 아닌 경우
      - [i-1]의 값은 이번 연산에서는 사용하지 않기 때문에 값을 저장함.
    4) 연산을 수행했을 때 v 안에 값이 없는 경우 (= 조금 전 연산으로 끝.)
     - 구해진 값에 절댓값을 취하여 ans와 비교 및 저장.
    이후 3)으로 돌아가 남아 있는 연산 순서 조합을 사용.
    etc.) 풀이가 너무 지저분하기도 하고 어거지로 풀린 느낌이 있음. 또한 어려운 문제는 아닌듯 싶은데 감이 쉽게 안잡혔음.
 */

#include <string>
#include <sstream> // stringstream
#include <vector>
#include <algorithm> // next_permutation

using namespace std;

typedef long long ll;

string do_calc(const vector<string> &v, char oper) // 문자열에서 현재 가능한 연산을 수행
{
    string ret;

    for (int i = 1; i < v.size(); i++) // 1부터 하는 이유는, [i]을 넣었는데 [1+1] 연산을 수행할 경우 [i]가 들어가면 안됨. (중간에 발생하면 골치아파짐)
    {
        if (v[i].front() == oper) // 현재 연산인 경우
        {
            int cnt = 1;                              // 수행할 연산의 횟수
            for (int j = i + 2; j < v.size(); j += 2) // 다음 연산자를 확인
                if (v[i].front() == v[j].front())     // 만약 현재 연산자와 같은 경우 (= 이 경우, 연산된 값을 재사용해야 함)
                    cnt++;
                else
                    break;

            ll k = stoll(v[i - 1]); // 연산을 수행하고 난 결괏값
            while (cnt--)
            {
                ll l = k, r = stoll(v[i + 1]); // 현재 연산자의 양 옆 값
                if (oper == '*')
                    k = l * r;
                else if (oper == '+')
                    k = l + r;
                else if (oper == '-')
                    k = l - r;
                i += 2; // 연산을 수행했으니 인접한 i-1, i, i+1의 볼일은 끝
            }

            ret += to_string(k);
        }
        else
            ret += v[i - 1]; // 이전 값을 넣어줌 (i = 1부터이므로)
    }

    if (v.size() >= 3 && v[v.size() - 2].front() != oper) // 연산이 끝나지 않았으며, 마지막 연산자를 사용하지 않았을 경우 (= 마지막 값은 보존되어 있음)
        ret += v.back();

    return ret;
}

ll solution(string expression)
{
    ll ans = 0;

    auto get_v = [&](const string &str) -> vector<string> // 숫자와 연산을 분리
    {
        vector<string> ret;

        int k;
        char c;
        stringstream ss(str);
        while (ss >> k >> c)
            ret.push_back(to_string(k)), ret.push_back(string() + c);
        ss >> k, ret.push_back(to_string(k));

        return ret;
    };

    string oper = "*+-";
    do
    {
        vector<string> v = get_v(expression); // 숫자와 연산을 분리하여 저장

        string str = expression; // 연산 과정에서의 문자열 (가능한 연산이 있을 경우, 연산을 수행한 문자열을 저장)
        for (int i = 0; i < 3; i++)
        {
            char curr = oper[i];
            str = do_calc(v, curr); // 연산 수행
            v = get_v(str);
            if (v.size() == 1) // 더 이상 실행할 연산이 없는 경우
            {
                ans = max(ans, llabs(stoll(str)));
                break;
            }
        }
    } while (next_permutation(oper.begin(), oper.end()));

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution("100-200-300-500-20") << endl;  //	920
//     cout << solution("11111-10-100-1-1000") << endl; //	1000
//     cout << solution("100-200*300-500+20") << endl;  //	60420
//     cout << solution("50*6-3*2") << endl;            //	300
// }