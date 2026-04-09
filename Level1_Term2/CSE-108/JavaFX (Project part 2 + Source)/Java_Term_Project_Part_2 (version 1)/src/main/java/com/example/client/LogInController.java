package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import my_util.Movie;
import my_util.SocketWrapper;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class LogInController {
    ActionEvent actionEvent;
    public TextField productionCompanyName;
    public static List<Movie> movieList = new ArrayList<>();
    public static List<Movie> otherPCmovieList = new ArrayList<>();
    public static String myProductionCompany;


    MenuViewController menuViewController;

    public void onLogInClick(ActionEvent actionEvent) throws IOException {
        //Client.connectToServer();
        this.actionEvent=actionEvent;
        SocketWrapper server = new SocketWrapper("127.0.0.1", 44444);
        String pcName = productionCompanyName.getText();
        System.out.println(productionCompanyName.getText());
        server.write(pcName);
        //new Thread(() -> {
            try {
                movieList = (ArrayList<Movie>)server.read();
                otherPCmovieList = (ArrayList<Movie>)server.read();
                myProductionCompany = (String) server.read();




            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }finally {
                try {
                    server.closeConnection();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if(StageApplication.flag==1){
                System.out.println("Clicked Transfer....");
                server.write(LogInController.myProductionCompany);
                server.write(TransferMovieController.toProductionName);
                server.write(TransferMovieController.movieName);
            }

        //}).start();
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("menu-view.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), 787, 587);
        } catch (IOException e) {
            e.printStackTrace();
        }
        //MenuViewController controller = fxmlLoader.getController();
        //controller.setApplication(this);
        stage.setTitle("Search Production Companies");
        stage.setScene(scene);



    }
    public void onResetClick(ActionEvent actionEvent) {
        productionCompanyName.setText("");
    }
}
