// 11021 A+B - 7
// https://boj.kr/11021

const fs = require('fs');
const input = fs.readFileSync('/dev/stdin').toString().split('\n');

const n = +input[0];

for (let i = 1; i <= n; i++) {
    const [a, b] = input[i].split(' ').map(Number)

    console.log(`Case #${i}: ${a + b}`);
}