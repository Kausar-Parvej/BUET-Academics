interface Employee{
    User lookup(User account_user);
    boolean approveLoan(Bank bank);
    double change_IR(String acc_type, double rate);
    double see_fund(Bank bank);
}


class Managing_director implements Employee{
    private String name;

    public Managing_director(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public User lookup(User account_user) {
        System.out.println(account_user.name + "'s current balance "+ account_user.getDeposit_amount());
        return account_user;
    }

    @Override
    public boolean approveLoan(Bank bank) {
        System.out.print("Loan for ");
        for (User ac_user : bank.loan_requested) {
            System.out.print(ac_user.name+ " ,");
            ac_user.setLoan_amount(ac_user.loan_request_amount+ac_user.getLoan_amount());
            ac_user.setDeposit_amount(ac_user.getDeposit_amount()+ac_user.loan_request_amount);
            ac_user.loan_request_amount = 0;
        }

        bank.loan_requested.clear();
        System.out.print("approved\n");
        return true;
    }

    @Override
    public double change_IR(String acc_type, double rate) {
        if(acc_type.equalsIgnoreCase("Savings")){
            Savings_account.interest_rate = rate/100;
        }
        else if(acc_type.equalsIgnoreCase("Student")){
            Student_account.interest_rate = rate/100;
        }
        else if(acc_type.equalsIgnoreCase("Fixed")){
            Fixed_account.interest_rate = rate/100;
        }
        System.out.println(acc_type + " Account's interest rate changed to " + rate);
        return rate;
    }

    @Override
    public double see_fund(Bank bank) {
        System.out.println("The internal fund of the bank is: " + bank.getFund_amount());
        return bank.getFund_amount();
    }
}


class Officer implements Employee{
    private String name;

    public Officer(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public User lookup(User account_user) {
        System.out.println(account_user.name + "'s current balance "+ account_user.getDeposit_amount());
        return account_user;
    }

    @Override
    public boolean approveLoan(Bank bank) {
        System.out.print("Loan for ");
        for (User ac_user : bank.loan_requested) {
            System.out.print(ac_user.name+ " ,");
            ac_user.setLoan_amount(ac_user.loan_request_amount+ac_user.getLoan_amount());
            ac_user.setDeposit_amount(ac_user.getDeposit_amount()+ac_user.loan_request_amount);
            ac_user.loan_request_amount = 0;
        }

        bank.loan_requested.clear();
        System.out.print("approved\n");
        return true;
    }

    @Override
    public double change_IR(String acc_type, double rate) {
        System.out.println("You don’t have permission for this operation");
        return 0;
    }

    @Override
    public double see_fund(Bank bank) {
        System.out.println("You don’t have permission for this operation");
        return 0;
    }
}


class Cashier implements Employee{
    private String name;

    public Cashier(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public User lookup(User account_user) {
        System.out.println(account_user.name + "'s current balance "+ account_user.getDeposit_amount());
        return account_user;
    }

    @Override
    public boolean approveLoan(Bank bank) {
        System.out.println("You don’t have permission for this operation");
        return false;
    }

    @Override
    public double change_IR(String acc_type, double rate) {
        System.out.println("You don’t have permission for this operation");
        return 0;
    }

    @Override
    public double see_fund(Bank bank) {
        System.out.println("You don’t have permission for this operation");
        return 0;
    }
}