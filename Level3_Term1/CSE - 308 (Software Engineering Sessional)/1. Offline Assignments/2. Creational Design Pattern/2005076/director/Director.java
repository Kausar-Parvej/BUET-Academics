package director;

import builders.Builder;
import shakeComponent.*;
import shakes.ShakeType;

public class Director {
    private final int chocolateShakePrice = 230;
    private final int coffeeShakePrice = 250;
    private final int strawberryShakePrice = 200;
    private final int vanillaShakePrice = 190;
    private final int zeroShakePrice = 240;

    public void makeChocolateShake(Builder builder){
        builder.setShakeType(ShakeType.CHOCOLATE_SHAKE);
        builder.setSyrupType(SyrupType.CHOCOLATE_SYRUP);
        builder.setIceCreamType(IceCreamType.CHOCOLATE_ICECREAM);
        builder.setBasePrice(chocolateShakePrice);
    }

    public void makeCoffeeShake(Builder builder){
        builder.setShakeType(ShakeType.COFFEE_SHAKE);
        builder.setCoffeeType(CoffeeType.COFFEE);
        builder.setBasePrice(coffeeShakePrice);
    }

    public void makeStrawberryShake(Builder builder){
        builder.setShakeType(ShakeType.STRAWBERRY_SHAKE);
        builder.setSyrupType(SyrupType.STRAWBERRY_SYRUP);
        builder.setIceCreamType(IceCreamType.STRAWBERRY_ICECREAM);
        builder.setBasePrice(strawberryShakePrice);
    }

    public void makeVanillaShake(Builder builder){
        builder.setShakeType(ShakeType.VANILLA_SHAKE);
        builder.setFlavorType(FlavorType.VANILLA_FLAVORING);
        builder.setJelloType(JelloType.JELLO);
        builder.setBasePrice(vanillaShakePrice);
    }

    public void makeZeroShake(Builder builder){
        builder.setShakeType(ShakeType.ZERO_SHAKE);
        builder.setSweetType(SweetType.SWEETENER);
        builder.setFlavorType(FlavorType.VANILLA_FLAVORING);
        builder.setJelloType(JelloType.SUGAR_FREE_JELLO);
        builder.setBasePrice(zeroShakePrice);
    }
}
