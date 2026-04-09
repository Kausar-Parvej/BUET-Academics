package server;

import javafx.application.Platform;
import my_util.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ReadThreadServer implements Runnable {
    private static final List<Movie> pcMovieList = new ArrayList<>();
    private static List<Movie> otherProductionMovieList = new ArrayList<>();
    private static String thisProduction;
    public static HashMap<String, NetworkUtil> clientMap = new HashMap<>();

    private Server server;
    private final Thread thr;
    private final NetworkUtil networkUtil;
    public HashMap<String, String> userMap;



    public ReadThreadServer(HashMap<String, String> map, NetworkUtil networkUtil, Server server) {
        this.server = server;
        this.userMap = map;
        this.networkUtil = networkUtil;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = networkUtil.read();
                if (o != null) {
                    if (o instanceof LoginDTO) {
                        LoginDTO loginDTO = (LoginDTO) o;
                        String password = userMap.get(loginDTO.getUserName());
                        loginDTO.setStatus(loginDTO.getPassword().equals(password));
                        networkUtil.write(loginDTO);

                        if(loginDTO.isStatus()){
                            String str = loginDTO.getUserName();
                            clientMap.put(str.toLowerCase(),this.networkUtil);
                            for(Movie object : Server.allMovieList){
                                if(object.getProductionCompany().equalsIgnoreCase(str)){
                                    pcMovieList.add(object);
                                }
                            }
                            thisProduction = pcMovieList.get(0).getProductionCompany();
                            otherProductionMovieList = ListOperation.otherProductionMovies((ArrayList<Movie>) Server.allMovieList,thisProduction);
                            ProductionCompanyInfo productionCompanyInfo = new ProductionCompanyInfo((ArrayList<Movie>) pcMovieList, (ArrayList<Movie>) otherProductionMovieList,thisProduction);
                            networkUtil.write(productionCompanyInfo);
                            System.out.println("checking ReadThreadServer 1....."+productionCompanyInfo.getThisProduction());
                            pcMovieList.clear();
                            otherProductionMovieList.clear();
                        }
                    }
                    if(o instanceof TransferMovieInfo){
                        TransferMovieInfo transferInfo = (TransferMovieInfo) o;
                        System.out.println("checking ReadThreadServer 2... transferred movie: "+ transferInfo.getTransferMovie().getTitle());

                        for(int i =0; i<Server.allMovieList.size(); i++){
                            if(Server.allMovieList.get(i).getTitle().equalsIgnoreCase(transferInfo.getTransferMovie().getTitle())){
                                Server.allMovieList.remove(i);
                            }
                        }
                        transferInfo.getTransferMovie().setProductionCompany(transferInfo.getToProductionCompany());
                        Server.allMovieList.add(transferInfo.getTransferMovie());
                        for(Movie mvi : Server.allMovieList){
                            if(mvi.getTitle().equalsIgnoreCase(transferInfo.getTransferMovie().getTitle())){
                                System.out.println("checking ReadThreadServer 77....has changed? "+mvi.getProductionCompany());
                            }
                        }
                        System.out.println("checking ReadThreadServer 3... transferred movie to : "+ transferInfo.getTransferMovie().getProductionCompany());

                        NetworkUtil toNetworkUtil = clientMap.get(transferInfo.getToProductionCompany().toLowerCase());
                        toNetworkUtil.write(transferInfo);
                    }
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                networkUtil.closeConnection();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}



