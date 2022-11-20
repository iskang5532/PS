// 2022-11-17
// 2252 줄 세우기
// https://www.acmicpc.net/problem/2252
/*
    위상정렬 (104,964KB, 2,424ms)
    시간 복잡도: ?
    풀이)
    - in_degree[]에 i번보다 작은 확인된 학생의 수는 k명. (k명 이상이 i번보다 작을 수도 있음)
    확인된 학생 모두 i번보다 앞에 존재해야 함. 그러므로, bfs를 수행할 때 확인된 학생이 모두 탐색한 경우에만 i번을 큐에 추가.
    - in_degree가 0인 학생을 큐에 넣은 후, bfs를 수행. (줄의 앞쪽; 여러 명일 수 있음)
    - 큐에 들어간 값은 ret[]에 저장 후, bfs의 수행이 최종적으로 완료되면 ret를 출력.
    참고:
    큐 사용법: https://coding-factory.tistory.com/602
    2차원 배열에 대해: https://www.geeksforgeeks.org/array-of-arraylist-in-java/
                    https://velog.io/@pranne1224/Java-Type-Safety-%EC%9D%B4%EC%8A%88-%EA%B2%BD%ED%97%98
                    https://pompitzz.github.io/blog/Java/whyCantCreateGenericsArray.html#%E1%84%8C%E1%85%A6%E1%84%82%E1%85%A6%E1%84%85%E1%85%B5%E1%86%A8%E1%84%80%E1%85%AA-%E1%84%87%E1%85%A2%E1%84%8B%E1%85%A7%E1%86%AF%E1%84%8B%E1%85%B4-%E1%84%8E%E1%85%A1%E1%84%8B%E1%85%B5%E1%84%8C%E1%85%A5%E1%86%B7
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAX = 32003; // max n

    static int n, m; // 사람의 수 n(1 ≤ n ≤ 32,000), 비교한 횟수 m(1 ≤ m ≤ 100,000)
    static ArrayList<Integer>[] adj = new ArrayList[MAX];
    // @SuppressWarnings("unchecked")
    // static ArrayList<Integer>[] adj = (ArrayList<Integer>[]) new ArrayList[MAX];
    static int[] in_degree = new int[MAX]; // in_degree[i] = k일 경우, i번 학생보다 작은 확인된 학생의 수는 k명

    static ArrayList<Integer> bfs() {
        ArrayList<Integer> ret = new ArrayList<>();

        Queue<Integer> q = new LinkedList<>();
        for (int i = 1; i <= n; i++)
            if (in_degree[i] == 0) // 앞선 사람이 없음
            {
                q.add(i);
                ret.add(i);
            }

        while (q.size() > 0) {
            int cur = q.poll();

            for (final int next : adj[cur])
                if (--in_degree[next] == 0) {
                    q.add(next);
                    ret.add(next);
                }

        }

        return ret;
    }

    public static void main(String[] argu) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());

        for (int i = 0; i <= n; i++)
            adj[i] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int lo = Integer.parseInt(st.nextToken()), hi = Integer.parseInt(st.nextToken());

            adj[lo].add(hi);
            in_degree[hi]++;
        }

        ArrayList<Integer> ans = bfs();

        for (final int i : ans)
            System.out.printf("%d ", i);
    }
}