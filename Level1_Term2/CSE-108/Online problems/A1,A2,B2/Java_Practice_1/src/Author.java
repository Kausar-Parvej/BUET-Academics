public class Author {
    private String name;
    private String email;

    Author(String name, String email) {
        setName(name);
        setEmail(email);
    }
	// write set and get methods
    public void setName(String nam){
        name=nam;
    }
    public void setEmail(String em){
        email=em;
    }

    public String getName(){
        return name;
    }
    public String getEmail(){
        return email;
    }
}
