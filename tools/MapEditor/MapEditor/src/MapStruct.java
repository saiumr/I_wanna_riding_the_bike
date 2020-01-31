package MapEditor.src;
import java.awt.*;
import java.util.*;

class MapStruct {
    public MapStruct(int col, int row){
        this.row = row;
        this.col = col;
        map = new Vector<>(row);
        for(int i=0;i<row;i++) {
            Vector<MapSheetImage> inner = new Vector<>();
            for(int j=0;j<col;j++)
                inner.addElement(null);
            map.addElement(inner);
        }
        System.out.println(map.size());
        System.out.println(map.get(0).size());
    }
    public void Clear(){
        for(int i=0;i<col;i++)
            for(int j=0;j<row;j++)
                this.SetImage(i, j, null);
    }
    public int GetRow(){
        return row;
    }
    public int GetCol(){
        return col;
    }
    public MapSheetImage GetImage(int col, int row){
        return map.get(row).get(col);
    }
    public void SetImage(int col, int row, MapSheetImage image){
        map.get(row).set(col, image);
    }
    public Dimension GetSize(){ return new Dimension(col, row); }

    private int row = 0;
    private int col = 0;
    private Vector<Vector<MapSheetImage>> map;
}
