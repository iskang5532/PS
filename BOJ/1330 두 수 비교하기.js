// 1330 두 수 비교하기
// https://boj.kr/11720

// sol.1)
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt')
    .toString().trim().split(' ');

const a = +input[0], b = +input[1];
console.log(a > b ? ">" : (a < b ? "<" : "=="));

// sol.2)
const [a, b] = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt')
    .toString().trim().split(' ').map(Number);

console.log(a > b ? ">" : (a < b ? "<" : "=="));