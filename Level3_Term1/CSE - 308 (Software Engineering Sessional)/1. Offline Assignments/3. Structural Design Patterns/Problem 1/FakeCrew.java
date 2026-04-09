public abstract class FakeCrew implements Passenger{
    String fakeCrewName;
    private final Passenger passenger;

    public FakeCrew(Passenger passenger){
        this.passenger = passenger;
        this.fakeCrewName = passenger.getName();
    }

    @Override
    public void login(String name) {
        passenger.login(name);
    }

    @Override
    public void repair() {
        passenger.repair();
    }

    @Override
    public void work() {
        passenger.work();
    }

    @Override
    public void logout() {
        passenger.logout();
    }
}
