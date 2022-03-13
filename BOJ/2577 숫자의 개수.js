// 2577 숫자의 개수
// https://boj.kr/2577

// sol.1)
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt')
    .toString().trim().split('\n');

const sum = String(input.reduce((sum, i) => +sum * +i));

let ans = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
for (let i of sum)
    ans[+i]++;

ans.map((i) => console.log(i));

// sol.2)
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt')
    .toString().trim().split('\n');

const sum = String(input.reduce((sum, i) => +sum * +i));

for (let i = 0; i < 10; i++)
    console.log(sum.split(i).length - 1);