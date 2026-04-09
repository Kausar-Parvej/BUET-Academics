public class Employee {

    private int id;
    private String name;
    private double salary;
    // you are not allowed to add any more class variables here

    // you are not allowed to write any other constructor
    public Employee(int id, String name, double salary) {
        this.id = id;
        this.name = name;
        this.salary = salary;
    }

    public String getName() {
        return this.name;
    }

    // add your code here

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public int getId() {
        return id;
    }
}