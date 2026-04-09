package stocks;

import subscribers.User;

import java.io.Serializable;
import java.util.ArrayList;

public class Stock implements Serializable {
    private String stockName;
    private int stockCount;
    private double stockPrice;

    public ArrayList<User> subscribers;

    public Stock(String stockName, int stockCount, double stockPrice) {
        this.stockName = stockName;
        this.stockCount = stockCount;
        this.stockPrice = stockPrice;

        subscribers = new ArrayList<>();
    }

    public String getStockName() {
        return stockName;
    }

    public void setStockName(String stockName) {
        this.stockName = stockName;
    }

    public int getStockCount() {
        return stockCount;
    }

    public void setStockCount(int stockCount) {
        this.stockCount = stockCount;
    }

    public double getStockPrice() {
        return stockPrice;
    }

    public void setStockPrice(double stockPrice) {
        this.stockPrice = stockPrice;
    }

    public ArrayList<User> getSubscribers() {
        return subscribers;
    }

    public void addSubscriber(User user){
        subscribers.add(user);
    }
    public void removeSubscriber(User user){
        subscribers.remove(user);
    }

    public void increasePrice(double price){
        this.stockPrice += price;
        notify("increase "+ stockName + " " + price);
        //System.out.println(stockName +"'s price increased by "+price);
    }
    public void decreasePrice(double price){
        this.stockPrice -= price;
        notify("decrease "+ stockName + " " + price);
        //System.out.println(stockName +"'s price decreased by "+price);
    }
    public void changeCount(int count){
        if(count > 0){
            this.stockCount = count;
            notify("change "+ stockName + " " + count);
            //System.out.println(stockName +"'s count changed to "+count);
        }
        else {
            System.out.println("Count should be positive integer!");
        }
    }

    private void notify(String msg){
        for(User user : subscribers){
            user.update(msg);
        }
    }
}
