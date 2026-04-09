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


import static com.example.client.LogInController.movieList;
import static com.example.client.LogInController.otherPCmovieList;


public class TransferMovieController {
    public static String movieName;
    public static String toProductionName;
    public TableView<Movie> movieTable;
    public TableView<Movie> pcTable;

    public TableColumn<Movie,String> movie;
    public TableColumn<Movie,String> pcColumn;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(LogInController.myProductionCompany);
        movie.setCellValueFactory(new PropertyValueFactory<>("title"));
        pcColumn.setCellValueFactory(new PropertyValueFactory<>("productionCompany"));

        ArrayList<Movie> temp = (ArrayList<Movie>) movieList;
        movieTable.getItems().clear();
        for(Movie object : temp){
            movieTable.getItems().add(object);
        }
        ArrayList<Movie> tempList = (ArrayList<Movie>) otherPCmovieList;
        pcTable.getItems().clear();
        for(Movie object : tempList){
            pcTable.getItems().add(object);
        }

    }

    public void onBackClick(ActionEvent actionEvent) {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(StageApplication.class.getResource("menu-view.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), 827, 521);
        } catch (IOException e) {
            e.printStackTrace();
        }
        stage.setTitle("Search Production Companies");
        stage.setScene(scene);
    }

    public void onTransferClick(ActionEvent actionEvent) {
        int selectedID = movieTable.getSelectionModel().getSelectedIndex();
        movieName = movieTable.getItems().get(selectedID).getTitle();
        movieTable.getItems().remove(selectedID);

        toProductionName = pcTable.getSelectionModel().getSelectedItem().getProductionCompany();
        System.out.println(movieName);
        System.out.println(toProductionName);
        if(movieName!=null){
            StageApplication.flag = 1;
            System.out.println("Movie is not null....");
        }
    }
}
