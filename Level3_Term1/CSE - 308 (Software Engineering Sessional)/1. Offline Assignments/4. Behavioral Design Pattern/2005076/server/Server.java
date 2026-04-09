package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Stack;

import stocks.Stock;
import subscribers.User;
import utilities.NetworkUtil;

public class Server {

    private ServerSocket serverSocket;
    public static HashMap<String, Stock> stockMap;
    public static HashMap<String, User> userMap;
    public static HashMap<String, NetworkUtil> clientMap; // HashMap of client's name and socket information

    public Server(HashMap<String, Stock> map1, HashMap<String, User> map2) {
        clientMap = new HashMap<>();
        stockMap = map1;
        userMap = map2;
        try {
            serverSocket = new ServerSocket(33333);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                serve(clientSocket);
            }
        } catch (Exception e) {
            System.out.println("server.Server starts:" + e);
        }
    }

    public void serve(Socket clientSocket) throws IOException, ClassNotFoundException {
        NetworkUtil networkUtil = new NetworkUtil(clientSocket);
        new ReadThreadServer(clientMap, networkUtil,this);
    }
}
