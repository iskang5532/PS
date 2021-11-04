/*
    영어 끝말잇기 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 영어 끝말잇기)
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/12981?language=cpp
    etc.)
    - 맵에 단어를 넣어 기억시킴.
    - 현재 단어가 맵에 존재하지 않을 경우, 단어를 넣음.
    - 현재 단어가 맵에 존재하거나 현재 단어의 첫 글자가 이전 단어의 마지막 글자와 다른 경우, 현재 사람의 번호와 차례를 반환시킴.
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(int n, vector<string> words)
{
    unordered_map<string, int> m;

    char prev = words.front()[0]; // 이전 단어의 마지막 글자
    for (int i = 0; i < words.size(); i++)
    {
        string word = words[i];
        if (m[word] || prev != word.front()) // 만약 이전에 불린 단어이거나 이전의 글자와 이어질 수 없는 경우
            return {i % n + 1, i / n + 1};

        m[word]++; // 현재 문자 추가
        prev = word.back();
    }

    return {0, 0}; // 끝말잇기가 원활하게 진행되는 경우
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     for (const auto &ans : solution(3, {"tank", "kick", "know",
//                                         "wheel", "land", "dream",
//                                         "mother", "robot", "tank"}))
//         cout << ans << " "; // 3 3
//     for (const auto &ans : solution(5, {"hello", "observe", "effect", "take", "either",
//                                         "recognize", "encourage", "ensure", "establish", "hang",
//                                         "gather", "refer", "reference", "estimate", "executive"}))
//         cout << ans << " "; // 0 0
//     for (const auto &ans : solution(2, {"hello", "one",
//                                         "even", "never",
//                                         "now", "world",
//                                         "draw"}))
//         cout << ans << " "; // 1 3
// }