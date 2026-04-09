package my_util;

import java.io.Serializable;

public class Movie implements Serializable {

    private final String title;
    private final int releasedYear;
    private final String genre;
    //private final String Genre2;
    //private final String Genre3;
    private final int runTime;
    private String productionCompany;

    private final int budget;
    private final long revenue;

    public Movie(String[] stringArray){

        this.title = stringArray[0];
        this.releasedYear = Integer.parseInt(stringArray[1]);
        this.genre = stringArray[2];
        this.runTime = Integer.parseInt(stringArray[3]);
        this.productionCompany = stringArray[4];
        this.budget = Integer.parseInt(stringArray[5]);
        this.revenue = Long.parseLong(stringArray[6]);
    }

    //Name,ReleaseYear,Genre1,Genre2,Genre3,RunningTime,ProductionCompany,Budget,revenue
    public String movieDetails(){
        return title+","+releasedYear+","+genre+","+runTime+","+productionCompany+","+budget+","+revenue;
    }

    public long getProfit(){
        return (this.revenue - this.budget);
    }


    public String getTitle() {
        return title;
    }

    public int getReleasedYear() {
        return releasedYear;
    }

    public String getGenre() {
        return genre;
    }

    public int getRunTime() {
        return runTime;
    }

    public String getProductionCompany() {
        return productionCompany;
    }

    public int getBudget() {
        return budget;
    }

    public long getRevenue() {
        return revenue;
    }

    public void setProductionCompany(String productionCompany) {
        this.productionCompany = productionCompany;
    }
}
