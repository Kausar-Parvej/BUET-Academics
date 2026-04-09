import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = "", name, subName;
        String flag = " ";

        Crew crew = new Crew("temp");
        Imposter imposter = new Imposter(new Crew("temp"));

        while(!input.equalsIgnoreCase("end")){
            input = scanner.next();

            if(input.equalsIgnoreCase("login")){
                name = scanner.next();
                subName = name.substring(0, 3);
                if(subName.equalsIgnoreCase("cre")){
                    crew = new Crew(name);
                    crew.login(name);
                    flag = "crew";
                }
                else if(subName.equalsIgnoreCase("imp")){
                    imposter = new Imposter(new Crew(name));
                    imposter.login(name);
                    flag = "imposter";
                }
            }

            else if(input.equalsIgnoreCase("repair")){
                if(flag.equals("crew")){
                    crew.repair();
                }
                else if(flag.equals("imposter")){
                    imposter.repair();
                }
                else{
                    System.out.println("Error! Login First");
                }
            }
            else if(input.equalsIgnoreCase("work")){
                if(flag.equals("crew")){
                    crew.work();
                }
                else if(flag.equals("imposter")){
                    imposter.work();
                }
                else{
                    System.out.println("Error! Login First");
                }
            }
            else if(input.equalsIgnoreCase("logout")){
                if(flag.equals("crew")){
                    crew.logout();
                }
                else if(flag.equals("imposter")){
                    imposter.logout();
                }
                else{
                    System.out.println("Error! Login First");
                }
                flag = " ";
            }
            else if(input.equalsIgnoreCase("end")){
                break;
            }
            else{
                System.out.println("Invalid Input!!");
            }
        }
    }
}
