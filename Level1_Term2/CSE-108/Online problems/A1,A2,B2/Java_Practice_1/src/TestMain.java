public class TestMain {
    public static void main(String[] args) {
        // Test Author class
        Author a = new Author("Herbert Schildt", "test@test.com");
        a.setEmail("herb@herbschildt.com");

        System.out.println("Author Name: " + a.getName());
        System.out.println("Author Email: " + a.getEmail());

        // Test Book class
        Book b = new Book("12345", "Java: The Complete Reference", a, 88.88, 90);
        b.setPrice(99.99);
        b.setQuantity(100);

        System.out.println("Book Isbn: " + b.getIsbn());
        System.out.println("Book Name: " + b.getName());
        System.out.println("Book Price: " + b.getPrice());
        System.out.println("Book Quantity: " + b.getQuantity());
        System.out.println("Book's Author Name: " + b.getAuthorName());
        System.out.println("Book's Author Email: " + b.getAuthor().getEmail());
    }
}

/* output
Author Name: Herbert Schildt
Author Email: herb@herbschildt.com
Book Isbn: 12345
Book Name: Java: The Complete Reference
Book Price: 99.99
Book Quantity: 100
Book's Author Name: Herbert Schildt
Book's Author Email: herb@herbschildt.com
*/