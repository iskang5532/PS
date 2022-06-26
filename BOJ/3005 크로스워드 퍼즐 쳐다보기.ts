// 2022-06-23
// 3005 크로스워드 퍼즐 쳐다보기
// https://www.acmicpc.net/problem/3005
/*
    구현 (9.332KB, 120ms)
    시간 복잡도: ?
    풀이)
    - (0, 0)과 맞닿는 외곽 부분만을 탐색하여 가장 짧은 문자열을 구함.
    이때, 문자열을 구하는 도중 현재 위치의 문자가 '#"일 경우, 이전에 구한 문자열 s는 ans와 비교하여 더 작은 값을 ans에 저장한 후 값을 비움.
    - 문자열 s만 구하고 ans에 저장이 안 될 수도 있으므로 탐색이 완료되었다면 ans의 값을 갱신해야 함.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

function get_s1(): string {
    let ans = "";
    for (let y = 0; y < r; y++) {
        let s = "";
        for (let x = 0; x < c; x++)
            if (input[y + 1][x] == '#') {
                if (s.length >= 2)
                    ans = ans == "" ? s : (ans < s ? ans : s);
                s = "";
            }
            else
                s += input[y + 1][x];

        if (s.length >= 2)
            ans = ans == "" ? s : (ans < s ? ans : s);
    }

    return ans;
}

function get_s2(): string {
    let ans = "";

    for (let x = 0; x < c; x++) {
        let s = "";
        for (let y = 0; y < r; y++)
            if (input[y + 1][x] == '#') {
                if (s.length >= 2)
                    ans = ans == "" ? s : (ans < s ? ans : s);
                s = "";
            }
            else
                s += input[y + 1][x];

        if (s.length >= 2)
            ans = ans == "" ? s : (ans < s ? ans : s);
    }

    return ans;
}

const [r, c] = input[0].split(' ').map(Number);
const s1 = get_s1(), s2 = get_s2();
const ans = s1 < s2 ? s1 : s2;
console.log(ans);