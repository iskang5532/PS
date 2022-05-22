// 2022-05-18
// 11656 접미사 배열
// https://www.acmicpc.net/problem/11656
/*
    문자열, 정렬 (11,224KB, 188ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s를 i번째부터 잘라 배열에 저장.
    - 배열을 오름차순 정렬 후, 원소를 출력.
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n");

const s = input[0];

let v = [];

for (let i = 0; i < s.length; i++) {
    v.push(s.slice(i, s.length));
}

v.sort();

for (const s of v) {
    console.log(s);
}
