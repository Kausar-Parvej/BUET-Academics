package com.example.client;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import my_util.Movie;


public class MovieDetailsController {
    public Label trailer;
    private  Movie movie;
    private Main main;
    private Stage stage;
    private Movie p;

    @FXML
    private ImageView playerImage;


    @FXML
    private Label pName;

    @FXML
    private Label pValue;

    @FXML
    private Label pClub;

    @FXML
    private Label pCountry;

    @FXML
    private Label pHeight;

    @FXML
    private Label pWeight;

    @FXML
    private Label pPosition;

    @FXML
    private Label pNumber;


    public void setMain(Main main) {
        this.main = main;
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }

    public void initiate(Movie player) {
        this.p = player;
        var cName = player.getGenre();
        var club_name = player.getProductionCompany();

        String url = ReadThread.movieImageLinkMap.get(player.getTitle().toLowerCase());
        if(url != null){
            boolean backgroundLoading = true;
            Image image = new Image(url, backgroundLoading);
            playerImage.setImage(image);
        }

       /* try {
            Image pImage = new Image(player.getImageSource(), true);
            playerImage.setImage(pImage);
        } catch (Exception e) {
            var loaded = Main.class.getResourceAsStream("/Assets/Image/Player Image/Anonymous.jpg");
            assert loaded != null;
            playerImage.setImage(new Image(loaded));
        }*/

        /*Image flagImage = null;
        var what = main.countryFlagMap.get(player.getCountry());
        if (what != null) flagImage = new Image(what, true);
        else flagImage = new Image("https://www.pngfind.com/pngs/m/295-2959995_anonymous-png-transparent-png.png", true);
        flag.setImage(flagImage);*/


       /* if (player.getClubName().equalsIgnoreCase(main.myClub.getName())) logo.setImage(main.cLogo);
        else {
            try {
                logo.setImage(new Image(main.clubLogoMap.get(player.getClubName()), true));
            } catch (Exception e) {
                logo.setImage(new Image("https://www.shopinimizaj.com/frontend/web/images/no-image.png", true));
            }
        }*/

        pName.setText(player.getTitle());
        pValue.setText(Integer.toString(player.getReleasedYear()));
        pClub.setText(club_name);
        pCountry.setText(player.getGenre());
        pHeight.setText(player.getRunTime() + " min");
        pWeight.setText(player.getBudget()/1000000 + "M $");
        pPosition.setText(player.getRevenue()/1000000 + "M $");
        pNumber.setText(player.getProfit()/1000000 + "M $");


    }

    public void setData(Movie movie) {
        this.movie = movie;
        var cName = movie.getGenre();
        var club_name = movie.getProductionCompany();

        String url = ReadThread.movieImageLinkMap.get(movie.getTitle().toLowerCase());
        if(url != null){
            boolean backgroundLoading = true;
            Image image = new Image(url, backgroundLoading);
            playerImage.setImage(image);
        }

       /* try {
            Image pImage = new Image(player.getImageSource(), true);
            playerImage.setImage(pImage);
        } catch (Exception e) {
            var loaded = Main.class.getResourceAsStream("/Assets/Image/Player Image/Anonymous.jpg");
            assert loaded != null;
            playerImage.setImage(new Image(loaded));
        }*/

        /*Image flagImage = null;
        var what = main.countryFlagMap.get(player.getCountry());
        if (what != null) flagImage = new Image(what, true);
        else flagImage = new Image("https://www.pngfind.com/pngs/m/295-2959995_anonymous-png-transparent-png.png", true);
        flag.setImage(flagImage);*/


       /* if (player.getClubName().equalsIgnoreCase(main.myClub.getName())) logo.setImage(main.cLogo);
        else {
            try {
                logo.setImage(new Image(main.clubLogoMap.get(player.getClubName()), true));
            } catch (Exception e) {
                logo.setImage(new Image("https://www.shopinimizaj.com/frontend/web/images/no-image.png", true));
            }
        }*/

        pName.setText(movie.getTitle());
        pValue.setText(Integer.toString(movie.getReleasedYear()));
        pClub.setText(club_name);
        pCountry.setText(movie.getGenre());
        pHeight.setText(movie.getRunTime() + " min");
        pWeight.setText(movie.getBudget()/1000000 + "M $");
        pPosition.setText(movie.getRevenue()/1000000 + "M $");
        pNumber.setText(movie.getProfit()/1000000 + "M $");


    }
}
