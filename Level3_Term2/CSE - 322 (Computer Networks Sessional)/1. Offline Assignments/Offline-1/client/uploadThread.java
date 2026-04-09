package client;

import java.io.*;
import java.net.Socket;

public class uploadThread implements Runnable {
    private String IP_ADDRESS;
    private int PORT;
    private File file;

    private final int CHUNK_SIZE = 4096;

    public uploadThread(String IP_ADDRESS, int PORT, File file) {
        this.IP_ADDRESS = IP_ADDRESS;
        this.PORT = PORT;
        this.file = file;
    }

    @Override
    public void run() {
        Socket socket = null;
        FileInputStream fileIn = null;
        OutputStream out = null;
        BufferedReader serverResponseReader = null;
        try {
            socket = new Socket(IP_ADDRESS, PORT);
            out = socket.getOutputStream();
            PrintWriter pw = new PrintWriter(out, true);

            if(!file.getName().endsWith(".txt") && !file.getName().endsWith(".jpg") && !file.getName().endsWith(".png") && !file.getName().endsWith(".jpeg") && !file.getName().endsWith(".mp4")){
                System.out.println("Invalid file format. Only .txt, .jpg, .png, .mp4 files are allowed. Please try again.");
                pw.println("Invalid file format. Only .txt, .jpg, .png, .mp4 files are allowed. Please try again");
                pw.flush();
            }
            else if(!file.exists()){
                System.out.println("File does not exist. Please try again.");
                pw.println("Invalid, File does not exist. Please try again");
                pw.flush();
            }
            else{
                fileIn = new FileInputStream(file);
                pw.println("UPLOAD " + file.getName());
                pw.flush();

                byte[] buffer = new byte[CHUNK_SIZE];
                int bytesRead;
                while ((bytesRead = fileIn.read(buffer)) != -1) {
                    //System.out.println("Sending Bytes: " + bytesRead);
                    out.write(buffer, 0, bytesRead);
                    out.flush();
                }

                out.flush();
                socket.shutdownOutput();
                System.out.println("File " + file.getName() + " uploaded successfully.");
            }

        } catch (Exception e) {
            System.out.println("Error uploading file: " + file.getName());
            e.printStackTrace();
        } finally {
            try {
                if (fileIn != null) fileIn.close();
                if (out != null) out.close();
                if (socket != null && !socket.isClosed()) socket.close();
            } catch (Exception e) {
                System.out.println("Error occurred while closing the connection: " + e.getMessage());
            }
            //System.out.println("Connection Closed.");
        }
    }
}
