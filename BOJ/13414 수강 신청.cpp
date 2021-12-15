// 13414 수강 신청
// https://www.acmicpc.net/problem/13414
/*
    map (35,432KB, 164ms)
    시간 복잡도: ?
    풀이)
    - l개만큼 학생을 받아 맵에 저장. 저장 시, 학생 = l번째와 같은 꼴로 만들어줌.
    같은 학생이 들어온 경우 기존 l값을 현재 l값으로 변경시키며 순서를 마지막으로 바꿈.
    이후 순서가 낮은 학생부터 출력해줘야 하는데, 맵의 경우 key를 기준으로 정렬이 됨. (원하는 것은 value 기준 정렬)
    그러므로 벡터와 같이 다른 공간을 만들어주어 옮겨담은 후, value를 기준으로 정렬 후 출력.
    - 주의할 점은, k명을 출력하면 안됨. 수강 가능 인원이 신청한 인원보다 많을 수 있음. (수강 가능 인원의 수만큼 출력할 때, OOB가 일어날 수 있음.)
    그러므로 k = min(k, (int)v.size())와 같은 코드를 넣어 OOB를 방지.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int k, l; // 수강 가능 인원 K(1 ≤ K ≤ 100,000), 대기목록의 길이 L(1 ≤ L ≤ 500,000)
    cin >> k >> l;

    unordered_map<string, int> um;
    for (int i = 0; i < l; i++)
    {
        string id; // len() == 8
        cin >> id;
        um[id] = i;
    }

    vector<pair<string, int>> v;
    for (auto itr = um.begin(); itr != um.end(); ++itr)
        v.push_back(*itr);
    sort(v.begin(), v.end(), [&](const pair<string, int> &p1, const pair<string, int> &p2)
         { return p1.second < p2.second; });

    k = min(k, (int)v.size());
    for (int i = 0; i < k; i++)
        cout << v[i].first << endl;
}