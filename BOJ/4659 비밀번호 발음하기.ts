// 2022-06-05
// 4659 비밀번호 발음하기
// https://www.acmicpc.net/problem/4659
/*
    구현 (9,448KB, 124ms)
    시간 복잡도: ?
    풀이)
    - a부터 z까지 문자 c가 자음인지 모음인지를 저장할 ch. (ch[c] == JA일 경우, 자음)
    - 연속된 자음 혹은 모음의 개수를 저장할 j, m. (j === 2일 경우, 연속된 자음의 개수는 2개)
    - 1번 조건 여부를 저장할 used_mo.
    - 이전에 탐색한 문자를 저장할 prev.
    etc.) isValid()에 string을 넘겨준 후, for..of를 이용할 경우 컴파일 에러. wht? (js에서는 정상)
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const JA = 0,
    MO = 1;
const ch: Number[] = (function () {
    let ch: Number[] = [];
    for (let c = "a".charCodeAt(0); c <= "z".charCodeAt(0); c++)
        ch[c] =
            c === "a".charCodeAt(0) ||
            c === "e".charCodeAt(0) ||
            c === "i".charCodeAt(0) ||
            c === "o".charCodeAt(0) ||
            c === "u".charCodeAt(0)
                ? MO
                : JA;

    return ch;
})();

function isValid(s: string[]): boolean {
    let used_mo = false;
    let j = 0,
        m = 0; // 연속된 자음 혹은 모음의 개수
    let prev = "";
    for (const c of s) {
        const k = c.charCodeAt(0);
        if (ch[k] === JA) {
            j++, (m = 0);
        } else if (ch[k] === MO) {
            used_mo = true;
            m++, (j = 0);
        }

        if (j === 3 || m === 3 || (prev !== "e" && prev !== "o" && prev === c)) {
            return false;
        }

        prev = c;
    }

    return used_mo ? true : false;
}

for (const _s of input) {
    const s = _s.trim();
    if (s === "end") {
        break;
    }

    console.log(`<${s}> is ${isValid(s.split("")) ? "" : "not "}acceptable.`);
}
