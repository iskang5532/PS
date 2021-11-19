/*
    광고 삽입 (코딩테스트 연습 > 2021 KAKAO BLIND RECRUITMENT > 광고 삽입)
    슬라이딩 윈도우, 구현
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/72414
    풀이)
    - 시분초를 초 단위로 바꿔주는 get_time 함수를 구현하여 사용. (편하도록)
    - 0초부터 광고의 길이까지 윈도우를 적용시킨 후, 영상의 길이만큼 슬라이딩 윈도우 시작.
     - 슬라이딩 윈도우 안에 영상이 들어온 경우, 슬라이딩 윈도우에 겹친 영상의 길이만큼 누적 재생 시간이 증가. (슬라이딩 윈도우 안에서의)
     - 슬라이딩 윈도우 밖으로 영상이 나간 경우, 슬라이딩 윈도우에 나간 영상의 길이만큼 누적 재생 시간이 감소. (슬라이딩 윈도우 안에서의)
    - 윈도우가 한 칸씩 움직일 때마다 윈도우 안에서의 누적 재생 시간의 값을 이전에 구했던 누적 재생 시간과 비교하며, 현재 값이 더 큰 경우 시작점 및 누적 재생 시간을 저장.
    etc.) 구현이 어려웠음. 이런 류의 문제 너무 어려워.
 */

#include <string>
#include <sstream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define HOUR 3600
#define MINUTE 60
typedef long long ll;
typedef pair<int, int> pii;

int get_time(const string &str) // 시간을 초단위로 변경
{
    stringstream ss(str);
    int h, m, s;
    char idx;
    ss >> h >> idx >> m >> idx >> s;
    return (h * HOUR) + (m * MINUTE) + s;
}

string solution(string play_time, string adv_time, vector<string> logs)
{
    int n = get_time(play_time);  // 동영상의 길이
    int len = get_time(adv_time); // 광고의 길이

    vector<int> v_start, v_end;
    for (const auto &log : logs)
    {
        int l = get_time(log.substr(0, 8));
        int r = get_time(log.substr(9, 8));

        v_start.push_back(l), v_end.push_back(r);
    }
    sort(v_start.begin(), v_start.end()), sort(v_end.begin(), v_end.end());

    int ans = 0;
    ll total = 0, mx = 0; // 윈도우 안에서의 누적 재생 시간 total, 모든 구간에서의 최대 누적 재생 시간 mx
    int cnt = 0;          // 해당 시간대에서의 증가량
    auto itr_s1 = v_start.begin(), itr_s2 = v_start.begin();
    auto itr_e1 = v_end.begin(), itr_e2 = v_end.begin();

    for (int l = 0, r = len; r <= n; l++, r++)
    {
        while (itr_s1 != v_start.end() && *itr_s1 < r) // 영상 시작점이 윈도우 안으로 들어온 경우 (= 윈도우 안에서의 누적 재생 시간 증가)
            cnt++, itr_s1++;
        while (itr_e1 != v_end.end() && *itr_e1 < r) // 영상 종료점이 윈도우 안으로 들어온 경우 (= 윈도우 안에서 누적할 시간이 없으므로 c--시켜 cnt값을 되돌림)
            cnt--, itr_e1++;
        while (itr_s2 != v_start.end() && *itr_s2 < l) // 영상 시작점이 윈도우 밖으로 나간 경우 (= 윈도우 안에서의 누적 재생 시간 감소)
            cnt--, itr_s2++;
        while (itr_e2 != v_end.end() && *itr_e2 < l) // 영상 끝점이 윈도우 밖으로 나간 경우 (= 윈도우 안에서 더 이상 감소할 누적 시간이 없으므로 c++시켜 cnt값을 되돌림
            cnt++, itr_e2++;

        total += cnt;
        if (mx < total)
            mx = total, ans = l;
    }

    string ret;
    ret += ans / HOUR / 10 + '0';
    ret += ans / HOUR % 10 + '0';
    ret += ":", ans %= HOUR;
    ret += ans / MINUTE / 10 + '0';
    ret += ans / MINUTE % 10 + '0';
    ret += ":", ans %= MINUTE;
    ret += ans / 10 + '0';
    ret += ans % 10 + '0';

    return ret;
}

// sol.2) 누적합
// 참고)
// - 이론: https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define HOUR 3600
#define MINUTE 60
typedef long long ll;
typedef pair<int, int> pii;

int get_time(const string &str) // 시간을 초단위로 변경
{
    stringstream ss(str);
    int h, m, s;
    char idx;
    ss >> h >> idx >> m >> idx >> s;
    return (h * HOUR) + (m * MINUTE) + s;
}

string solution(string play_time, string adv_time, vector<string> logs)
{
    int n = get_time(play_time);  // 동영상의 길이
    int len = get_time(adv_time); // 광고의 길이

    vector<int> v_start, v_end;
    for (const auto &log : logs)
    {
        int l = get_time(log.substr(0, 8));
        int r = get_time(log.substr(9, 8));

        v_start.push_back(l), v_end.push_back(r);
    }
    sort(v_start.begin(), v_start.end()), sort(v_end.begin(), v_end.end());

    ll pSum[360001]; // pSum[i] = k일 경우, i초까지의 누적 재생 시간은 k
    fill(pSum, pSum + n, 0);
    for (const auto &log : logs)
    {
        int l = get_time(log.substr(0, 8));
        int r = get_time(log.substr(9, 8));
        pSum[l]++, pSum[r]--;
    }

    for (int i = 0; i <= n; i++) // 현재 시간대의 영상 개수를 구함
        pSum[i] += pSum[i - 1];
    for (int i = 0; i <= n; i++) // 현재 시간대의 누적 재생 시간을 구함
        pSum[i] += pSum[i - 1];

    ll mx = 0, ans = 0; // 모든 구간에서의 최대 누적 재생 시간 mx
    for (int l = 0, r = len; r <= n; l++, r++)
    {
        ll total = pSum[r - 1] - pSum[l - 1]; // 광고의 길이만큼
        if (total > mx)
            mx = total, ans = l;
    }

    string ret;
    ret += ans / HOUR / 10 + '0';
    ret += ans / HOUR % 10 + '0';
    ret += ":", ans %= HOUR;
    ret += ans / MINUTE / 10 + '0';
    ret += ans / MINUTE % 10 + '0';
    ret += ":", ans %= MINUTE;
    ret += ans / 10 + '0';
    ret += ans % 10 + '0';

    return ret;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution("02:03:55", "00:14:15",
//                      {"01:20:15-01:45:14",
//                       "00:40:31-01:00:00",
//                       "00:25:50-00:48:29",
//                       "01:30:59-01:53:29",
//                       "01:37:44-02:02:30"})
//          << endl; //	"01:30:59"
//     cout << solution("99:59:59", "25:00:00",
//                      {"69:59:59-89:59:59",
//                       "01:00:00-21:00:00",
//                       "79:59:59-99:59:59",
//                       "11:00:00-31:00:00"})
//          << endl; //	"01:00:00"
//     cout << solution("50:00:00", "50:00:00",
//                      {"15:36:51-38:21:49",
//                       "10:14:18-15:36:51",
//                       "38:21:49-42:51:45"})
//          << endl; //	"00:00:00"
//     cout << solution("00:00:10", "00:00:05",
//                      {"00:00:08-00:00:10"})
//          << endl; //	"00:00:05"
// }