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
import my_util.ListOperation;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;

import static com.example.client.LogInController.movieList;

public class HighestGrossingMovieController {
    public TableView<Movie> table;
    public TableColumn<Movie,String> name;
    public TableColumn<Movie, Integer> year;
    public TableColumn<Movie,String> genre;
    public TableColumn<Movie,Integer> runTime;
    public TableColumn<Movie,Integer> budget;
    public TableColumn<Movie,Long> revenue;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(LogInController.myProductionCompany);
        name.setCellValueFactory(new PropertyValueFactory<>("title"));
        year.setCellValueFactory(new PropertyValueFactory<>("releasedYear"));
        genre.setCellValueFactory(new PropertyValueFactory<>("genre"));
        runTime.setCellValueFactory(new PropertyValueFactory<>("runTime"));
        budget.setCellValueFactory(new PropertyValueFactory<>("budget"));
        revenue.setCellValueFactory(new PropertyValueFactory<>("revenue"));

        ArrayList<Movie> temp = ListOperation.search_By_MaximumRevenue((ArrayList<Movie>) movieList);
        table.getItems().clear();
        for(Movie object : temp){
            table.getItems().add(object);
        }
    }

    public void onBackClick(ActionEvent actionEvent){
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("menu-view.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), 735, 525);
        } catch (IOException e) {
            e.printStackTrace();
        }
        stage.setTitle("Search Production Companies");
        stage.setScene(scene);
    }
}
