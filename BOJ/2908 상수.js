// 2908 상수
// https://www.acmicpc.net/problem/2908

const fs = require('fs');
const input = fs.readFileSync('/dev/stdin').toString().split(' ');

const a = Number(input[0].split('').reverse().join(''));
const b = Number(input[1].split('').reverse().join(''));

console.log(a > b ? a : b);