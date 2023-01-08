// 2023-01-06
// 15596 정수 N개의 합
// https://www.acmicpc.net/problem/15596
/*
    구현 (13,740KB, 12ms)
 */


#include <vector>
long long sum(std::vector<int> &a) {
	long long ans = 0;
    
    for (const int& i : a)
        ans += i;
    
	return ans;
}
