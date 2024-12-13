import java.util.*;
import java.io.*;

public class Sol
{
  private static int abs(int x)
  {
    return (x >= 0? x:-x);
  }

  private static String lookAlong(List<String> grid, int x, int y, int dx, int dy, int upTo)
  {
    int maxY = grid.size();
    int maxX = grid.get(0).length();
   
    // will go out of bounds looking 
    if( 
        !( (x + dx*(upTo-1)) >= 0 && (x + dx*upTo) <= maxX ) || 
        !( (y + dy*(upTo-1)) >= 0 && (y + dy*upTo) <= maxY )
      ) return "";
 
    String build = "";
    //System.out.print("x=" + x + " y=" + y + " dx=" + dx + " dy=" + dy + " upTo=" + upTo + "\t");
    for(int mul = 0; mul < upTo; mul++)
    {
      build += grid.get( y + dy*mul ).charAt( x + dx*mul );
    }
    //System.out.println(build);
    return build;
  }

  private static int search(String toFind, int x, int y, List<String> grid)
  {
    List<String> strsAlongPaths = new ArrayList<>();
    int wordLen = toFind.length();

    // all of the possible directions
    for(int dy = -1; dy <= 1; dy++)
    {
      for(int dx = -1; dx <= 1; dx++)
      {
        if(dy != 0 || dx != 0)
          strsAlongPaths.add( lookAlong(grid, x, y, dx, dy, wordLen) );
      }
    }
    //System.out.println();
    
    // count up the matches
    int count = 0;
    for(String str : strsAlongPaths)
    {
      if(str.equals(toFind)) //count++;
      {
        for(int dy=-1; dy <= 1; dy++)
        {
          for(int dx=-1; dx <= 1; dx++)
          {
            if(dy == 0 || dx == 0)
            {
              String t1 = lookAlong(grid, x + dx*(wordLen-1), y + dy*(wordLen-1), (dx == 0 ? -1:-dx), (dy == 0 ? -1:-dy), wordLen);
              String t2 = lookAlong(grid, x + dx*(wordLen-1), y + dy*(wordLen-1), (dx == 0 ?  1:-dx), (dy == 0 ?  1:-dy), wordLen);
              if(t1.equals(toFind)) return 1;
              if(t2.equals(toFind)) return 1;
            }
          }
        }
      }
    }
    return count;
  }

  public static void main(String[] args) throws FileNotFoundException
  {
    Scanner in = new Scanner(new FileInputStream("small2")); 

    List<String> grid = new ArrayList<>();
    while(in.hasNextLine()) grid.add(in.nextLine());

    int count = 0;

    for(int y = 0; y < grid.size(); y++)
    {
      String row = grid.get(y);
      for(int x = 0; x < row.length(); x++)
      {
        count += search("MAS", x, y, grid);
      }
    }

    System.out.println("count = " + count);
  }
}
