class Figure {
    double d1, d2;
	
    Figure(double a, double b) {
        this.d1 = a;
        this.d2 = b;
    }

	// your code
    double area(){
        System.out.print("Area for Figure is undefined: ");
        return 0.0;
    }
}

// your code
class Rectangle extends Figure{

    Rectangle(double a, double b) {
        super(a,b);
    }

    double area(){
        System.out.print("Area for Rectangle: ");
        return d1*d2;
    }


}

class Triangle extends Figure{

    Triangle(double a, double b) {
        super(a, b);
    }


    double area(){
        System.out.print("Area for Triangle: ");
        return 0.5*this.d1*this.d2;
    }


}


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