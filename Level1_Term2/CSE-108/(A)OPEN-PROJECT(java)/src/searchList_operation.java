import java.util.ArrayList;

public class searchList_operation {



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
            if (object.getYear_of_Release() == number) {
                tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_By_Genre(ArrayList<Movie> list, String str){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getGenre1().equalsIgnoreCase(str) || object.getGenre2().equalsIgnoreCase(str) || object.getGenre3().equalsIgnoreCase(str)) {
                tempList.add(object);
            }
        }
        return tempList;
    }
    public static ArrayList<Movie> search_BY_ProductionCompany(ArrayList<Movie> list, String str){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getProduction_Company().equalsIgnoreCase(str)) {
                tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_BY_RunTime(ArrayList<Movie> list, int start, int end){
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie object : list) {
            if (object.getRunning_Time() >= start && object.getRunning_Time() <= end) {
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

    public static ArrayList<Movie> search_By_MostRecent(ArrayList<Movie> list, String str){
        boolean flag = false;
        int recentYear = 0;
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie mvi : list) {
            if (mvi.getProduction_Company().equalsIgnoreCase(str) && mvi.getYear_of_Release() > recentYear) {
                recentYear = mvi.getYear_of_Release();
                flag = true;
            }
        }
        if(flag){
            for (Movie object : list) {
                if (object.getProduction_Company().equalsIgnoreCase(str) && object.getYear_of_Release() == recentYear)
                    tempList.add(object);
            }
        }
        return tempList;
    }

    public static ArrayList<Movie> search_By_MaximumRevenue(ArrayList<Movie> list, String str){
        boolean flag = false;
        long maxRevenue = 0;
        ArrayList<Movie> tempList = new ArrayList<>();
        for (Movie mvi : list) {
            if (mvi.getProduction_Company().equalsIgnoreCase(str) && mvi.getRevenue() > maxRevenue) {
                maxRevenue = mvi.getRevenue();
                flag = true;
            }
        }
        if(flag){
            for (Movie object : list) {
                if (object.getProduction_Company().equalsIgnoreCase(str) && object.getRevenue() == maxRevenue)
                    tempList.add(object);
            }
        }
        return tempList;
    }

    public static long search_for_TotalProfit(ArrayList<Movie> list, String str){
        movieList.flag = false;
        long sumProfit = 0;
        for (Movie object : list) {
            if (object.getProduction_Company().equalsIgnoreCase(str)) {
                sumProfit += object.getProfit();
                movieList.flag = true;
            }
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
                if(list.get(j).getProduction_Company().equalsIgnoreCase(list.get(i).getProduction_Company())){
                    array[i]++;
                    array[j] = -1000;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (array[i] > 0)
                pcList.add(list.get(i).getProduction_Company());
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
                if(list.get(j).getProduction_Company().equalsIgnoreCase(list.get(i).getProduction_Company())){
                    array[i]++;
                    array[j] = -1000;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (array[i] > 0)
                movieCount.add(array[i]);
        }
        return movieCount;
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
//            if(Recent_movieList.get(i).getYear_of_Release() > recentYear){
//                recentYear = Recent_movieList.get(i).getYear_of_Release();
//                index = i;
//            }
//        }
//        recentMovies[0] = Recent_movieList.get(index);
//        for(int i=1; i<Recent_movieList.size(); i++){
//            recentYear = 0;
//            for(int j=0; j<Recent_movieList.size(); j++){
//                if(Recent_movieList.get(j).getYear_of_Release() < recentMovies[i-1].getYear_of_Release() && Recent_movieList.get(j).getYear_of_Release() > recentYear){
//                    recentYear = Recent_movieList.get(j).getYear_of_Release();
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