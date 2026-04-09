import java.util.ArrayList;
import java.util.HashMap;

public class Bank {
    private double initial_fund = 1000000;
    private double fund_amount;
    public static int year_clock;

    public HashMap<String, Account> accounts;
    public HashMap<String, Employee> employees;
    public ArrayList<User> loan_requested;


    public Bank() {
        fund_amount = initial_fund;
        year_clock = 0;

        accounts = new HashMap<>();
        employees = new HashMap<>();
        loan_requested = new ArrayList<>();

        Managing_director md = new Managing_director("MD");
        Officer o1 = new Officer("S1");
        Officer o2 = new Officer("S2");
        Cashier c1 = new Cashier("C1");
        Cashier c2 = new Cashier("C2");
        Cashier c3 = new Cashier("C3");
        Cashier c4 = new Cashier("C4");
        Cashier c5 = new Cashier("C5");

        employees.put(md.getName().toLowerCase(), md);
        employees.put(o1.getName().toLowerCase(), o1);
        employees.put(o2.getName().toLowerCase(), o2);
        employees.put(c1.getName().toLowerCase(), c1);
        employees.put(c2.getName().toLowerCase(), c2);
        employees.put(c3.getName().toLowerCase(), c3);
        employees.put(c4.getName().toLowerCase(), c4);
        employees.put(c5.getName().toLowerCase(), c5);

        System.out.println("Bank Created; MD, S1, S2, C1, C2, C3, C4, C5 created");

    }

    public double getFund_amount() {
        return fund_amount;
    }

    public void setFund_amount(double fund_amount) {
        this.fund_amount = fund_amount;
    }

    public int getYear_clock() {
        return year_clock;
    }

    public void setYear_clock(int year_clock) {
        this.year_clock = year_clock;
    }
}
