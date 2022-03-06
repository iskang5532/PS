// 11720 숫자의 합
// https://boj.kr/11720

const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'text.txt').toString().trim().split('\n');

const ans = input[1]
    .split('')
    .reduce((sum, i) => +sum + +i);

console.log(ans);