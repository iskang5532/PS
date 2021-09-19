/* 
 * 14888 연산자 끼워넣기
 * next_permutation
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/14888
 * ETC) 이 문제는 연산자의 우선순위를 고려하지 않는 문제이다.
 * 그렇기에, 숫자 순열이 아닌 연산자 순열을 이용해야 한다. (숫자 순열일 경우 항상 앞에 둔 연산을 먼저 이용)
 */

#include <iostream>
#include <vector>
#include <algorithm> // next_permutation

using namespace std;

#define endl "\n"
#define INF 987654321

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 수의 개수 (2 <= 11)
    cin >> n;

    vector<int> arr(n); // 입력된 숫자 (1 <= Ai <= 100)
    for (auto &elem : arr)
        cin >> elem;

    int a, b, c, d; // 덧셈, 뺄셈, 곱셈, 나눗셈의 개수
    cin >> a >> b >> c >> d;
    vector<int> oper; // 연산자들을 저장할 공간
    for (int i = 0; i < a; i++)
        oper.push_back(1); // 덧셈
    for (int i = 0; i < b; i++)
        oper.push_back(2); // 뺄셈
    for (int i = 0; i < c; i++)
        oper.push_back(3); // 곱셈 *
    for (int i = 0; i < d; i++)
        oper.push_back(4); // 나눗셈 /

    int high = -INF, low = INF; // 최댓값 및 최솟값
    do
    {
        auto itr = arr.begin(); // n번째 숫자
        int num = *itr;         // 첫 번째 값을 넣음

        for (const auto &c : oper) // n번째 연산
            if (c == 1)      num += *(itr++); // +
            else if (c == 2) num -= *(itr++); // -
            else if (c == 3) num *= *(itr++); // *
            else if (c == 4) num /= *(itr++); // /

        high = max(high, num), low = min(low, num); // 최댓값 및 최솟값 갱신
    } while (next_permutation(oper.begin(), oper.end())); // 연산 순열

    cout << high << endl;
    cout << low << endl;
}