package builders;

import shakeComponent.*;
import shakes.Shake;
import shakes.ShakeType;

public class ShakeBuilder implements Builder{
    private ShakeType shakeType;
    private MilkType milkType = MilkType.MILK;
    private SyrupType syrupType;
    private IceCreamType iceCreamType;
    private CoffeeType coffeeType;
    private SweetType sweetType = SweetType.SUGAR;
    private FlavorType flavorType;
    private JelloType jelloType;
    private int basePrice;
    private boolean hasCandy = false;
    private boolean hasCookies = false;


    @Override
    public void resetAll() {
        this.shakeType = null;
        this.milkType = MilkType.MILK;
        this.syrupType = null;
        this.iceCreamType = null;
        this.coffeeType = null;
        this.sweetType = SweetType.SUGAR;
        this.flavorType = null;
        this.jelloType = null;
        this.basePrice = 0;
        this.hasCandy = false;
        this.hasCookies = false;
    }
    @Override
    public void setShakeType(ShakeType shakeType) {
        this.shakeType = shakeType;
    }

    @Override
    public void setMilkType(MilkType milkType) {
        this.milkType = milkType;
    }

    @Override
    public void setSyrupType(SyrupType syrupType){
        this.syrupType = syrupType;
    }

    @Override
    public void setIceCreamType(IceCreamType iceCreamType) {
        this.iceCreamType = iceCreamType;
    }

    @Override
    public void setCoffeeType(CoffeeType coffeeType) {
        this.coffeeType = coffeeType;
    }


    @Override
    public void setSweetType(SweetType sweetType) {
        this.sweetType = sweetType;
    }

    @Override
    public void setFlavorType(FlavorType flavorType) {
        this.flavorType = flavorType;
    }

    @Override
    public void setJelloType(JelloType jelloType) {
        this.jelloType = jelloType;
    }

    @Override
    public void setBasePrice(int basePrice) {
        this.basePrice = basePrice;
    }


    @Override
    public void setHasCandy(boolean hasCandy) {
        this.hasCandy = hasCandy;
    }

    @Override
    public void setHasCookies(boolean hasCookies) {
        this.hasCookies = hasCookies;
    }

    public Shake getResult(){
        Shake temp = new Shake(shakeType, milkType, syrupType, iceCreamType, coffeeType, sweetType, flavorType, jelloType, basePrice, hasCandy, hasCookies );
        return temp;
    }
}
