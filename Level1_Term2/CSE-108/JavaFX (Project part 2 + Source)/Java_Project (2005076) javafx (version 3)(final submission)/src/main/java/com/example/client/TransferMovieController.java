package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import javafx.stage.Stage;
import my_util.Movie;
import my_util.TransferMovieInfo;

import java.io.IOException;
import java.util.ArrayList;

public class TransferMovieController {
    public Label transferMovie;
    private Main main;
    private Movie movie;
    public TableView<Movie> pcTable;

    public TableColumn<Movie,String> pcColumn;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(ReadThread.thisProductionCompany);
        //transferMovie.setText(this.movie.getTitle());
        pcColumn.setCellValueFactory(new PropertyValueFactory<>("productionCompany"));

        ArrayList<Movie> tempList = (ArrayList<Movie>) ReadThread.otherPCmovieList;
        pcTable.getItems().clear();
        for(Movie object : tempList){
            pcTable.getItems().add(object);
        }

    }

    public void onBackClick(ActionEvent actionEvent) {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        stage.close();
    }

    public void onTransferClick(ActionEvent actionEvent) {

        String toProductionName = pcTable.getSelectionModel().getSelectedItem().getProductionCompany();

        if(toProductionName!=null){
            for(int i=0; i<ReadThread.thisMovieList.size();i++){
                if(this.movie == ReadThread.thisMovieList.get(i)){
                    ReadThread.thisMovieList.remove(i);
                    break;
                }
            }
            try {
                Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("Checking TransferMovieController 1......Selected Production is not null");
            TransferMovieInfo transferInfo = new TransferMovieInfo(ReadThread.thisProductionCompany, toProductionName, this.movie);
            try {
                Main.getNetworkUtil().write(transferInfo);
                Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
                stage.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    public void setData(Movie movie) {
        this.movie = movie;
    }
}
