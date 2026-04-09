package server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HTTPServer {
    private static final int PORT = 5076;

    public static String readFileData(File file, int fileLength) throws IOException {
        FileInputStream fileIn = null;
        byte[] fileData = new byte[fileLength];

        try {
            fileIn = new FileInputStream(file);
            fileIn.read(fileData);
        } finally {
            if (fileIn != null)
                fileIn.close();
        }

        return String.valueOf(fileData);
    }

    public static void main(String[] args) {
        try {
            ServerSocket serverConnect = new ServerSocket(PORT);
            System.out.println("server started.\nListening for connections on port : " + PORT + " ...\n");

            while (true) {
                Socket clientSocket = serverConnect.accept();
                new Thread(new ServerThread(clientSocket)).start();
            }
        } catch (IOException e){
            System.out.println("Error starting the server: " + e.getMessage());
        }
    }
}
