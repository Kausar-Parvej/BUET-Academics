package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import my_util.Movie;
import my_util.ProductionCompanyInfo;

import java.io.IOException;
import java.util.ArrayList;

public class MenuViewController {

    private ProductionCompanyInfo pcInfo;
    private Main main;
    public Label thisPC;

    public TableView<Movie> table;
    public TableColumn<Movie,String> name;
    public TableColumn<Movie, Integer> year;
    public TableColumn<Movie,String> genre;
    public TableColumn<Movie,Integer> runTime;
    public TableColumn<Movie,Integer> budget;
    public TableColumn<Movie,Long> revenue;


    @FXML
    void initialize(){
        thisPC.setText(ReadThread.thisProductionCompany);
        name.setCellValueFactory(new PropertyValueFactory<>("title"));
        year.setCellValueFactory(new PropertyValueFactory<>("releasedYear"));
        genre.setCellValueFactory(new PropertyValueFactory<>("genre"));
        runTime.setCellValueFactory(new PropertyValueFactory<>("runTime"));
        budget.setCellValueFactory(new PropertyValueFactory<>("budget"));
        revenue.setCellValueFactory(new PropertyValueFactory<>("revenue"));

        ArrayList<Movie> temp = (ArrayList<Movie>) ReadThread.thisMovieList;
        table.getItems().clear();
        for(Movie object : temp){
            table.getItems().add(object);
        }
    }

    public void onRecentMovieClick(ActionEvent actionEvent) {
        try {
            main.showRecentMoviePage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onHighestGrossingMovieClick(ActionEvent actionEvent) {
        try {
            main.showHighestGrossingMoviePage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onTotalProfitClick(ActionEvent actionEvent) {
        try {
            main.showTotalProfitPage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onTransferMovieClick(ActionEvent actionEvent) {
        try {
            main.showTransferMoviePage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onAddMovieClick(ActionEvent actionEvent) {
    }

    public void onBackClick(ActionEvent actionEvent) {
        try {
            main.showHomePage(ReadThread.thisProductionCompany.toUpperCase());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void setMain(Main main) {
        this.main = main;
    }


}
