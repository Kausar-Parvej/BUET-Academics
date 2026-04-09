package server;

import my_util.Movie;
import my_util.NetworkUtil;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Server {

    private static final String MOVIE_FILE = "copyOf-movies.txt";
    public static final String OUTPUT_FILE_NAME = "copyOf-movies.txt";
    private static final String MOVIE_IMAGE_FILE = "movie_thumbnail_Links.txt";
    public static List<Movie> allMovieList = new ArrayList<>();

    private ServerSocket serverSocket;
    public HashMap<String, String> userMap;

    Server() throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader(MOVIE_FILE));
        BufferedReader imageFileBufferedReader = new BufferedReader(new FileReader(MOVIE_IMAGE_FILE));
        //HashMap<String, SocketWrapper> clientMap = new HashMap<>();

        while (true) {
            String single_line = bufferedReader.readLine();
            if (single_line == null) break;

            String[] single_word = single_line.split(",");
            Movie movie = new Movie(single_word);
            allMovieList.add(movie);

            String single_line2 = imageFileBufferedReader.readLine();
            if(single_line2 != null){
                ReadThreadServer.movieImageMap.put(movie.getTitle().toLowerCase(), single_line2);
            }
        }
        bufferedReader.close();
        imageFileBufferedReader.close();

        /*BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME));
        for (Movie mvi : allMovieList) {
            bufferedWriter.write(mvi.movieDetails());
            bufferedWriter.write(System.lineSeparator());
        }
        bufferedWriter.close();*/


        userMap = new HashMap<>();
        for(Movie object : allMovieList){
            userMap.put(object.getProductionCompany().toLowerCase(), "abc");
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
