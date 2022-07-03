// 2022-06-27
// 25287 순열 정렬
// https://www.acmicpc.net/problem/25287
/*
    그리디 (17,780KB, 2,728ms)
    시간 복잡도: ?
    풀이)
    - 내림차가 없으면 되므로, 현재 탐색중인 수가 이전 수보다 작지 않도록 만든다.
    - 현재까지의 가장 큰 값을 저장할 prev.
    - 기존 값과 연산된 값들 중 더 작은 값을 저장할 mn, 더 큰 값을 저장할 mx.
    - 현재 값 k를 이전 값인 i-1보다 작지 않도록 만들기 위해서는 i-1 <= mn 혹은 i-1 <= mx여야 한다.
    다음 값이 내림차순으로 발생하지 않도록 현재 값은 가능한 낮은 값을 유지해야 한다.
    그러므로, 만약 i-1 <= mn이 성립한다면 mn을 사용하며, 성립하지 않고 i-1 <= mx가 성립한다면 mx를 사용한다.
    두 경우 모두 성립하지 않을 시, 내림차가 발생.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

function isValid(i: number) {
    const n = +input[1 + i * 2]; // 순열의 길이 (1 ≤ n ≤ 50,000)
    const v = input[2 + i * 2].split(' ').map(Number);

    let valid = true;
    let prev = 0; // 현재까지 가장 큰 값
    for (let pos = 0; pos < n; pos++) {
        const k = v[pos];

        // 기존 값과 연산 후의 값
        let mn = Math.min(k, n - k + 1), // 더 작은 값
            mx = Math.max(k, n - k + 1); // 더 큰 값

        if (prev <= mn)
            prev = mn;
        else if (prev <= mx)
            prev = mx;
        else
            valid = false;
    }


    return valid;
}

const tc = +input[0];// 1 ≤ tc ≤ 50,000

let ans: string[] = [];
for (let i = 0; i < tc; i++)
    ans.push(isValid(i) ? "YES" : "NO");

for (const s of ans)
    console.log(s);