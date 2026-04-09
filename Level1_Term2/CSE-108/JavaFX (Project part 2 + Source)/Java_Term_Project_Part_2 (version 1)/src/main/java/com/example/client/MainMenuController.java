package com.example.client;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

import java.io.IOException;

public class MainMenuController {
    @FXML
    private Label welcomeText;
    private StageApplication application;


    public StageApplication getApplication() {
        return application;
    }

    public void setApplication(StageApplication application) {
        this.application = application;
    }

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }

    public void searchMovieMenu() throws IOException {
        application.goToSearchMovieStage();
    }
    @FXML
    protected void searchPCmenu() throws IOException {
        application.goToSearchPCstage();
    }
}