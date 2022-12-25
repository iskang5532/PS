// 2022-12-23
// 16113 시그널
// https://www.acmicpc.net/problem/16113
/*
    맵, 구현 (20,472KB, 156ms)
    시간 복잡도: ?
    풀이)
    - 1을 제외한 나머지 수는 3x5의 형식을 띄고 있음. 이를 2진수로 변환하여 맵에 저장한 후, 입력된 시그널에 맞춰 수로 변환.
    - 숫자와 숫자 사이에는 공백이 존재함. 그러므로 1 옆에는 모두 흰색.
    이를 이용하여 현재 탐색중인 열이 모두 검은색이면서 인접한 곳에 검은색이 없을 경우, 1임을 알 수 있음.
    - x를 옮겨가며 해당 위치에 수가 있는지 확인하며, 있을 경우 어떤 수인지 확인.
    이때, 수를 발견했을 경우 해당 수의 행만큼 x를 옮겨줘야 중복 검사를 면할 수 있음.
 */

 import java.io.*;
 import java.util.*;
 
 public class Main {
     static final int MAX = 100003; // max n
 
     static StringBuilder ans = new StringBuilder();
     static boolean[][] board = new boolean[50][MAX];
     static Map<Integer, Character> m = new HashMap<>();
 
     static void _init_map() {
         m.put(0b111101101101111, '0');
         // m.put(0b010010010010010, '1');
         m.put(0b111001111100111, '2');
         m.put(0b111100111100111, '3');
         m.put(0b100100111101101, '4');
         m.put(0b111100111001111, '5');
         m.put(0b111101111001111, '6');
         m.put(0b100100100100111, '7');
         m.put(0b111101111101111, '8');
         m.put(0b111100111101111, '9');
     }
 
     static char get_num(int x) // 시그널 해독
     {
         int bit = 0;
         for (int i = 0; i < 3 * 5; i++)
             if (board[i / 3][x + i % 3])
                 bit |= 1 << i;
 
         return m.get(bit);
     }
 
     public static void main(String[] argm) throws IOException {
         BufferedReader br = new BufferedReader(new InputStreamReader((System.in)));
 
         int n = Integer.parseInt(br.readLine()); // 시그널의 길이 (5 ≤ n ≤ 100,000)
         String signal = br.readLine();
 
         for (int y = 0; y < 5; y++)
             for (int x = 0; x < n / 5; x++)
                 board[y][x] = (signal.charAt(y * (n / 5) + x) == '#' ? true : false);
 
         _init_map();
         for (int x = 0; x < n / 5;) {
             boolean isOne = true; // 숫자가 있다면, 해당 숫자가 1인지를 저장
             if (board[0][x]) // 숫자가 있는가?
             {
                 for (int y = 0; y < 5 && isOne; y++)
                     if (board[y][x + 1] == true)
                         isOne = false;
 
                 ans.append(isOne ? '1' : get_num(x));
             }
 
             x += (isOne ? 1 : 3);
         }
 
         System.out.println(ans.toString());
     }
 }