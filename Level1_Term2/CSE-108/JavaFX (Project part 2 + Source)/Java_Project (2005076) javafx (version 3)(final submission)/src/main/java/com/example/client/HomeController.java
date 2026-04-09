package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

import javafx.stage.Stage;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;

public class HomeController {

    public Label productionCompany;
    private Main main;

    @FXML
    private Button button;

    @FXML
    void initialize(){
        productionCompany.setText(ReadThread.thisProductionCompany);
    }

    public void init(String msg) {
        productionCompany.setText(msg);
        productionCompany.setText(ReadThread.thisProductionCompany);
        //Image img = new Image(Main.class.getResourceAsStream("1.png"));
        //image.setImage(img);
    }


    void setMain(Main main) {
        this.main = main;
    }

    public void onMenuViewClick(ActionEvent actionEvent) {
        try {
            Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onLogOutClick(ActionEvent actionEvent) {
        try {
            Integer object = Integer.valueOf(7);
            Main.getNetworkUtil().write(object);

            Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
            stage.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
