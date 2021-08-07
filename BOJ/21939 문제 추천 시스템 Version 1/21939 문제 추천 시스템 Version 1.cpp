/* 
 * 21939 문제 추천 시스템 Version 1
 * priority_queue (우선순위 큐)
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/21939
 * ETC.) 도저히 모르겠어서 참고 사이트를 거의 먹다시피 참고했다.
 * ___ 이론 ___
 * - 최댓값과 최솟값을 출력해주기 위해 정보를 저장할 두 pq 선언 (오름차 및 내림차)
 * - 또한, 삭제할 값을 저장할 drop_pq 선언. (= 나중에 한꺼번에 처리)
 * -> 이 둘을 묶어 클래스로 선언.
 * 풀이의 특이한 점은, 삭제 명령어를 받았을 때 바로 삭제하는 것이 아닌, 출력 시 한꺼번에 삭제함 (priority_queue의 정렬이나 세그먼트 트리 - lazy propagation와 같은 개념인듯)
 * 1) 입력값을 받았을 때, 두 pq에 넣어 줌 (최댓값 및 최솟값을 알아내기 위해 둘 다 활용)
 * 2) 커맨드를 입력 받음
 * - add일 경우, 1번과 같이 두 pq에 넣어 줌
 * - solved일 경우, drop_pq에 넣어 둠
 * - recommended일 경우, k값에 맞는 PQ에 대해서 drop_pq.top()과 pq.top()이 다를 때까지 제거함 (= top이 같은 경우 계속 제거하여 출력할 top이 제거 대상이 아닐 때까지 반복)
 *  이는, PQ에 존재하는 drop_pq 또한 pq와 같은 정렬이 되기 때문에 가능
 * 참고: https://blog.naver.com/jinhan814/222421203400
 */

#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"

struct Info
{
    int P, L; // 번호 및 난이도
};
struct _less // 내림차
{
    bool operator()(const Info &p1, const Info &p2)
    {
        if (p1.L == p2.L)
            return p1.P < p2.P;
        return p1.L < p2.L;
    }
};
struct _greater // 오름차
{
    bool operator()(const Info &p1, const Info &p2)
    {
        if (p1.L == p2.L)
            return p1.P > p2.P;
        return p1.L > p2.L;
    }
};

template <typename Func> // 정렬(오름차 or 내림차)에 맞춰 선언
class PQ
{
    priority_queue<Info, vector<Info>, Func> pq, drop_pq;

    void drop()
    {
        while (!drop_pq.empty() && pq.top().P == drop_pq.top().P) // pq의 top이 제거 대싱이 아니게 될 때까지 제거
            pq.pop(), drop_pq.pop();
    }

public:
    PQ() = default;

    int recommended()
    {
        drop();            // 출력 전에 정리함 (drop() 주석 참고)
        return pq.top().P; // top() 반환
    }
    void added(const Info &p) { pq.push(p); };
    void solved(const int p) { drop_pq.push(Info{p, 0}); } // drop_pq가 Info로 선언되었기 때문에 p값에 0을 추가하여 넣어줌 (0은 쓸모없는 값이며, 0이 아니여도 됨)
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 1 <= 100k
    cin >> n;

    PQ<_less> _max;    // 내림차순
    PQ<_greater> _min; // 오름차순

    for (int i = 0; i < n; i++)
    {
        int p, l;
        cin >> p >> l;
        _max.added(Info{p, l});
        _min.added(Info{p, l});
    }

    int m; // 1 <= 10k
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string cmd;
        cin >> cmd;

        char c = cmd[0];
        if (c == 'r') // recommended
        {
            int flag;
            cin >> flag;
            if (flag == 1)
                cout << _max.recommended() << endl;
            else if (flag == -1)
                cout << _min.recommended() << endl;
        }
        else if (c == 'a') // added
        {
            int p, l;
            cin >> p >> l;
            _max.added(Info{p, l});
            _min.added(Info{p, l});
        }
        else if (c == 's') // solved
        {
            int p;
            cin >> p;
            _max.solved(p);
            _min.solved(p);
        }
    }
}