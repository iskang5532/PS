/*
    키패드 누르기 (코딩테스트 연습 > 2020 카카오 인턴십 > 키패드 누르기)
    시간 복잡도: ?
    문제:https://programmers.co.kr/learn/courses/30/lessons/67256?language=cpp
    풀이)
    - 키패드의 위치를 x축과 y축에 대해 위치를 갖게끔 선언해주었으며, 왼손과 오른손의 시작점 또한 이에 맞춰 선언.
    - 위치에 맞게 손을 이동시키며, 만약 가운데 번호가 입력일 경우, 가장 가까운 손을 이동시킴.
    만약 거리가 같은 경우, 주로 사용하는 손을 이동시킴. 이때 입력으로 들어온 hand의 첫 번째 글자를 대문자로 바꿔준 값을 이용.
 */

#include <string>
#include <vector>

using namespace std;

#define x first
#define y second
typedef pair<int, int> pii;

string solution(vector<int> numbers, string hand)
{
    string answer = "";

    pii pad[10] = {{1, 3}, {0, 0}, {1, 0}, {2, 0},  // 키패드의 위치
                           {0, 1}, {1, 1}, {2, 1}, 
                           {0, 2}, {1, 2}, {2, 2}};
    pii l = {0, 3}, r = {2, 3}; // 손의 시작 위치
    for (const int k : numbers)
    {
        char h; // 사용할 손 (왼손, 오른손)
        if (k == 1 || k == 4 || k == 7) 
            h = 'L';
        else if (k == 3 || k == 6 || k == 9) 
            h = 'R';
        else // 2, 5, 8, 0
        {
            int dist_l = abs(pad[k].x - l.x) + abs(pad[k].y - l.y); // 왼손에서부터의 거리
            int dist_r = abs(pad[k].x - r.x) + abs(pad[k].y - r.y); // 오른손에서부터의 거리
            if (dist_l < dist_r) // 왼손이 짧은 경우
                h = 'L';
            else if (dist_l > dist_r) // 오른손이 짧은 경우
                h = 'R';
            else 
                h = hand.front() - 32; // 주로 사용하는 손의 첫 번째 문자를 대문자로 바꿔 입력
        }
        if (h == 'L') // 손의 위치 변경
            l = pad[k];
        else if (h == 'R')
            r = pad[k];
        answer.push_back(h);
    }
    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << "LRLLLRLLRRL" << endl
//          << solution({1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5}, "right") << endl;
//     cout << "LRLLRRLLLRR" << endl
//          << solution({7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2}, "left") << endl;
// }