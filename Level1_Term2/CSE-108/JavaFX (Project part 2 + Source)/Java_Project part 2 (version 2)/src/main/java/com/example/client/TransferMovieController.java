package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import my_util.Movie;
import my_util.TransferMovieInfo;

import java.io.IOException;
import java.util.ArrayList;

public class TransferMovieController {
    private Main main;
    public TableView<Movie> movieTable;
    public TableView<Movie> pcTable;

    public TableColumn<Movie,String> movie;
    public TableColumn<Movie,String> pcColumn;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(ReadThread.thisProductionCompany);
        movie.setCellValueFactory(new PropertyValueFactory<>("title"));
        pcColumn.setCellValueFactory(new PropertyValueFactory<>("productionCompany"));

        ArrayList<Movie> temp = (ArrayList<Movie>) ReadThread.thisMovieList;
        movieTable.getItems().clear();
        for(Movie object : temp){
            movieTable.getItems().add(object);
        }
        ArrayList<Movie> tempList = (ArrayList<Movie>) ReadThread.otherPCmovieList;
        pcTable.getItems().clear();
        for(Movie object : tempList){
            pcTable.getItems().add(object);
        }

    }

    public void onBackClick(ActionEvent actionEvent) {
        try {
            main.showMenuViewPage();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onTransferClick(ActionEvent actionEvent) {
        int selectedID = movieTable.getSelectionModel().getSelectedIndex();
        Movie selectedMovie = movieTable.getItems().get(selectedID);

        movieTable.getItems().remove(selectedID);
        ReadThread.thisMovieList.remove(selectedMovie);

        String toProductionName = pcTable.getSelectionModel().getSelectedItem().getProductionCompany();

        if(selectedMovie!=null){
            System.out.println("Checking TransferMovieController 1......Selected Movie is not null");
            TransferMovieInfo transferInfo = new TransferMovieInfo(ReadThread.thisProductionCompany, toProductionName, selectedMovie);
            try {
                main.getNetworkUtil().write(transferInfo);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void setMain(Main main) {
        this.main = main;
    }
}
