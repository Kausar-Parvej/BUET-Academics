package com.example.client;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Region;
import my_util.Movie;

import java.io.IOException;
import java.util.List;

public class MovieListViewController {

    private Main main;
    @FXML
    private ScrollPane scrollPane;

    @FXML
    private GridPane gridPane;

    private PChomeWindowController clubHomeWindowController;

    public void loadPlayerCards(List<Movie> playerList) {
        try {
            int row = 0;
            int col = 0;
            for (Movie player : playerList) {
                FXMLLoader fxmlLoader = new FXMLLoader();
                fxmlLoader.setLocation(getClass().getResource("movie-card.fxml"));

                Parent card = fxmlLoader.load();

                MovieCardController playerCardController = fxmlLoader.getController();
                playerCardController.setData(player);
                playerCardController.setClubHomeWindowController(this.clubHomeWindowController);


                gridPane.add(card, col, row++);
                card.getStyleClass().add(player.getProductionCompany().replace(' ', '_'));

                //set grid width
                gridPane.setMinWidth(Region.USE_COMPUTED_SIZE);
                gridPane.setPrefWidth(Region.USE_COMPUTED_SIZE);
                gridPane.setMaxWidth(Region.USE_PREF_SIZE);

                double width = 500;
                gridPane.setMinWidth(width);
                gridPane.setPrefWidth(width);
                gridPane.setMaxWidth(Region.USE_PREF_SIZE);

                //set grid height
                gridPane.setMinHeight(Region.USE_COMPUTED_SIZE);
                gridPane.setPrefHeight(Region.USE_COMPUTED_SIZE);
                gridPane.setMaxHeight(Region.USE_PREF_SIZE);

                GridPane.setMargin(card, new Insets(10));

//                card.toFront();
            }
//            gridPane.toFront();
//            scrollPane.toFront();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public PChomeWindowController getClubHomeWindowController() {
        return clubHomeWindowController;
    }

    public void setClubHomeWindowController(PChomeWindowController clubHomeWindowController) {
        this.clubHomeWindowController = clubHomeWindowController;
    }

}
