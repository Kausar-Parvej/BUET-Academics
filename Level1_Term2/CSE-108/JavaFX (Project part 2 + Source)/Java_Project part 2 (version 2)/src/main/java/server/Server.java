package server;

import my_util.Movie;
import my_util.NetworkUtil;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Server {

    private static final String INPUT_FILE_NAME = "movies.txt";
    private static final String OUTPUT_FILE_NAME = "out.txt";
    public static List<Movie> allMovieList = new ArrayList<>();

    private ServerSocket serverSocket;
    public HashMap<String, String> userMap;

    Server() throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader(INPUT_FILE_NAME));
        //HashMap<String, SocketWrapper> clientMap = new HashMap<>();

        while (true) {
            String single_line = bufferedReader.readLine();
            if (single_line == null) break;

            String[] single_word = single_line.split(",");
            Movie movie = new Movie(single_word);
            allMovieList.add(movie);
        }
        bufferedReader.close();

        userMap = new HashMap<>();
        for(Movie object : allMovieList){
            userMap.put(object.getProductionCompany().toLowerCase(), "a");
        }
        try {
            serverSocket = new ServerSocket(33333);
            System.out.println("server is running....");
            while (true) {
                Socket clientSocket = serverSocket.accept();
                serve(clientSocket);
            }
        } catch (Exception e) {
            System.out.println("Server starts:" + e);
        }
    }

    public void serve(Socket clientSocket) throws IOException {
        NetworkUtil networkUtil = new NetworkUtil(clientSocket);
        new ReadThreadServer(userMap, networkUtil,this);
    }


    public static void main(String[] args) {
        try {
            new Server();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
