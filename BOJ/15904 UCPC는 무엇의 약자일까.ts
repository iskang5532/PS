// 2022-06-30
// 15904 UCPC는 무엇의 약자일까?
// https://www.acmicpc.net/problem/15904
/*
    그리디 (9,332KB, 120ms)
    시간 복잡도: ?
    풀이)
    - UCPC를 만들기만 하면 됨. 그러므로, UCPC의 각 문자가 순서대로 나오는지 확인.
    - 이전에 나온 문자를 저장할 prev. (default: null)
    - 가장 먼저 'U'가 필요함. 만약 현재 문자가 'U'이면서 prev의 값이 null일 경우, 'U'로 바꿈.
    위와 같이 나머지 문자 또한 확인.
    etc.) 순수 구현인 줄 알았으나 그리디한 문제
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n");

let valid = false;
let prev = '';
for(const c of input[0])
{
    if (c == 'U' && prev == '') prev = 'U';
    if (c == 'C' && prev == 'U')  prev = 'C';
    if (c == 'P' && prev == 'C')  prev = 'P';
    if (c == 'C' && prev == 'P')  valid = true;
}

console.log(valid ? "I love UCPC" : "I hate UCPC");