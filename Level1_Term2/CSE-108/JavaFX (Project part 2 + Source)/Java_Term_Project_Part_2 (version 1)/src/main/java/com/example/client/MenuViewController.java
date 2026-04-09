package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;

public class MenuViewController {
    public Label thisPC;
    private StageApplication application;
    public TableView<Movie> table;
    public TableColumn<Movie,String> name;
    public TableColumn<Movie, Integer> year;
    public TableColumn<Movie,String> genre;
    public TableColumn<Movie,Integer> runTime;
    public TableColumn<Movie,Integer> budget;
    public TableColumn<Movie,Long> revenue;


    @FXML
    void initialize(){
        thisPC.setText(LogInController.myProductionCompany);
        name.setCellValueFactory(new PropertyValueFactory<>("title"));
        year.setCellValueFactory(new PropertyValueFactory<>("releasedYear"));
        genre.setCellValueFactory(new PropertyValueFactory<>("genre"));
        runTime.setCellValueFactory(new PropertyValueFactory<>("runTime"));
        budget.setCellValueFactory(new PropertyValueFactory<>("budget"));
        revenue.setCellValueFactory(new PropertyValueFactory<>("revenue"));

        ArrayList<Movie> temp = (ArrayList<Movie>) LogInController.movieList;
        table.getItems().clear();
        for(Movie object : temp){
            table.getItems().add(object);
        }
    }

    public void onRecentMovieClick(ActionEvent actionEvent) throws IOException {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("mostRecent-movie.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 778, 396);
        stage.setTitle("Most Recent Movie!");
        stage.setScene(scene);
    }

    public void onHighestGrossingMovieClick(ActionEvent actionEvent) throws IOException {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("highestGrossing-movie.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 785, 354);
        stage.setTitle("Highest Grossing Movie!");
        stage.setScene(scene);
    }

    public void onTotalProfitClick(ActionEvent actionEvent) throws IOException {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("total-profit.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 779, 354);
        stage.setTitle("Total Profit!");
        stage.setScene(scene);
    }
    public void setApplication(StageApplication application) {
        this.application = application;
    }

    public void onTranferMovieClick(ActionEvent actionEvent) throws IOException {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("transfer-movie.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 827, 521);
        stage.setTitle("Transfer Movie!");
        stage.setScene(scene);
    }

    public void onAddMovieClick(ActionEvent actionEvent) {
    }

    public void onLogOutClick(ActionEvent actionEvent) {
    }
}
