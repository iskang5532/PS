/* 새로 생긴 놀이기구는 인기가 매우 많아 줄이 끊이질 않습니다.
 * 이 놀이기구의 원래 이용료는 price원 인데, 놀이기구를 N 번 째 이용한다면 원래 이용료의 N배를 받기로 하였습니다.
 * 즉, 처음 이용료가 100이었다면 2번째에는 200, 3번째에는 300으로 요금이 인상됩니다.
 * 놀이기구를 count번 타게 되면 현재 자신이 가지고 있는 금액에서 얼마가 모자라는지를 return 하도록 solution 함수를 완성하세요.
 * 단, 금액이 부족하지 않으면 0을 return 하세요. 

 * 제한사항
 * 놀이기구의 이용료 price : 1 ≤ price ≤ 2,500, price는 자연수
 * 처음 가지고 있던 금액 money : 1 ≤ money ≤ 1,000,000,000, money는 자연수
 * 놀이기구의 이용 횟수 count : 1 ≤ count ≤ 2,500, count는 자연수

 * 입출력 예) price = 3, money = 20, count = 4 => result is 10*/

/* 
 * 코딩테스트 연습 - 위클리 챌린지 - 1주차
 * 시간 복잡도: ?
 * 문제: https://programmers.co.kr/learn/courses/30/lessons/82612?language=cpp
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