/*
    실패율 (코딩테스트 연습 > 2019 KAKAO BLIND RECRUITMENT > 실패율)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/42889
    풀이)
    - 전체 인원을 구해줌.
    - 해당 스테이지에 몇 명의 인원이 존재하는지를 파악함.
    - 실페율은 [스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수 / 스테이지에 도달한 플레이어 수]이다.
     - 현재 스테이지에 존재하는 인원은 도달했지만 클리어하지 못한 인원이다. (분자)
     - 전체 인원에서 이전 스테이지의 인원을 빼주게 된다면 스테이지에 도달한 수가 된다. (분모)
     이를 이용해 실패율을 구해준다.
    - 실패율을 구할 때 주의할 점은, 남은 스테이지는 있지만 인원이 없을 수도 있다. (= total == 0)
    이는 k/0이 될 수 있으므로 예외 처리를 해줘야 한다.
    etc.) cmp에서 비교를 p1 > p1처럼 해놓고서 tc찾느라 고생한 문제..
 */

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages)
{
    vector<int> arr(N + 1 + 1, 0); // arr[i] = 3일 때, i층의 인원은 3명 (stages의 원소는 N+1 이하의 자연수이므로 +1)
    for (const auto &elem : stages)
        arr[elem]++;

    vector<pair<int, double>> v; // {층, 실패율}
    int total = stages.size();   // i층까지 도달한 인원
    for (int i = 1; i <= N; i++) // 1층부터 N층까지
    {
        int curr = arr[i]; // 현재 층에 있는 인원
        double k;          // 실패율
        if (total == 0)
            k = 0;
        else
            k = (double)curr / total;
        v.push_back({i, k});
        total -= curr; // 현재 인원은 다음 층에 존재할 수 없음
    }

    sort(v.begin(), v.end(), [&](const pair<int, double> &p1, const pair<int, double> &p2)
         {if (p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second > p2.second; });

    vector<int> answer;
    for (const auto &[i, k] : v)
        answer.push_back(i);

    return answer;
}

// void print_ans(const vector<int> &ans);
// #include <iostream>
// #define endl "\n"
// int main()
// {
//     print_ans(solution(5, {2, 1, 2, 6, 2, 4, 3, 3})); // 3 4 2 1 5
//     print_ans(solution(4, {4, 4, 4, 4, 4}));          // 4 1 2 3
//     print_ans(solution(5, {2, 1, 2, 4, 2, 4, 3, 3})); // 4 3 2 1 5
//     print_ans(solution(5, {1, 2, 2, 2, 2, 2, 2}));    // 2 1 3 4 5
//     print_ans(solution(4, {1, 2, 3, 2, 1}));          // 3 2 1 4
// }
// void print_ans(const vector<int> &ans)
// {
//     for (const auto &elem : ans)
//         cout << elem << " ";
//     cout << endl;
// }