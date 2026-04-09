package my_util;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class ProductionCompanyInfo implements Serializable {
    private List<Movie> pcMovieList = new ArrayList<>();
    private List<Movie> otherProductionMovieList = new ArrayList<>();
    private final String thisProduction;

    public ProductionCompanyInfo(ArrayList<Movie> thisList, ArrayList<Movie> otherList, String pcName){
        this.pcMovieList = thisList;
        this.otherProductionMovieList = otherList;
        this.thisProduction = pcName;
    }

    public List<Movie> getPcMovieList() {
        return pcMovieList;
    }

    public List<Movie> getOtherProductionMovieList() {
        return otherProductionMovieList;
    }

    public String getThisProduction() {
        return thisProduction;
    }
}
