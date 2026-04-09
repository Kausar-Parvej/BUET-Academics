package com.example.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

import my_util.NetworkUtil;

import java.io.IOException;

public class Main extends Application {

    private Stage stage;
    private NetworkUtil networkUtil;

    public Stage getStage() {
        return stage;
    }

    public NetworkUtil getNetworkUtil() {
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
        stage.setScene(new Scene(root, 400, 250));
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


    public void showMenuViewPage() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("menu-view.fxml"));
        Parent root = loader.load();

        MenuViewController controller = loader.getController();
        controller.setMain(this);

        stage.setTitle("Home");
        stage.setScene(new Scene(root, 787, 587));
        stage.show();
        //controller.init(pcInfo);
    }
    public void showRecentMoviePage() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("mostRecent-movie.fxml"));
        Parent root = loader.load();

        MostRecentMovieController controller = loader.getController();
        controller.setMain(this);

        stage.setTitle("Most Recent Movie");
        stage.setScene(new Scene(root, 778, 396));
        stage.show();
    }
    public void showHighestGrossingMoviePage() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("highestGrossing-movie.fxml"));
        Parent root = loader.load();

        HighestGrossingMovieController controller = loader.getController();
        controller.setMain(this);

        stage.setTitle("Highest Grossing Movie");
        stage.setScene(new Scene(root, 778, 396));
        stage.show();
    }
    public void showTotalProfitPage() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("total-profit.fxml"));
        Parent root = loader.load();

        TotalProfitController controller = loader.getController();
        controller.setMain(this);

        stage.setTitle("Total Profit");
        stage.setScene(new Scene(root, 778, 396));
        stage.show();
    }
    public void showTransferMoviePage() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("transfer-movie.fxml"));
        Parent root = loader.load();

        TransferMovieController controller = loader.getController();
        controller.setMain(this);

        stage.setTitle("Total Profit");
        stage.setScene(new Scene(root, 827, 521));
        stage.show();
    }

    public void showAlert() {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Incorrect Credentials");
        alert.setHeaderText("Incorrect Credentials");
        alert.setContentText("The username and password you provided is not correct.");
        alert.showAndWait();
    }

}
