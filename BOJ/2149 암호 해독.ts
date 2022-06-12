// 2022-06-10
// 2149 암호 해독
// https://www.acmicpc.net/problem/2149
/*
    구현 (9,344KB, 148ms)
    시간 복잡도: ?
    풀이)
    - 키 k와 암호문 s가 주어진다.
    암호문을 구하기 위해서는 정렬된 키가 필요하므로, 키를 정렬한다.
    1. 정렬된 키 sk에 암호문을 맞춘다. (= v)
    2. 정렬된 키 sk를 기존 k의 값과 같이 되돌린다. (= ans)
    3. 구한 ans를 출력하되, 열을 먼저 출력한다.
    - 주의할 점은, 문제 설명의 예시와 같이 키에 동일한 문자가 존재할 수 있다.
    ans를 채우기 위해 k와 sk를 비교하는 과정에서 k == sk일 때, 무작정 ans에 값을 넣게 된다면 동일한 값이 들어갈 수 있다.
    etc.) 문제 설명과 같이 암호문을 구하는 문제인줄
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_arr(k: string, s: string): string[] {
    let v: string[] = Array.from({ length: k.length }, () => "");
    for (let i = 0; i < s.length; i++) {
        v[Math.floor(i / Math.floor(s.length / k.length))] += s[i];
    }

    let ans: string[] = []; // 평문
    const sk = k
        .split("")
        .sort((a, b) => (a < b ? -1 : 1))
        .join(""); // sorted k
    for (let i = 0; i < k.length; i++) {
        const cur = sk[i];
        for (let j = 0, flag = true; j < k.length && flag; j++) {
            const next = k[j];
            if (cur === next && ans[j] === undefined) {
                (ans[j] = v[i]), (flag = false);
            }
        }
    }

    return ans;
}

function get_ans(arr: string[]): string {
    let ans = "";
    for (let j = 0; j < Math.floor(s.length / k.length); j++) {
        for (let i = 0; i < k.length; i++) {
            ans += arr[i][j];
        }
    }
    return ans;
}

const [k, s] = [input[0].trim(), input[1].trim()];
const arr = get_arr(k, s);
const ans = get_ans(arr);
console.log(ans);
