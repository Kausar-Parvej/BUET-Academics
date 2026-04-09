package com.example.client;

import javafx.application.Platform;
import my_util.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ReadThread implements Runnable {
    public static List<Movie> thisMovieList = new ArrayList<>();
    public static List<Movie> otherPCmovieList = new ArrayList<>();
    public static String thisProductionCompany;
    public static HashMap<String, String> movieImageLinkMap = new HashMap<>();
    private final Thread thr;
    private final Main main;

    public ReadThread(Main main) {
        this.main = main;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = main.getNetworkUtil().read();
                if (o != null) {
                    if (o instanceof LoginDTO) {
                        LoginDTO loginDTO = (LoginDTO) o;
                        System.out.println(loginDTO.getUserName());
                        System.out.println(loginDTO.isStatus());
                        // the following is necessary to update JavaFX UI components from user created threads
                        Platform.runLater(new Runnable() {
                            @Override
                            public void run() {
                                if (loginDTO.isStatus()) {
                                    try {
                                        main.showHomePage(loginDTO.getUserName().toUpperCase());
                                    } catch (Exception e) {
                                        e.printStackTrace();
                                    }
                                } else {
                                    main.showAlert();
                                }
                            }
                        });
                    }
                    if(o instanceof ProductionCompanyInfo){
                        ProductionCompanyInfo pcInfo = (ProductionCompanyInfo) o;
                        System.out.println("checking ReadThread 1...."+pcInfo.getThisProduction());
                        thisMovieList = pcInfo.getPcMovieList();
                        otherPCmovieList = pcInfo.getOtherProductionMovieList();
                        thisProductionCompany = pcInfo.getThisProduction();
                    }
                    if(o instanceof TransferMovieInfo){
                        TransferMovieInfo transferInfo = (TransferMovieInfo) o;
                        System.out.println("checking ReadThread 2....Transfer movie to "+transferInfo.getToProductionCompany());
                        ReadThread.thisMovieList.add(transferInfo.getTransferMovie());
                        Platform.runLater(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    Main.showProductionHomePage(ReadThread.thisProductionCompany, (ArrayList<Movie>) ReadThread.thisMovieList);
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        });
                    }
                    /*if(o instanceof Movie){
                        Platform.runLater(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    System.out.println("checking ReadThread 3....Transfer movie from "+ReadThread.thisProductionCompany);
                                    Main.showProductionHomePage(ReadThread.thisProductionCompany);
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        });
                    }*/
                    if(o instanceof SendResources){
                        SendResources resources = (SendResources) o;
                        movieImageLinkMap = resources.getImageLinkMap();
                    }

                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                main.getNetworkUtil().closeConnection();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}



