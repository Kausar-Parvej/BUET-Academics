public class Movie {

    private final String Title;
    private final int Year_of_Release;
    private final String Genre1;
    private final String Genre2;
    private final String Genre3;
    private final int Running_Time;
    private final String Production_Company;
    private final int Budget;
    private final long Revenue;

    public Movie(String[] stringArray){

        this.Title = stringArray[0];
        this.Year_of_Release = Integer.parseInt(stringArray[1]);
        this.Genre1 = stringArray[2];
        this.Genre2 = stringArray[3];
        this.Genre3 = stringArray[4];
        this.Running_Time = Integer.parseInt(stringArray[5]);
        this.Production_Company = stringArray[6];
        this.Budget = Integer.parseInt(stringArray[7]);
        this.Revenue = Long.parseLong(stringArray[8]);
    }

    //Name,ReleaseYear,Genre1,Genre2,Genre3,RunningTime,ProductionCompany,Budget,Revenue
    public void printMovie_Details(){
        System.out.print("\tName:"+Title+", Release_Year:"+Year_of_Release+", Genre:"+Genre1+","+Genre2+","+Genre3);
        System.out.println(", Run_Time:"+Running_Time+", Production_Company:"+Production_Company+", Budget:"+Budget+", Revenue:"+Revenue);
    }
    public String movieDetails(){
        return Title+","+Year_of_Release+","+Genre1+","+Genre2+","+Genre3+","+Running_Time+","+Production_Company+","+Budget+","+Revenue;
    }
    public long getProfit(){
        return (this.Revenue - this.Budget);
    }


    public String getTitle() {
        return Title;
    }

    public int getYear_of_Release() {
        return Year_of_Release;
    }

    public String getGenre1() {
        return Genre1;
    }

    public String getGenre2() {
        return Genre2;
    }

    public String getGenre3() {
        return Genre3;
    }

    public int getRunning_Time() {
        return Running_Time;
    }

    public String getProduction_Company() {
        return Production_Company;
    }

    public long getRevenue() {
        return Revenue;
    }
}
