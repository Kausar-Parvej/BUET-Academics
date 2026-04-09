package my_util;

import java.io.Serializable;

public class TransferMovieInfo implements Serializable {
    private final String fromProductionCompany;
    private final String toProductionCompany;
    private final Movie transferMovie;

    public TransferMovieInfo(String from, String to, Movie movie){
        this.fromProductionCompany = from;
        this.toProductionCompany = to;
        this.transferMovie = movie;
    }

    public String getFromProductionCompany() {
        return fromProductionCompany;
    }

    public String getToProductionCompany() {
        return toProductionCompany;
    }

    public Movie getTransferMovie() {
        return transferMovie;
    }
}
