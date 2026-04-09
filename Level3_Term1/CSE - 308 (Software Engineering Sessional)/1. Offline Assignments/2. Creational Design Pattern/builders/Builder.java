package builders;

import shakes.*;
import shakeComponent.*;

public interface Builder {
    void setShakeType(ShakeType shakeType);
    void setMilkType(MilkType milkType);
    void setSyrupType(SyrupType syrupType);
    void setIceCreamType(IceCreamType iceCreamType);
    void setCoffeeType(CoffeeType coffeeType);
    void setSweetType(SweetType sweetType);
    void setFlavorType(FlavorType flavorType);
    void setJelloType(JelloType jelloType);
    void setBasePrice(int basePrice);
    void resetAll();
    void setHasCandy(boolean hasCandy);
    void setHasCookies(boolean hasCookies);
}
