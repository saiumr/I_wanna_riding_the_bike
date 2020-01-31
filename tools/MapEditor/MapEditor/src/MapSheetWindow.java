package MapEditor.src;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.*;
import java.io.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import javax.swing.*;
/**
 * 存储图像的结构体
 */
class MapSheetImage {
    MapSheetImage(String ownerName, String name, BufferedImage image, ImageInfo info){
        x = info.x;
        y = info.y;
        w = info.width;
        h = info.height;
        this.name = name;
        this.image = image.getSubimage(x, y, w, h);
        this.ownerName = ownerName;
    }
    public BufferedImage GetImage(){
        return image;
    }
    public Point GetPosition(){
        return new Point(x, y);
    }
    public Dimension GetSize(){
        return new Dimension(w, h);
    }
    public String GetName(){ return name; }
    public int GetX(){ return x; }
    public int GetY(){ return y; }
    public int GetWidth(){ return w; }
    public int GetHeight(){ return h; }
    public String GetOwnerFileName(){ return ownerName; }
    private int x = 0;
    private int y = 0;
    private int w = 0;
    private int h = 0;
    private BufferedImage image = null;
    private String name;
    private String ownerName;
}

/**
 * MapSheet的抽象数据类型
 */
class MapSheetStruct{
    MapSheetStruct(String jsonfilename, String totleImageFilename, Vector<MapSheetImage> images){
        this.jsonFilename = jsonfilename;
        this.images = images;
        this.totleImageFilename = totleImageFilename;
    }
    public Vector<MapSheetImage> GetImages(){
        return images;
    }
    public String GetJsonFilename(){
        return jsonFilename;
    }
    public String GetTotleImageFilename(){
        return totleImageFilename;
    }
    private String jsonFilename;
    private String totleImageFilename;
    private Vector<MapSheetImage> images;
}

class MapSheetWindow extends JFrame{
    /**
     * 每一份MapSheet对应的一份面板
     */
    class ImagePanel extends JPanel{

        public ImagePanel(MapSheetStruct struct){
            super();
            mapSheetInfo = struct;
            this.setVisible(true);
            //鼠标按下的事件处理
            this.addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {}

                @Override
                public void mousePressed(MouseEvent e) {
                    int i=0;
                    Vector<MapSheetImage> mapSheetImages = mapSheetInfo.GetImages();
                    for(i=0;i<mapSheetImages.size();i++){
                        MapSheetImage imageinfo = mapSheetImages.get(i);
                        if(Collision.PointInRect(e.getX(), e.getY(), imageinfo.GetX(), imageinfo.GetY(), imageinfo.GetWidth(), imageinfo.GetHeight())) {
                            currentSelectedImage = imageinfo;
                            break;
                        }
                    }
                    repaint();
                    GlobalFields.ChangeCurrentImage(currentSelectedImage);
                }

                @Override
                public void mouseReleased(MouseEvent e) {}
                @Override
                public void mouseEntered(MouseEvent e) {}
                @Override
                public void mouseExited(MouseEvent e) {}
            });
            //鼠标移动的事件处理
            this.addMouseMotionListener(new MouseMotionListener() {
                @Override
                public void mouseDragged(MouseEvent e) {}

                @Override
                public void mouseMoved(MouseEvent e) {
                    int i=0;
                    Vector<MapSheetImage> mapSheetImages = mapSheetInfo.GetImages();
                    for(i=0;i<mapSheetImages.size();i++){
                        MapSheetImage imageinfo = mapSheetImages.get(i);
                        if(Collision.PointInRect(e.getX(), e.getY(), imageinfo.GetX(),imageinfo.GetY(), imageinfo.GetWidth(), imageinfo.GetHeight())){
                            currentMovedOnImage = imageinfo;
                            setToolTipText(currentMovedOnImage.GetOwnerFileName()+"->"+currentMovedOnImage.GetName());
                            break;
                        }
                    }
                    if(i==mapSheetImages.size()) {
                        currentMovedOnImage = null;
                        setToolTipText("");
                    }
                    repaint();
                }
            });
        }

        @Override
        public void paint(Graphics g){
            super.paint(g);
            Vector<MapSheetImage> mapSheetImages = mapSheetInfo.GetImages();
            for(int i = 0; i< mapSheetImages.size(); i++){
                MapSheetImage image = mapSheetImages.get(i);
                g.drawImage(image.GetImage(), image.GetX(), image.GetY(), image.GetWidth(), image.GetHeight(), this);
            }
            if(currentSelectedImage!=null){
                g.setColor(Color.CYAN);
                g.drawRect(currentSelectedImage.GetX(), currentSelectedImage.GetY(), currentSelectedImage.GetWidth(), currentSelectedImage.GetHeight());;
            }
            if(currentMovedOnImage!=null){
                g.setColor(Color.GREEN);
                g.drawRect(currentMovedOnImage.GetX(), currentMovedOnImage.GetY(), currentMovedOnImage.GetWidth(), currentMovedOnImage.GetHeight());;
            }
        }

        public MapSheetStruct GetMapSheetStruct(){
            return mapSheetInfo;
        }

        private MapSheetStruct mapSheetInfo;
        private MapSheetImage currentSelectedImage = null;
        private MapSheetImage currentMovedOnImage = null;
    }//ImagePanel

    /**
     * 显示所有MapSheet的总面板
     */
    public MapSheetWindow(){
        super("MapSheets");
        this.setSize(200, 100);
        this.setLocation(0, 0);
        this.setMinimumSize(new Dimension(100, 100));
        this.setResizable(true);
        tabbedPane.setBackground(Color.GRAY);
        tabbedPane.setVisible(true);
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setContentPane(tabbedPane);
        Hide();
    }

    public void AddImageSheet(String jsonfilename, String imagename, Vector<ImageInfo> info){
        Vector<MapSheetImage> mapSheetImages = new Vector<>();
        BufferedImage bufferedImage = null;
        try {
            System.out.println(imagename);
            bufferedImage = ImageIO.read(new File(imagename));
        }catch(IOException e){
            e.printStackTrace();
        }
        for(int i=0;i<info.size();i++){
            ImageInfo instance = info.get(i);
            MapSheetImage image = new MapSheetImage(new File(jsonfilename).getName(), instance.name, bufferedImage, instance);
            mapSheetImages.add(image);
        }
        MapSheetStruct struct = new MapSheetStruct(jsonfilename, imagename, mapSheetImages);
        tabbedPane.addTab(new File(imagename).getName(), new ImagePanel(struct));
        GlobalFields.AddMapSheetStruct(new File(imagename).getName(), struct);
        this.repaint();
        this.Show();
    }

    public void Show(){
        this.setVisible(true);
    }

    public void Hide(){
        this.setVisible(false);
    }

    private JTabbedPane tabbedPane = new JTabbedPane();
}
