/* 
 * 코딩테스트 연습 - 위클리 챌린지 - 2주차
 * 시간 복잡도: ?
 * 문제: https://programmers.co.kr/learn/courses/30/lessons/83201
 * ETC.) 다른 사람들의 풀이를 본 후 내 풀이를 보니 너무 어렵게 푼 기분이 든다.
 * 입력으로 주어지는 scores의 col, row가 바뀌었다보니 헷갈렸으며, 결국 다시 바꾼 값을 저장할 변수를 만듬
 */

// #include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

string solution(vector<vector<int>> scores)
{
    int n = scores.size();
    vector<vector<int>> arr(n, vector<int>(n)); // scores의 값을 원점(대각선?) 기준으로 뒤집어줌
    for (int col = 0; col < n; col++)
    {
        for (int row = 0; row < n; row++)
            arr[col][row] = move(scores[row][col]);
    }

    auto find_idx = [&](vector<vector<int>> &arr, const int &col, const int &idx) -> int
    {
        auto [lo, hi] = equal_range(arr[col].begin(), arr[col].end(), idx);

        int ret = hi - lo;
        return ret;
    };

    vector<double> result(n); // 값의 총합 및 평균을 저장
    string answer = "";

    for (int i = 0; i < n; i++)
    {
        result[i] = accumulate(arr[i].begin(), arr[i].end(), 0); // i번째 학생의 점수 합을 저장

        int idx = arr[i][i], len = n; // 자기 자신에게 메긴 점수 및 점수의 개수 (개수는 평균을 구할 때 사용)
        sort(arr[i].begin(), arr[i].end());

        int _max = *max_element(arr[i].begin(), arr[i].end()); // 점수의 최댓값
        int _min = *min_element(arr[i].begin(), arr[i].end()); // 점수의 최솟값
        if ((idx == _max || idx == _min) && find_idx(arr, i, idx) == 1) // 자신에게 메긴 점수가 최댓값 혹은 최솟값이며 유일한 경우
            result[i] -= idx, len--; // 현재 값을 제외해주며, 점수의 개수를 한 개 빼줌
            
        result[i] /= len; // 개수만큼 나누어 평균을 구함

        if (result[i] >= 90) answer += 'A';
        else if (result[i] >= 80) answer += 'B';
        else if (result[i] >= 70) answer += 'C';
        else if (result[i] >= 50) answer += 'D';
        else answer += 'F';
    }

    return answer;
}

// int main()
// {
//     cout << solution({{100, 90, 98, 88, 65},
//                       {50, 45, 99, 85, 77},
//                       {47, 88, 95, 80, 67},
//                       {61, 57, 100, 80, 65},
//                       {24, 90, 94, 75, 65}})
//          << endl;
//     cout << solution({{50, 90}, {50, 87}}) << endl;
//     cout << solution({{70, 49, 90}, {68, 50, 38}, {73, 31, 100}}) << endl;
// }