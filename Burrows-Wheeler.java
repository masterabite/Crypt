import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
  public static void main(String[] args){
    String book = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
    
    Scanner scan = new Scanner(System.in);
    int n = scan.nextInt();
    --n;
    String str = scan.next();
    
    int[] cnt = new int[book.length()];
    int[] les = new int[book.length()];
    int[] eq = new int[str.length()];

    int pos;
    for (int i = 0; i < str.length(); ++i){
        pos = book.indexOf(str.charAt(i));
        eq[i] = cnt[pos]++;
    }
    
    les[0] = 0;
    for (int i = 1; i < book.length(); ++i){
        les[i] = les[i-1]+cnt[i-1];
    }
    
    String ans = "";
    
    for (int i = n, k = 0; k < str.length(); ++k) {
        ans += str.charAt(i);
        pos = book.indexOf(str.charAt(i));
        i = eq[i]+les[pos];
    }
    
    for (int i = ans.length()-1; i >= 0; --i) {
        System.out.print(ans.charAt(i));
    }System.out.println();
  }
}
