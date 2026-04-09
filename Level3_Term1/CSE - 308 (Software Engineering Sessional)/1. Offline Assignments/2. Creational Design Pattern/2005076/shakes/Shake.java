package shakes;

import shakeComponent.*;

public class Shake {
    private final ShakeType shakeType;
    private final MilkType milkType;
    private final SyrupType syrupType;
    private final IceCreamType iceCreamType;
    private final CoffeeType coffeeType;
    private final SweetType sweetType;
    private final FlavorType flavorTye;
    private final JelloType jelloType;
    private final int basePrice;
    private final boolean hasCandy;
    private final boolean hasCookies;

    public Shake(ShakeType shakeType, MilkType milkType, SyrupType syrupType, IceCreamType iceCreamType, CoffeeType coffeeType, SweetType sweetType, FlavorType flavorTye, JelloType jelloType, int basePrice, boolean hasCandy, boolean hasCookies) {
        this.shakeType = shakeType;
        this.milkType = milkType;
        this.syrupType = syrupType;
        this.iceCreamType = iceCreamType;
        this.coffeeType = coffeeType;
        this.sweetType = sweetType;
        this.flavorTye = flavorTye;
        this.jelloType = jelloType;
        this.basePrice = basePrice;
        this.hasCandy = hasCandy;
        this.hasCookies = hasCookies;
    }

    public ShakeType getShakeType() {
        return shakeType;
    }

    public MilkType getMilkType() {
        return milkType;
    }

    public SyrupType getSyrupType() {
        return syrupType;
    }

    public IceCreamType getIceCreamType() {
        return iceCreamType;
    }

    public CoffeeType getCoffeeType() {
        return coffeeType;
    }

    public SweetType getSweetType() {
        return sweetType;
    }

    public FlavorType getFlavorTye() {
        return flavorTye;
    }

    public JelloType getJelloType() {
        return jelloType;
    }

    public boolean isHasCandy() {
        return hasCandy;
    }

    public boolean isHasCookies() {
        return hasCookies;
    }

    public int getShakePrice() {
        int price = this.basePrice;
        if(this.milkType == MilkType.ALMOND_MILK){
            price += 60;
        }
        if(this.hasCandy){
            price += 50;
        }
        if(this.hasCookies){
            price += 40;
        }

        return price;
    }

    public void print(){
        System.out.println("\n--------------------------------------------");
        System.out.println(shakeType.name());
        System.out.print("Ingredients: " + milkType.name() + ", " + sweetType.name());
        if(syrupType != null) System.out.print(", " + syrupType.name());
        if(iceCreamType != null) System.out.print(", " + iceCreamType.name());
        if(coffeeType != null) System.out.print(", " + coffeeType.name());
        if(flavorTye != null) System.out.print(", " + flavorTye.name());
        if(hasCandy) System.out.print(", CANDY");
        if(hasCookies) System.out.print(", COOKIES");

        System.out.println("\nPrice: " + getShakePrice());
        if(milkType == MilkType.ALMOND_MILK) System.out.println("\t--> 60tk increased for Almond Milk");
        if(hasCandy) System.out.println("\t--> 50tk increased for adding candy");
        if(hasCookies) System.out.println("\t--> 40tk increased for adding cookies");


    }

}
