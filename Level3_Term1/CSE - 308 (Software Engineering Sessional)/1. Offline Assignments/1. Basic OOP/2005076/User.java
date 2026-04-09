public class User{
    public String name;
    public String account_type;
    private double deposit_amount;

    private double loan_amount;
    public double loan_request_amount;

    public User(String name, String account_type, double deposit_amount) {
        this.name = name;
        this.account_type = account_type;
        this.deposit_amount = deposit_amount;
        this.loan_amount = 0;
        this.loan_request_amount = 0;
    }

    public double getDeposit_amount() {
        return deposit_amount;
    }

    public void setDeposit_amount(double deposit_amount) {
        this.deposit_amount = deposit_amount;
    }

    public double getLoan_amount() {
        return loan_amount;
    }

    public void setLoan_amount(double loan_amount) {
        this.loan_amount = loan_amount;
    }
}

