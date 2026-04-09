package client;

import java.io.File;
import java.util.Scanner;

public class UploaderClient {

    private static final String IP_ADDRESS = "localhost";
    private static final int PORT = 5076;

    private static final String rootDirectory = "client/upload_from";


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the file name to upload or type 'exit' to quit: ");
        String fileName = scanner.nextLine();

        while (true) {
            if (fileName.equals("exit")) {
                System.out.println("Exiting Client...");
                break;
            }

            String filePath = rootDirectory + "/" + fileName;
            //System.out.println("File in: " + filePath);
            File file = new File(filePath);

            new Thread( new uploadThread(IP_ADDRESS, PORT, file)).start();

            System.out.println("Enter another file name to upload (or type 'exit' to quit): ");
            fileName = scanner.nextLine();
        }
    }
}
