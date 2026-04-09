package server;

import java.io.*;
import java.net.Socket;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.Date;
import java.util.Objects;

public class ServerThread implements Runnable{
    private final Socket clientSocket;
    private final int CHUNK_SIZE = 4096;
    private static final String ROOT_DIRECTORY = "server/root_directory";
    private static final String UPLOAD_DIRECTORY = "server/root_directory/uploaded";

    public ServerThread(Socket socket){
        this.clientSocket = socket;
    }

    @Override
    public void run(){
        BufferedReader in = null;
        try {
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            OutputStream out = clientSocket.getOutputStream();

            String inputLine = in.readLine();

//            if(inputLine == null || !inputLine.startsWith("GET")){
//                String errorResponse = "<html><body><h1>400 - Bad Request</h1></body></html>";
//                sendResponse(out, "400 Bad Request", "text/html", errorResponse.getBytes());
//                return;
//            }

            if(inputLine != null){
                //System.out.println("input: " + inputLine);
                if(inputLine.startsWith("UPLOAD")){
                    handleUploadRequest(inputLine, clientSocket.getInputStream(), out);
                }
                else if(inputLine.startsWith("Invalid")){
                    System.out.println(inputLine);
                }
                else{
                    handleRequest(inputLine, out);
                }
            }


        } catch (IOException e) {
            System.out.println("Client request handling error: " + e.getMessage());
        } finally {
            try {
                if(in != null) in.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void handleUploadRequest(String inputLine, InputStream inS, OutputStream out) throws IOException {
        String[] tokens = inputLine.split(" ");
        System.out.println("Handling Upload...");
        if (tokens.length != 2) {
            System.out.println("Invalid Request");
            return;
        }

        String fileName = tokens[1];

        File uploadDir = new File(UPLOAD_DIRECTORY);
//        if (!uploadDir.exists()) {
//            if (!uploadDir.mkdirs()) {
//                System.out.println("Failed to create upload directory: " + UPLOAD_DIRECTORY);
//                return;  // Exit if directory creation fails
//            }
//            System.out.println("Upload directory created: " + UPLOAD_DIRECTORY);
//        }

        logToFile("Request:" + inputLine);
        //File fileToSave = new File(UPLOAD_DIRECTORY, fileName);
        File fileToSave = new File(uploadDir, fileName);

        //System.out.println("upLOD:" + UPLOAD_DIRECTORY);
        try (FileOutputStream fileOut = new FileOutputStream(fileToSave)) {
            byte[] buffer = new byte[CHUNK_SIZE];
            int bytesRead;

            while ((bytesRead = inS.read(buffer)) != -1) {
                //System.out.println("Received Bytes: " + bytesRead);
                fileOut.write(buffer, 0, bytesRead);
                fileOut.flush();
            }
            fileOut.flush();
            fileOut.close();
            bytesRead = 0;
            System.out.println("File uploaded successfully: " + fileName);
            logToFile("File uploaded successfully: " + fileName);

        } catch (IOException e) {
            System.out.println("Error saving file: " + e.getMessage());
        }finally {
            try {
                if (out != null) out.close();
                if (inS != null) inS.close();
                if (clientSocket != null && !clientSocket.isClosed()) clientSocket.close();
            } catch (Exception e) {
                System.out.println("Error occurred while closing the connection: " + e.getMessage());
            }
        }
    }



    private void handleRequest(String inputLine, OutputStream out) throws IOException {
        String[] requestTokens;
        String filePath = "";
        if(inputLine != null){
            logToFile("HTTP Request: " + inputLine);
            requestTokens = inputLine.split(" ");
            String urlPath = URLDecoder.decode(requestTokens[1], StandardCharsets.UTF_8);
            if(urlPath.equals("/")){
                filePath = ROOT_DIRECTORY;
            }
            else{
                filePath = ROOT_DIRECTORY + urlPath;
            }
        }

        File askedFile = new File(filePath);

        //System.out.println(inputLine);
        //System.out.println(filePath);
        //System.out.println(askedFile.getAbsolutePath());

        if(askedFile.exists()){
            if(askedFile.isDirectory()){
                directoryListing(askedFile, out);
            } else {
                sendFile(askedFile, out);
            }
        }
        else {
            String errorResponse = "<html><body><h1>404 - File Not Found</h1></body></html>";
            sendResponse(out, "404 Not Found", "text/html", errorResponse.getBytes());
            System.out.println("404: Page not found");
        }


    }

    private String getMimeType(File file){
        String fileName = file.getName();
        if(fileName.endsWith(".html") || fileName.endsWith(".htm")){
            return "text/html";
        } else if(fileName.endsWith(".jpg") || fileName.endsWith(".jpeg")){
            return "image/jpeg";
        } else if(fileName.endsWith(".png")){
            return "image/png";
        } else if(fileName.endsWith(".gif")){
            return "image/gif";
        } else if(fileName.endsWith(".txt")){
            return "text/plain";
        }

        else {
            return "application/octet-stream";
        }
    }

    private void sendResponse(OutputStream out, String status, String contentType, byte[] content){
        try {
            String responseHeader = "HTTP/1.0 " + status + "\r\n" +
                    "Server: Java HTTP Server: 1.0\r\n" +
                    "Date: " + new Date() + "\r\n" +
                    "Content-Type: " + contentType + "\r\n" +
                    "Content-Length: " + content.length + "\r\n" +
                    "\r\n";


            out.write(responseHeader.getBytes());
            out.write(content);
            out.flush();

            logToFile("HTTP Response: " + responseHeader);

            out.close();
        } catch (IOException e) {
            System.out.println("Error occurred while sending the response: " + e.getMessage());
            e.printStackTrace();
        }
    }


    private void directoryListing(File directory, OutputStream out) {
        String relativePath = directory.getPath().substring(ROOT_DIRECTORY.length());
//        if (relativePath.equals("")) {
//            relativePath = "/";
//        }
        StringBuilder response = new StringBuilder("<html><body><h1>Directory Listing</h1><ul>");

        for (File file : Objects.requireNonNull(directory.listFiles())) {
            String filePath = relativePath + "/" + file.getName();
            //System.out.println("file P:" + filePath);

            if (file.isDirectory()) {
                response.append("<li><b><i><a href=\"").append(filePath).append("\">")
                        .append(file.getName()).append("</a></i></b></li>");
            } else {
                response.append("<li><a href=\"").append(filePath).append("\">")
                        .append(file.getName()).append("</a></li>");
            }
        }
        response.append("</ul></body></html>");
        sendResponse(out, "200 OK", "text/html", response.toString().getBytes());
    }

    private void sendFile(File file, OutputStream out) {
       String mimeString = getMimeType(file);
       byte[] buffer = new byte[CHUNK_SIZE];
       int readByte;
       try {
           FileInputStream fileIn = new FileInputStream(file);
           ByteArrayOutputStream byteStream = new ByteArrayOutputStream();

           while((readByte = fileIn.read(buffer)) != -1){
               byteStream.write(buffer, 0, readByte);
           }
           fileIn.close();
           sendResponse(out, "200 OK", mimeString, byteStream.toByteArray());

       } catch (IOException e) {
           e.printStackTrace();
           sendResponse(out, "500 Internal server Error", "text/plain", "Internal server Error".getBytes());
       }
    }

    private void logToFile(String logMessage) {
        File logFile = new File("./server/logs/serverLog.txt");

        try (FileWriter fw = new FileWriter(logFile, true);
             BufferedWriter bw = new BufferedWriter(fw);
             PrintWriter out = new PrintWriter(bw)) {
            out.println(new Date() + " - " + logMessage);
            out.println("--------------------------");
        } catch (IOException e) {
            System.out.println("Error occurred while writing to log file: " + e.getMessage());
        }
    }
}
