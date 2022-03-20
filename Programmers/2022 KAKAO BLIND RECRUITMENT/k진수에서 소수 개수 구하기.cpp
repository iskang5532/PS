// k진수에서 소수 개수 구하기 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > k진수에서 소수 개수 구하기)
// https://programmers.co.kr/learn/courses/30/lessons/92335
/*
    sol.1) 구현, 수학
    시간 복잡도: ?
    풀이)
    1. 입력된 값 n을 k진수로 변환해 s에 저장.
    2. s 전체를 탐색하며, 0 혹은 시작점에서부터 다음 0 혹은 마지막 위치까지의 값을 str에 저장.
    3. num이 소수인지를 판별하며, 소수일 경우 ans++.
    주의할 점은, 뽑아낸 값 num이 int 자료형의 표현 범위를 벗어날 수 있으므로 long long을 사용.
    etc.) 에라토스테네스의 체를 이용할 수 있다고 하는데, 범위를 벗어난 게 아닌가?
    - 0인 구간에서 소수인지를 판별함. 만약 마지막 값이 0이 아닐 경우, 해당 구간의 값은 소수인지 판별하지 않게 됨.
    그러므로, 마지막에 num이 소수인지를 판별해줌. (단, num이 존재해야 함)
    참고)
    - 문제해설: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string conv(int n, int k)
{
    string ret;
    while (n)
        ret.push_back(n % k + '0'), n /= k; // k진수로 변환
    reverse(ret.begin(), ret.end());        // 가장 큰 자릿수부터 입력이 되어 있으므로 뒤집어줌

    return ret;
}

bool isPrime(ll k)
{
    if (k == 1)
        return false;
    for (ll i = 2; i <= sqrt(k); i++)
        if (k % i == 0)
            return false;

    return true;
}

int solution(int n, int k)
{
    string s = conv(n, k);

    int ans = 0;
    string num;
    for (int i = 0; i < s.length(); i++)
        if (s[i] - '0' != 0) // 구간을 탐색
            num.push_back(s[i]);
        else
        {
            if (num.size() && isPrime(stoll(num)))
                ans++;
            num.clear();
        }
    if (num.size() && isPrime(stoll(num))) // 마지막 구간을 추가
        ans++;

    return ans;
}

// int main()
// {
//     cout << solution(437674, 3) << '\n';  // 3
//     cout << solution(110011, 10) << '\n'; // 2
// }

/*
    sol.2)
    시간 복잡도: ?
    풀이)
    - k진수로 변환한 문자열 s에서 '0'을 ' '으로 변환한 후, stringstream을 사용하여 수를 뽑아냄.
    참고)
    - 문제해설: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
    - 문자열 변경 풀이 참고: https://blog.naver.com/jinhan814/222621802463
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string conv(int n, int k)
{
    string ret;
    while (n)
        ret.push_back(n % k + '0'), n /= k; // k진수로 변환
    reverse(ret.begin(), ret.end());        // 가장 큰 자릿수부터 입력이 되어 있으므로 뒤집어줌

    return ret;
}

bool isPrime(ll k)
{
    if (k == 1)
        return false;
    for (ll i = 2; i <= sqrt(k); i++)
        if (k % i == 0)
            return false;

    return true;
}

int solution(int n, int k)
{
    string s = conv(n, k);
    for (auto &c : s)
        if (c == '0')
            c = ' ';

    int ans = 0;
    stringstream ss(s);
    string num;
    while (ss >> num)
        if (isPrime(stoll(num)))
            ans++;

    return ans;
}

// int main()
// {
//     cout << solution(437674, 3) << '\n';  // 3
//     cout << solution(110011, 10) << '\n'; // 2
// }