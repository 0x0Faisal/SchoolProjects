import java.util.*;
/**
 *
 * In this class we will solve a quadratic congruence equation of the form,
 * 		ax^2 + bx + c = 0 mod p			where "=" is a Congruence
 *
 * 
 * @author CSC281 team project
 *
 */
public class QuadraticCongruenceEquation {
	
	//input integers
	private static int a;
	private static int b;
	private static int c;
	private static int p;
	// d = b^2 - 4ac
	private static int d;
	//Alpha variable
	private static int alpha;
	// the solutions
	private static int x1, x2;
	
	//checks if p is odd prime or not
	public static boolean isOddPrime(int p) {   
		if(p <= 2)
			return false;
		int x = (int)Math.sqrt(p);
		
		for(int i = 2; i <= x; i++)
			if(p % i == 0)
				return false;
		return true;
	}
	
	//Check if d is perfect square
	public static boolean isPerfectSquare(double d) {
		double x = Math.sqrt(d);
		if(x - (int)x == 0)
			return true;
		return false;
	}
	
	//find the value of alpha
	public static int findAlpha() throws ArithmeticException {
    	int k = 0;
    	boolean bool = false;
    	while(!bool) {
    		bool = isPerfectSquare(d + (p * k));
    		System.out.println(bool);
    		if(bool)
    			return (int)(Math.sqrt(d + (p * k)));
    		k++;
    	}
    	throw new ArithmeticException("Alpha value cannot be found");
    }
	
	//Method to find inverse of a in m
	public static int Inverse(int a, int m) throws ArithmeticException {
	    	a = a % m;
	    	
	    	for(int i = 1; i < m; i++)
	    		if((a * i) % m == 1)
	    			return i;
	    	throw new ArithmeticException("a has no inverse");
	    }
	
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		
		//reading values
		System.out.print("Enter a, b, c and p: ");
		a = input.nextInt(); b = input.nextInt(); c = input.nextInt();  p = input.nextInt();
		
		//p must be odd prime
		//and p is not divides a
		if(isOddPrime(p) && p % a != 0) {
			// d = b^2 - 4ac
			d = (int) (Math.pow(b, 2) - (4 * a * c));
			//p must not divide d 
			//d need to be perfect square, by b^2 - 4ac = alpha^2
			if(isPerfectSquare(d) && d % p != 0) {  //the original is p % d  
				//determine the value of "d^(p-1)/2 (mod p)" 
				// when it's Congruence to 1 (mod p) --> Has solution
				if(Math.pow(d, (p-1) / 2) % p == 1) {
					try{
							alpha = findAlpha();
						int bCopy = -b;                    
						int a2 = (2 * a) % p;    //a2 has the remainder of 2 * a in mod p
						
						//add p to negative b for avoiding negative value
						while(bCopy < 0 && bCopy < p) {    
							bCopy += p;
						}
						//change a2 to store the inverse
						a2 = Inverse(a2, p);
						
						//final solution
						if(a2 != 0 && alpha != 0) {
							x1 = (bCopy + alpha) * a2;
							x1 %= p;
							x2 = (bCopy - alpha) * a2;
							x2 %= p;
							System.out.println("The solutions are {" + x1 + ", " + x2 + "}");
						}
						else
							System.out.println("Alpha or invers of 2a is zero");

					} catch(ArithmeticException e){}
					} 
					else { 
						if(Math.sqrt((p-1) / 2) % p == 1)
							System.out.println("No solution");
						else
							System.out.println("Somthing wrong");
					}
			} 
			else
				System.out.println("d is not perfect Square");
		}
		 else
			System.out.println("P is not odd prime or a is not Congruence to \"1 mod p\"");
	}

}
