package MapEditor.src;

import javax.swing.*;
import java.awt.*;

class MainWindow extends JFrame{
    static MainWindow CreateDefaultMainWindow(){
        return new MainWindow("", Canva.DefaultGridNum.width, Canva.DefaultGridNum.height);
    }
    static MainWindow CreateMainWindow(String projectPath, int gridCol, int gridRow){
        return new MainWindow(projectPath, gridCol, gridRow);
    }
    MainWindow(String projectPath, int gridCol, int gridRow){
        super();
        initWindow();
        GlobalFields.SetProjectPath(projectPath);
        canva = Canva.CreateCanva(gridCol, gridRow);
        panel.add(canva, BorderLayout.CENTER);
        panel.add(propertyPanel, BorderLayout.EAST);
        panel.add(topToolBar, BorderLayout.NORTH);
        LayerPropertyTab tab = new LayerPropertyTab();
        propertyPanel.add(tab);
        topToolBar.AssociateCanva(canva);
        MapSheetWindow mapSheetWindow = new MapSheetWindow();
        GlobalFields.AssociateLayerImagePanel(tab.GetImagePanel());
        MainMenu menu = new MainMenu();
        this.setJMenuBar(menu);
        menu.AssociateMapSheetWindow(mapSheetWindow);
        menu.AssociateCanva(canva);
        this.pack();
    }

    private void initWindow(){
        this.setSize(800, 600);
        this.setTitle("MapEditor");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(true);
        panel.setBackground(Color.GRAY);
        this.setContentPane(panel);
        this.setLocationRelativeTo(panel);
        this.setVisible(true);
    }

    private JPanel panel = new JPanel(new BorderLayout(), true);
    private Canva canva;
    private TopToolBar topToolBar = new TopToolBar();
    private PropertyPanel propertyPanel = new PropertyPanel();
}
