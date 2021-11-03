/*
    오픈채팅방 (코딩테스트 연습 - 2019 KAKAO BLIND RECRUITMENT - 오픈채팅방)
    일시: 21.10.29
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/42888?language=cpp
    etc.) VSC에서 한글 출력이 안 돼서 당황했던 문제.
    - 입력된 문자열을 순서대로 탐색하며, 명령어에 맞춰 id와 닉네임을 구한다.
    - 큐를 이용해 출력의 순서를 입력했으며, {고유 id, 메시지}를 저장.
    - 맵을 이용해 id의 값을 닉네임으로 만든 후, change가 들어올 때마다 값을 변경시켜 줌. 이후 출력에서 id에 맞는 값을 사용.
    모든 문자열을 탐색한 경우, 큐에 저장된 값을 이용함.
    - id는 그에 맞는 값을 가져와 사용하며 뒤에 큐에 저장된 메시지를 붙인 후 저장.
    이후 큐가 빌 때까지 반복.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

vector<string> solution(vector<string> record)
{
    unordered_map<string, string> m;
    queue<pair<string, string>> q;

    for (const string &str : record)
    {
        string id;
        int pos;

        if (str.front() == 'E') // enter
        {
            pos = 6;
            while (str[pos] != ' ')
                id += str[pos], pos++;
            m[id] = str.substr(pos + 1, 10); // 10 이하의 문자열이여도 마지막 문자까지만 읽어 가져옴
            q.push({id, string("님이 들어왔습니다.")});
        }
        else if (str.front() == 'L') // leave
        {
            id = str.substr(6, 10);
            q.push({id, "님이 나갔습니다."});
        }
        else if (str.front() == 'C') // change
        {
            pos = 7;
            while (str[pos] != ' ')
                id += str[pos], pos++;
            m[id] = str.substr(pos + 1, 10);
        }
    }

    vector<string> answer;
    while (!q.empty())
    {
        auto [id, cmd] = q.front();
        q.pop();

        string str = m[id] + cmd;

        answer.push_back(str);
    }
    return answer;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     auto v1 = solution({"Enter uid1234 Muzi",
//                         "Enter uid4567 Prodo",
//                         "Leave uid1234",
//                         "Enter uid1234 Prodo",
//                         "Change uid4567 Ryan"});
//     for (const auto &elem : v1)
//         cout << elem << endl;
//     // Prodo님이 들어왔습니다.
//     // Ryan님이 들어왔습니다.
//     // Prodo님이 나갔습니다.
//     // Prodo님이 들어왔습니다.
// }

/*
    sol.2) std::stringstream
    - stringstream을 이용해 입력된 문자열에서 더 쉽게 원하는 문자열을 추출했음.
    etc.) 처음 이용해봤는데 정말 편리하다.
 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>

using namespace std;

vector<string> solution(vector<string> record)
{
    unordered_map<string, string> m;
    queue<pair<string, string>> q;

    for (const string &_str : record)
    {
        stringstream str(_str); // 문자열 초기화
        string cmd, id, name;
        str >> cmd >> id >> name; // 공백을 제외한 문자열을 가져옴

        if (cmd.front() == 'E') // enter
        {
            m[id] = name;
            q.push({id, "님이 들어왔습니다."});
        }
        else if (cmd.front() == 'L') // leave
            q.push({id, "님이 나갔습니다."});
        else if (cmd.front() == 'C') // change
            m[id] = name;
    }

    vector<string> answer;
    while (!q.empty())
    {
        auto [id, cmd] = q.front();
        q.pop();

        string str = m[id] + cmd;

        answer.push_back(str);
    }
    return answer;
}