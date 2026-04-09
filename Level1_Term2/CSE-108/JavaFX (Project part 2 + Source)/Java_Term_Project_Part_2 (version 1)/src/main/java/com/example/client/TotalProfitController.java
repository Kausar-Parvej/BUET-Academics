package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import my_util.ListOperation;
import my_util.Movie;


import java.io.IOException;
import java.util.ArrayList;

import static com.example.client.LogInController.movieList;

public class TotalProfitController {


    public Label totalProfit;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(LogInController.myProductionCompany);
        long sumProfit = ListOperation.search_for_TotalProfit((ArrayList<Movie>) movieList);
        totalProfit.setText(Long.toString(sumProfit));
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
