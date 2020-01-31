package MapEditor.src;

import javax.swing.*;


public class MapEditor extends JFrame{
    public static void main(String[] args) {
        mainWindow = MainWindow.CreateDefaultMainWindow();
    }

    public static void CreateNewMapProject(String projectPath, int gridCol, int gridRow){
        if(mainWindow!=null)
            mainWindow.dispose();
        mainWindow = MainWindow.CreateMainWindow(projectPath, gridCol, gridRow);
    }

    static private MainWindow mainWindow;
}