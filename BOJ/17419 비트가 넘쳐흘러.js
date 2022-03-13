// 17419 비트가 넘쳐흘러
// https://boj.kr/17419 

const input = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'text.txt')
    .toString().trim().split('');

let ans = 0;
input.map(i => +i && ans++); // 1의 개수를 파악

console.log(ans - 1); // n이 포함되므로 제외해줌