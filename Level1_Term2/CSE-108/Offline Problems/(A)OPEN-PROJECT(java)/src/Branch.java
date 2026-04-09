public class Branch {

    private int id;
    private String name;
    private Account []  accounts;
    private int accountCount;
	// add your code here
    public static int count=0;
    public static Branch [] br;

    /*      private Branch branches [] = new Branch[20];
        branches=new Branch[20];*/
	// you are allowed to add variables here
    // there can be at most 20 branches  

    // you are not allowed to write any other constructor
    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        this.accounts = new Account[10];
        // add your code here
        for(int i=0; i<10; i++){
            accounts[i]=new Account(0, "temp", 0.0);
        }
        count++;
    }
    // you are not allowed to modify this method
    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }

// add your code here

    static{
        br = new Branch[2];
        for(int i=0; i<2; i++ ) {
            Branch.br[i] = new Branch(i + 1, "temp");
        }
    }

    public double getBranchBalance(){
        double sum_balance=0;
        for(int i=0; i<accountCount;i++){
            sum_balance+=accounts[i].getBalance();
        }
        return sum_balance;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public Account[] getAccounts() {
        return accounts;
    }

    public void setAccounts(Account[] accounts) {
        this.accounts = accounts;
    }

    public void setAccountCount(int accountCount) {
        this.accountCount = accountCount;
    }

    public int getAccountCount() {
        return accountCount;
    }

    /*public static void init(){
        br = new Branch[3];
        for(int i=0; i<2; i++ ){
            br[i] = new Branch(i+1, "temp");
        }
    }*/

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
