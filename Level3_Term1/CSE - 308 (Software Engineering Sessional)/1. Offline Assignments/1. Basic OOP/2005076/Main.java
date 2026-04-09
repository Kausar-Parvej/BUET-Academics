import java.util.Map;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String command;
        System.out.println("\n\t\tOffline - 1 of Software Engineering: \n");

        Bank myBank = new Bank();
        Scanner input = new Scanner(System.in);

        String input_line = input.nextLine();
        String[] input_words = input_line.split(" ");

        command = input_words[0];
        String flag = null;
        String name = null;
        Account acc3;
        while(!command.equalsIgnoreCase("End")){
            if(input_words[0].equalsIgnoreCase("Create")){
                if(input_words.length == 4){
                    if(myBank.accounts.get(input_words[1].toLowerCase()) != null){
                        System.out.println("Account already exists!!");
                    }
                    else if(myBank.employees.get(input_words[1].toLowerCase()) != null){
                        System.out.println("Employee exists with this name!!");
                    }
                    else {
                        if(input_words[2].equalsIgnoreCase("Student")) {
                            acc3 = new Student_account();
                        }
                        else if(input_words[2].equalsIgnoreCase("Savings")) {
                             acc3 = new Savings_account();
                        }
                        else{
                            acc3 = new Fixed_account();
                        }

                        double init_amount = Double.parseDouble(input_words[3]);

                        acc3.createAccount(input_words[1], init_amount);
                        if(acc3.getAccount_user() != null){
                            myBank.accounts.put(input_words[1].toLowerCase(), acc3);
                            flag = "user";
                            name = input_words[1];
                        }
                    }
                }
            }
            else if(input_words[0].equalsIgnoreCase("Close")){
                if(flag!= null && flag.equals("user") && name != null){
                    System.out.println("Transaction Closed for " + name);
                }
                else if(flag!= null && flag.equals("employee") && name != null){
                    System.out.println("Operation for " + name + " closed");
                }
                flag = null;
                name = null;
            }
            else if(input_words[0].equalsIgnoreCase("Open")){
                if(myBank.employees.get(input_words[1].toLowerCase()) != null){
                    flag = "employee";
                    name = input_words[1];
                    System.out.print(name + " active");
                    if(myBank.loan_requested.size() > 0)
                        System.out.print(", there are loan approvals pending\n");
                }
                else if(myBank.accounts.get(input_words[1].toLowerCase()) != null){
                    flag = "user";
                    name = input_words[1];
                    System.out.println("Welcome back, " + name);
                }
                else{
                    System.out.println("Invalid Open!!");
                }
            }

            if(flag!= null && flag.equals("user") && name != null){
                Account acc = myBank.accounts.get(name.toLowerCase());
                if(input_words[0].equalsIgnoreCase("Deposit")){
                    double money = Double.parseDouble(input_words[1]);
                    acc.deposit(money);
                }
                else if(input_words[0].equalsIgnoreCase("Withdraw")){
                    double money = Double.parseDouble(input_words[1]);
                    acc.withdraw(money);
                }
                else if(input_words[0].equalsIgnoreCase("Query")){
                    acc.query_deposit();
                }
                else if(input_words[0].equalsIgnoreCase("Request")){
                    double money = Double.parseDouble(input_words[1]);
                    acc.request_loan(money, myBank);
                }
            }

            if(flag!= null && flag.equals("employee") && name != null){
                Employee emp = myBank.employees.get(name.toLowerCase());

                if(input_words[0].equalsIgnoreCase("Lookup")){
                    Account acc2 = myBank.accounts.get(input_words[1].toLowerCase());
                    if(acc2 == null){
                        System.out.println("No account exist with this name!");
                    }
                    else
                        emp.lookup(acc2.getAccount_user());
                }
                else if(input_words[0].equalsIgnoreCase("Approve")){
                    emp.approveLoan(myBank);
                }
                else if(input_words[0].equalsIgnoreCase("Change")){
                    if(input_words.length == 3){
                        double modified_IR = Double.parseDouble(input_words[2]);
                        emp.change_IR(input_words[1], modified_IR);
                    }
                }
                else if(input_words[0].equalsIgnoreCase("See")){
                    emp.see_fund(myBank);
                }

            }
            if(input_words[0].equalsIgnoreCase("INC")){
                System.out.println("1 year passed");
                Bank.year_clock ++;
                for(Map.Entry<String, Account> account_set : myBank.accounts.entrySet()){
                    account_set.getValue().one_year_pass();
                }

            }

            input_words = input.nextLine().split(" ");
            command = input_words[0];
        }
    }
}
