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


public class MostRecentMovieController {
    public Label thisPC;
    LogInController logInController;
    @FXML
    private TableView<Movie> table;
    @FXML
    private TableColumn<Movie,String> name;
    @FXML
    private TableColumn<Movie, Integer> year;
    @FXML
    private TableColumn<Movie,String> genre;
    @FXML
    private TableColumn<Movie,Integer> runTime;
    @FXML
    private TableColumn<Movie,Integer> budget;
    @FXML
    private TableColumn<Movie,Long> revenue;

    @FXML
    void initialize(){
        thisPC.setText(LogInController.myProductionCompany);
        name.setCellValueFactory(new PropertyValueFactory<>("title"));
        year.setCellValueFactory(new PropertyValueFactory<>("releasedYear"));
        genre.setCellValueFactory(new PropertyValueFactory<>("genre"));
        runTime.setCellValueFactory(new PropertyValueFactory<>("runTime"));
        budget.setCellValueFactory(new PropertyValueFactory<>("budget"));
        revenue.setCellValueFactory(new PropertyValueFactory<>("revenue"));

        ArrayList<Movie> temp = ListOperation.search_By_MostRecent((ArrayList<Movie>) movieList);
        table.getItems().clear();
        for(Movie object : temp){
            table.getItems().add(object);
        }
    }

    public void onBackClick(ActionEvent actionEvent){
        //logInController.onLogInClick(logInController.actionEvent);
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

    public void setLogInController(LogInController logInController) {
        this.logInController = logInController;
    }
}
