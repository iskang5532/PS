/*
    멀쩡한 사각형 (코딩테스트 연습 > Summer/Winter Coding(2019) > 멀쩡한 사각형)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/62048?language=cpp
    etc.) 약 90분 정도 걸린 문제. 규칙을 깨닫기까지 너무 오래 걸림. 게다가 다른 분들의 풀이를 보니 보기 더 편한 규칙이 있었다.
    - 제거할 블럭(= idx)의 개수를 찾음.
    - 패턴(= idx)이 반복되는 경우, 하나의 패턴에 대한 idx값을 구하여 패턴의 횟수만큼 곱하여 최종적인 idx값을 구함. (여기서 최대공약수를 이용)
    - idx 구하기
     - 각 모서리에서 시작하기 때문에 모서리에 대한 idx값을 제거해준다. 이는 min(w, h)개이다.
     - 만약 w == h인 경우, 최대공약수를 구해 w == h == 1이 되어 idx값이 구해질 것이다.
     - 만약 w != h인 경우, 대각선을 긋다 보면 1번 열에서 2번 열로 이동할 때가 있으며 이때의 idx는 +2가 된다.
     즉, 이동해야 할 열의 횟수인 w-1번을 2로 곱한 값을 idx에 추가해준다.
 */

#include <string>
#include <vector>
#include <algorithm> // abs

using namespace std;

typedef long long ll;

ll get_gcd(ll a, ll b)
{
    while (b != 0)
    {
        ll r = a % b;
        a = b;
        b = r;
    }

    return a;
}

ll solution(int w, int h)
{
    ll answer = 1LL * w * h;

    if (w > h) // w값이 더 작게
        swap(w, h);

    ll mul = 1;
    ll gcd = get_gcd(w, h); // 반복되는 횟수를 구하기 위한 최대공약수
    w /= gcd, h /= gcd, mul *= gcd;

    ll idx = 2 + abs(w - h) - 1; // 제거되는 블럭의 개수 (각 꼭지점의 개수 및 크기가 커질 때 +1)
    if (w != h)
        idx += (w - 1) * 2; // 다음 열로 바뀌는 구간의 개수 (= 2개씩)

    answer -= (idx * mul); // 반복되는 횟수만큼

    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(8, 12) << endl;               // 80
//     cout << solution(99999999, 100000000) << endl; // 9'999'999'700'000'002
// }