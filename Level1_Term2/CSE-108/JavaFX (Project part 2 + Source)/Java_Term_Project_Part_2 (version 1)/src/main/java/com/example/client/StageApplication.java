package com.example.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

//import server.Server;

public class StageApplication extends Application {
    public static int flag;

    static {
        flag = 0;
    }

    Stage stage;

    public static void main(String[] args) {

        launch();
    }

    /*public static void connectToServer() throws IOException {
        SocketWrapper server = new SocketWrapper("127.0.0.1", 44444);
        Scanner test=new Scanner(System.in);
        String send=test.nextLine();
        server.write(send);

        new Thread(()->{



        }).start();
    }*/

    @Override
    public void start(Stage primaryStage) throws IOException {
        this.stage = primaryStage;
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("log-in.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 715, 405);

        //MainMenuController controller = fxmlLoader.getController();
        //controller.setApplication(this);
        LogInController controller = fxmlLoader.getController();

        stage.setTitle("Log In!");
        stage.setScene(scene);
        stage.show();
    }

    void transferMovieStage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("transfer-movie.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 702, 492);
        stage.setTitle("Search Movies");
        stage.setScene(scene);
        stage.show();
    }

    void goToSearchMovieStage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("searchMovie-menu.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 450, 290);
        MovieMenuController controller = fxmlLoader.getController();
        controller.setApplication(this);
        stage.setTitle("Search Movies");
        stage.setScene(scene);
        stage.show();
    }
    void goToSearchByMovieTitleStage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("searchBY-movieTitle.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 850, 350);
        stage.setTitle("Search Production Companies");
        stage.setScene(scene);
        stage.show();
    }


    void goToSearchPCstage() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("productionCompany-menu.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 450, 290);
        stage.setTitle("Search Production Companies");
        stage.setScene(scene);
        stage.show();
    }
}