import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class movieList {

    private static final String INPUT_FILE_NAME = "movies.txt";
    private static final String OUTPUT_FILE_NAME = "movies.txt";
    public static boolean flag;
    public static final List<Movie> MovieList = new ArrayList<>();



    public static void main(String[] args) throws Exception {

        BufferedReader bufferedReader = new BufferedReader(new FileReader(INPUT_FILE_NAME));

        while (true) {
            String single_line = bufferedReader.readLine();
            if (single_line == null) break;

            String[] single_word = single_line.split(",");
            Movie movie = new Movie(single_word);
            MovieList.add(movie);
        }
        bufferedReader.close();

        Main_Menu();


    }

    private static void Main_Menu() {

        while (true) {
            System.out.println();
            System.out.println("\t\tMain Menu:");
            System.out.println("\t\t1) Search Movies");
            System.out.println("\t\t2) Search Production Companies");
            System.out.println("\t\t3) Add Movie");
            System.out.println("\t\t4) Exit System");
            System.out.println();
            System.out.print("\t\t");

            Scanner scan = new Scanner(System.in);
            if (!scan.hasNextInt()) {
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-4 !!");
                continue;
            }
            int option = scan.nextInt();

            if (option == 1) searchMovies();
            else if (option == 2) searchProduction_Company();
            else if (option == 3) addMovie();
            else if (option == 4) {
                System.out.println();
                System.out.println("\t\t\t---Successfully Exited the Program...Thank You---");
                System.out.println();
                try {
                    exitSystem();
                } catch (Exception e) {
                    throw new RuntimeException(e);
                }
                break;
            } else
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-4 !!");

        }
    }

    private static void searchMovies() {
        Scanner scanLine = new Scanner(System.in);
        Scanner scanInt = new Scanner(System.in);
        while (true) {
            System.out.println();
            System.out.println("\t\tMovie Searching Options:");
            System.out.println("\t\t1) By Movie Title");
            System.out.println("\t\t2) By Release Year");
            System.out.println("\t\t3) By Genre");
            System.out.println("\t\t4) By Production Company");
            System.out.println("\t\t5) By Running Time");
            System.out.println("\t\t6) Top 10 Movies");
            System.out.println("\t\t7) Back to Main Menu");
            System.out.println();
            System.out.print("\t\t");

            Scanner scan = new Scanner(System.in);
            if (!scan.hasNextInt()) {
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-7 !!");
                continue;
            }
            int option = scan.nextInt();

            if (option == 1) {
                System.out.println();
                System.out.println("\tEnter the Movie name you want to search:");
                System.out.print("\t");
                String movieTitle = scanLine.nextLine();
                System.out.println();
                Movie searchedMovie = searchList_operation.search_By_Title((ArrayList<Movie>) MovieList, movieTitle);
                if (searchedMovie != null) {
                    System.out.println("\t\tThe details of your searched Movie:");
                    searchedMovie.printMovie_Details();
                } else
                    System.out.println("\t\tNo such movie with this name!");
            }

            else if (option == 2) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tEnter the Released Year of the movies you want to see:");
                System.out.print("\t");
                int releasedYear = scanInt.nextInt();
                System.out.println();
                tempList = searchList_operation.search_By_ReleaseYear((ArrayList<Movie>) MovieList, releasedYear);
                if (tempList.size() > 0) {
                    System.out.println("\t\tIn the year " + releasedYear + " these movies had been released:");
                    for (Movie mvi : tempList) {
                        mvi.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such movie with this release year!");
            }

            else if (option == 3) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tThe Genre of the movies you want to see:");
                System.out.print("\t");
                String genre = scanLine.nextLine();
                System.out.println();
                tempList = searchList_operation.search_By_Genre((ArrayList<Movie>) MovieList, genre);
                if (tempList.size() > 0) {
                    System.out.println("\t\tWe have movies for Genre " + genre.toUpperCase() + ":");
                    for (Movie mvi : tempList) {
                        mvi.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such movie with this genre!");
            }

            else if (option == 4) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tEnter a particular Production Company to see it's produced movies:");
                System.out.print("\t");
                String PC = scanLine.nextLine();
                System.out.println();
                tempList = searchList_operation.search_BY_ProductionCompany((ArrayList<Movie>) MovieList, PC);
                if (tempList.size() > 0) {
                    System.out.println("\t\tThe production company " + PC.toUpperCase() + " has produced these movies:");
                    for (Movie mvi : tempList) {
                        mvi.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such movie with this production company!");
            }

            else if (option == 5) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tEnter a range of Run-Time to see the movies in this range(in minute):");
                System.out.print("\t");
                int initialTime = scanInt.nextInt();
                int finalTime = scanInt.nextInt();
                System.out.println();
                tempList = searchList_operation.search_BY_RunTime((ArrayList<Movie>) MovieList, initialTime, finalTime);
                if (tempList.size() > 0) {
                    System.out.println("\t\tThe movies whose run time in the range " + initialTime + "-" + finalTime + " :");
                    for (Movie mvi : tempList) {
                        mvi.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such movie with this running time range!");
            }

            else if (option == 6) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\t\tDisplaying TOP 10 MOVIES (based on profit):");
                tempList = searchList_operation.Top_10_Movies((ArrayList<Movie>) MovieList);
                for (Movie mvi : tempList) {
                    mvi.printMovie_Details();
                }
            }

            else if (option == 7) break;

            else
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-5 !!");
        }
    }


    private static void searchProduction_Company() {
        Scanner scanLine = new Scanner(System.in);
        while (true) {
            System.out.println();
            System.out.println("\t\tProduction Company Searching Options:");
            System.out.println("\t\t1) Most Recent Movies");
            System.out.println("\t\t2) Movies with the Maximum Revenue");
            System.out.println("\t\t3) Total Profit");
            System.out.println("\t\t4) List of Production Companies and the Count of their Produced Movies");
            System.out.println("\t\t5) Back to Main Menu");
            System.out.println();
            System.out.print("\t\t");

            Scanner scan = new Scanner(System.in);
            if (!scan.hasNextInt()) {
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-5 !!");
                continue;
            }
            int option = scan.nextInt();

            if (option == 1) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tEnter a particular Production Company to see it's most recent produced movie:");
                System.out.print("\t");
                String productionCom = scanLine.nextLine();
                System.out.println();
                tempList = searchList_operation.search_By_MostRecent((ArrayList<Movie>) MovieList, productionCom);
                if (tempList.size() > 0) {
                    System.out.println("\t\tThe Latest  Movie of the production company " + productionCom.toUpperCase() + " :");
                    for (Movie mvi : tempList) {
                        mvi.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such production company with this name!");

            }

            else if (option == 2) {
                ArrayList<Movie> tempList;
                System.out.println();
                System.out.println("\tEnter a particular Production Company to see it's Highest Grossed produced movie:");
                System.out.print("\t");
                String productionCom = scanLine.nextLine();
                System.out.println();
                tempList = searchList_operation.search_By_MaximumRevenue((ArrayList<Movie>) MovieList, productionCom);
                if (tempList.size() > 0) {
                    System.out.println("\t\tThe Highest Grossed Movie of the production company " + productionCom.toUpperCase() + " :");
                    for (Movie object : tempList) {
                        object.printMovie_Details();
                    }
                } else
                    System.out.println("\t\tNo such production company with this name!");
            }

            else if (option == 3) {
                long totalProfit;
                System.out.println();
                System.out.println("\tEnter a particular Production Company to see it's total profit (or loss):");
                System.out.print("\t");
                String productionCom = scanLine.nextLine();
                System.out.println();
                totalProfit = searchList_operation.search_for_TotalProfit((ArrayList<Movie>) MovieList, productionCom);
                if (flag) {
                    if (totalProfit >= 0) {
                        System.out.println("\t\tThe total Profit of the production company " + productionCom + " : " + totalProfit + " $");
                    } else
                        System.out.println("\t\tThe total Loss of the production company " + productionCom + " : " + (-totalProfit) + " $");
                } else
                    System.out.println("\t\tNo such production company with this name!");
            }

            else if (option == 4) {
                ArrayList<String> pcList;
                ArrayList<Integer> movieCount;
                System.out.println();
                System.out.println("\tDisplaying all the Production Company and the number of movies they have produced:");
                System.out.println();
                pcList = searchList_operation.List_of_ProductionCompanies((ArrayList<Movie>) MovieList);
                movieCount = searchList_operation.ProductionCompany_totalMovie((ArrayList<Movie>) MovieList);

                for (int i = 0; i < pcList.size(); i++) {
                        System.out.println("\t\t" + (i+1) + ") " + pcList.get(i) + ", Number of produced movie: " + movieCount.get(i));
                }
            }

            else if (option == 5) break;
            else
                System.out.println("\t\t!! Invalid Input. Please Enter the number 1-5 !!");
        }
    }

    private static void addMovie() {
        Scanner scanLine = new Scanner(System.in);
        String[] movieData = new String[9];
        System.out.println();
        System.out.println("\tPlease enter the details of the Movie that you want to add:");
        System.out.println();

        System.out.println("\t\tEnter the Name of the movie:");
        System.out.print("\t\t");
        movieData[0] = scanLine.nextLine();
        for (Movie mvi : MovieList) {
            if (mvi.getTitle().equalsIgnoreCase(movieData[0])) {
                System.out.println();
                System.out.println("\t\t!! Error, this movie already exists in the List !! ");
                return;
            }
        }

        System.out.println("\t\tEnter the Release Year:");
        System.out.print("\t\t");
        movieData[1] = scanLine.nextLine();

        System.out.println("\t\tEnter the Genres of the movie (Please follow the format: Genre1,Genre2,Genre3) you can use SPACE in place of Genre2 and Genre3 :");
        System.out.print("\t\t");
        Scanner newScan = new Scanner(System.in);
        String genres = newScan.nextLine();
        String[] genre = genres.split(",");
        movieData[2] = genre[0];
        movieData[3] = genre[1];
        movieData[4] = genre[2];

        System.out.println("\t\tEnter the Run Time of the movie (in minute):");
        System.out.print("\t\t");
        movieData[5] = scanLine.nextLine();

        System.out.println("\t\tEnter the Production Company:");
        System.out.print("\t\t");
        movieData[6] = scanLine.nextLine();

        System.out.println("\t\tEnter the Budget of the movie:");
        System.out.print("\t\t");
        movieData[7] = scanLine.nextLine();

        System.out.println("\t\tEnter the Revenue of the movie:");
        System.out.print("\t\t");
        movieData[8] = scanLine.nextLine();
        System.out.println();

        Movie movie = new Movie(movieData);
        MovieList.add(movie);

        System.out.println("\t\tMovie has been perfectly added....Exit the program successfully to save it to the file");
    }

    private static void exitSystem() throws Exception {

        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME));
        for (Movie mvi : MovieList) {
            bufferedWriter.write(mvi.movieDetails());
            bufferedWriter.write(System.lineSeparator());
        }
        bufferedWriter.close();
    }
}


     //-------------------------------------------!!COMPLETED!!--------------------------------------------//
