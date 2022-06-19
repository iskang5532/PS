// 2022-06-15
// 1283 단축키 지정
// https://www.acmicpc.net/problem/1283
/*
    구현, 문자열 (9,356KB, 120ms)
    시간 복잡도: ?
    풀이)
    - 사용된 문자인지를 저장할 셋.
    대소문자를 구분치 않으므로, 문자를 저장할 떄 대문자로 저장.
    - 입력된 문자열을 공백을 기준으로 나눠 배열 arr에 저장.
    - arr에 저장된 문자열을 탐색하며, 셋에 저장되어 있지 않은 문자가 나왔을 시 pos에 위치를 저장.
    - arr에 저장된 문자열의 문자를 하나씩 ans에 저장하되, 문자의 위치가 {y, x}와 같을 시 괄호로 묶어 저장.
    - 입력받은 모든 문자열이 위 과정을 거친 경우, ans 출력.
    etc.) 지저분한듯
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr


function get_ans(S: Set<string>, s: string): string {
    const arr = s.split(' ');

    let done = false;
    let y = -1, x = -1;
    for (let i = 0; i < arr.length && !done; i++)  // 첫 글자 확인
    {
        const c = arr[i][0].toUpperCase();
        if (!S.has(c))
            S.add(c), y = i, x = 0, done = true;
    }

    for (let i = 0; i < arr.length && !done; i++) // 왼쪽에서부터
        for (let j = 1; j < arr[i].length && !done; j++) {
            const c = arr[i][j].toUpperCase();
            if (!S.has(c))
                S.add(c), y = i, x = j, done = true;
        }

    let ans = "";
    for (let i = 0; i < arr.length; i++, ans += ' ')
        for (let j = 0; j < arr[i].length; j++)
            if (i == y && j == x)
                ans += `[${arr[i][j]}]`;
            else
                ans += arr[i][j];
    return ans;
}

const n = +input[0]; // 1 ≤ N ≤ 30

let S: Set<string> = new Set();
let ans: string[] = [];
for (let i = 1; i <= n; i++)
    ans.push(get_ans(S, input[i].trim()));
console.log(ans.join('\n'));

