// 2022-06-02
// 12904 A와 B
// https://www.acmicpc.net/problem/12904
/*
    그리디 (9,360KB, 164ms)
    시간 복잡도: ?
    풀이)
    - s → t가 아닌 t → s가 될 수 있는지를 구함.
    - s에 'A'를 추가하는 연산은 t에서 'A'를 제거하는 연산이며, 문자열을 뒤집고 'B'를 추가하는 연산은 'B'를 제거하고 뒤집는 연산이다.
    이를 합산해보면, t의 마지막 문자는 항상 제거하게 되며 마지막 문자가 'B'인 경우 뒤집기가 추가된다.
    두 문자열의 길이가 같아질 때까지 연산을 수행한 후, 문자열을 비교하여 출력한다.
    - t의 마지막 문자가 'A'인 경우, 임의의 문자열 s는 'A'를 추가하는 연산밖에 할 수 없다.
    s에 'B'를 추가하게 될 경우, t의 마지막 문자는 'B'여야 하기 때문이다.
    - 추가 및 제거, 뒤집기 연산을 위해 문자열을 배열로 만든 후 수행.
    etc.)
    - 참고하진 않았지만, 설명이 잘 되어있음. https://www.acmicpc.net/board/view/83783
 */

const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_str(t) {
    let arr = t.split('');
    while (s.length !== arr.length)
        if (arr[arr.length - 1] == 'A')
            arr.pop();
        else
            arr.pop(), arr.reverse();

    return arr.join('').trim();
}

const [s, t] = input.map(s => s.trim());// (length: 1 ≤ S ≤ 999, 2 ≤ T ≤ 1000, S < T)
const _s = get_str(t);

console.log(Number(s === _s));