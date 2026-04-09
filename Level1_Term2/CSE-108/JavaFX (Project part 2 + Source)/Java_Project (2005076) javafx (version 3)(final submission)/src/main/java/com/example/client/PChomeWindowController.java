package com.example.client;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;

import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
import javafx.stage.Modality;
import javafx.stage.Stage;
import my_util.ListOperation;
import my_util.Movie;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PChomeWindowController {
    public ImageView pcImage;
    public Label ageLabel;
    public Label heightLabel;
    public Label salaryLabel;
    public TextField runTimeFromTextField;
    public TextField runTimeToTextField;
    public Label totalProfit;
    public TextField enterGenre;
    public TextField enterYear;

    //@FXML
    //private ImageView clubLogoImage;

    @FXML
    private Label productionNameFirstLine;
    

    @FXML
    private Label productionNameSecondLine;



    @FXML
    private TextField searchMovieNameTextField;

    @FXML
    private Button searchMovieButton;

    @FXML
    private Button resetMovieSearchButton;


    @FXML
    private VBox playerListVBox;

//    @FXML
//    private ScrollPane scrollPane;
//
//    @FXML
//    private GridPane gridPane;


    @FXML
    private Button resetFiltersButton;


    //private Club club;
    private Movie movie;
    private String clubName;
    private String logoImgSource;
    private List<Movie> playerListOnDisplay;
    private Main main;


    private boolean aBoolean = false;




    @FXML
    void applyFilters(ActionEvent event) {
        /*Database db = new Database();
        db.addPlayer(club.getPlayers());
        applyFiltersCountry(db);
        applyFiltersPosition(db);
        applyFiltersAge(db);
        applyFiltersHeight(db);
        applyFiltersSalary(db);

        loadPlayerCards(db.getPlayerList());*/
    }
/*
    private void applyFiltersSalary(Database db) {
        double lo, hi;
        try {
            lo = Double.parseDouble(salaryFromTextField.getText());
        } catch (Exception e) {
            lo = 0;
            salaryFromTextField.setText(String.valueOf(lo));
        }
        try {
            hi = Double.parseDouble(salaryToTextField.getText());
        } catch (Exception e) {
            hi = club.getMaxSalaryPlayers().get(0).getSalary();
            salaryToTextField.setText(String.valueOf(hi));
        }
        db.setPlayerList(db.searchPlayerBySalary(lo, hi));
    }

    private void applyFiltersHeight(Database db) {
        double lo, hi;
        try {
            lo = Double.parseDouble(heightFromTextField.getText());
        } catch (Exception e) {
            lo = 0;
            heightFromTextField.setText(String.valueOf(lo));
        }
        try {
            hi = Double.parseDouble(heightToTextField.getText());
        } catch (Exception e) {
            hi = club.getMaxHeightPlayers().get(0).getHeight();
            heightToTextField.setText(String.valueOf(hi));
        }
        db.setPlayerList(db.searchPlayerByHeight(lo, hi));
    }

    private void applyFiltersAge(Database db) {
        int lo, hi;
        try {
            lo = Integer.parseInt(ageFromTextField.getText());
        } catch (Exception e) {
            lo = 0;
            ageFromTextField.setText(String.valueOf(lo));
        }
        try {
            hi = Integer.parseInt(ageToTextField.getText());
        } catch (Exception e) {
            hi = club.getMaxAgePlayers().get(0).getAge();
            ageToTextField.setText(String.valueOf(hi));
        }
        db.setPlayerList(db.searchPlayerByAge(lo, hi));
    }

    private void applyFiltersPosition(Database db) {
        for (TreeItem<CheckBox> item:
                filterTreePosition.getRoot().getChildren()) {
            if (!item.getValue().isSelected()) {
                // remove players playing at this position
                for (Player player:
                        db.searchPlayerByPosition(item.getValue().getText())) {
                    db.getPlayerList().remove(player);
                }
            }
        }
    }

    private void applyFiltersCountry(Database db) {
        for (TreeItem<CheckBox> item:
             filterTreeCountry.getRoot().getChildren()) {
            if (!item.getValue().isSelected()) {
                // remove players from this country
                for (Player player:
                        db.searchPlayerByCountry(item.getValue().getText())) {
                    db.getPlayerList().remove(player);
                }
            }
        }
    }
*/
    @FXML
    void initialize(){
        String str;
        long sumProfit = ListOperation.search_for_TotalProfit((ArrayList<Movie>) ReadThread.thisMovieList);
        str = sumProfit/1000000 + "M $";
        totalProfit.setText(str);
    }

    public void init(String clubName, ArrayList<Movie> mviList) {
        this.clubName = clubName;
        initClubInfo();
        loadPlayerCards(mviList);
    }

    private void initClubInfo() {
        //String clubName = this.clubName.replace(' ', '_');
        String clubName = ReadThread.thisProductionCompany.replace(' ', '_');
        //logoImgSource = this.club.getImgSource();
        //clubLogoImage.setImage(new Image(getClass().getResourceAsStream(logoImgSource)));
        String[] words = clubName.split("_");
        productionNameFirstLine.setText(words[0].toUpperCase());
        if (words.length == 2) {
            productionNameSecondLine.setText(words[1].toUpperCase());
        }
        else if(words.length > 2){
            productionNameSecondLine.setText(words[1].toUpperCase() + " " + words[2].toUpperCase());
        }
        else {
            productionNameSecondLine.setText("");
        }
    }

    // for listing players under any condition
    private void loadPlayerCards(List<Movie> movieList) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("movieListView.fxml"));
            Parent root = fxmlLoader.load();

            MovieListViewController movieListViewController = fxmlLoader.getController();
            movieListViewController.setClubHomeWindowController(this);
            movieListViewController.loadPlayerCards(movieList);
            //movieListViewController.setMain(this.main);

            playerListVBox.getChildren().clear();
            playerListVBox.getChildren().add(root);

            this.playerListOnDisplay = new ArrayList<>(movieList);

        } catch (IOException e) {
            e.printStackTrace();
        }

    }


    public void onBackClick(ActionEvent actionEvent) {
        Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("home.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), 673, 419);
        } catch (IOException e) {
            e.printStackTrace();
        }
        stage.setTitle("Home");
        stage.setScene(scene);
        stage.show();
    }

    public void onSearchClickByName(ActionEvent actionEvent) {
        String movieName = searchMovieNameTextField.getText();
        if(movieName != null){
            Movie searchedMovie = ListOperation.search_By_Title((ArrayList<Movie>) ReadThread.thisMovieList, movieName);
            ArrayList<Movie> tempList = new ArrayList<>();
            tempList.add(searchedMovie);

            try {
                if(searchedMovie != null){
                    Main.showProductionHomePage(ReadThread.thisProductionCompany, tempList);
                }
                else {
                    Main.showAlert2();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void onSearchClearClick(ActionEvent actionEvent) {
        searchMovieNameTextField.setText(null);
        try {
            Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onMostRecentMovieClick(ActionEvent actionEvent) {
        ArrayList<Movie> tempList = ListOperation.search_By_MostRecent((ArrayList<Movie>) ReadThread.thisMovieList);
        try {
            Main.showProductionHomePage(ReadThread.thisProductionCompany, tempList);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onHighestGrossingMovieClick(ActionEvent actionEvent) {
        ArrayList<Movie> tempList = ListOperation.search_By_MaximumRevenue((ArrayList<Movie>) ReadThread.thisMovieList);
        try {
            Main.showProductionHomePage(ReadThread.thisProductionCompany, tempList);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void applyFiltersClick(ActionEvent actionEvent) {

        /*String movieGenre = null;
        String movieYear = null;
        String  fromTime = null;
        String toTime = null;*/
        String movieGenre = enterGenre.getText();
        //movieYear = enterYear.getText();
        //fromTime = runTimeFromTextField.getText();
        //toTime = runTimeToTextField.getText();

        //ArrayList<Movie> tempList = new ArrayList<>(ReadThread.thisMovieList);
        ArrayList<Movie> tempList = null;

        if(movieGenre != null){
            tempList = ListOperation.search_By_Genre((ArrayList<Movie>) ReadThread.thisMovieList, movieGenre);
        }
        /*if(movieYear != null){
            //Integer num = Integer.valueOf(movieYear);
            //tempList = ListOperation.search_By_ReleaseYear(tempList, num);
        }
        if(fromTime != null && toTime!= null){
            //Integer num1 = Integer.valueOf(fromTime);
            //Integer num2 = Integer.valueOf(toTime);
            //tempList = ListOperation.search_BY_RunTime(tempList, num1, num2);
        }*/
        try {
            if(tempList != null){
                Main.showProductionHomePage(ReadThread.thisProductionCompany, tempList);
            }
            else{
                Main.showAlert2();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void resetFiltersClick(ActionEvent actionEvent) {
        enterGenre.setText(null);
        enterYear.setText(null);
        runTimeFromTextField.setText(null);
        runTimeToTextField.setText(null);
        try {
            Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void onAddMovieClick(ActionEvent actionEvent) {
        try {
            Stage window = new Stage();
            window.initModality(Modality.APPLICATION_MODAL);
            window.setTitle("ADD Movie");

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("add-movie.fxml"));
            Parent root = fxmlLoader.load();


            Scene scene = new Scene(root);
            window.setScene(scene);
            window.showAndWait();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

   /* public void setMain(Main main) {
        this.main = main;
    }*/
}
