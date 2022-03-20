// 주차 요금 계산 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > 주차 요금 계산)
// https://programmers.co.kr/learn/courses/30/lessons/92341
/*
    구현, 파싱
    시간 복잡도: ?
    풀이)
    - 차량의 남은 주차 시간을 저장할 v. (v[i] = t일 때, i번째 차량의 남은 기본 시간은 t. 만약 음수일 경우, -t만큼 시간 초과)
    - 차량의 입/출차 시간의 시를 분으로 바꿔 연산. (= hour_to_min)
    - 차량의 입차 시간을 저장할 car_lsit. (car_list[i] = t일 때, i번쨰 차량의 입차 시간은 t)
    1. 입/출차 기록(= records)를 확인.
    만약 차량이 입차 된 경우, car_list에 차량의 번호와 입차 시간을 저장.
    만약 차량이 출차 된 경우, 해당 차량의 입차 시간을 이용해 주차된 시간을 v에서 제거. 또한, car_list에서 제거.
    2. 만약 car_list에 차량이 남아 있을 시, 출차시킴.
    3. v에 저장된 모든 차량을 탐색. 만약 차량의 남아 있는 시간이 기본 시간과 다를 경우 해당 차량은 입/출차 기록이 있음.
    만약 남아 있는 시간이 양수, 즉 기본 시간 내 주차된 경우, 기본 요금을 ans에 저장.
    만약 남아 있는 시간이 음수, 즉 기본 시간을 넘겼을 경우 기본 요금에 추가 요금을 포함하여 ans에 저장.
    참고)
    - 문제해설: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;
#define MAX 10'003

int hour_to_min(const string &t)
{
    int h = stoi(t.substr(0, 2)) * 60,
        m = stoi(t.substr(3.2));

    return h + m;
}

vector<int> solution(vector<int> fees, vector<string> records)
{
    const int def_t = fees[0]; // 기본 시간

    int v[MAX]; // v[i] = t일 때, i번쨰 차량의 남은 시간 t
    fill(v, v + MAX, def_t);

    unordered_map<int, int> car_list; // 차량의 출입 시간을 저장
    for (const auto &recode : records)
    {
        stringstream ss(recode);
        string _t, _car, cs; // 시간, 차량 번호, 내역
        ss >> _t >> _car >> cs;
        int t = hour_to_min(_t), car = stoi(_car); // 입/출차 시간 (시 to 분)

        if (cs == "IN") // 입차
            car_list[car] = t;
        else // 출차
        {
            v[car] -= t - car_list[car]; // 주차된 시간
            car_list.erase(car);
        }
    }

    const int LAST = hour_to_min("23:59");
    for (const auto &[car, t] : car_list) // 남아 있는 차량의 주차 시간을 정산
        v[car] -= LAST - t;

    vector<int> ans;
    for (int i = 0; i < 10'000; i++)
    {
        int money = fees[1]; // 기본 요금
        if (v[i] < 0)        // 기본 시간을 넘긴 차량
            money += ceil(double(1) * abs(v[i]) / fees[2]) * fees[3];

        if (v[i] != def_t) // 시간 변화가 있는 경우 (= 입/출차된 차량)
            ans.push_back(money);
    }

    return ans;
}

// template <typename T>
// void print_ans(const vector<T> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << '\n';
// }
// int main()
// {
//     print_ans(solution({180, 5000, 10, 600}, {"05:34 5961 IN",
//                                               "06:00 0000 IN",
//                                               "06:34 0000 OUT",
//                                               "07:59 5961 OUT",
//                                               "07:59 0148 IN",
//                                               "18:59 0000 IN",
//                                               "19:09 0148 OUT",
//                                               "22:59 5961 IN",
//                                               "23:00 5961 OUT"})); // [14600, 34400, 5000]
//     print_ans(solution({1, 461, 1, 10}, {"00:00 1234 IN"}));       // [14841]
// }