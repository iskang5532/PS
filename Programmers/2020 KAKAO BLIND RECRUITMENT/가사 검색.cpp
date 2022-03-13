// 가사 검색 (코딩테스트 연습 > 2020 KAKAO BLIND RECRUITMENT > 가사 검색)
// https://programmers.co.kr/learn/courses/30/lessons/60060
/*
    시간 복잡도: ?
    풀이)
    - 트라이를 이용한 문자열 탐색으로 품.
    - 트라이를 두 개 선언하여 접미사와 접두사를 나눠 관리.
    pre는 알고 있는 문자열이 접두사(= '?'가 접미사)이며, suf는 알고 있는 문자열이 접미사(= '?'가 접두사)이다.
    - queries에서 뽑은 문자열 query가 PRE인지 SUF인지 확인. (알고 있는 문자열이 접두사인가 접미사인가)
    그에 맞춰 pre 혹은 suf에서 탐색.
    - "????"와 같은 입력이 들어왔을 경우, 길이가 4인 문자열의 개수를 출력해줘야 한다. 이를 위해 pre 및 suf의 첫 번째 포인터의 cnt를 +1해준다.
    참고)
    - 트라이 구현: https://ansohxxn.github.io/algorithm/trie/
    - 접두사로 ?가 있는 경우 해결: https://blog.naver.com/jinhan814/222535225549
 */

#include <iostream>
#include <vector>
#include <algorithm> // reverse

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 10'003 // string max len
#define PRE 0
#define SUF 1

struct Trie
{
    int cnt;
    Trie *trie[26];
    Trie() : cnt(), trie{} {}
    ~Trie()
    {
        for (int i = 0; i < 26; i++)
            delete trie[i];
    }

    void add(const string &s, int pos = 0)
    {
        if (pos == s.length())
            return;

        int c = s[pos] - 'a';

        if (trie[c] == nullptr)
            trie[c] = new Trie();

        trie[c]->add(s, pos + 1);
        trie[c]->cnt++;
    }

    int find(const string &s, int pos = 0)
    {
        if (pos == s.length())
            return cnt;

        int c = s[pos] - 'a';
        if (trie[c] == nullptr)
            return 0;

        return trie[c]->find(s, pos + 1);
    }
};

vector<int> solution(vector<string> words, vector<string> queries)
{

    Trie pre[MAX], suf[MAX];

    for (auto s : words)
    {
        pre[s.length()].cnt++, pre[s.length()].add(s); // 길이 n의 글자의 개수++ 및 문자열 추가
        reverse(s.begin(), s.end());
        suf[s.length()].cnt++, suf[s.length()].add(s);
    }

    vector<int> ans(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
        string query = queries[i];

        int cur = PRE; // 알고 있는 문자열이 접두사
        if (query.front() == '?')
            cur = SUF, reverse(query.begin(), query.end()); // 알고 있는 문자열이 접미사

        string s = string(query.begin(), query.begin() + query.find('?')); // '?'를 제거한 문자열
        if (cur == PRE)
            ans[i] = pre[query.length()].find(s);
        else
            ans[i] = suf[query.length()].find(s);
    }

    return ans;
}

// int main()
// {
//     FAST_IO;

//     vector<int> v = solution({"frodo", "front", "frost", "frozen", "frame", "kakao"},
//                              {"fro??", "????o", "fr???", "fro???", "pro?", "?????"}); // 3 2 4 1 0 5

//     for (const auto &i : v)
//         cout << i << ' ';
// }