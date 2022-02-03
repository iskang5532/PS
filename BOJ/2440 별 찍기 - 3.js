// 별 찍기 - 3
// https://www.acmicpc.net/problem/2440

let fs = require('fs');
let input = fs.readFileSync('/dev/stdin').toString().split(' ');

for (let i = 0; i < input[0]; i++) {
    let star = '';

    for (let j = 0; j < input[0] - i; j++)
        star += '*';

    console.log(star);
}