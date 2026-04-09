public class Imposter extends FakeCrew{
    public Imposter(Passenger passenger) {
        super(passenger);
    }

    @Override
    public void login(String name){
        super.login(name);
        System.out.println("\"We won’t tell anyone; you are an imposter.\"");
    }

    @Override
    public void repair(){
        super.repair();
        System.out.println("\"Damaging the spaceship\"");
    }

    @Override
    public void work(){
        super.work();
        System.out.println("\"Trying to kill a crewmate. \nSuccessfully killed a crewmate.\"");
    }

    @Override
    public void logout(){
        super.logout();
        System.out.println("\"See you again Comrade Imposter.\"");
    }

    @Override
    public String getName() {
        return this.fakeCrewName;
    }
}
