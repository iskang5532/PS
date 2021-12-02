/*
    2064 IP 주소
    비트마스킹 (2,024KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2064
    풀이)
    - 입력된 값을 정렬 후, 가장 큰 값과 작은 값을 비교하여 틀린 구간을 확인하여 m을 구함.
    1) 입력된 값을 네 영역으로 8비트씩 나눈 후, 각 값을 비트로 이어줌. (= 총 32비트)
    2) 입력된 값을 정렬해줌. (가장 큰 값(= a)과 작은 값(= b)의 차이는 중간에 존재하는 값의 차이를 포함하므로 마지막 값만 비교해주면 됨.)
    3) m값을 구해줌.
    - 두 값을 앞에서부터 비트를 하나씩 비교.
    만약 두 비트가 같을 경우, m++해주며 다음 비트를 비교.
    만약 두 비트가 다를 경우, 비교를 종료. (= 네트워크 주소)
    4) 구해진 m값을 이용해 네트워크 주소 및 네트워크 마스크 출력.
    - 뒤에서부터 m만큼의 비트를 버린 a 혹은 b를 출력시킴.
    - 뒤에서부터 m만큼의 비트를 버린 1비트로 이루어진 bit(= (1 << 32)-1)를 출력.
    etc.) 비트셋 연습하려고 풀었는데, 비트셋 쓰니까 더 헷갈리는 기분.
    - (1 << 32) - 1과 같은 1로 이루어진 비트를 부르는 용어가 있나?
    참고)
    - 입력: https://blog.naver.com/jinhan814/222303599967
    - 비트셋에 대해: https://www.crocus.co.kr/549
                    https://blog.naver.com/jinhan814/222536104201
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <bitset>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"

int get_m(const bitset<32> &a, const bitset<32> &b)
{
    int m = 0;
    while (a[31 - m] == b[31 - m] && m < 32)
        m++;
    return 32 - m;
}
void print(const int bit)
{
    cout << ((bit >> 24) & 255) << '.';
    cout << ((bit >> 16) & 255) << '.';
    cout << ((bit >> 8) & 255) << '.';
    cout << (bit & 255) << endl;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ n ≤ 1,000
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int a, b, c, d;
        char idx;
        cin >> a >> idx >> b >> idx >> c >> idx >> d;

        arr.push_back(a << 24 | b << 16 | c << 8 | d); // 8비트씩 나눠준 후, 각 비트를 이어 값을 만듬
    }
    sort(arr.begin(), arr.end());

    bitset<32> mx(arr.front()), mn(arr.back());

    int m = get_m(mx, mn);

    bitset<32> INF; // 1로만 이루어진 32비트의 값
    INF.set();
    print((mx & (INF << m)).to_ulong()); // 네트워크 주소
    print((INF << m).to_ulong());        // 네트워크 마스크
}