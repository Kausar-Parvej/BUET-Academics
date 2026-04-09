package my_util;


import java.io.Serializable;
import java.util.HashMap;

public class SendResources implements Serializable {
    private final HashMap<String, String> imageLinkMap;

    public SendResources(HashMap<String, String> map){
        this.imageLinkMap = map;
    }

    public HashMap<String, String> getImageLinkMap() {
        return imageLinkMap;
    }
}
