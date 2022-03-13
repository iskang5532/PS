/*
    순위 검색 (코딩테스트 연습 > 2021 KAKAO BLIND RECRUITMENT > 순위 검색)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/72412
    풀이)
    - 5차원 배열을 이용.
    - arr[a][b][c][d] = {1, 2}라고 할 때, 코딩테스트에 a로 참여했으며, b 직군을 선택했고, c 경력이면서, 소울푸드로 d를 선택한 사람의 점수는 각각 1, 2.
    - 입력되는 a, b, c, d는 정해져 있으므로 맵을 이용해 각각 숫자를 부여함. (= um[str] = (int))
    1) 지원자들의 정보를 확인. (a, b, c, d의 입력은 stringsteam을 이용했음)
    2) 입력받은 정보를 배열에 사용하기 위해 맵에 저장된 숫자로 변환.
    3) 배열에 점수를 푸쉬해줌.
    이때, 개발팀에서 원하는 정보 중 상관 없다는 의미인 "-"가 들어올 수 있으므로 이를 고려해줘야 한다.
    언어에 "-"가 들어올 경우, cpp과 java, python에 대한 모든 점수들을 구해줘야 한다.
    이를 표현하기 위해 현재 정보에 "-"가 들어왔다고 가정하여 "-"가 들어갈 수 있는 모든 경우의 수를 구한 후, 해당 위치에 점수를 푸쉬해준다. (bit 이용)
    4) 개발팀에서 원하는 정보를 하나씩 받아와 배열에 입력하여 점수를 가져온 후, 조건에 맞는 개수를 찾음.
    이때 정렬 및 lower_bound를 이용한 풀이는 신기하게도 시간 초과 됐음.
    etc.) 다른 사람의 풀이를 보는데 맨 윗사람의 풀이를 보고 감탄했음. 나중에 한번 배열 없이 맵만을 이용해 풀어봐야겠음.
 */

#include <vector>
#include <string>
#include <sstream> // stringstream
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> _info, vector<string> _query)
{
    unordered_map<string, int> um;
    um["-"] = 0;
    um["cpp"] = 1, um["java"] = 2, um["python"] = 3; // language
    um["backend"] = 1, um["frontend"] = 2;           // position
    um["junior"] = 1, um["senior"] = 2;              // carrer
    um["chicken"] = 1, um["pizza"] = 2;              // food

    vector<int> arr[4][3][3][3]; // 지원자들의 정보를 저장 (arr[a][b][c][d] = {1, 2}라고 할 때, 코딩테스트에 a로 참여했으며, b 직군을 선택했고, c 경력이면서, 소울푸드로 d를 선택한 사람의 점수는 각각 1, 2)
    for (const auto &info : _info)
    {
        stringstream ss(info);
        string _language, _pos, _carrer, _food, _score;
        ss >> _language >> _pos >> _carrer >> _food >> _score;

        int language = um[_language], pos = um[_pos], carrer = um[_carrer], food = um[_food], score = stoi(_score); // 입력된 문자열을 숫자로 변환 (배열에 사용하기 위함)
        for (int bit = 0; bit < 16; bit++) // "-"가 들어갈 수 있는 모든 경우의 수를 구함
        {
            int flag[4] = {language, pos, carrer, food};
            if (bit & 1) flag[0] = 0;
            if (bit & 2) flag[1] = 0;
            if (bit & 4) flag[2] = 0;
            if (bit & 8) flag[3] = 0;

            arr[flag[0]][flag[1]][flag[2]][flag[3]].push_back(score);
        }
    }
    vector<int> answer;
    for (const auto &query : _query)
    {
        int cnt = 0;
        stringstream ss(query);
        string _language, _pos, _carrer, _food, _score, idx;
        ss >> _language >> idx >> _pos >> idx >> _carrer >> idx >> _food >> _score;

        int language = um[_language], pos = um[_pos], carrer = um[_carrer], food = um[_food], score = stoi(_score);
        for (const auto &k : arr[language][pos][carrer][food]) // 개발팀에서 원하는 지원자들의 점수를 확인
            if (k >= score)
                cnt++;

        answer.push_back(cnt);
    }

    return answer;
}

// #include <iostream>
// #define endl "\n"
// void print_ans(const vector<int> &arr);
// int main()
// {
//     print_ans(solution({"java backend junior pizza 150",
//                         "python frontend senior chicken 210",
//                         "python frontend senior chicken 150",
//                         "cpp backend senior pizza 260",
//                         "java backend junior chicken 80",
//                         "python backend senior chicken 50"},
//                        {"java and backend and junior and pizza 100",
//                         "python and frontend and senior and chicken 200",
//                         "cpp and - and senior and pizza 250",
//                         "- and backend and senior and - 150",
//                         "- and - and - and chicken 100",
//                         "- and - and - and - 150"})); // 1, 1, 1, 1, 2, 4
// }
// void print_ans(const vector<int> &arr)
// {
//     for (const auto &elem : arr)
//         cout << elem << " ";
//     cout << endl;
// }