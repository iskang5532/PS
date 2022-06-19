// 2022-06-15
// 22233 가희와 키워드
// https://www.acmicpc.net/problem/22233
/*
    셋, 파싱 (140,232KB, 1,316ms)
    시간 복잡도: ?
    풀이)
    - 메모장에 적은 n개의 키워드를 셋 s에 저장.
    - 문자열을 입력받음.
    입력받은 문자열 s를 쉼표를 구분하여 나눈 후, 셋에서 문자열을 지움.
    셋의 크기를 배열 ans에 저장.
    이후 입력받은 문자열도 위와 마찬가지로 진행.
    - 주의할 점은,  셋이 갱신될 때마다 출력할 경우 TLE.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

function get_set(n: number, m: number): Set<string> {
    let S = new Set("");

    for (let i = 1; i <= n; i++)
        S.add(input[i].trim());

    return S;
}

function update_set(S: Set<string>, word: string) {

    let s = "";
    for (let i = 0; i < word.length; i++) {
        if (word[i] === ',')
            S.delete(s), s = "";
        else
            s += word[i];
    }
    S.delete(s);
}

const [n, m] = input[0].split(' ').map(Number);
const S = get_set(n, m);

let ans: number[] = [];
for (let i = 0; i < m; i++) {
    update_set(S, input[n + 1 + i].trim());
    ans.push(S.size);
}

console.log(ans.join('\n'));