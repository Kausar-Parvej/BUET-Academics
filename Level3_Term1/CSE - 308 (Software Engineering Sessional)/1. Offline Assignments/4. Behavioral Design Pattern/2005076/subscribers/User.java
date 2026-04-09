package subscribers;

import java.io.Serializable;
import java.util.ArrayList;

import server.SystemAdministrator;
import stocks.Stock;

public class User implements subscriber, Serializable {
    private String userName;
    private ArrayList<Stock> subscribedStocks;

    public boolean isSubscriber(Stock stock) {
        for(Stock stk : subscribedStocks){
            if(stk.getStockName().equals(stock.getStockName())){
                return true;
            }
        }
        return false;
    }

    public User(String userName) {
        this.userName = userName;
        subscribedStocks = new ArrayList<>();
    }

    public String getUserName() {
        return userName;
    }

    public void subscribeTo(Stock stock){
        subscribedStocks.add(stock);
        System.out.println(userName +" Subscribed to "+stock.getStockName());
    }
    public void unsubscribeFrom(Stock stock){
        subscribedStocks.remove(stock);
        System.out.println(userName +" Unsubscribed from "+stock.getStockName());
    }
    public void viewAllStocks(){
        for(Stock stock : subscribedStocks){
            System.out.println(stock.getStockName() +" "+ stock.getStockCount() +" "+ stock.getStockPrice());
        }
    }
    @Override
    public void update(String msg) {
        SystemAdministrator.updateNotify(this, msg);
    }
}
