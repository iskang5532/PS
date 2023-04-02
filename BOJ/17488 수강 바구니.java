// 2023-03-29
// 17488 수강 바구니
// https://www.acmicpc.net/problem/17488
/*
    구현 (150,580KB, 1,420ms)
    시간 복잡도: ?
    풀이)
    - 과목을 신청한 학생을 select[]에 저장.
    - select[]의 크기와 cnt[]의 크기를 비교하여 과목을 신청한 학생이 모두 신청에 성공할 수 있는지 확인.
    만약 cnt[]의 크기가 클 경우, 모두 성공이므로 해당 학생들을 ans[]에 저장.
    만약 select[]의 크기가 클 경우, 신청할 수 없음.
    성공 혹은 실패 후 cnt[]는 신청한 학생의 수만큼 값을 뺌.
    - 총 두 번의 수행으로 ans[]를 구함.
    - ans[]에 저장된 값을 출력. (이때, 오름차순 출력이 필요하므로 정렬)
    만약 ans[]가 비었을 경우, 학생은 수강 신청에 실패.
 */

import java.io.*;
import java.util.*;

public class Main {
    static int MAX = 1003;// max n, m

    static int n, m; // 학생의 수 n, 과목의 수 m(1 ≤ n, m ≤ 1,000)
    static int[] cnt = new int[MAX];
    static ArrayList<Integer>[] ans = new ArrayList[MAX]; // 학생의 신청 성공 과목을 저장

    static void get_ans(BufferedReader br) throws IOException {
        ArrayList<Integer>[] select = new ArrayList[MAX]; // select[i] = {a, b}일 경우, i번 과목을 선택한 학생은 {a, b}
        for (int i = 0; i < MAX; i++)
            select[i] = new ArrayList<>();

        for (int i = 1; i <= n; i++) {
            StringTokenizer tk = new StringTokenizer(br.readLine());
            while (true) {
                int p = Integer.parseInt(tk.nextToken());
                if (p == -1)
                    break;
                select[p].add(i);
            }
        }

        for (int i = 1; i <= m; i++) // i번 과목
        {
            if (cnt[i] >= select[i].size())
                for (final int people : select[i])
                    ans[people].add(i);
            cnt[i] -= select[i].size();
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer tk;
        tk = new StringTokenizer(br.readLine());
        n = Integer.parseInt(tk.nextToken());
        m = Integer.parseInt(tk.nextToken());

        tk = new StringTokenizer(br.readLine());
        for (int i = 1; i <= m; i++)
            cnt[i] = Integer.parseInt(tk.nextToken());

        for (int i = 0; i < MAX; i++)
            ans[i] = new ArrayList<>();

        get_ans(br);
        get_ans(br);

        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= n; i++, sb.append('\n'))
            if (ans[i].isEmpty())
                sb.append("망했어요");
            else {
                Collections.sort(ans[i]);
                for (final int p : ans[i])
                    sb.append(p).append(' ');
            }
        System.out.println(sb.toString());
    }
}