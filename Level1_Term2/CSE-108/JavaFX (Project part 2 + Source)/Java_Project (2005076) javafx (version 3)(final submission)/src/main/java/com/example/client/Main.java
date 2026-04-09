package com.example.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

import my_util.Movie;
import my_util.NetworkUtil;

import java.io.IOException;
import java.util.ArrayList;

public class Main extends Application {

    private static Stage stage;
    private static NetworkUtil networkUtil;

    public Stage getStage() {
        return stage;
    }

    public static NetworkUtil getNetworkUtil() {
        return networkUtil;
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        stage = primaryStage;
        connectToServer();
        showLoginPage();
    }

    public static void main(String[] args) {
        // This will launch the JavaFX application
        launch(args);
    }



    private void connectToServer() throws IOException {
        String serverAddress = "127.0.0.1";
        int serverPort = 33333;
        networkUtil = new NetworkUtil(serverAddress, serverPort);
        new ReadThread(this);
    }
    public void showLoginPage() throws Exception {
        // XML Loading using FXMLLoader
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("login.fxml"));
        Parent root = loader.load();

        // Loading the controller
        LoginController controller = loader.getController();
        controller.setMain(this);

        // Set the primary stage
        stage.setTitle("Login");
        stage.setScene(new Scene(root, 603, 371));
        stage.show();
    }
    public void showHomePage(String userName) throws Exception {

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("home.fxml"));
        Parent root = loader.load();

        // Loading the controller
        HomeController controller = loader.getController();
        controller.init(userName);
        controller.setMain(this);

        // Set the primary stage
        stage.setTitle("Home");
        stage.setScene(new Scene(root, 673, 419));
        stage.show();
    }


    public static void showProductionHomePage(String clubName, ArrayList<Movie> mList) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(Main.class.getResource("productionHomeWindow.fxml"));

        Parent root = fxmlLoader.load();

        PChomeWindowController controller = fxmlLoader.getController();
        if(mList != null){
            controller.init(clubName, mList);
        }
        //controller.setMain(this);

        //Scene scene = new Scene(root);
        stage.setTitle(clubName);
        stage.setScene(new Scene(root, 1100, 600));
        stage.setX(10);
        stage.setY(10);
        stage.show();


        /*stage.setTitle(clubName);
        stage.setScene(scene);
        stage.setX(10);
        stage.setY(10);
        stage.show();*/
    }


    public void showAlert() {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Incorrect Credentials");
        alert.setHeaderText("Incorrect Credentials");
        alert.setContentText("The username and password you provided is not correct.");
        alert.showAndWait();
    }
    public static void showAlert2() {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Incorrect Credentials");
        alert.setHeaderText("ERROR");
        alert.setContentText("No Such Movie in This Production Company");
        alert.showAndWait();
    }

}
