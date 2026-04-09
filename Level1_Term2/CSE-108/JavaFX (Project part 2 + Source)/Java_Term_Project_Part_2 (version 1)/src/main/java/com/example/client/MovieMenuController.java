package com.example.client;

import java.io.IOException;

public class MovieMenuController {
    private StageApplication application;

    public StageApplication getApplication() {
        return application;
    }

    public void setApplication(StageApplication application) {
        this.application = application;
    }
    public void searchByMovieTitle() throws IOException {
        application.goToSearchByMovieTitleStage();
    }
}
