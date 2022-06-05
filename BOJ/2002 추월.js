// 2022-06-01
// 2002 추월
// https://www.acmicpc.net/problem/2002
/*
    구현, 맵 (9,752KB, 200ms)
    시간 복잡도: O(logN)
    풀이)
    - 차랑이 들어간 순서를 저장할 m. (m[s] = k일 경우, 차량 번호 s는 터널에 k번째로 들어감)
    = i번째로 빠져나간 차량이 몇 번째로 터널에 들어왔는지를 저장할 v. (v[i] = k일 때, i번째 차량은 k번째로 터널에 들어옴)
    - 터널에서 빠져나간 차량 s를 기준으로, 아직 터널에 남아 있는 차량 중에서 s보다 일찍 들어온 차량이 있을 시 ans++.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_v(n) {
    let m = new Map(); // 차량이 들어온 순서를 저장
    for (let i = 1; i <= n; i++) {
        let s = input[i].trim();
        m.set(s, i);
    }

    let v = [];  // v[i] = k일 때, i번째 차량은 k번째로 터널에 들어옴
    for (let i = n + 1; i < 2 * n + 1; i++) {
        let s = input[i].trim();
        v[i - n - 1] = m.get(s);
    }

    return v;
}

function get_ans(v) {
    let ans = 0;
    for (let i = 0; i < n - 1; i++)
        for (let j = i + 1, flag = true; j < n && flag; j++)
            if (v[i] > v[j])
                ans++, flag = false;
    return ans;
}

const n = +input[0]; // 차의 대수 (1 ≤ N ≤ 1,000)
const v = get_v(n);
console.log(get_ans(v));