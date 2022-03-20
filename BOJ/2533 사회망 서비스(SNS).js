// 2533 사회망 서비스(SNS)
// https://www.acmicpc.net/problem/2533
const PATH = process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt';
const input = require('fs').readFileSync(PATH, 'utf-8')
    .toString().trim().split('\n');
const n = +input[0];

const g = Array.from({ length: n + 1 }, () => []);
for (let i = 1; i < input.length; i++) {
    const [a, b] = input[i].split(' ').map(Number);
    g[a].push(b), g[b].push(a);
}

const v = Array.from({ length: n + 1 }, () => [0, 1]);
function dfs(cur, dad) {

    for (const next of g[cur]) {
        if (next == dad)
            continue;

        dfs(next, cur);
        v[cur][0] += v[next][1];
        v[cur][1] += Math.min(v[next][1], v[next][0]);
    }

}

dfs(1, -1);

console.log(Math.min(v[1][0], v[1][1]));