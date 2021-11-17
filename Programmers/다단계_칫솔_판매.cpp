/*
    다단계 칫솔 판매 (코딩테스트 연습 > 2021 Dev-Matching: 웹 백엔드 개발자(상반기) > 다단계 칫솔 판매)
    유니온 파인드
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/77486
    풀이)
    - 맵을 이용. (유니온 파인드; 해당 맵에는 조직원 윗사람의 이름과 조직원이 획득한 금액을 저장)
    0) 유니온 파인드 선언. (해당 조직원들의 가장 윗사람이자 센터의 이름을 "-"로 선언)
    1) 조직원과 해당 조직원의 윗사람을 입력받아 맵에 저장.
    2) 판매 실적을 올린 조직원과 금액을 이용해 해당 조직원 밑 윗사람들에게 금액을 부여.
    - 금액을 배분할 윗사람이 존재하는 경우, 90%만을 가지며 없을 경우 100%을 가져야 함.
    금액을 90%와 10%로 나눴으며, 조직원에게 90%를 가져감.
    이후 윗사람이 존재할 경우 남은 10%를 이용해 다시 90% 및 10%로 나누며, 윗사람이 존재하지 않을 경우 남은 10%를 조직원이 가져감.
    - 쓸때없는 시간을 낭비하지 않기 위해 금액이 0원이 되는 순간 배분을 멈춤.
    3) 조직원들을 순서대로 확인하여 획득한 금액을 저장.
    etc.) 당장 떠오르는 방법은 유니온 파인드였는데, 괜히 어려운 방법으로 빙 돌아온 느낌.
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Union_find
{
    unordered_map<string, pair<string, int>> m; // m[human] = {parent, k}일 때 조직원 human의 윗사람은 parent, human의 획득 금액은 k

    Union_find(string str) { m[str] = {"A", 0}; } // center 선언

    void union_parent(string human, string parent, int k) { m[human] = {parent, k}; } // 현재 조직원의 윗사람과 금액을 설정
    void added_k(string human, int k)
    {
        k *= 100; // 칫솔의 개당 가격을 곱해 금액을 구함

        m[human].second += k - (k / 10), k /= 10; // 현재 조직원은 90%의 가격을 얻으며, 나머지 10%는 저장

        while (m[human].first != "A" && k != 0) // 현재 조직원 위의 사람이 있거나 남아 있는 금액이 0원이 아닌 경우
        {
            human = m[human].first;
            m[human].second += k - (k / 10), k /= 10;
        }
        m[human].second += k; // 남아 있는 금액을 마지막 사람이 가짐
    }
    int get_k(const string &human) { return m[human].second; } // 현재 조직원의 획득 금액을 반환
};

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{

    Union_find uf("-");

    for (int i = 0; i < enroll.size(); i++)
        uf.union_parent(enroll[i], referral[i], 0); // 조직원 등록

    for (int i = 0; i < seller.size(); i++)
        uf.added_k(seller[i], amount[i]); // 판매액 등록

    vector<int> answer;
    for (int i = 0; i < enroll.size(); i++)
        answer.push_back(uf.get_k(enroll[i])); // 조직원이 얻은 판매액을 저장

    return answer;
}

// void print_ans(const vector<int> &arr);
// #include <iostream>
// #define endl "\n"
// int main()
// {
//     print_ans(solution({"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"},
//                        {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"},
//                        {"young", "john", "tod", "emily", "mary"},
//                        {12, 4, 2, 5, 10})); // [360, 958, 108, 0, 450, 18, 180, 1080]
//     print_ans(solution({"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"},
//                        {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"},
//                        {"sam", "emily", "jaimie", "edward"},
//                        {2, 3, 5, 4})); // [0, 110, 378, 180, 270, 450, 0, 0]
// }
// void print_ans(const vector<int> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << endl;
// }