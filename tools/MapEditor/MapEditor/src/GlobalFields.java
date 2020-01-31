package MapEditor.src;

import java.util.*;
import java.awt.*;

class GlobalFields {
    static public Dimension WindowSize = new Dimension(800, 600);
    static private MapSheetImage currentImage = null;
    static private LayerPropertyTab.ImagePanel listener = null;
    static public MapSheetImage GetSelectedImage(){
        return currentImage;
    }
    static public void AssociateLayerImagePanel(LayerPropertyTab.ImagePanel panel){
        listener = panel;
    }
    static public void SetProjectPath(String path){ projectPath = path; }
    static public String GetProjectPath(){ return projectPath; }
    static public void AddMapSheetStruct(String name, MapSheetStruct struct){
        mapSheetStructMap.put(name, struct);
    }
    static public MapSheetStruct GetMapSheetStruct(String name){
        if(mapSheetStructMap.containsKey(name))
            return mapSheetStructMap.get(name);
        return null;
    }
    static public Vector<MapSheetStruct> GetMapSheetStructs(){
        Set<String> keyset = mapSheetStructMap.keySet();
        Vector<MapSheetStruct> structs = new Vector<>();
        for(Iterator<String> iter=keyset.iterator();iter.hasNext();){
            structs.add(mapSheetStructMap.get(iter.next()));
        }
        return structs;
    }
    static private String projectPath = "";
    static private Map<String, MapSheetStruct> mapSheetStructMap = new HashMap<>();
    static public void ChangeCurrentImage(MapSheetImage image){
        currentImage = image;
        listener.NotifyImage();
    }
}
