package MapEditor.src;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

enum OperatorType{
    SELECT,
    GRAB,
    ERASE
}

class Canva extends JPanel implements MouseListener {
    static Canva CreateCanva(int gridColNum, int gridRowNum){
        return new Canva(gridColNum, gridRowNum);
    }
    Canva(int gridColNum, int gridRowNum){
        super();
        this.mapStruct = new MapStruct(gridColNum, gridRowNum);
        this.setBackground(Color.LIGHT_GRAY);
        this.setMinimumSize(new Dimension(100, 100));
        this.setSize(GlobalFields.WindowSize.width/3*2, GlobalFields.WindowSize.height-100);
        this.setPreferredSize(new Dimension(GlobalFields.WindowSize.width/3*2, GlobalFields.WindowSize.height-100));
        this.setVisible(true);
        this.addMouseListener(this);
        this.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if(optype==OperatorType.GRAB && mouseButton==MouseEvent.BUTTON1){
                    Point delta = new Point(new Double(e.getX()-oldMousePos.getX()).intValue(), new Double(e.getY()-oldMousePos.getY()).intValue());
                    position.x += delta.x;
                    position.y += delta.y;
                    repaint();
                }
                if(optype==OperatorType.SELECT && mouseButton==MouseEvent.BUTTON1 && e.isControlDown()){
                    Point grididx = GetMouseColliedGrid(e.getX(), e.getY());
                    SetGridImage(grididx.x, grididx.y, GlobalFields.GetSelectedImage());
                    repaint();
                }
                if(optype==OperatorType.ERASE && mouseButton==MouseEvent.BUTTON1 && e.isControlDown()){
                    Point grididx = GetMouseColliedGrid(e.getX(), e.getY());
                    SetGridImage(grididx.x, grididx.y, null);
                    repaint();
                }
                oldMousePos.x = e.getX();
                oldMousePos.y = e.getY();
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                oldMousePos.x = e.getX();
                oldMousePos.y = e.getY();
                holvedGridPos = GetMouseColliedGrid(e.getX(), e.getY());
                repaint();
            }
        });
        this.addMouseWheelListener(new MouseWheelListener() {
            @Override
            public void mouseWheelMoved(MouseWheelEvent e) {
                final int deltasize = 2;
                if(gridsize.width+e.getWheelRotation()*deltasize>DefaultMinGridSize.width)
                    gridsize.width += e.getWheelRotation()*deltasize;
                else
                    gridsize.width = DefaultMinGridSize.width;
                if(gridsize.height+e.getWheelRotation()*deltasize>DefaultMinGridSize.height)
                    gridsize.height += e.getWheelRotation()*deltasize;
                else
                    gridsize.height = DefaultMinGridSize.height;
                repaint();
            }
        });
    }

    @Override
    public void mouseClicked(MouseEvent e){}
    @Override
    public void mouseEntered(MouseEvent e){}
    @Override
    public void mouseExited(MouseEvent e){}
    @Override
    public void mousePressed(MouseEvent e){
        mouseButton = e.getButton();
        if(optype==OperatorType.SELECT && GlobalFields.GetSelectedImage()!=null){
            Point grididx = GetMouseColliedGrid(e.getX(), e.getY());
            SetGridImage(grididx.x, grididx.y, GlobalFields.GetSelectedImage());
            repaint();
        }
        if(optype==OperatorType.ERASE){
            Point grididx = GetMouseColliedGrid(e.getX(), e.getY());
            SetGridImage(grididx.x, grididx.y, null);
            repaint();
        }
    }

    @Override
    public void mouseReleased(MouseEvent e){
        mouseButton = MouseEvent.NOBUTTON;
    }

    @Override
    public void paint(Graphics g){
        super.paint(g);
        DrawMapImages(g);
        if(optype==OperatorType.SELECT)
            DrawPrevGridImage(g);
        DrawGrid(g);
    }

    public void SetGridImage(int col, int row, MapSheetImage image){
        if(col>=0 && row>=0)
            mapStruct.SetImage(col, row, image);
    }

    private void DrawPrevGridImage(Graphics g){
        if(holvedGridPos.x>=0 && holvedGridPos.y>=0 && GlobalFields.GetSelectedImage()!=null){
            Point maptl = GetMapPosition();
            g.drawImage(GlobalFields.GetSelectedImage().GetImage(), maptl.x+holvedGridPos.x*gridsize.width, maptl.y+holvedGridPos.y*gridsize.height, gridsize.width, gridsize.height, this);
        }
    }

    private void DrawMapImages(Graphics g){
        for(int i = 0; i< mapStruct.GetCol(); i++){
            for(int j = 0; j< mapStruct.GetRow(); j++){
                MapSheetImage image = mapStruct.GetImage(i, j);
                if(image!=null) {
                    Point maptl = GetMapPosition();
                    g.drawImage(image.GetImage(), maptl.x+i*gridsize.width, maptl.y+j*gridsize.height, gridsize.width, gridsize.height, this);
                }
            }
        }
    }

    private void DrawGrid(Graphics g){
        Dimension size = this.getSize();
        Dimension gridnum = mapStruct.GetSize();
        Dimension mapsize = new Dimension(gridsize.width*gridnum.width, gridsize.height*gridnum.height);
        padding.width = (size.width-mapsize.width)/2;
        padding.height = (size.height-mapsize.height)/2;
        g.setColor(Color.BLACK);
        for(int i=0;i<=gridnum.width;i++) {
            Point maptl = GetMapPosition();
            g.drawLine(maptl.x+i*gridsize.width, maptl.y,
                       maptl.x+i*gridsize.width,maptl.y+mapsize.height);
        }
        for(int i=0;i<=gridnum.height;i++) {
            g.drawLine(position.x+padding.width, position.y+padding.height+i*gridsize.height,
                    position.x+padding.width+mapsize.width, position.y+padding.height+i*gridsize.height);
        }
    }

    private Point GetMapPosition(){
        return new Point(position.x+padding.width, position.y+padding.height);
    }

    private Point GetMouseColliedGrid(int mx, int my){
        Dimension gridNum = mapStruct.GetSize();
        int i=0, j=0;
        for(i=0;i<gridNum.width;i++){
            for(j=0;j<gridNum.height;j++){
                Point maptl = GetMapPosition();
                Rectangle gridrect = new Rectangle(maptl.x+i*gridsize.width, maptl.y+j*gridsize.height, gridsize.width, gridsize.height);
                if(Collision.PointInRect(mx, my, gridrect.x, gridrect.y, gridrect.width, gridrect.height)){
                    return new Point(i, j);
                }
            }
        }
        return new Point(-1, -1);
    }

    public void SetOperation(OperatorType type){
        optype = type;
        switch(optype){
            case SELECT:
                this.setCursor(Cursor.getDefaultCursor());
                break;
            case GRAB:
                this.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                break;
            case ERASE:
                this.setCursor(getToolkit().createCustomCursor(new ImageIcon("resources/cursor_eraser.png").getImage(), new Point(0, 21), "eraser"));
                break;
            default:
                this.setCursor(Cursor.getDefaultCursor());
                break;
        }
    }

    public void ResetPosition(){
        position.x = 0;
        position.y = 0;
        repaint();
    }

    public MapStruct GetMapStruct(){
        return this.mapStruct;
    }

    private Dimension gridsize = DefaultGridSize;
    private Dimension padding = new Dimension();
    private Point position = new Point(0, 0);
    private Point oldMousePos = new Point(0, 0);
    private int mouseButton = MouseEvent.NOBUTTON;
    private OperatorType optype = OperatorType.SELECT;
    private MapStruct mapStruct;
    private Point holvedGridPos = new Point(-1, -1);

    public static Dimension DefaultGridNum = new Dimension(20, 20);
    public static Dimension DefaultGridSize = new Dimension(40, 40);
    public static Dimension DefaultMinGridSize = new Dimension(5,5);
}
