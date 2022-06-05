// 2022-06-03
// 1213 팰린드롬 만들기
// https://www.acmicpc.net/problem/1213
/*
    그리디, 투 포인터? (9,336KB, 128ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 문자열로 팰린드롬을 구하는 함수 get_ans()를 수행.
    만약 만들 수 없으면 빈 문자열을 반환.
    - 문자의 개수를 센 후 cnt에 저장.
    - 여러 개의 팰린드롬이 존재할 수 있으나, 출력은 사전 순으로 앞서는 것을 출력해야 하므로 'A'를 우선으로 탐색 및 ans의 앞에서부터 저장.
    현재 탐색 중인 문자를 ans에 저장하되, 위치는 ans의 가장 앞인 l과 가장 뒤인 r, 중앙의 위치인 m.
    이후 저장할 때마다 l++, r--.
    - 현재 탐색 중인 문자의 개수가 홀수일 경우
     - 문자열의 길이가 짝수이거나 이전에 ans[m]에 값을 넣었을 경우, 빈 문자열 반환.
     - ans[m]에 문자를 넣은 후, cnt[c]--. (남은 문자의 개수를 0 혹은 짝수로 만듦)
    - 현재 문자의 개수가 남아 있으면, 남은 문자를 모두 소모하여 [l]과 [r]에 넣음.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_ans(s) {
    let ans = [];
    ans.length = s.length;

    let cnt = [];
    for (const c of s)
        cnt[c] === undefined ? cnt[c] = 1 : cnt[c]++;

    const sz = s.length;
    let l = 0, r = sz - 1, m = Math.floor(sz / 2);
    for (let i = 'A'.charCodeAt(); i <= 'Z'.charCodeAt(); i++) {
        const c = String.fromCharCode(i);

        if (cnt[c] & 1) {
            if (!(sz & 1) || ans[m] !== undefined) // 문자열의 길이가 짝수 or 중앙의 위치에 이미 문자를 넣었을 경우
                return "";
            ans[m] = c, cnt[c]--; // 문자의 개수를 0 혹은 짝수로 만듦
        }

        while (cnt[c]) {
            ans[l] = ans[r] = c, cnt[c] -= 2;
            l++, r--;
        }
    }

    return ans.join('').trim();
}

const s = input[0].trim();
const ans = get_ans(s);
console.log(ans === "" ? "I'm Sorry Hansoo" : ans);