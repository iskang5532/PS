// 1094 막대기
// https://www.acmicpc.net/problem/1094
const x = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt', 'utf-8');

console.log((+x).toString(2).match(/1/g).length);