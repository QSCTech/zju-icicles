package Package1;

import java.util.Scanner;

/**
 * This class performs calculations on circle.
 * It includes 2 methods for calculating area and circumference of a circle
 * @author ABC
 * @version 1.0
 * @since 08 Feb 2016
 */
public class Circle {
 
	/**
	 * PI attribute
	 */
	public static double  PI=3.14159;
 
	/**
	 * Calculate area of a circle
	 * @param radius double
	 * @return area double 
	 */
	public static double area(double radius)
	{
		return PI*radius*radius;
	}
	
	/**
	 * Calculate circumference of a circle 
	 * @param radius double
	 * @return circumference
	 */
	
	public static double circumference(double radius)
	{
		return PI*2*radius;
	}
	
	public static void main(String[] args)
	{
		
		System.out.println("Enter a radius: ");
		Scanner scanner = new Scanner(System.in);
		double radius = scanner.nextDouble();
		System.out.println("A circle of radius "+ radius + " m has an area of "+ Circle.area(radius) + " m2");
		
		System.out.println("A circle of radius "+ radius + " m has a circumference of "+ Circle.circumference(radius) + " m");
		scanner.close();
	}
}

