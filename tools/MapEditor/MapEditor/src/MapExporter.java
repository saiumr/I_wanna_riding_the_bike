package MapEditor.src;

import java.nio.file.Files;
import java.util.*;
import java.io.*;
import org.json.*;

public class MapExporter {
    public MapExporter(Vector<MapSheetStruct> mapsheetStructs, MapStruct mapStruct, String path){
        Export(mapsheetStructs, mapStruct, path);
    }

    public void Export(Vector<MapSheetStruct> mapSheetStructs, MapStruct mapStruct, String path){
        File file = new File(path);
        System.out.println("save to "+path);
        File exportDir = new File(file.getParent()+File.separator+file.getName().replaceAll("\\..*", ""));
        if(!exportDir.exists()) {
            System.out.println("create dir:"+exportDir.getPath());
            exportDir.mkdir();
        }
        exportMap2Json(mapSheetStructs, mapStruct, exportDir.getAbsolutePath(), file.getName());
        copyMapSheetResources(mapSheetStructs, exportDir.getAbsolutePath());
    }

    private void exportMap2Json(Vector<MapSheetStruct> mapSheetStructs, MapStruct mapStruct, String dirpath, String jsonFilename){
        String mapName = jsonFilename;
        JSONObject root = new JSONObject();
        //写入地图名称
        root.put("name", mapName);
        //写入地图需要的MapSheet文件名称
        JSONArray mapSheetArray = new JSONArray();
        for(int i=0;i<mapSheetStructs.size();i++) {
            MapSheetStruct struct = mapSheetStructs.get(i);
            mapSheetArray.put(new File(struct.GetJsonFilename()).getName());
        }
        root.put("MapSheetJsonFilename", mapSheetArray);
        //写入地图大小
        JSONObject mapsize = new JSONObject();
        mapsize.put("row", mapStruct.GetRow());
        mapsize.put("col", mapStruct.GetCol());
        root.put("map size", mapsize);
        //构建图像 名称-索引 的映射表
        Map<String, Integer> ImageName_Index = new HashMap<>();
        int count = 0;
        for(int i=0;i<mapSheetStructs.size();i++){
            Vector<MapSheetImage> images = mapSheetStructs.get(i).GetImages();
            for(int j=0;j<images.size();j++){
                MapSheetImage image = images.get(j);
                String imageAlias = image.GetOwnerFileName()+":"+image.GetName();
                ImageName_Index.put(imageAlias, count++);
            }
        }
        //将映射表写入
        JSONObject name_idx_maptable = new JSONObject();
        Set<String> keyset = ImageName_Index.keySet();
        for(Iterator<String> iter=keyset.iterator();iter.hasNext();){
            String name = iter.next();
            name_idx_maptable.put(name, ImageName_Index.get(name));
        }
        root.put("Name-Idx table" , name_idx_maptable);

        //将地图图块信息写入
        JSONArray mapinfo = new JSONArray();
        for(int i=0;i<mapStruct.GetRow();i++){
            for(int j=0;j<mapStruct.GetCol();j++){
                MapSheetImage image = mapStruct.GetImage(j, i);
                int idx = -1;
                if(image!=null) {
                    String imageAlias = image.GetOwnerFileName() + ":" + image.GetName();
                    idx = ImageName_Index.get(imageAlias);
                }
                mapinfo.put(idx);
            }
        }
        root.put("info", mapinfo);

        try {
            String exportPath = dirpath+File.separator+mapName;
            Writer writer = new FileWriter(new File(exportPath));
            writer.write(root.toString('\n'));
            writer.flush();
            writer.close();
            System.out.println("export to "+exportPath);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    private void copyMapSheetResources(Vector<MapSheetStruct> mapSheetStructs, String dirpath){
        for(int i=0;i<mapSheetStructs.size();i++){
            MapSheetStruct struct = mapSheetStructs.get(i);
            try {
                String jsonFilename = new File(struct.GetJsonFilename()).getName(),
                        totleImageFilename = new File(struct.GetTotleImageFilename()).getName();
                String jsonDst = dirpath+File.separator+jsonFilename,
                        totleImageDst = dirpath+File.separator+totleImageFilename;
                if(!new File(jsonDst).exists()){
                    System.out.println("copying <"+struct.GetJsonFilename()+"> to <"+jsonDst+">");
                    Files.copy(new File(struct.GetJsonFilename()).toPath(), new File(jsonDst).toPath());
                }
                if(!new File(totleImageDst).exists()) {
                    System.out.println("copying <" + struct.GetTotleImageFilename() + "> to <" + totleImageDst + ">");
                    Files.copy(new File(struct.GetTotleImageFilename()).toPath(), new File(totleImageDst).toPath());
                }
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }
}
