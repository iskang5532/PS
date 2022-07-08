// 16455 K번째 수를 찾는 함수
// https://www.acmicpc.net/problem/11004
/*
    정렬 (21,552KB, 36ms)
    시간 복잡도: O(n)
    풀이) nth_element를 이용해 k번째 수를 [k-1]의 위치로 옮김. (주의할 점은, 그 외의 값들은 정렬된 것이 아님)
    etc.) 시간 제한이 널널하지 않아서 O(nlogn)으로 풀 시 TLE.
 */
#include <vector>
#include <algorithm>

int kth(std::vector<int> &arr, int k)
{
    k--;
    nth_element(arr.begin(), arr.begin() + k, arr.end());
    return arr[k];
}
