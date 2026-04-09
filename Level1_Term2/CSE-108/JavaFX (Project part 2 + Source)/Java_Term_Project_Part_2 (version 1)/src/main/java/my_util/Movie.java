package my_util;

import java.io.Serializable;

public class Movie implements Serializable {

    private final String title;
    private final int releasedYear;
    private final String genre;
    //private final String Genre2;
    //private final String Genre3;
    private final int runTime;
    private final String productionCompany;

    private final int budget;
    private final long revenue;

    public Movie(String[] stringArray){

        this.title = stringArray[0];
        this.releasedYear = Integer.parseInt(stringArray[1]);
        String Genre1 = stringArray[2];
        String Genre2 = stringArray[3];
        String Genre3 = stringArray[4];
        this.genre = Genre1 + " "+Genre2 +" "+Genre3;
        this.runTime = Integer.parseInt(stringArray[5]);
        this.productionCompany = stringArray[6];
        this.budget = Integer.parseInt(stringArray[7]);
        this.revenue = Long.parseLong(stringArray[8]);
    }

    //Name,ReleaseYear,Genre1,Genre2,Genre3,RunningTime,ProductionCompany,Budget,revenue
    public String movieDetails(){
        return ("\tName:"+ title +", Release Year:"+ releasedYear +", Genre:"+ genre +", Run Time:"+ runTime +", Production Company:"+ productionCompany +", Budget:"+ budget +", revenue:"+ revenue);
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
}
