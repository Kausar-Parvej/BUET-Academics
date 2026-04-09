package client;

import stocks.Stock;
import subscribers.User;
import utilities.NetworkUtil;

import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class UserInteract {
    public static User user;
    public static boolean loggedIn;
    public static String savedMsg;
    private static Scanner scan;
    private static NetworkUtil networkUtil;
    public static HashMap<String, Stock> stocksMap;
    public static HashMap<String, User> userMap;

    public static NetworkUtil getNetworkUtil() {
        return networkUtil;
    }

    public static void main(String[] args) throws IOException {
        savedMsg = "";
        System.out.print("Log in as: ");
        scan = new Scanner(System.in);
        Scanner scanner2 = new Scanner(System.in);
        String userName = scanner2.next();
        loggedIn = true;

        connectToServer();
        networkUtil.write("login " + userName);

        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }


        user = userMap.get(userName);
        if(user == null){
            user = new User(userName);
            userMap.put(userName, user);
        }
        System.out.println("logged in as "+userName);
        networkUtil.write(user);
        mainMenu();
    }
    private static void connectToServer() throws IOException {
        String serverAddress = "127.0.0.1";
        int serverPort = 33333;
        networkUtil = new NetworkUtil(serverAddress, serverPort);
        new ReadThreadClient();
    }

    private static void mainMenu() throws IOException {

        String inputLine;
        String[] inputParts;
        System.out.println();
        stocksMap.forEach((str, stk)
                -> System.out.println(stk.getStockName() +" "+ stk.getStockCount() +" "+ stk.getStockPrice())
        );
        System.out.println("Enter your command:");
        System.out.println();
        while (true) {
            if(!loggedIn){
                System.out.println("log in again:");
                String str = scan.next();
                if(str.equalsIgnoreCase("login")){
                    System.out.println(savedMsg);
                    savedMsg = "";
                    loggedIn = true;
                }
                else{
                    continue;
                }
            }
            inputLine = scan.nextLine();
            inputParts = inputLine.split(" ");

            if(inputParts[0].equalsIgnoreCase("S")){
                Stock stock = stocksMap.get(inputParts[1]);
                if(stock != null){
                    if(user.isSubscriber(stock)){
                        System.out.println("already subscribed to "+stock.getStockName());
                    }
                    else{
                        user.subscribeTo(stock);
                        stock.addSubscriber(user);
                        networkUtil.write("subscribe "+ user.getUserName() +" " + inputParts[1]);
                    }
                }
            }
            else if(inputParts[0].equalsIgnoreCase("U")){
                Stock stock = stocksMap.get(inputParts[1]);
                if(stock != null){
                    if(user.isSubscriber(stock)){
                        user.unsubscribeFrom(stock);
                        stock.removeSubscriber(user);
                        networkUtil.write("unsubscribe "+ user.getUserName() +" " + inputParts[1]);
                    }
                    else{
                        System.out.println("not a subscriber to "+ stock.getStockName());
                    }
                }
            }
            else if(inputParts[0].equalsIgnoreCase("V")){
                user.viewAllStocks();
            }
            else if(inputParts[0].equalsIgnoreCase("logout")){
                loggedIn = false;
            }
            else if(inputParts[0].equalsIgnoreCase("exit")){
                System.out.println("! Exiting from client.UserInteract !");
                break;
            }
        }
    }
}
