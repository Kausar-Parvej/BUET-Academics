import builders.ShakeBuilder;
import director.Director;
import shakeComponent.MilkType;
import shakes.Shake;

import java.util.ArrayList;
import java.util.Scanner;

public class Order {
    public static void main(String[] args) {
        Director director = new Director();
        ShakeBuilder builder = new ShakeBuilder();

        Scanner scanner = new Scanner(System.in);
        int orderCount = 0;
        boolean flag = false;
        boolean flag2;
        String input;

        ArrayList<Shake> orderList = new ArrayList<>();

        while(true){
            orderList.clear();
            System.out.println("\n\tPress 'o' to open orders and 'end' to end program");
            input = scanner.next();
            if(input.equalsIgnoreCase("end")) break;
            if(input.equalsIgnoreCase("o")){
                while(true){
                    flag = false;
                    flag2 = false;
                    System.out.println("\n\tChocolate Shake ---> press 'ch'");
                    System.out.println("\tCoffee Shake -------> press 'c'");
                    System.out.println("\tStrawberry Shake ---> press 's'");
                    System.out.println("\tVanilla Shake ------> press 'v'");
                    System.out.println("\tZero Shake ---------> press 'z'");
                    System.out.println("\tTo Close the order -> press 'e'");
                    input = scanner.next();

                    if(input.equalsIgnoreCase("ch")){
                        orderCount++;
                        director.makeChocolateShake(builder);
                        flag = true;
                    }
                    else if(input.equalsIgnoreCase("c")){
                        orderCount++;
                        director.makeCoffeeShake(builder);
                        flag = true;
                    }
                    else if(input.equalsIgnoreCase("s")){
                        orderCount++;
                        director.makeStrawberryShake(builder);
                        flag = true;
                    }
                    else if(input.equalsIgnoreCase("v")){
                        orderCount++;
                        director.makeVanillaShake(builder);
                        flag = true;
                    }
                    else if(input.equalsIgnoreCase("z")){
                        orderCount++;
                        director.makeZeroShake(builder);
                        flag = true;
                    }
                    else if(input.equalsIgnoreCase("o")){
                        System.out.println("Error Placing new order, would you like to add something else?");
                    }


                    else if(input.equalsIgnoreCase("e")){
                        if(orderCount == 0){
                            System.out.println("Place at least one item as an order!");
                        }
                        else
                            flag2 = true;
                    }

                    if(flag){
                        System.out.println("Would you like to substitute almond milk for regular milk? (y or n)");
                        input = scanner.next();
                        if(input.equalsIgnoreCase("y")){
                            builder.setMilkType(MilkType.ALMOND_MILK);
                        }

                        System.out.println("Would you like to have candy added on top? (y or n)");
                        input = scanner.next();
                        if(input.equalsIgnoreCase("y")){
                            builder.setHasCandy(true);
                        }
                        System.out.println("Would you like to have cookies added on top? (y or n)");
                        input = scanner.next();
                        if(input.equalsIgnoreCase("y")){
                            builder.setHasCookies(true);
                        }

                        Shake shake = builder.getResult();
                        orderList.add(shake);
                        builder.resetAll();

                        System.out.println("Order has been placed successfully. Press 'e' to end or press any key to continue with the order");
                        input = scanner.next();
                        if(input.equalsIgnoreCase("e")) flag2 = true;
                    }

                    if(flag2){
                        System.out.print("\n\t Your Order:");
                        for(Shake order : orderList){
                            order.print();
                        }
                        System.out.println("----------------------------------------------");
                        break;
                    }
                }
            }
            else{
                System.out.println("\nTry again and Press 'O'");
            }
        }
    }
}
