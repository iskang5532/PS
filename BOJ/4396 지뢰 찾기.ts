// 2022-06-15
// 4396 지뢰 찾기
// https://www.acmicpc.net/problem/4396
/*
    구현 (9,396KB, 120ms)
    시간 복잡도: ?
    풀이)
    - 주변에 지뢰가 몇 개 있는지를 저장할 cnt. (cnt[y][x] = k일 때, {y, x} 주변에는 지뢰가 k개)
    - 해당 위치에 지뢰가 존재하는지를 저장할 bomb. (bomb[y][x] = true일 때, {y, x}는 지뢰가 존재)
    1. 탐색중인 칸 {y, x}가 플레이어가 고른 칸일 경우, ans[y][x]에 cnt[y][x]를 저장.
    이때, {y, x}에 지뢰가 존재할 경우 boom = true.
    2. 만약 지뢰가 있는 칸을 골랐을 경우
    bomb의 모든 값을 확인하며, 지뢰의 위치와 똑같은 ans의 위치에 지뢰를 넣음. (기존 값 → '*')
    3. ans 출력.
 */


const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

const dy = [- 1, -1, 0, 1, 1, 1, 0, -1];
const dx = [0, 1, 1, 1, 0, - 1, -1, -1];
const OOB = (ny: number, nx: number): boolean => { return !(0 <= ny && ny < n) || !(0 <= nx && nx < n); };

function get_bomb(n: number): [boolean[][], number[][]] {
    let bomb: boolean[][] = Array.from(Array(n), () => (Array(n)));
    let cnt: number[][] = Array.from(Array(n), () => (Array(n).fill(0)));

    for (let y = 0; y < n; y++)
        for (let x = 0; x < n; x++) {
            const c = input[1 + y][x];
            if (c === '*') {
                bomb[y][x] = true;

                for (let d = 0; d < 8; d++) {
                    const [ny, nx] = [y + dy[d], x + dx[d]];
                    if (OOB(ny, nx))
                        continue;
                    cnt[ny][nx]++;
                }
            }
        }

    return [bomb, cnt];
}

function get_ans(n: number, bomb: boolean[][], cnt: number[][]): string[][] {
    let ans: string[][] = Array.from(Array(n), () => Array(n));

    let boom = false; // 폭탄을 건드렸는가
    for (let y = 0; y < n; y++)
        for (let x = 0; x < n; x++) {
            let c = input[n + 1 + y][x];
            if (bomb[y][x] && c === 'x')
                boom = true;

            ans[y][x] = (c === 'x' ? cnt[y][x].toString() : '.');
        }
    for (let y = 0; y < n && boom; y++)
        for (let x = 0; x < n; x++)
            if (bomb[y][x])
                ans[y][x] = '*';

    return ans;
}

const n = +input[0]; // 1 ≤ N ≤ 30
// bomb[y][x] = true일 떄, {y, x}에 지뢰가 존재함
// cnt[y][x] = k일 때, {y, x} 주변에 지뢰가 k개 존재함
const [bomb, cnt] = get_bomb(n);
const ans = get_ans(n, bomb, cnt);
for (let i = 0; i < ans.length; i++)
    console.log(ans[i].join(''));
