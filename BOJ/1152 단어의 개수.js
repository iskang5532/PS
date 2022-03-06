// 1152 단어의 개수
// https://boj.kr/1152
/*
    - 입력의 마지막은 '\n'
    - trim은 공백뿐만 아니라 개행문자도 지워줌.
    참고) https://www.acmicpc.net/board/view/78881
*/

// sol.1)
const str = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt').toString().split('');

let ans = 0;
for (const str of input)
    if (str.length && str != '\n')
        ans++;
console.log(ans);


// sol.2)
// 공백이 연속으로 존재하지 않으므로 가능한 풀이
const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt').toString().trim().split('');

console.log(input[0] === '' ? 0 : input.length);
