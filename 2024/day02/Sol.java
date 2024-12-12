import java.util.*;
import java.io.*;

public class Sol
{
  static final String ANSI_RESET = "\u001B[0m" ;
  static final String ANSI_RED   = "\u001B[41m"; 
  static final String ANSI_GREEN = "\u001B[42m";
  static final String ANSI_YELLOW= "\u001B[43m";

  public static boolean isSafeProblemDampener(List<Integer> report)
  {
    if(isSafe(report)) return true;
    else
    {
      for(int i = 0; i < report.size(); i++)
      {
        List<Integer> copy = new ArrayList<>();
        copy.addAll(report);
        copy.remove(i);
        if(isSafe(copy)) return true;
      }
      return false;
    }
  }

  public static boolean isSafe(List<Integer> report)
  {
    int minDiff = 1, maxDiff = 3;
    int dir = 0;
    Integer prev = -1;
    for(int i = 0; i < report.size(); i++)
    {
      Integer level = report.get(i);
      if(prev == -1)
      {
        prev = level;
        continue;
      }

      int diff = Math.abs(level - prev);
    
      int testDir = (level-prev == 0 ? 0:level - prev > 0 ? 1:-1);
      if(dir == 0) dir = testDir;


      if(!(diff >= minDiff && diff <= maxDiff) || testDir != dir)
      {
        //if(doRecursion)
        //{
          //List<Integer> copy1 = new ArrayList<>();
          //copy1.addAll(report);
          //copy1.remove(i);
          
          //List<Integer> copy2 = new ArrayList<>();
          //copy2.addAll(report);
          //copy2.remove(i-1);

          //System.out.println(ANSI_YELLOW + "trying\t"+level + " @ " + i + "\t"+report + ANSI_RESET);
          //System.out.println(ANSI_YELLOW + "trying\t"+prev + " @ " + (i-1) +"\t"+report+ ANSI_RESET);
          
          //return isSafe(copy1, false) || isSafe(copy2, false);
        //}

        return false;
      }

      prev = level;
    }
    return true;
  }

  public static void main(String[] args) throws FileNotFoundException
  {
    Scanner fileReader = new Scanner(new FileInputStream("input"));

    List<List<Integer>> reports = new LinkedList<>();

    while(fileReader.hasNextLine())
    {
      Scanner reportReader = new Scanner(fileReader.nextLine());
      List<Integer> report = new LinkedList<>();
      while(reportReader.hasNext())
        report.add( reportReader.nextInt() );
      reports.add(report);
    }

    int numSafeReports = 0;

    for(List<Integer> report : reports)
    {
      if(isSafeProblemDampener(report))
      {
        //System.out.println(ANSI_GREEN + "safe\t"+report + ANSI_RESET);
        numSafeReports++;
      }
      else
      {
        //System.out.println(ANSI_RED + "unsafe\t"+report + ANSI_RESET);
      }
    }
    System.out.println(numSafeReports + " reports are safe");
  }
}
