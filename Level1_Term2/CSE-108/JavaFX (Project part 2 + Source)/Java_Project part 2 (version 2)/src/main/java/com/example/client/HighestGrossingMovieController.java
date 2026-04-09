package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import my_util.ListOperation;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;


public class HighestGrossingMovieController {
    private Main main;
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
        thisPC.setText(ReadThread.thisProductionCompany);
        name.setCellValueFactory(new PropertyValueFactory<>("title"));
        year.setCellValueFactory(new PropertyValueFactory<>("releasedYear"));
        genre.setCellValueFactory(new PropertyValueFactory<>("genre"));
        runTime.setCellValueFactory(new PropertyValueFactory<>("runTime"));
        budget.setCellValueFactory(new PropertyValueFactory<>("budget"));
        revenue.setCellValueFactory(new PropertyValueFactory<>("revenue"));

        ArrayList<Movie> temp = ListOperation.search_By_MaximumRevenue((ArrayList<Movie>) ReadThread.thisMovieList);
        table.getItems().clear();
        for(Movie object : temp){
            table.getItems().add(object);
        }
    }

    public void onBackClick(ActionEvent actionEvent){
        try {
            main.showMenuViewPage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void setMain(Main main) {
        this.main = main;
    }
}
