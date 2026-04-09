package utilities;


import stocks.Stock;
import subscribers.User;

import java.io.Serializable;
import java.util.HashMap;

public class SendResources implements Serializable {
    public final HashMap<String, Stock> StockMap;
    public final HashMap<String, User> userMap;

    public SendResources(HashMap<String, Stock> stockMap, HashMap<String, User> userMap) {
        this.StockMap = stockMap;
        this.userMap = userMap;
    }
}
