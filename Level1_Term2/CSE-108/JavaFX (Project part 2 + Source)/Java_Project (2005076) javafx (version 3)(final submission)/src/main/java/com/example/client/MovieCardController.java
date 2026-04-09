package com.example.client;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.stage.Modality;
import javafx.stage.Stage;
import my_util.Movie;

import java.io.IOException;

public class MovieCardController {

    private Main main;
    @FXML
    private ImageView playerImage;

    @FXML
    private Label playerNameLabel;

    @FXML
    private Label playerPositionLabel;

    @FXML
    private Button playerDetailsButton;

    @FXML
    private Button playerSellButton;

    @FXML
    private Label playerPriceLabel;

    private Movie movie;
    private PChomeWindowController clubHomeWindowController;

    @FXML
    void onTransferClick(ActionEvent event) {

        try {
            Stage window = new Stage();
            window.initModality(Modality.APPLICATION_MODAL);
            window.setTitle(movie.getTitle());

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("transfer-movie.fxml"));
            Parent root = fxmlLoader.load();

            TransferMovieController controller = fxmlLoader.getController();
            controller.setData(movie);

            Scene scene = new Scene(root);
            window.setScene(scene);
            window.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    void hideSellButton(MouseEvent event) {
        playerSellButton.setVisible(false);
    }

    @FXML
    void showSellButton(MouseEvent event) {
        playerSellButton.setVisible(true);
    }

    @FXML
    void onMovieDetailsClick(ActionEvent event) {

        try {
            Stage window = new Stage();
            window.initModality(Modality.APPLICATION_MODAL);
            window.setTitle(movie.getTitle());

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("movie-details.fxml"));
            Parent root = fxmlLoader.load();

            MovieDetailsController controller = fxmlLoader.getController();
            controller.setData(movie);

            Scene scene = new Scene(root);
            window.setScene(scene);
            window.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    @FXML
    public void selectPlayer(MouseEvent event) {
//        System.out.println(this.player.getName());
//        playerSellButton.setVisible(true);
    }

    public void setData(Movie movie) {
        this.movie = movie;
        playerNameLabel.setText(movie.getTitle());
        playerPositionLabel.setText(Integer.toString(movie.getReleasedYear()));
        playerPriceLabel.setText("Profit: " + movie.getProfit()/1000000 + "M $");
        //playerImage.setImage(new Image(getClass().getResourceAsStream(player.getImgSource())));
        String url = ReadThread.movieImageLinkMap.get(movie.getTitle().toLowerCase());
        if(url != null){
            boolean backgroundLoading = true;
            Image image = new Image(url, backgroundLoading);
            playerImage.setImage(image);
        }

    }

    public PChomeWindowController getClubHomeWindowController() {
        return clubHomeWindowController;
    }

    public void setClubHomeWindowController(PChomeWindowController clubHomeWindowController) {
        this.clubHomeWindowController = clubHomeWindowController;
    }

}
