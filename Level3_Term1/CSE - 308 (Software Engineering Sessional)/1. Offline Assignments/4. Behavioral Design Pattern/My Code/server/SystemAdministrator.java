package server;

import server.Server;
import stocks.Stock;
import subscribers.User;
import utilities.NetworkUtil;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class SystemAdministrator {
    private static final String INPUT_FILE_NAME = "init_stocks.txt";
    public static HashMap<String, Stock> stocksMap;
    public static HashMap<String, User> userMap;

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader(INPUT_FILE_NAME));
        stocksMap = new HashMap<>();
        userMap = new HashMap<>();

        while (true) {
            String readLine = bufferedReader.readLine();
            if (readLine == null) break;

            String[] singleWord = readLine.split(" ");
            Stock stock = new Stock(singleWord[0], Integer.parseInt(singleWord[1]), Double.parseDouble(singleWord[2]));
            stocksMap.put(singleWord[0], stock);
        }
        bufferedReader.close();
        new Thread(()->{
            new Server(stocksMap, userMap);
        }).start();

        mainMenu();
    }

    private static void mainMenu() {
        Scanner scan = new Scanner(System.in);
        String inputLine;
        String[] inputParts;
        System.out.println("Enter your command:");
        while (true) {
            inputLine = scan.nextLine();
            inputParts = inputLine.split(" ");
            if(inputParts[0].equalsIgnoreCase("exit")){
                System.out.println("Exiting from system administration!");
                break;
            }

            Stock stock = stocksMap.get(inputParts[1]);
            //if(stock == null) continue;
            if(inputParts[0].equalsIgnoreCase("I")){
                stock.increasePrice(Double.parseDouble(inputParts[2]));
            }
            else if(inputParts[0].equalsIgnoreCase("D")){
                stock.decreasePrice(Double.parseDouble(inputParts[2]));
            }
            else if(inputParts[0].equalsIgnoreCase("C")){
                stock.changeCount(Integer.parseInt(inputParts[2]));
            }
            else
                System.out.println("Invalid Input !!");

        }
    }

    public static void updateNotify(User user, String msg) {
        NetworkUtil networkUtil = Server.clientMap.get(user.getUserName());
        try {
            if(networkUtil.getSocket().isConnected()){
                networkUtil.write(msg);
            }
        } catch (IOException e) {
            System.out.println(user.getUserName() +" can not notified");
        }
    }

}
