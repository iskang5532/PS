/* 
 * 2800 괄호 제거
 * 스택, 비트 마스크
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2800
 * etc.) 괄호를 지울 경우의 수를 구하는 게 어려웠음.
 * - 모든 경우의 수를 구하기 위해 비트 마스크를 이용.
 * - for(1, 3)인 경우 01, 10, 11이며 이는 2개의 모든 경우의 수이다.
 * 1) 괄호마다 i번쨰 비트의 위치로 저장한다.
 * 2) 괄호 쌍의 개수만큼 비트가 생성되었을 것이며, for문을 돌며 비트를 사용시킨다. (즉, 괄호를 포함 혹은 제거. 풀이는 제거하는 쪽으로)
 * 참고: https://hsin.hr/coci/archive/2011_2012/ (CONTEST #6, 반례)
 * - 추가로 식 자체를 여러 쌍의 괄호가 감쌀 수가 있으며, 이를 입력 시 중복된 문자열이 구해질 수 있기 때문에 정렬 후에 중복을 제거시켜 준다.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // sort

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

struct pii
{
    int pos, cnt;
};

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    string str;      // 입력 문자열 (str.len <= 200)
    vector<pii> arr; // 각 괄호의 위치(= pos)와 번호(= cnt)를 저장
    stack<int> st;   // 닫힘 괄호에 사용될 번호를 저장

    int cnt = 1; // 괄호 쌍의 번호
    char c;
    for (int i = 0; cin >> c; i++)
    {
        str.push_back(c);

        if (c == '(')
            arr.push_back(pii{i, cnt}), st.push(cnt), cnt <<= 1; // 닫힘 괄호가 나올 때 사용할 번호 저장 및 번호의 크기 업데이트
        else if (c == ')')
            arr.push_back(pii{i, st.top()}), st.pop(); // 저장된 번호 사용하여 닫힘 괄호에 번호를 매김
    }

    cnt = arr.size() / 2; // 괄호 쌍의 개수 (= (열림 + 닫힘) / 2)
    int msb = 1 << cnt;   // 최상위 비트 (most significant bit, msb) ([모든 경우의 수 - 1]의 값. ex) 1000 - 1 = 0111)

    vector<string> ans;
    for (int bit = 1; bit < msb; bit++) // 괄호를 제거할 위치
    {
        auto itr = arr.begin(); // -번째 괄호에 대한 정보
        string temp;            // 괄호를 제거한 문자열
        for (int i = 0; i < str.length(); i++)
        {
            if ((*itr).pos == i && (*itr).cnt & bit) // 현재 문자가 괄호이면서 제거할 문자(괄호)인 경우
            {
                itr++;    // 다음 위치로
                continue; // 문자를 추가하지 않고 다음 문자를 탐색
            }
            else if ((*itr).pos == i) // 괄호이지만 제거할 문자가 아닌 경우
                itr++;
            temp.push_back(str[i]); // 문자 추가
        }

        ans.push_back(temp);
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end()); // 중복 제거
    for (const auto &elem : ans)
        cout << elem << endl;
}

// 6%
// input: (1)(1)
// ouput:
// (1)1
// 1(1)
// 11

// 18%
// input: (((1)))
// output:
// ((1))
// ((1))
// ((1))
// (1)
// (1)
// (1)
// 1