import java.util.*;

/**
 * CFG: (symbols, non-terminals, rules, start symbol)
 * PDA: (states, symbols, symbols on stack, transitions, start state, end state)
 */

/**
 * representing:
 * S --> mul(N,N) | SS | *e
 * N --> ND | D
 * D --> 1 | 2 | 3  | 4 | 5 | 6 | 7 | 8 | 9 | 0
 */ 

/**
* MAJOR TRANSITION BECAUSE I JUST WANT TO SOLVE THIS
* SO NOW IM GOING TO SEE IF PATTERN WITH SCANNER WORKS
*/

public class PDA
{
  // only states are going to be q0, q1, q2
  // end state is going to be q2
  // start state is going to be q0
  private String curState = "q0";
  private String endState = "q2";
  private Map<String, List<Transition>> transitions = new HashMap<>();
  private Stack<Node> stack = new Stack<>();
  
  private interface Node
  {
    int eval();
    String type();
    String toString();
  }

  private class S implements Node
  {
    private Node left, right;
    
    public String type() { return "S"; }

    public int eval()
    {
      if(left.type().equals("N")) return left.eval() * right.eval();
      else if(left.type().equals("S")) return left.eval() + right.eval();
      return -1;
    }

    public String toString()
    {
      if(left.type().equals("N")) return "mul(" + left.toString() + "," + right.toString() + ")";
      else if(left.type().equals("S")) return left.toString() + right.toString();
      return "error"; 
    }
  }

  private class N implements Node
  {
    private String digit;
    private Node child;

    public String type() { return "N"; }
    
    public int eval()
    {
      try{ return Integer.parseInt(toString());  }
      catch (Exception e) { return -1; } 
    }
  
    public String toString()
    {
      return digit + child.toString();
    }
  }

  private class D implements Node
  {
    private String digit;

    public String type() { return "D"; }
    
    public int eval()
    {
      try{ return Integer.parseInt(toString());  }
      catch (Exception e) { return -1; } 
    }

    public String toString() { return digit; }
  }

  private class Transition
  {
    private String fromInput; // Node.type()
    private String fromStack; // Node.type()
    private String toState;
    private String toStack;   // Node.type() 
    public Transition(String fi, String fs, String tstate, String tstack) { fromInput = fi; fromStack = fs; toState = tstate; toStack = tstack; }
  } 

  /**
   * representing:
   * S --> mul(N,N) | SS | *e (getting "rid of" the lambda here)
   * N --> ND | D
   * D --> 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
   */   
  public PDA(String input)
  {
    // e = epsilon (lambda)
    List<Transition> q0 = new ArrayList<>();   
    q0.add(new Transition("","","q1","$"));
    transitions.put("q0",q0); 
    
    List<Transition> q1 = new ArrayList<>();   
    q1.add(new Transition("","$","q2","")); 
    q1.add(new Transition("","(N,N)lum", "q1","S")); 
    q1.add(new Transition("","SS", "q1","S")); 
    q1.add(new Transition("","DN", "q1","N")); 
    q1.add(new Transition("","D", "q1","N")); 
    q1.add(new Transition("","0", "q1","D")); 
    q1.add(new Transition("","1", "q1","D")); 
    q1.add(new Transition("","2", "q1","D")); 
    q1.add(new Transition("","3", "q1","D")); 
    q1.add(new Transition("","4", "q1","D")); 
    q1.add(new Transition("","5", "q1","D")); 
    q1.add(new Transition("","6", "q1","D")); 
    q1.add(new Transition("","7", "q1","D")); 
    q1.add(new Transition("","8", "q1","D")); 
    q1.add(new Transition("","9", "q1","D")); 
    
    transitions.put("q1",q1); 

    run(input);
  }

  private void run(String input)
  {
    Scanner charStream = new Scanner(input);
    charStream.useDelimiter("");
    while(!curState.equals("q2"))
    {
      transition(charStream);
    }
  } 

  private void transition(Scanner input)
  {
    String next = "";
    if(input.hasNext()) next = input.next();

    List<Transition> possible = transitions.get(curState);

    Transition transition;
    for(Transition t : possible)
    {
      if(t.fromInput.equals("no"))
      {

      }
    }
  }

}
