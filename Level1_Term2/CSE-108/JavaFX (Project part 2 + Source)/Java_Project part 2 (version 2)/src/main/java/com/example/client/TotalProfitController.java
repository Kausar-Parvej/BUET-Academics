package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import my_util.ListOperation;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;

public class TotalProfitController {
    private Main main;


    public Label totalProfit;
    public Label thisPC;

    @FXML
    void initialize(){
        thisPC.setText(ReadThread.thisProductionCompany);
        long sumProfit = ListOperation.search_for_TotalProfit((ArrayList<Movie>) ReadThread.thisMovieList);
        totalProfit.setText(Long.toString(sumProfit));
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
