/*
    로또의 최고 순위와 최저 순위 (코딩테스트 연습 > 2021 Dev-Matching: 웹 백엔드 개발자(상반기) > 로또의 최고 순위와 최저 순위)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/77484?language=cpp#fn1
    풀이)
    - 맵을 이용한 풀이를 이용함.
    - 당첨 번호를 기억시킴 (맵의 특성을 생각한 배열 m. m[i] = true일 경우 숫자 i가 당첨 번호에 존재.)
    - 6위가 될 수 있는 경우는 1개 및 0개로 2개이며, 나머지는 1개이다. 이를 주의해서 풀어야 함.
    그러므로 최저 순위는 7위라고 가정.
    1) 민우의 로또에 적힌 숫자와 당첨 번호를 비교하여 맞춘 개수 및 0의 개수를 구함. (= cnt, z)
    2) 최고 순위 및 최저 순위를 구해줌.
    - 최저 순위는 값 7에서 맞춘 개수를 빼줌. (= 7 - cnt)
    - 최고 순위는 값 7에서 맞춘 개수 및 0의 개수를 빼줌. (= 7 - cnt - z)
    이떄 주의할 점은, 맞춘 개수개 1개 이하 혹은 맞춘 개수와 0의 개수의 합이 1개 이하일 때, 즉 6위가 되는 순간이다.
    위에서 최저 순위를 7로 값을 맞췄기에 연산 또한 7부터이다.
    그러므로 1개 혹은 0개일 때는 순위를 6, 7이 아닌 6위로 고정시켜줘야 한다. (= 예외 처리)
    etc.) 쉬운 문제라고 생각했지만 1개 이하의 번호가 일치했을 때의 순위 구현이 조금 힘들었음. 논리적으로 너무 약한듯..
 */

#include <vector>
using namespace std;
#define MAX 45 + 1 // 로또 번호의 최댓값

vector<int> solution(vector<int> lottos, vector<int> win_nums)
{
    bool m[MAX]; // 당첨 번호 여부 (m[i] = true일 경우 숫자 i가 당첨 번호에 존재)
    fill(m, m + MAX, false);

    for (const auto &elem : win_nums)
        m[elem] = true;

    int cnt = 0, z = 0; // 일치하는 숫자의 개수 cnt, 0의 개수 z
    for (const auto &elem : lottos)
        if (m[elem])
            cnt++;
        else if (elem == 0)
            z++;

    // 1개는 6위, 0개는 7위로 가정
    int hi = 7 - cnt - z; // 최고 순위 (맞춘 개수와 0의 개수를 빼줌)
    int lo = 7 - cnt;     // 최저 순위 (맞춘 개수를 빼줌)

    if (cnt + z <= 1) // 1개 이하인 경우 6위로 정정
        hi = 6;
    if (cnt <= 1)
        lo = 6;

    return {hi, lo};
}

// void print_ans(const vector<int> &arr);
// #include <iostream>
// #define endl "\n"
// int main()
// {
//     print_ans(solution({44, 1, 0, 0, 31, 25}, {31, 10, 45, 1, 6, 19})); //	{3, 5}
//     print_ans(solution({0, 0, 0, 0, 0, 0}, {38, 19, 20, 40, 15, 25}));  //	{1, 6}
//     print_ans(solution({45, 4, 35, 20, 3, 9}, {20, 9, 3, 45, 4, 35}));  //	{1, 1}
//     print_ans(solution({1, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6}));        //	{1, 6}
//     print_ans(solution({1, 2, 3, 4, 5, 6}, {11, 12, 13, 14, 15, 16}));  //	{6, 6} tc.14
// }
// void print_ans(const vector<int> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << endl;
// }