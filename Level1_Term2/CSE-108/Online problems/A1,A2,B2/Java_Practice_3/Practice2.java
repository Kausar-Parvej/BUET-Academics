class Animal {
    private String name;
    private int age;

    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
    }
	
    public boolean isLethalToAdultHumans() {
        return false;
    }
	
	// your code 
} 

// your code

class TestAnimal {
    public static void main(String[] args) {
        Bird alex = new Albatross("Alex", 39);
        Mammal spot = new Dog("Spot", 7);
        Mammal fred = new FruitBat("Fred", 10);
        Reptile steph = new EasternBrownSnake("Steph", 12);
        Fish bruce = new GreatWhiteShark("Bruce", 40);
        Arachnid charlotte = new RedBackSpider("Charlotte", 1);
        Mammal perry = new Platypus("Perry", 5);
        Mammal bob = new Human("Bob", 20);

        Animal[] animals = {alex, spot, fred, steph, bruce, charlotte, perry, bob};
        for (Animal a : animals) {
            System.out.print(a.getInfo());
            if (a instanceof Mammal) {
                ((Mammal) a).printBloodType();
            }
            System.out.println(a.isLethalToAdultHumans() ? ", it's lethal!" : ", fortunately non-lethal");
        }
    }
}

/* main output
Alexis a Albatross, aged 39, fortunately non-lethal
Spotis a Dog, aged 7, Warm-Blooded!, fortunately non-lethal
Fredis a FruitBat, aged 10, Warm-Blooded!, fortunately non-lethal
Stephis a EasternBrownSnake, aged 12, it's lethal!
Bruceis a GreatWhiteShark, aged 40, fortunately non-lethal
Charlotteis a RedBackSpider, aged 1, it's lethal!
Perryis a Platypus, aged 5, Warm-Blooded!, fortunately non-lethal
Bobis a Human, aged 20, Warm-Blooded!, fortunately non-lethal
*/