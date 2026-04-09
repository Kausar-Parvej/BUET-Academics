import java.util.Scanner;

public class Main {
    public static Container currentDirectory;
    public static Container rootDirectory;

    public static void main(String[] args) {
        rootDirectory = new Container("root", "Root", "");
        currentDirectory = rootDirectory;

        Scanner scanner = new Scanner(System.in);
        String input = "";
        String name,tempString;

        while (!input.equalsIgnoreCase("end")){
            input = scanner.next();

            if(input.equals("cd")){
                String directory = scanner.next();
                if(!directory.equals("~")){
                    Container temp = currentDirectory.changeDirectory(directory);
                    if(temp != null){
                        currentDirectory = temp;
                    }
                }
                else{
                    currentDirectory = rootDirectory;
                    System.out.println("In the root directory");
                }

            }

            else if(input.equals("ls")){
                name = scanner.next();
                currentDirectory.findChild(name);
            }

            else if(input.equals("list")){
                currentDirectory.childList();
            }

            else if(input.equals("delete")){
                name = scanner.next();
                if(!name.equals("-r")){
                    currentDirectory.delete(name);
                }
                else{
                    name = scanner.next();
                    currentDirectory.recursiveDelete(name);
                }
            }
            else if(input.equals("mkdir")){
                name = scanner.next();
                currentDirectory.makeDir(name);
            }

            else if(input.equals("touch")){
                name = scanner.next();
                int size = scanner.nextInt();
                currentDirectory.touch(name,size);
            }

            else if(input.equals("mkdrive")){
                name = scanner.next();
                rootDirectory.makeDrive(name);
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
