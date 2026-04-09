package client;

import server.Server;
import stocks.Stock;
import utilities.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;


public class ReadThreadClient implements Runnable {
    private final Thread thr;

    public ReadThreadClient() {
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = UserInteract.getNetworkUtil().read();
                if (o != null) {
                    if (o instanceof SendResources) {
                        SendResources resources = (SendResources) o;
                        UserInteract.stocksMap = resources.StockMap;
                        UserInteract.userMap = resources.userMap;
                    }
                    if(o instanceof String){
                        String msg = (String) o;
                        String[] msgPart = msg.split(" ");
                        if(msgPart[0].equalsIgnoreCase("increase")){
                            Stock tempStock = UserInteract.stocksMap.get(msgPart[1]);
                            tempStock.setStockPrice(tempStock.getStockPrice() + Double.parseDouble(msgPart[2]));
                            String print = "Updated "+tempStock.getStockName()+": stock price increased by "+ msgPart[2];
                            if(UserInteract.loggedIn) System.out.println(print);
                            else UserInteract.savedMsg += print+"\n";
                        }
                        else if(msgPart[0].equalsIgnoreCase("decrease")){
                            Stock tempStock = UserInteract.stocksMap.get(msgPart[1]);
                            tempStock.setStockPrice(tempStock.getStockPrice() - Double.parseDouble(msgPart[2]));
                            String print2 = "Updated "+tempStock.getStockName()+": stock price decreased by "+ msgPart[2];
                            if(UserInteract.loggedIn) System.out.println(print2);
                            else UserInteract.savedMsg += print2+"\n";
                        }
                        else if(msgPart[0].equalsIgnoreCase("change")){
                            Stock tempStock = UserInteract.stocksMap.get(msgPart[1]);
                            tempStock.setStockCount(Integer.parseInt(msgPart[2]));
                            String print3 = "Updated "+tempStock.getStockName()+": stock count changed to "+ msgPart[2];
                            if(UserInteract.loggedIn) System.out.println(print3);
                            else UserInteract.savedMsg += print3+"\n";
                        }
                    }
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                UserInteract.getNetworkUtil().closeConnection();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}



