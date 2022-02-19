// 2739 구구단
// https://www.acmicpc.net/problem/2739

// sol.1) 반복문
const fs = require('fs');
const input = fs.readFileSync('/dev/stdin').toString().split(' ');

const n = Number(input); // const n = parseInt(input[0]);
for (let i = 1; i <= 9; i++)
    console.log(`${n} * ${i} = ${n * i}`);



// sol.2) 문자열 이용
// 출력할 문자열들을 한 개의 문자열에 모두 저장하여 한 번의 출력만을 수행.
const fs = require('fs');
const input = fs.readFileSync('/dev/stdin').toString().split(' ');

const n = Number(input); // const n = parseInt(input[0]);
let ans = "";
for (let i = 1; i <= 9; i++) {
    const s = `${n} * ${i} = ${n * i}\n`;
    ans += s;
}

console.log(ans);