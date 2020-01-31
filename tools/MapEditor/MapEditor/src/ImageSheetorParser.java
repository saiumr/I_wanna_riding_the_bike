package MapEditor.src;
import java.io.*;
import java.util.*;

import org.json.*;

class ImageInfo{
    public ImageInfo(String name, int x, int y, int w, int h){
        this.name = name;
        this.x = x;
        this.y = y;
        this.width = w;
        this.height = h;
    }
    public String name;
    public int x;
    public int y;
    public int width;
    public int height;
}

class ImageSheetorParser {
    public ImageSheetorParser(String filename){
        Parse(filename);
    }

    String ReadJsonFile(String filename){
        StringBuilder source = new StringBuilder();
        File file = new File(filename);
        try {
            InputStreamReader isreader = new InputStreamReader(new FileInputStream(file));
            BufferedReader breader = new BufferedReader(isreader);
            String line = breader.readLine();
            while(line!=null){
                source.append(line);
                source.append("\n");
                line = breader.readLine();
            }
        }catch(FileNotFoundException e) {
            e.printStackTrace();
        }catch(IOException e){
            e.printStackTrace();
        }
        return source.toString();
    }

    void Parse(String filename){
        jsonFilename = filename;
        String source = ReadJsonFile(filename);
        JSONObject root = new JSONObject(source);
        if(root.has("image_path")){
            image_filename = root.getString("image_path");
        }else{
            isvalid = false;
            System.out.println("image "+filename+" is not found");
        }
        JSONArray array = root.getJSONArray("images");
        for(int i=0;i<array.length();i++){
            JSONObject image_info = array.getJSONObject(i);
            String name = null;
            if(image_info.has("name"))
                name = image_info.getString("name");
            else{
                isvalid = false;
                System.out.println("image has no name");
            }
            int x = -1, y = -1, w = -1, h = -1;
            if(image_info.has("rect")){
                JSONObject rect = image_info.getJSONObject("rect");
                if(rect.has("x") && rect.has("y") && rect.has("width") && rect.has("height")){
                    x = rect.getInt("x");
                    y = rect.getInt("y");
                    w = rect.getInt("width");
                    h = rect.getInt("height");
                }else{
                    isvalid = false;
                    System.out.println("image don't have rect");
                }
            }else{
                isvalid = false;
                System.out.println("image has no react");
            }
            ImageInfo info = new ImageInfo(name, x, y, w, h);
            images.add(info);
        }
    }

    @Override
    public String toString(){
        StringBuilder str = new StringBuilder();
        if(Valid()) {
            str.append("image path:"+image_filename+"\n");
            for(int i=0;i<images.size();i++) {
                ImageInfo info = images.get(i);
                str.append(info.name+":\t");
                str.append("x:");
                str.append(info.x);
                str.append(" ");
                str.append("y:");
                str.append(info.y);
                str.append(" ");
                str.append("width:");
                str.append(info.width);
                str.append(" ");
                str.append("height:");
                str.append(info.height);
                str.append("\n");
            }
        }else
            str.append("MapSheetImage Json Invalid");
        return str.toString();
    }

    String GetJsonFileName() { return jsonFilename; }

    String GetImageFileName(){
        return image_filename;
    }

    Vector<ImageInfo> GetImageInfo(){
        return images;
    }

    boolean Valid(){
        return isvalid;
    }

    String image_filename = null;
    String jsonFilename = null;
    Vector<ImageInfo> images = new Vector<>();
    boolean isvalid = true;
}
