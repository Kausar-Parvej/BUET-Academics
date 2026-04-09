class Figure {
    double d1, d2;
	
    Figure(double a, double b) {
        this.d1 = a;
        this.d2 = b;
    }

	// your code
}

// your code

class FindAreas {
    public static void main(String[] args) {
        Figure f = new Figure(10, 10);
        Rectangle r = new Rectangle(9, 5);
        Triangle t = new Triangle(10, 8);

        Figure ref;
        ref = f;
        System.out.println(ref.area());

        ref = r;
        System.out.println(ref.area());

        ref = t;
        System.out.println(ref.area());
    }
}

/* main output
Area for Figure is undefined: 0.0
Area for Rectangle: 45.0
Area for Triangle: 40.0
 */