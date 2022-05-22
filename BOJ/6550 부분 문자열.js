// 2022-05-20
// 6550 부분 문자열
// https://www.acmicpc.net/problem/6550
/*
    그리디 (10,080KB, 184ms)
    시간 복잡도: O(s2.length())
    풀이)
    - s1의 시작점 l, s2의 시작점 r.
    - s2[0]에서부터 탐색.
    만약 s1[l] == s2[r]일 경우, l++.
    만약 s1의 문자를 모두 탐색한 경우, "Yes" (= s1는 s2의 부분 문자열)
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const isValid = (s1, s2) => {
    for (let l = 0, r = 0; r < s2.length; r++) {
        if (s1[l] == s2[r])
            l++;
        if (l == s1.length)
            return true;
    }
    return false;
};

for (let i = 0; i < input.length; i++) {
    const [s1, s2] = input[i].split(' ');

    console.log(isValid(s1, s2) ? "Yes" : "No");
}
