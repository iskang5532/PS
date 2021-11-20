/*
    부족한 금액 계산하기 (코딩테스트 연습 > 위클리 챌린지 > 부족한 금액 계산하기(1주차))
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/82612
    풀이)
    놀이기구를 탄 이후, 지불해야 할 요금이 부족할 상황이 있을 것이며, 그 상황에서 부족한 금액을 구해야 함.
    1) count번 탔을 때의 비용(= used)을 구함.
     - 횟수가 증가함에 따라 비용 또한 증가하므로, 가격과 횟수를 연관지어 수식을 완성시킴.
    2) 소지중인 금액과 비교. (소지중인 금액으로 필요한 비용을 모두 지불이 가능한가?)
     - 만약 가능한 경우, 부족한 금액은 0원이므로 0을 반환.
     - 만약 불가능한 경우, 소지중인 금액에서 비용을 절감한 값을 반환함. (= 부족한 금액)
 */

using namespace std;

long long solution(int price, int money, int count)
{
    long long used = 0; // 총 사용 금액
    for (int cnt = 1; cnt <= count; cnt++)
        used += price * cnt; // 이용 횟수를 고려하며 금액 추가

    long long rem = money - used; // 이용료를 차감한 보유 금액
    if (rem < 0)
        return -rem;
    else
        return 0;
}

#include <iostream>
#define endl "\n"
int main()
{
    cout << solution(3, 20, 4) << endl; // 10
}