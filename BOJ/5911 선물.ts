// 2022-07-06
// 5911 선물
// https://www.acmicpc.net/problem/5911
/*
    그리디, 정렬 (10,016KB, 184ms)
    시간 복잡도: ?
    풀이)
    - 선물을 보내는데 필요한 선물 비용을 기준으로 오름차순 정렬.
    만약, 선물 비용이 같으면 선물의 가격을 기준으로 내림차순 정렬.
    내림차순 정렬의 이유는, 더 비싼 가격의 선물을 할인하게 되면 선물 비용이 줄어들기 때문.
    - 현재까지 가장 비싼 선물 가격을 저장할 mx.
    - i번째 선물과 이전까지의 선물 비용의 합이 b를 넘을 수 있음.
    이때, 현재까지 확인한 선물 가격 중 가장 비싼 선물인 mx를 할인시킨다면 남은 b원으로 살 수 있는지를 확인.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n");

function get_ans(v: { p: number, s: number; }[], b: number): number {
    let ans = 0;
    let mx = 0;
    for (const { p, s } of v) {
        mx = Math.max(mx, p);

        if (b - (p + s) + mx - Math.floor(mx / 2) < 0)
            break;
        b -= p + s, ans++;
    }

    return ans;
}

const [n, b] = input[0].split(' ').map(Number);
let v: { p: number, s: number; }[] = [];
for (let i = 1; i <= n; i++) {
    const [p, s] = input[i].split(' ').map(Number);
    v.push({ p, s });
}

v.sort((p1, p2) => {
    const a = p1.p + p1.s, b = p2.p + p2.s;
    return a != b ? a - b : p2.p - p1.p; // 선물 비용 오름차순, 선물 가격 내림차순
});

console.log(get_ans(v, b));
