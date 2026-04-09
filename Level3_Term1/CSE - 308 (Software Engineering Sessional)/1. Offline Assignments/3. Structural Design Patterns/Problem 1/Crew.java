public class Crew implements Passenger{
    String crewName;

    public Crew(String name){
        this.crewName = name;
    }
    @Override
    public void login(String name) {
        System.out.println("Welcome Crewmate!");
    }

    @Override
    public void repair() {
        System.out.println("Repairing the spaceship.");
    }

    @Override
    public void work() {
        System.out.println("Doing research");
    }

    @Override
    public void logout() {
        System.out.println("Bye Bye crewmate.");
    }

    @Override
    public String getName() {
        return this.crewName;
    }
}
