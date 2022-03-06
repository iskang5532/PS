// 3613 Java vs C++
// https://www.acmicpc.net/problem/3613
const s = require('fs').readFileSync(process.platform === 'linux' ? '/dev/stdin' : 'a_test/text.txt').toString().trim();


function isValid() {
    if (s[0] == '_' || s[s.length - 1] == '_' || s[0] == s[0].toUpperCase())
        return false;
    if (s.includes("__"))
        return false;

    if (s.includes('_'))
        language = "cpp";
    else
        language = "java";

    if (language == "cpp")
        for (const c of s)
            if (c != '_' && c == c.toUpperCase())
                return false;


    return true;
}

function get_ans() {

    if (language == "cpp") // to java
        return s.split('_')
            .map((word, idx) => !idx ? word : word[0].toUpperCase() + word.slice(1))
            .join('');
    else if (language == "java") // to cpp
    {
        let ret = "";
        for (const c of s) {
            if (c == c.toUpperCase())
                ret += '_'
            ret += c.toLowerCase();
        }

        return ret;
    }
}

let language = '';

console.log(isValid() ? get_ans() : "Error!");