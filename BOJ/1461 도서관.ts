// 2022-06-29
// 1461 도서관
// https://www.acmicpc.net/problem/1491
/*
    그리디 (9,600KB, 144ms)
    시간 복잡도: ?
    풀이)
    - 음수와 양수를 서로 번갈아 사용하는 것은 0을 지나친다는 것이며, 이는 책을 다시 들 수 있다는 것이다.
    즉, 음수와 양수를 나눠 봐도 무방하다.
    - 입력된 값이 음수일 경우 v1, 양수일 경우 v2에 저장. 이때, 편의를 위해 음수를 양수로 바꿔 저장.
    이후 내림차순 정렬. (이 또한 편의를 위함임)
    - 가장 큰 값을 ans에 저장한 후, m만큼 다음 값으로 이동 후 반복한다.
    이때 저장할 값은 책을 놓고 0으로 돌아오는 것을 포함하여야 하므로 *2를 해준다.
    - 책의 위치 중 가장 먼 값을 마지막으로 이동한다면 걸음을 최대한 줄일 수 있으므로, 가장 큰 값을 ans에서 제거한다. (책을 놓은 후 0으로 이동하지 않음)
    이때 주의해야 할 점은, v1 혹은 v2에 값이 존재하지 않을 수 있다.
    etc.) 풀이를 보기 전과 후의 난이도 차이가 엄청났음
    참고)
    - 이론: https://blog.naver.com/jinhan814/222345341352
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

const [n, m] = input[0].split(' ').map(Number);
const v = input[1].split(' ').map(Number);

const v1: number[] = [], v2: number[] = []; // 음수를 양수로 바꿔 저장할 v1, 양수를 저장할 v2
for (const i of v)
    i < 0 ? v1.push(-i) : v2.push(i);

v1.sort((a, b) => b - a), v2.sort((a, b) => b - a);

let ans = 0;
for (let i = 0; i < v1.length; i += m)
    ans += v1[i] * 2;
for (let i = 0; i < v2.length; i += m)
    ans += v2[i] * 2;

ans -= (v1.length ? v1[0] : 0) > (v2.length ? v2[0] : 0) ? v1[0] : v2[0]; // 더 큰 값을 뺌 (단, 값이 존재해야 함)

console.log(ans);
