package my_util;

public class TransferMovieInfo {
    private String fromProductionCompany;
    private String toProductionCompany;
    private String transferMovie;

    public TransferMovieInfo(String from, String to, String movie){
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

    public String getTransferMovie() {
        return transferMovie;
    }
}
