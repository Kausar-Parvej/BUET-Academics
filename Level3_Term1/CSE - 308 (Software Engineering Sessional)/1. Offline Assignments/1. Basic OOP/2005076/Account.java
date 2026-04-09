interface Account{
    User createAccount(String name, double init_deposit);
    double deposit(double amount);
    double withdraw(double amount);
    void request_loan(double amount, Bank bank);
    void query_deposit();
    User getAccount_user();

    void one_year_pass();
}

class Savings_account implements Account{
    private User account_user;
    public static  double interest_rate;
    public static double annual_deduct_amount;
    private double max_loan;

    @Override
    public User getAccount_user(){
        return this.account_user;
    }

    @Override
    public User createAccount(String name,double init_deposit) {
        interest_rate = 0.1;
        annual_deduct_amount = 500;
        max_loan = 10000;
        User user = new User(name, "Savings", init_deposit);
        account_user = user;
        System.out.println("Savings account for "+account_user.name+"Created; initial balance "+account_user.getDeposit_amount());
        return user;
    }
    @Override
    public double deposit(double amount) {
        account_user.setDeposit_amount(account_user.getDeposit_amount() + amount);
        System.out.println(amount + "deposited; current balance " + account_user.getDeposit_amount());
        return amount;
    }

    @Override
    public double withdraw(double amount) {
        if(account_user.getDeposit_amount() - amount < 1000){
            System.out.println("Invalid transaction; current balance "+ account_user.getDeposit_amount());
        }
        else{
            account_user.setDeposit_amount(account_user.getDeposit_amount() - amount);
            System.out.println(amount + "is withdrawn; current balance(Savings Account) " + account_user.getDeposit_amount());
        }
        return amount;
    }

    @Override
    public void request_loan(double amount, Bank bank) {
        if(amount > max_loan){
            System.out.println("Loan request Invalid!!");
        }
        else{
            System.out.println("Loan request successful, sent for approval");
            account_user.loan_request_amount = amount;
            bank.loan_requested.add(account_user);
        }
    }

    @Override
    public void query_deposit() {
        System.out.println("Current Balance " + account_user.getDeposit_amount()+"$, loan "+ account_user.getLoan_amount()+"$");
    }

    @Override
    public void one_year_pass(){
        double current_val = account_user.getDeposit_amount();
        account_user.setDeposit_amount(current_val + current_val*interest_rate - account_user.getLoan_amount()*0.1 - 500);
    }
}


class Student_account implements Account{
    private User account_user;
    public static  double interest_rate;
    public static double annual_deduct_amount;
    private double max_loan;

    @Override
    public User getAccount_user(){
        return this.account_user;
    }

    @Override
    public User createAccount(String name, double init_deposit) {
        interest_rate = 0.05;
        annual_deduct_amount = 0;
        max_loan = 1000;
        User user = new User(name, "Student", init_deposit);
        account_user = user;
        System.out.println("Student account for "+account_user.name+" Created; initial balance "+account_user.getDeposit_amount());
        return user;
    }
    @Override
    public double deposit(double amount) {
        account_user.setDeposit_amount(account_user.getDeposit_amount() + amount);
        System.out.println(amount + " deposited; current balance " + account_user.getDeposit_amount());
        return amount;
    }

    @Override
    public double withdraw(double amount) {
        if(amount > 10000.0 || account_user.getDeposit_amount() - amount < 0.0){
            System.out.println("Invalid transaction; current balance "+ account_user.getDeposit_amount());
        }
        else{
            account_user.setDeposit_amount(account_user.getDeposit_amount() - amount);
            System.out.println(amount + " is withdrawn; current balance(Student Account) " + account_user.getDeposit_amount());
        }
        return amount;
    }

    @Override
    public void request_loan(double amount, Bank bank) {
        if(amount > max_loan){
            System.out.println("Loan request Invalid!!");
        }
        else{
            System.out.println("Loan request successful, sent for approval");
            account_user.loan_request_amount = amount;
            bank.loan_requested.add(account_user);
        }

    }

    @Override
    public void query_deposit() {
        System.out.println("Current Balance " + account_user.getDeposit_amount()+"$, loan "+ account_user.getLoan_amount()+"$");
    }

    @Override
    public void one_year_pass(){
        double current_val = account_user.getDeposit_amount();
        account_user.setDeposit_amount(current_val + current_val*interest_rate - account_user.getLoan_amount()*0.1);
    }
}


class Fixed_account implements Account{
    private User account_user;
    public static  double interest_rate;
    public static double annual_deduct_amount;
    private double max_loan;
    private double init_min_deposit = 100000;

    @Override
    public User getAccount_user(){
        return this.account_user;
    }

    @Override
    public User createAccount(String name, double init_deposit) {
        interest_rate = 0.15;
        annual_deduct_amount = 500;
        max_loan = 100000;
        if(init_deposit < init_min_deposit){
            System.out.println("Initial deposit is less than the minimum required amount!");
            return null;
        }
        User user = new User(name, "Fixed", init_deposit);
        account_user = user;
        System.out.println("Fixed Deposit account for "+account_user.name+" Created; initial balance "+account_user.getDeposit_amount());
        return user;
    }
    @Override
    public double deposit(double amount) {
        account_user.setDeposit_amount(account_user.getDeposit_amount() + amount);
        System.out.println(amount + " deposited; current balance " + account_user.getDeposit_amount());
        return amount;
    }

    @Override
    public double withdraw(double amount) {
        if(account_user.getDeposit_amount() - amount < 0 || Bank.year_clock < 1){
            System.out.println("Invalid transaction; current balance "+ account_user.getDeposit_amount());
        }
        else{
            account_user.setDeposit_amount(account_user.getDeposit_amount() - amount);
            System.out.println(amount + " is withdrawn; current balance(Fixed Account) " + account_user.getDeposit_amount());
        }
        return amount;
    }

    @Override
    public void request_loan(double amount, Bank bank) {
        if(amount > max_loan){
            System.out.println("Loan request Invalid!!");
        }
        else{
            System.out.println("Loan request successful, sent for approval");
            account_user.loan_request_amount = amount;
            bank.loan_requested.add(account_user);
        }
    }

    @Override
    public void query_deposit() {
        System.out.println("Current Balance " + account_user.getDeposit_amount()+"$, loan "+ account_user.getLoan_amount()+"$");
    }

    @Override
    public void one_year_pass(){
        double current_val = account_user.getDeposit_amount();
        account_user.setDeposit_amount(current_val + current_val*interest_rate - account_user.getLoan_amount()*0.1);
    }
}