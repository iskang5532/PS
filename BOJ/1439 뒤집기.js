// 1439 뒤집기
// https://www.acmicpc.net/problem/1439

// sol.1) 그리디
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'text.txt')
    .toString().trim();

let zero = 0, one = 0;
let prev = '\0';
for (const c of input)
    if (prev != c) {
        c == '0' ? zero++ : one++;
        prev = c;
    }

console.log(Math.min(zero, one));


// sol.2) 정규 표현식
/*
    "000"과 같이 1이 존재하지 않을 수 있으며, 이떄 match().length를 사용할 시 오류가 발생.
    이를 예방하기 위해 match()의 반환값이 존재하지 않을 시 빈 배열 []을 넣어 length를 0으로 만들어줌.
    참고: https://www.acmicpc.net/source/38470467
*/
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'text.txt')
    .toString().trim();

const zero = (input.match(/0+/g) || []).length;
const one = (input.match(/1+/g) || []).length;

console.log(Math.min(zero, one));
