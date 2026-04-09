public class Branch {

    private int id;
    private String name;
    private Account []  accounts;
    private int accountCount;
	// add your code here
    private static Branch [] br;
    private static int branchCount=0;

	// you are allowed to add variables here
    // there can be at most 20 branches  

    // you are not allowed to write any other constructor
    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        this.accounts = new Account[10];
        // add your code here
        this.accountCount = 0;
        br[branchCount] = this;
        branchCount++;
    }
    // you are not allowed to modify this method
    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }

// add your code here

    static{
        br = new Branch[20];
    }
    public double getBranchBalance(){
        double sum_balance=0;
        for(int i=0; i<accountCount;i++){
            sum_balance+=accounts[i].getBalance();
        }
        return sum_balance;
    }
    public Account getMinBalanceAccount(){
        int index=0;
        double min_balance=accounts[0].getBalance();
        for(int i=0; i<accountCount;i++){
            if(accounts[i].getBalance()<min_balance){
                min_balance=accounts[i].getBalance();
                index=i;
            }
        }
        return accounts[index];
    }

    public static void transferBalance(Account a, Account b, int i) {
        a.setBalance(a.getBalance()-i);
        b.setBalance(b.getBalance()+i);
    }


    public static void printAllBranchesInfo(){
        for(int j=0; j<2; j++){
            System.out.println("Branch Id: " + br[j].id + ", Branch Name: " + br[j].name);
            for(int i=0; i<br[j].accountCount; i++){
                System.out.println("Account Number: " + br[j].accounts[i].getNumber() + ", Customer Name: " + br[j].accounts[i].getCustomer()+", Balance: "+ br[j].accounts[i].getBalance());
            }
        }
    }
}
