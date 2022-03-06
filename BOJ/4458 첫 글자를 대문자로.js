// 4458 첫 글자를 대문자로
// https://boj.kr/4458

const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'text.txt').toString().split('\n');

const n = +input[0];

for (let i = 1; i <= n; i++)
    console.log(input[i][0].toUpperCase() + input[i].slice(1));