// 2022-06-30
// 11508 2+1 세일
// https://www.acmicpc.net/problem/11508
/*
    그리디 (23,928KB, 320ms)
    시간 복잡도: ?
    풀이)
    - 큰 값을 없애면 최소비용으로 구매할 수 있음.
    - 세 가지 제품 중 가장 낮은 값이지만 다른 제품에 비해 상대적으로 비싼 값일 경우 제외.
    - 입력된 값을 v에 저장한 후 내림차순 정렬.
    - v의 세 번째 값마다 ans에서 제외. (세 가지 제품 중 마지막 제품은 구매 가격에서 제외)
 */

// const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
// const input = require("fs").readFileSync(PATH, "utf-8").split("\n");
let input: any[] = [];
const read = require("readline").createInterface({ input: process.stdin, output: process.stdout })
    .on("line", function (line: any) {
        input.push(line);
    }).on("close", function () {
        solution(input);
        process.exit();
    });

function solution(input: any) {
    const [n, ...v] = input.map(Number);

    v.sort((a: number, b: number) => b - a);

    let ans = 0;
    for (let i = 0; i < n; i++)
        if (i % 3 != 2)
            ans += v[i];

    console.log(ans);
}