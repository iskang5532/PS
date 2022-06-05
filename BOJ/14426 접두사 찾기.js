// 2022-05-30
// 14426 접두사 찾기
// https://www.acmicpc.net/problem/14426
/*
    셋 (52,004KB, 4,512ms)
    시간 복잡도: ?
    풀이)
    - 문자열을 저장할 셋 S.
    - 문자열 s를 n개 입력받음.
     - 문자열 s를 1개부터 s.length()개의 문자열로 쪼개어 셋에 저장.
    - 문자열 s를 m개 입력받음.
     - 입력받은 문자열 s가 셋에 존재하는지 확인.
     만약 존재할 경우 ans++.
    - 주의할 점은, 입력받은 n개의 문자열 혹은 m개의 문자열을 가져올 때 필요없는 문자(\r)가 포함될 수 있음. (trim()을 이용하여 해결함)
    etc.) 트라이 전용 문제는 아닌듯 싶다.
 */
const PATH = process.platform === "linux" ? "/dev/stdin" : "text.txt";
const input = require("fs").readFileSync(PATH, "utf-8").toString().trim().split("\n"); // arr

function get_set() {
    let S = new Set();
    for (let i = 1; i <= n; i++) {
        let s = input[i].trim();

        let _s = "";
        for (let i = 0; i < s.length; i++)
            _s += s[i], S.add(_s);
    }

    return S;
}

function get_ans() {
    let ans = 0;
    for (let i = 1 + n; i <= n + m; i++) {
        let s = input[i].trim();
        if (S.has(s))
            ans++;
    }

    return ans;
}

const [n, m] = input[0].split(' ').map(Number);

const S = get_set();
const ans = get_ans();
console.log(ans);
