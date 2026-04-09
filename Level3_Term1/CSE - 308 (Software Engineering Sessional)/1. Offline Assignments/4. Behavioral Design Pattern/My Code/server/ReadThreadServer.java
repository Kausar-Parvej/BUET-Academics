package server;

import stocks.Stock;
import subscribers.User;
import utilities.*;

import java.io.IOException;
import java.net.Socket;
import java.util.HashMap;


public class ReadThreadServer implements Runnable {
    private Server server;
    private final Thread thr;
    private final NetworkUtil networkUtil;
    public HashMap<String, NetworkUtil> clientSocketMap;



    public ReadThreadServer(HashMap<String, NetworkUtil> map, NetworkUtil networkUtil, Server server) {
        this.server = server;
        this.clientSocketMap = map;
        this.networkUtil = networkUtil;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = networkUtil.read();
                if (o != null) {
                    if (o instanceof String) {
                        String msg = (String) o;
                        String[] msgPart = msg.split(" ");
                        if(msgPart[0].equalsIgnoreCase("login")){
                            SendResources sendResources = new SendResources(Server.stockMap, Server.userMap);
                            networkUtil.write(sendResources);
                        }
                        else if(msgPart[0].equalsIgnoreCase("subscribe")){
                            User user = Server.userMap.get(msgPart[1]);
                            Stock stock = Server.stockMap.get(msgPart[2]);
                            stock.addSubscriber(user);
                            user.subscribeTo(stock);
                        }
                        else if(msgPart[0].equalsIgnoreCase("unsubscribe")){
                            User user = Server.userMap.get(msgPart[1]);
                            Stock stock = Server.stockMap.get(msgPart[2]);
                            stock.removeSubscriber(user);
                            user.unsubscribeFrom(stock);
                        }
                    }
                    if(o instanceof User){
                        User user = (User) o;
                        Server.userMap.put(user.getUserName(), user);
                        System.out.println(user.getUserName() + " logged in");
                        Server.clientMap.put(user.getUserName(), networkUtil);
                    }
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                networkUtil.closeConnection();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}



