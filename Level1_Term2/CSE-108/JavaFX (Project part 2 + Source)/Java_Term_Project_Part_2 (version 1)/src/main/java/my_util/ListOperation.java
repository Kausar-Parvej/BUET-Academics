package my_util;

import java.util.ArrayList;

public class ListOperation {



    //--------------------Implementing (1) Search Movies_functions----------------------//


    public static Movie search_By_Title(ArrayList<Movie> list, String str){
        for (Movie object : list) {
            if (object.getTitle().equalsIgnoreCase(str)) {
                return object;
            }
        }
        return null;
    }

    public static ArrayList<Movie> search_By_ReleaseYear(ArrayList<Movie> list, int number){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getReleasedYear() == number) {
                tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_By_Genre(ArrayList<Movie> list, String str){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getGenre().equalsIgnoreCase(str) ) {
                tempList.add(object);
            }
        }
        return tempList;
    }
    public static ArrayList<Movie> search_BY_ProductionCompany(ArrayList<Movie> list, String str){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getProductionCompany().equalsIgnoreCase(str)) {
                tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_BY_RunTime(ArrayList<Movie> list, int start, int end){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getRunTime() >= start && object.getRunTime() <= end) {
                tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> Top_10_Movies(ArrayList<Movie> list){
        int n = 10;
        int index = 0;
        long maxProfit = 0;
        ArrayList<Movie> tempList = new ArrayList<>();
        for(Movie object : list){
            if(object.getProfit() > maxProfit){
                maxProfit = object.getRevenue();
                index = list.indexOf(object);
            }
        }
        tempList.add(list.get(index));
        for(int i = 1; i < n; i++){
            maxProfit = 0;
            for (Movie object : list) {
                if (object.getProfit() < tempList.get(i-1).getProfit() && object.getProfit() > maxProfit) {
                    maxProfit = object.getProfit();
                    index = list.indexOf(object);
                }
            }
            tempList.add(list.get(index));
        }
        return tempList;
    }



        //------------------Implementing (2) Search Production Companies_functions--------------------//

    public static ArrayList<Movie> search_By_MostRecent(ArrayList<Movie> list){
        boolean flag = false;
        int recentYear = 0;
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie mvi : list) {
            if (mvi.getReleasedYear() > recentYear) {
                recentYear = mvi.getReleasedYear();
                flag = true;
            }
        }
        if(flag){
            for (Movie object : list) {
                if (object.getReleasedYear() == recentYear)
                    tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_By_MaximumRevenue(ArrayList<Movie> list){
        boolean flag = false;
        long maxRevenue = 0;
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie mvi : list) {
            if (mvi.getRevenue() > maxRevenue) {
                maxRevenue = mvi.getRevenue();
                flag = true;
            }
        }
        if(flag){
            for (Movie object : list) {
                if (object.getRevenue() == maxRevenue)
                    tempList.add(object);
            }
        }
        return tempList;
    }

    public static long search_for_TotalProfit(ArrayList<Movie> list){
       // MovieList.flag = false;
        long sumProfit = 0;
        for (Movie object : list) {
                sumProfit += object.getProfit();
                //MovieList.flag = true;
        }
        return sumProfit;
    }

    public static ArrayList<String> List_of_ProductionCompanies(ArrayList<Movie> list){
        ArrayList<String> pcList = new ArrayList<>();
        int n = list.size();
        int[] array = new int[n];
        for(int i =0; i< n; i++)
            array[i] = 1;

        for(int i =0; i<n; i++){
            for(int j = i+1; j<n; j++){
                if(list.get(j).getProductionCompany().equalsIgnoreCase(list.get(i).getProductionCompany())){
                    array[i]++;
                    array[j] =-list.size() -1000;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (array[i] > 0)
                pcList.add(list.get(i).getProductionCompany());
        }
        return pcList;
    }
    public static ArrayList<Integer> ProductionCompany_totalMovie(ArrayList<Movie> list){
        ArrayList<Integer> movieCount = new ArrayList<>();
        int n = list.size();
        int[] array = new int[n];
        for(int i =0; i< n; i++)
            array[i] = 1;

        for(int i =0; i<n; i++){
            for(int j = i+1; j<n; j++){
                if(list.get(j).getProductionCompany().equalsIgnoreCase(list.get(i).getProductionCompany())){
                    array[i]++;
                    array[j] = -list.size() -1000;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (array[i] > 0)
                movieCount.add(array[i]);
        }
        return movieCount;
    }
    public static ArrayList<Movie> otherProductionMovies(ArrayList<Movie> list, String str){
        ArrayList<Movie> pcList = new ArrayList<>();
        int n = list.size();
        int[] array = new int[n];
        for(int i =0; i< n; i++)
            array[i] = 1;

        for(int i =0; i<n; i++){
            for(int j = i+1; j<n; j++){
                if(list.get(j).getProductionCompany().equalsIgnoreCase(list.get(i).getProductionCompany())){
                    array[i]++;
                    array[j] =-list.size() -1000;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (array[i] > 0 && !list.get(i).getProductionCompany().equalsIgnoreCase(str))
                pcList.add(list.get(i));
        }
        return pcList;
    }

}


     //-------------------------------------------!!COMPLETED!!--------------------------------------------//


           //Sorting all movies according to their release year for a particular Production Company

//private static void sort_By_MostRecent(){
//    int flag=0;
//    System.out.println();
//    System.out.println("\tEnter a particular Production Company to see it's most recent produced movies:");
//    System.out.print("\t");
//    Scanner scan = new Scanner(System.in);
//    String productionCom = scan.nextLine();
//    System.out.println();
//    List<Movie> Recent_movieList = new ArrayList<>();
//    for (Movie movie : MovieList) {
//        if (movie.getProduction_Company().equalsIgnoreCase(productionCom)) {
//            if (flag == 0)
//                System.out.println("\t\tThe latest Movies of the production company " + movie.getProduction_Company() + " according to their released year:");
//            Recent_movieList.add(movie);
//            flag = 1;
//        }
//    }
//    if(flag==1){
//        Movie[] recentMovies = new Movie[Recent_movieList.size()];
//        int recentYear = 0;
//        int index = 0;
//        for(int i=0; i<Recent_movieList.size(); i++){
//            if(Recent_movieList.get(i).getReleasedYear() > recentYear){
//                recentYear = Recent_movieList.get(i).getReleasedYear();
//                index = i;
//            }
//        }
//        recentMovies[0] = Recent_movieList.get(index);
//        for(int i=1; i<Recent_movieList.size(); i++){
//            recentYear = 0;
//            for(int j=0; j<Recent_movieList.size(); j++){
//                if(Recent_movieList.get(j).getReleasedYear() < recentMovies[i-1].getReleasedYear() && Recent_movieList.get(j).getReleasedYear() > recentYear){
//                    recentYear = Recent_movieList.get(j).getReleasedYear();
//                    index = j;
//                }
//            }
//            recentMovies[i] = Recent_movieList.get(index);
//        }
//        for(int i = 0; i<Recent_movieList.size(); i++)
//            recentMovies[i].printMovie_Details();
//    }
//    else System.out.println("\t\tNo such production company with this name!");
//}