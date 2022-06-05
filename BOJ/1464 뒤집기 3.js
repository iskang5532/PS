// 2022-05-31
// 1464 뒤집기 3
// https://www.acmicpc.net/problem/1464
/*
    그리디 (9,336KB, 152ms)
    시간 복잡도: O(n)
    풀이)
    - 정답을 저장할 배열 ans. (문자로 이루어짐)
    - ans의 첫 번째 문자인 ans[0]은 입력되는 문자 중에서 가장 빠른 문자여야 한다.
    그러므로, 입력되는 문자 c와 비교하여 더 빠른 문자를 ans[]에 오도록 한다.
    - 입력되는 문자와 ans[0] 비교.
    만약 ans[0] < c일 경우, ans의 가장 뒤에 넣는다.
    만약 ans[0] >= c일 경우, ans의 가장 앞에 넣는다.
    etc.) 웰노운..?
    참고)
    - 코드 참고: https://kangminjun.tistory.com/entry/BOJ-1464-%EB%B2%88-%EB%92%A4%EC%A7%91%EA%B8%B0-3
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_arr(s) {
    let ans = [];

    for (const c of s) {
        if (ans.length === 0)
            ans.push(c);
        else if (ans[0] < c)
            ans.push(c);
        else
            ans.unshift(c);
    }

    return ans;
}

const s = input[0].trim();
const arr = get_arr(s);

console.log(arr.join(''));