// 2022-06-08
// 2257 화학식량
// https://www.acmicpc.net/problem/2257
/*
    sol.1) 스택 (9,356KB, 136ms)
    시간 복잡도: ?
    풀이)
    - 스택을 이용하며, top번째 스택에 값을 저장. (2차원 배열 st를 스택으로 사용)
    - 알파벳인 경우, top번째 스택에 값을 추가.
    - 열린 괄호('(')인 경우, top++.
    - 닫힌 괄호('(')인 경우
     - top번째 스택에 존재하는 값을 모두 더하여 top - 1번째 스택에 넣음.
     - top--
    - 숫자인 경우
     - top번째 스택의 값을 빼내어 수만큼 곱한 후, 다시 넣음.
     - top번째 스택에 값이 없을 수 있음. 이때는 top-1번째 스택의 값을 사용. (괄호 안에 알파벳이 없는 경우)
    - 0번째 스택에 존재하는 값을 모두 더한 후 출력.
    참고)
    - 코드: https://www.acmicpc.net/board/view/1713
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const MAX = 103;

function get_ans(s: string): number {
    let st = Array.from(Array(MAX), () => Array());

    for (let i = 0, top = 0; i < s.length; i++) {
        const c = s[i];
        if (c === "(") {
            top++;
        } else if (c === ")") {
            const sum = st[top].reduce((prev, cur) => prev + cur, 0);
            (st[top] = []), st[top - 1].push(sum), top--;
        } else if ("1" <= c && c <= "9") {
            let k: number;

            st[top].length
                ? ((k = st[top].pop()), st[top].push(k * +c)) // 괄호 안에 알파벳이 존재
                : ((k = st[top - 1].pop()), st[top - 1].push(k * +c)); // 괄호 안에 알파벳이 없음
        } else {
            st[top].push(c == "H" ? 1 : c == "C" ? 12 : 16);
        }
    }

    return st[0].reduce((prev, cur) => prev + cur, 0);
}

const s = input[0].trim();
const ans = get_ans(s);
console.log(ans);

/*
    sol.2) 배열 (9,336KB, 120ms)
    시간 복잡도: ?
    풀이)
    - 괄호가 닫힐 때 v에 prev가 더해짐. 그러므로, 곱셈 연산을 할 때 prev를 한 번 뺸 횟수만큼 연산을 수행해야 함.
    참고)
    - 코드: https://www.acmicpc.net/board/view/1713
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const MAX = 103;

function get_ans(s: string): number {
    let v: number[] = Array.from({ length: MAX }, () => 0);
    let prev = 0; // 곱 연산에 사용될 이전 값
    for (let i = 0, top = 0; i < s.length; i++) {
        const c = s[i];
        if (c == "(") {
            top++, (v[top] = 0);
        } else if (c == ")") {
            (v[top - 1] += prev = v[top]), top--;
        } else if ("1" <= c && c <= "9") {
            v[top] > 0 ? (v[top] += prev * (+c - 1)) : (v[top - 1] += prev * (+c - 1));
        } else {
            v[top] += prev = c == "H" ? 1 : c == "C" ? 12 : 16;
        }
    }

    return v[0];
}

const s = input[0].trim();
const ans = get_ans(s);
console.log(ans);
