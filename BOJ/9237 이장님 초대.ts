// 2022-06-28
// 9237 이장님 초대
// https://www.acmicpc.net/problem/9237
/*
    그리디 (19,160KB, 252ms)
    시간 복잡도: ?
    풀이)
    - 가장 빠르게 묘목이 다 자라는 날짜를 구하기 위해서는 늦게 걸리는 묘목을 먼저 심으면 된다.
    - 입력된 묘목의 자라는 기간을 t[]에 저장한 후, 내림차순 정렬을 한다.
    이후, 묘목을 심는 날은 하루를 소모하므로, 묘목을 심을 때마다 해당 묘목이 다 자라게 되는 날을 늘려준다.
    - 묘목을 구입한 날이 1일째이며 묘목을 심는데 1일이 필요하다. 즉, 해당 나무가 다 자라게 되는 날짜는 ti + 2이다.
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").split("\n"); // arr

function get_ans(v: number[]): number {
    let ans = 0;
    for (let i = 0; i < v.length; i++)
        ans = Math.max(ans, v[i] + i + 2);

    return ans;
}

const n = +input[0]; // 묘목의 수 (1 ≤ n ≤ 100,000)
const v = input[1].split(' ').map(Number); // 나무가 다 자라는데 걸리는 시간 (1 ≤ ti ≤ 1,000,000)

v.sort((a: number, b: number) => b - a); // 오름차순 정렬
console.log(get_ans(v));