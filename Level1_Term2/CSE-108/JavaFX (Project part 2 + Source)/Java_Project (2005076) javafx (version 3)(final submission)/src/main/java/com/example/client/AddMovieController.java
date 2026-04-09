package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;

public class AddMovieController {


    public TextField name;
    public TextField genre;
    public TextField budget;
    public TextField revenue;
    public TextField profit;
    public TextField trailerLink;
    public Text productionCompany;
    public TextField year;
    public TextField imageURL;
    public TextField runTime;

    @FXML
    void initialize(){
        productionCompany.setText(ReadThread.thisProductionCompany);
    }

    public void onSubmitClick(ActionEvent actionEvent) {
        String [] stringArray = new String[7];

        stringArray[0] = name.getText();
        stringArray[1] = year.getText();
        stringArray[2] = genre.getText();
        stringArray[3] = runTime.getText();
        stringArray[4] = ReadThread.thisProductionCompany;
        stringArray[5] = budget.getText();
        stringArray[6] = revenue.getText();

        String imageSource = imageURL.getText();
        String trailerSource = trailerLink.getText();

        Movie newObject = new Movie(stringArray);
        ReadThread.thisMovieList.add(newObject);

        try {
            Main.getNetworkUtil().write(newObject);
            Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
        } catch (IOException e) {
            e.printStackTrace();
        }
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        stage.close();
    }

    public void onCancelClick(ActionEvent actionEvent) {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        stage.close();
    }
}
