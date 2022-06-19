// 2022-06-11
// 1593 문자 해독
// https://www.acmicpc.net/problem/1593
/*
    슬라이딩 윈도우 (16,564KB, 272ms)
    시간 복잡도: ?
    풀이)
    - 문자열 W에 존재하는 문자의 개수를 cnt에 저장.
    - 문자열 s에서 길이 g만큼의 문자열에 존재하는 문자의 개수를 센 후, cnt에 존재하는 값과 같은지 확인.
    문자의 개수가 같다는 것은 W로 만들 수 있는 순열이란 뜻.
    - 슬라이딩 윈도우를 사용하여 s에서 g만큼 확인.
    etc.) 문제 이해가 어려웠음
    - for..of를 사용하면 컴파일 에러. why?
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function isValid(cnt: []): boolean {
    for (let c1: number = "A".charCodeAt(0), c2: number = "a".charCodeAt(0); c2 <= "z".charCodeAt(0); c1++, c2++) {
        if (cnt[c1] !== 0 || cnt[c2] !== 0)
            return false;
    }

    return true;
}

function get_ans(g: number, S: number, w: string, s: string): number {
    let ans = 0;

    let cnt: any = Array.from({ length: 200 }, () => 0);
    for (let i = 0; i < w.length; i++)
        cnt[w[i].charCodeAt(0)]--;

    for (let i = 0; i < g; i++)
        cnt[s[i].charCodeAt(0)]++;
    if (isValid(cnt))
        ans++;

    for (let l = 0, r = g; r < S; l++, r++) {
        cnt[s[l].charCodeAt(0)]--, cnt[s[r].charCodeAt(0)]++;

        if (isValid(cnt))
            ans++;
    }

    return ans;
}

const [g, S] = input[0].split(" ").map(Number);
const w = input[1].trim(), s = input[2].trim();

const ans = get_ans(g, S, w, s);
console.log(ans);