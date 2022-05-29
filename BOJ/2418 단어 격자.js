// 2022-05-27
// 2418 단어 격자
// https://www.acmicpc.net/problem/2418
/*
    DP (21,736KB, 288ms)
    시간 복잡도: O(hwl * 8)
    풀이)
    - dp[y][x][dep] == k일 때, (y, x)에 도달하면서 dep번째 단어까지 만들 수 있는 개수는 k개.
    - 단어에서 탐색중인 문자의 위치를 dep이라 할 때, dep번째까지의 단어를 만들 수 있는 경우의 수를 구한 후 dp에 저장.
    - (y, x)가 board[dep]의 문자와 일치하는 경우, 이전 위치 [py][px]에서 이전 문자 board[dep - 1]를 찾음.
    이후, 현재 위치 dp인 dp[y][x]에 이전 문자의 경우의 수인 dp[py][nx]를 더함. (= dp[y][x][dep] += dp[py][px][dep - 1])
    etc.)
    - 이러한 dp 문제를 푼 적이 있었는데, 결국 까먹고 헤맴..
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const [h, w, l] = input[0].split(' ').map(Number);
const s = input[h + 1];

const OOB = (py, px) => { return !(0 <= py && py < h) || !(0 <= px && px < w); }

const get_dp = () => {
    let board = Array.from(Array(h), () => (Array(w)));
    let dp = Array.from(Array(h), () => (Array.from(Array(w), () => Array(l).fill(0))))

    for (let i = 0; i < h; i++)
        for (let j = 0; j < w; j++) {
            board[i][j] = input[1 + i][j];

            if (board[i][j] === s[0])
                dp[i][j][0]++;
        }


    const dy = [-1, -1, 0, 1, 1, 1, 0, -1]; // 북에서부터 시계 방향
    const dx = [0, 1, 1, 1, 0, -1, -1, -1];

    for (let dep = 1; dep < l; dep++)
        for (let y = 0; y < h; y++)
            for (let x = 0; x < w; x++)
                if (board[y][x] == s[dep]) // 필요한 문자인 경우
                    for (let d = 0; d < 8; d++) {
                        const [py, px] = [y + dy[d], x + dx[d]]; // 이전 문자의 위치
                        if (OOB(py, px))
                            continue;
                        if (board[py][px] != s[dep - 1])
                            continue;

                        dp[y][x][dep] += dp[py][px][dep - 1];
                    }

    return dp;
}

let dp = get_dp();

let ans = 0;
for (let y = 0; y < h; y++)
    for (let x = 0; x < w; x++)
        ans += dp[y][x][l - 1];
console.log(ans);