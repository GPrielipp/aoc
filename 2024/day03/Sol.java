import java.util.*;
import java.io.*;
import java.util.regex.*;

public class Sol
{
  public static void main(String[] args) throws FileNotFoundException,  NumberFormatException
  {
    //Scanner in = new Scanner(new FileInputStream("smallinput")); 
    //String input = "";
    //while(in.hasNextLine())
    //input += in.nextLine();
    //PDA pda = new PDA(input);

    Scanner in = new Scanner(new FileInputStream("input"));
    String input = "";
    while(in.hasNextLine()) input += in.nextLine();

    int sum = 0;
    Pattern mulPat = Pattern.compile("mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don\'t\\(\\)");
    Pattern intPat = Pattern.compile("[0-9]+");
   
    Matcher muls = mulPat.matcher(input);
    boolean doMul = true;
    while(!muls.hitEnd() && muls.find()) 
    {
      String next = muls.group();
      if(next.equals("do()")) doMul = true;
      else if(next.equals("don't()")) doMul = false;
      else
      {
        Matcher nums = intPat.matcher(next);
        nums.find();
        Integer a = Integer.parseInt(nums.group()); 
        nums.find();
        Integer b = Integer.parseInt(nums.group()); 
        
        if(doMul)
          sum += a * b;
      } 
    }
    System.out.println("Sum is " + sum);
  }
}
