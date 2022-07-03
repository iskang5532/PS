// 2022-07-03
// 21600 계단
// https://www.acmicpc.net/problem/21600
/*
    그리디 (21,972KB, 232ms)
    시간 복잡도: ?
    풀이)
    - 히스토그램에서 i번째 영역에서 만들 수 있는 최대 계단 높이를 h[]에 저장한 후, 가장 큰 값을 출력.
    - 계단의 높이는 1씩 높아짐.
    만약 이전 계단의 높이보다 현재 영역의 높이가 더 큰 경우, 계단을 더 쌓을 수 있음.
    만약 이전 계단의 높이보다 현재 영역의 높이가 더 작은 경우, 계단을 더 쌓을 수 없음.
    이는, 현재 영역의 크기가 곧 계단의 높이가 됨. (계단은 높지만, 만들 수 있는 계단의 높이는 현재 영역이 최대이므로)
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n");

const n = +input[0];
const v = input[1].split(' ').map(Number);

let h = Array.from({ length: n + 1 }, () => 0); // h[i] = k일 때, i에서의 최대 계단 높이는 k (i까지가 아닌, i에서의)
let ans = 0;
for (let i = 0; i < n; i++) {
    if (v[i] > h[i]) // 이전 계단의 높이보다 현재 영역이 더 큰 경우
        h[i + 1] = h[i] + 1;
    else
        h[i + 1] = v[i];
    ans = Math.max(ans, h[i + 1]);
}


console.log(ans);