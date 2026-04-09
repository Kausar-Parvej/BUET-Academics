/************Topics of Practice*************************/
/* => Dynamic Allocation of objects         		   */
/* => Constructor overloading		        		   */
/* => Copy constructor				        		   */
/* => Passing and returning objects from functions     */
/*******************************************************/

#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class Book{
	int isbn;
	char* title;
	int price;
	public:
		//Constructor functions
		Book(){//default constructor
		    cout<<"In the default constructor of Book"<<endl;
			//Write your code here
			isbn=-1;
			price=0;
			char s[]="No Title";
			title=new char[strlen(s)+1];
			strcpy(title,s);
		}

		Book(int isbn, char* title, int price){//constructor with arguments
			cout<<"In the parameterized constructor of Book "<<isbn<<endl;
			//Write your code here
			this->isbn=isbn;
			this->price=price;
			this->title=new char[strlen(title)+1];
			strcpy(this->title,title);

		}
		Book(const Book &book){//Copy constructor
		    cout<<"In the copy constructor of Book "<<isbn<<endl;
			//Write your code here
			isbn=book.isbn;
			price=book.price;
			title=new char[strlen(book.title)+1];
			strcpy(title,book.title);
		}

		//Destructor function
		~Book(){
		    cout<<"In the destructor of Book "<<isbn<<endl;
			//Write your code here
			delete[] title;
		}

		//Write the setter functions here
        void setter(int i, char *s, int p)
        {
            isbn=i;
            title=new char[strlen(s)+1];
			strcpy(title,s);
            price=p;
        }

        void setter(char *s)
        {
            title=new char[strlen(s)+1];
			strcpy(title,s);
        }

        void setter(int i)
        {
            isbn=i;
        }

		//Write the getter functions here
		int get_isbn()
		{
		    return isbn;
		}
		char* get_title()
		{
		    return title;
		}
		int get_price()
		{
		    return price;
		}

		//Service functions
		void print(){
			//Write your code here
			 cout<<endl;
			 cout<<"title: "<<title<<", isbn: "<<isbn<<", price: "<<price<<endl;
			 cout<<endl;
		}

		int isTheSameBook(Book b){
			//Write your code here
			return isbn==b.isbn? 1:0;
		}

		Book generateNewEdition(int isbn, int price){
			//Write your code here
			Book temp;
			temp.isbn=isbn;
			temp.price=price;
			temp.title=new char[strlen(this->title)+1];
			strcpy(temp.title, this->title);
			return temp;
		}
};

int main(){
	//To do: Create a book object named b1 with the default constructor
	Book b1;

	//To do: Set the properties of b1 as follows: isbn=101, title="Teach yourself C++", price=230
    b1.setter(101,"Teach yourself C++", 230);

	//To do: Print the details of b1
	b1.print();

	//To do: Create a book object named b2 with values initialized as- isbn=102, title="Teach Yourself Java", price=235
    Book b2(102, "Teach Yourself Java", 235);

	//To do: Crate a book object b3 and initialize with b2
	Book b3(102, "Teach Yourself Java", 235);

	//To do: Check if b2 and b3 represent the same book. Print "Yes" or "No" based on the check result.

	//To do: Change the title of b3 to "Teach Yourself Java in Thirty Days"
    b3.setter("Teach Yourself Java in Thirty Days");

	//To do: Change the isbn of b3 to 103
	b3.setter(103);

	//To do: Print the details of book b2 and b3
	b2.print();
	b3.print();

	//To do: Create a book b4 as a new edition of b3. Set the isbn and price of the new edition to 104 and 600, respectively
	Book b4;
	b4=b3.generateNewEdition(104, 600);

	//To do: Print the details of b4
	b4.print();

	//To do: Create a Book pointer named bp1
	Book *bp1;

	//To do: Allocate a Book object to bp1 initialized as- isbn=104, title="C++ For Dummies", price=400
    bp1=new Book(104, "C++ For Dummies", 400);

	//To do: Print the details of the book pointed by bp1
	bp1->print();

	//To do: Free the memory allocated to bp1
	delete bp1;

	//To do: Create a Book pointer named bl1 and allocate three book objects to it without any initialization
	Book *bl1;
	bl1=new Book[3];

	//To do: Set the properties of the three book objects pointed to by bl1 as follows:
	// <isbn=201, title=Compilers, price=340>,
	// <isbn=202, title=Operating Systems, price=450>,
	// <isbn=203, title=Data Communications, price=600>
	bl1[0].setter(201, "Compilers", 340);
    bl1[1].setter(202, "Operating Systems", 450);
    bl1[2].setter(203, "Data Communications", 600);

	//To do: Print the details of all the three books pointed to by bl1
    bl1[0].print();
    bl1[1].print();
    bl1[2].print();

	//To do: Free the memory allocated to bl1
	delete[] bl1;

	return 0;
}
