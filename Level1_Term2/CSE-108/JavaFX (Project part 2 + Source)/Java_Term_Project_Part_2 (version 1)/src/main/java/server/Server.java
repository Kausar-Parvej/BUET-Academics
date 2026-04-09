package server;

import com.example.client.StageApplication;
import my_util.ListOperation;
import my_util.Movie;
import my_util.SocketWrapper;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class Server {

    private static final String INPUT_FILE_NAME = "movies.txt";
    private static final String OUTPUT_FILE_NAME = "out.txt";
    public static boolean flag;
    private static final List<Movie> allMovieList = new ArrayList<>();
    private static final List<Movie> pcMovieList = new ArrayList<>();
    private static List<Movie> otherProductionMovieList = new ArrayList<>();
    private static String thisProduction;


    public static void main(String[] args) throws IOException {

        BufferedReader bufferedReader = new BufferedReader(new FileReader(INPUT_FILE_NAME));
        HashMap<String, SocketWrapper> clientMap = new HashMap<>();

        while (true) {
            String single_line = bufferedReader.readLine();
            if (single_line == null) break;

            String[] single_word = single_line.split(",");
            Movie movie = new Movie(single_word);
            allMovieList.add(movie);
        }
        bufferedReader.close();

        ServerSocket serverSocket = new ServerSocket(44444);
        System.out.println("server is running....");

        while(true){
            Socket clientSocket = serverSocket.accept();
            SocketWrapper client = new SocketWrapper(clientSocket);

            new Thread(()->{
                try {
                    String string = (String) client.read();
                    System.out.println(string);
                    clientMap.put(string,client);

                    for(Movie object : allMovieList){
                        if(object.getProductionCompany().equalsIgnoreCase(string)){
                            pcMovieList.add(object);
                        }
                    }
                    if(!pcMovieList.isEmpty()){
                        thisProduction = pcMovieList.get(0).getProductionCompany();
                    }
                    otherProductionMovieList = ListOperation.otherProductionMovies((ArrayList<Movie>) allMovieList,thisProduction);
                    client.write(pcMovieList);
                    pcMovieList.clear();
                    client.write(otherProductionMovieList);
                    otherProductionMovieList.clear();
                    client.write(thisProduction);

                    new Thread(()->{
                        while(true){
                            try {
                                if(StageApplication.flag==1){
                                    System.out.println("kausarrrr.....");
                                    String fromProductionCompany = (String) client.read();
                                    String toProductionCompany = (String) client.read();
                                    String transferMovie = (String) client.read();

                                    System.out.println(fromProductionCompany);
                                    System.out.println(toProductionCompany);
                                    System.out.println(transferMovie);
                                }



                            } catch (IOException | ClassNotFoundException e) {
                                e.printStackTrace();
                            }
                        }

                    }).start();





                } catch (IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                }finally {
                    try {
                        client.closeConnection();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

            }).start();
        }
    }
}
