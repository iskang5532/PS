// 10951 A+B - 4
// https://boj.kr/10951

const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt').toString().trim().split('\n');

for (let s of input)
    console.log(s.split(' ').reduce((prev, k) => +prev + +k, 0));
