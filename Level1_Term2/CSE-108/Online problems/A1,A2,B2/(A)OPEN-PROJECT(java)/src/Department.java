import java.lang.reflect.GenericDeclaration;
import java.lang.reflect.TypeVariable;

public class Department {

    private int id;
    private String name;
    private Employee[] employees;
    private int employeeCount;
    // add your code here
    // you are allowed to add variables here
    private int employeeIndex=0;
    private static Department[] departments;

    // there can be at most 10 departments

    // you are not allowed to write any other constructor
    public Department(int id, String name) {
        this.id = id;
        this.name = name;
        this.employees = new Employee[10];
        // add your code here
        for (int i=0; i<10; i++){
            employees[i] = new Employee(0,"temp", 0.0);
        }
        employeeCount=0;
    }

    // add your code here

    static{
        departments = new Department[10];
        for(int i=0; i<10; i++){
            departments[i] = new Department(0,"temp");
        }
    }

    /*public static double getTotalSalary(Department ob1, Department ob2) {
        double totalSalary=0;
        totalSalary=ob1.getDepartmentSalary()+ob2.getDepartmentSalary();
        return totalSalary;
    }*/
    public static void getTotalSalary(Department ob1, Department ob2) {
        System.out.println("Department: "+ob1.name+" ID: "+ob1.id);
        for(int i=0; i< ob1.employeeCount; i++){
            System.out.println("Employee: "+ob1.employees[i].getName()+" ID: "+ ob1.employees[i].getId()+" Salary: "+ ob1.employees[i].getSalary());
        }
        System.out.println("Department: "+ob2.name+" ID: "+ob2.id);
        for(int i=0; i< ob2.employeeCount; i++){
            System.out.println("Employee: "+ob2.employees[i].getName()+" ID: "+ ob2.employees[i].getId()+" Salary: "+ ob2.employees[i].getSalary());
        }
    }

    public void addEmployee(Employee ob) {
        this.employees[employeeCount++]=ob;
    }

    public double getDepartmentSalary() {
        double sumSalary=0;
        for(int i=0; i<employeeCount; i++){
            sumSalary+=employees[i].getSalary();
        }
        return sumSalary;
    }

    public Employee getMaxSalaryEmployee() {
        double maxSalary=employees[0].getSalary();
        for(int i=0; i<employeeCount; i++){
            if(employees[i].getSalary()>maxSalary){
                maxSalary=employees[i].getSalary();
                employeeIndex=i;
            }
        }
        return employees[employeeIndex];
    }

    public void giveIncrementToEmployees(double slry) {
        for(int i=0; i<employeeCount; i++){
            if(i==employeeIndex)
                continue;
            employees[i].setSalary(employees[i].getSalary()+slry);
        }
    }

}