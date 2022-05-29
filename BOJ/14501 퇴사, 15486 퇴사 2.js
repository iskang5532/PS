// 2022-05-23
// 14501 퇴사, 15486 퇴사 2
// https://boj.kr/14501 https://boj.kr/15486
/*
    DP (158,864KB, 1,724ms)
    시간 복잡도: O(n)
    풀이)
    - dp[i] = k일 때, i일에 얻을 수 있는 최대 금액은 k.
    - n+1일에 퇴사. 즉, n+1일에 얻을 수 있는 최대 금액을 출력해야 함.
    현재 풀이에서는 for문에서 n일까지 갱신됨.
    즉, dp[n+1]은 갱신되지 않았으므로 두 값을 비교 후 더 큰 값을 출력함. (dp[n] > dp[n+1]일 수 있음)
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "a_test/text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

const get_ans = (n) => {
    const MAX = 1510000;
    let dp = Array.from({ length: MAX }, () => 0);
    // Array(MAX).fill(0);

    for (let i = 1; i <= n; i++) {
        dp[i] = Math.max(dp[i], dp[i - 1]);

        const [t, p] = input[i].split(' ').map(Number);
        const nt = i + t;
        dp[nt] = Math.max(dp[nt], dp[i] + p);
    }

    return Math.max(dp[n], dp[n + 1]);
}


const n = +input[0];
console.log(get_ans(n));