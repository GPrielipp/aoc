import java.util.*;
import java.io.*;

public class Sol
{
  public static void main(String[] args) throws FileNotFoundException
  {
    Scanner is = new Scanner(new FileInputStream("input"));
    List<Integer> l1 = new ArrayList<>();
    List<Integer> l2 = new ArrayList<>();
    List<Integer> list = l1;
    Map<Integer,Integer> numOccurrences = new HashMap<>();

    boolean isL1 = true;
   
    // read in the data
    while(is.hasNext())
    {
      Integer in = is.nextInt();
      list.add(in);
      if(isL1)
      {
        list = l2;
      }
      else
        list = l1;
      isL1 = !isL1;
    }
   
    // "pair" up the values 
    Collections.sort(l1);
    Collections.sort(l2);

    for(Integer i : l1)
      numOccurrences.put(i, 0);
    for(Integer i : l2)
    {
      if(numOccurrences.containsKey(i))
        numOccurrences.replace(i, numOccurrences.get(i)+1);
    }

    // find the differences and compute the sum
    int sum = 0;
    Iterator<Integer> i1 = l1.iterator();
    Iterator<Integer> i2 = l2.iterator();
    while(i1.hasNext() && i2.hasNext())
    {
      int diff = Math.abs(i2.next() - i1.next()); 
      sum += diff; 
    }

    System.out.println("Total difference = " + sum);

    sum = 0;
    for(Integer key : l1) 
    {
      //System.out.println(key + ": " + numOccurrences.get(key));
      sum += key * numOccurrences.get(key);
    }

    System.out.println("Similarity score = " + sum);
  }
}
