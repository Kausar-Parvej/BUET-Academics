public class Book {
    String isbn;
    String name;
    Author author;
    double price;
    int quantity;

    public Book(String isbn, String name, Author author, double price, int quantity) {
        setIsbn(isbn);
        setName(name);
        setAuthor(author);
        setPrice(price);
        setQuantity(quantity);
    }
	
	// write set and get methods
    public void setIsbn(String isb){
        isbn=isb;
    }
    public void setName(String nam){
        name=nam;
    }
    public void setAuthor(Author ob){
        author=ob;
    }
    public void setPrice(double pr){
        price=pr;
    }
    public void setQuantity(int n){
        quantity=n;
    }


    public String getIsbn(){
        return isbn;
    }
    public String getName(){
        return name;
    }
    public double getPrice(){
        return price;
    }
    public int getQuantity(){
        return quantity;
    }
    public String getAuthorName(){
        return author.getName();
    }
    public Author getAuthor(){
        return author;
    }

	// write other methods to successfully run TestMain 
}
