// 2022-06-17
// 24954 물약 구매
// https://www.acmicpc.net/problem/24954
/*
    DFS (12,320KB, 2,264ms)
    시간 복잡도: O(n!)?
    풀이)
    - n의 개수가 10이므로, dfs를 이용하여 최적화된 구매 비용을 구함.
    - i번쨰로 구매할 물약의 번호를 order에 저장.
    - order에 저장된 순으로 물약을 구매.
     - 물약을 구매할 때 사용한 가격을 저장할 sum.
     - 물약의 가격을 저장할 price. (따로 변수를 만든 이유는, 구매 순서에 따라 물약의 가격이 달라지므로 dfs 수행마다 따로 생성)
     - 현재 물약의 가격 price[cur]를 sum에 저장. 만약 price[cur] <= 0일 경우, 1을 저장.
     - 현재 구매할 물약의 번호가 cur일 때, info[cur]의 값을 이용하여 다른 물약의 가격을 낮춤.
     - ans에 sum과 비교하여 더 작은 값을 저장.
    etc.)
    - c를 n개가 아닌 4개만 받아놓고 TLE난다고 난리쳤던 문제
    - 물약은 여러번이 아닌 한번만 구매 가능한듯.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

function dfs(dep: number) {
    if (dep === n) {
        let sum = 0;

        let price = [...c];
        for (let i = 0; i < n; i++) {
            const cur = order[i];
            sum += Math.max(1, price[cur]);
            for (const { a, d } of info[cur])
                price[a] -= d;
        }

        ans = Math.min(ans, sum);
        return;
    }

    for (let i = 0; i < n; i++)
        if (!visited[i]) {
            visited[i] = true, order[dep] = i;
            dfs(dep + 1);
            visited[i] = false;
        }
}

const n = +input[0]; // 물약의 개수 (2 ≤ n ≤ 10)
const c = input[1].split(' ').map((i: string) => +i); // 물약의 가격 (1 ≤ c ≤ 1k)
const info: { a: number, d: number; }[][] = Array.from({ length: n }, () => []); // info[i] = {a, d}일 때, i번 물약을 구매할 시 a번 가격 -= d
// const info: Array<number>[][] = Array.from({ length: n }, () => []); 


let visited = Array.from({ length: n }, () => false);
let order = Array.from({ length: n }, () => 0);
let ans = 987654321;

for (let i = 0, pos = 2; i < n; i++, pos++) {
    let p = +input[pos]; // 할인 정보 개수 (0 ≤ p ≤ n-1)
    for (let j = 0; j < p; j++) {
        const [a, d] = input[++pos].split(' ').map((i: string) => +i);
        info[i].push({ a: a - 1, d });
    }
}

dfs(0);

console.log(ans);