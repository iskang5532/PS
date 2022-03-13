/*
    [1차] 추석 트래픽 (코딩테스트 연습 > 2018 KAKAO BLIND RECRUITMENT > [1차] 추석 트래픽)
    Sliding Window
    시간 복잡도: O(n*1000) (슬라이딩 윈도우에서의 시간 복잡도)
    문제: https://programmers.co.kr/learn/courses/30/lessons/17676?language=cpp
    etc.) 구현이 어려웠던 문제였으며, tc가 잘 주어져서 반례찾기 없이 끝냈음.
    - 입력된 초가 소숫점 세 자릿수까지 가능하므로 단위를 s에서 ms로 바꿔줌.
    - 모든 시간대를 ms로 바꿨을 때의 값은 10^9 미만이기 때문에 슬라이딩 윈도우로 접근.
    - 주어지는 응답완료시간의 값이 00:00:00.000일 때 ms로 바꿀 시 0이 된다. 이때 처리시간 T를 빼 시작시간을 구하게 된다면 음수의 값이 나온다.
    이를 방지하기 위해 T의 최댓값인 3000ms를 더해 음수가 나올 수 없게 해준다.
    - 시작시간과 완료시간, 처리시간을 구하게 되었다면 0부터 1day+3s까지 1s의 간격을 두며 조사한다.
    - 만약 1000ms의 구간에 시작시간과 완료시간이 들어오게 되는 순간을 저장한다.
 */

#include <string>
#include <sstream>
#include <queue>

using namespace std;
#define ms 1000 // 바꿀 단위
#define MAX (86'400 + 3) * ms

int solution(vector<string> lines)
{
    priority_queue<int, vector<int>, greater<int>> pq_start, pq_end; // 시작시간과 완료시간을 저장
    for (const auto &line : lines)
    {
        stringstream ss(line);
        string ymd, t1, t2;
        ss >> ymd >> t1 >> t2;

        int hh = stoi(t1.substr(0, 2)) * ms,
            mm = stoi(t1.substr(3, 2)) * ms,
            ss_sss = stod(t1.substr(6, 10)) * ms;
        double process_time;
        stringstream t3(t2);
        t3 >> process_time, process_time *= ms;

        int idx = 3 * ms; // 응답완료시간의 최솟값(09-15-00:00:00)에서 T의 최댓값(3)을 뺄 시 날짜가 이 전날로 바뀔 수 있으므로 시간대를 우측으로 3초 옮김
        int end = ((hh * 3600) + (mm * 60) + ss_sss + idx),
            start = end - process_time + 1; // 처리시간은 끝시간(= 응답완료시간)을 포함하므로 +1ms
        pq_start.push(start), pq_end.push(end);
    }

    int ans = 0;
    for (int l = 0, r = 1 * ms, cnt = 0; r <= MAX; l++, r++) // 슬라이딩 윈도우
    {
        while (!pq_start.empty() && r >= pq_start.top()) // 범위 안에 들어오게 된 경우
            cnt++, pq_start.pop();
        while (!pq_end.empty() && l >= pq_end.top()) // 범위 밖으로 나간 경우
            cnt--, pq_end.pop();

        ans = max(ans, cnt);
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
// cout << solution({"2016-09-15 01:00:04.001 2.0s", // 1
//                   "2016-09-15 01:00:07.000 2s"})
//      << endl;
// cout << solution({"2016-09-15 01:00:04.002 2.0s", // 2
//                   "2016-09-15 01:00:07.000 2s"})
//      << endl;
// cout << solution({"2016-09-15 20:59:57.421 0.351s", // 7
//                   "2016-09-15 20:59:58.233 1.181s",
//                   "2016-09-15 20:59:58.299 0.8s",
//                   "2016-09-15 20:59:58.688 1.041s",
//                   "2016-09-15 20:59:59.591 1.412s",
//                   "2016-09-15 21:00:00.464 1.466s",
//                   "2016-09-15 21:00:00.741 1.581s",
//                   "2016-09-15 21:00:00.748 2.31s",
//                   "2016-09-15 21:00:00.966 0.381s",
//                   "2016-09-15 21:00:02.066 2.62s"})
//      << endl;
// cout << solution({"2016-09-15 00:00:00.000 3s"}) // 1
//      << endl;
// cout << solution({"2016-09-15 23:59:59.999 0.001s"}) // 1
//      << endl;
// cout << solution({"2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s"}) // 2
//      << endl;
// }