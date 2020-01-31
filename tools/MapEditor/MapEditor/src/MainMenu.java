package MapEditor.src;

import jdk.nashorn.internal.objects.Global;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.text.NumberFormat;

/**
 * 按下"新建地图"时打开的对话框
 */
class NewMapDialog extends JDialog{
    public NewMapDialog(Component parent){
        super();
        this.setSize(400, 300);
        this.setResizable(false);
        this.setLocationRelativeTo(parent);
        JPanel panel = new JPanel();
        this.setContentPane(panel);
        panel.setLayout(new BorderLayout());
        panel.add(createSavePathPanel(), BorderLayout.NORTH);
        panel.add(createMapSizePanel(), BorderLayout.CENTER);
        panel.add(createButtonPanel(), BorderLayout.SOUTH);
        Show();
    }

    private JPanel createSavePathPanel(){
        JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(400, 100));
        panel.setLayout(new BorderLayout());
        panel.add(new JLabel("保存到:"), BorderLayout.NORTH);

        JPanel savePanel = new JPanel();
        GridBagLayout gblayout = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();

        JTextField pathFiled = new JTextField(25);
        c.gridwidth = 9;
        gblayout.setConstraints(pathFiled, c);

        JButton saveButton = new JButton("浏览...");
        saveButton.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                JFileChooser fileChooser = null;
                if(pathFiled.getText()==""){
                    fileChooser = new JFileChooser();
                }else{
                    File file = new File(pathFiled.getText());
                    if(file.exists())
                        fileChooser = new JFileChooser(pathFiled.getText());
                    else
                        fileChooser = new JFileChooser();
                }
                fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                fileChooser.showSaveDialog(savePanel);
                projectPath = fileChooser.getSelectedFile().getPath();
                pathFiled.setText(projectPath);
            }
            @Override
            public void mousePressed(MouseEvent e) { }
            @Override
            public void mouseReleased(MouseEvent e) { }
            @Override
            public void mouseEntered(MouseEvent e) { }
            @Override
            public void mouseExited(MouseEvent e) { }
        });
        c.gridwidth = GridBagConstraints.REMAINDER;
        gblayout.setConstraints(saveButton, c);

        savePanel.add(pathFiled);
        savePanel.add(saveButton);
        savePanel.setLayout(gblayout);
        panel.add(savePanel, BorderLayout.CENTER);
        return panel;
    }

    private JPanel createMapSizePanel(){
        JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(400, 100));
        panel.setLayout(new BorderLayout());
        panel.add(new Label("地图大小:"), BorderLayout.NORTH);
        JPanel sizepanel = new JPanel();
        GridBagLayout gblayout = new GridBagLayout();
        sizepanel.setLayout(gblayout);
        GridBagConstraints c = new GridBagConstraints();

        JLabel widthlabel = new JLabel("宽:");
        widthlabel.setHorizontalAlignment(JLabel.CENTER);
        widthlabel.setVerticalAlignment(JLabel.CENTER);
        c.gridwidth = 1;
        gblayout.setConstraints(widthlabel, c);

        JFormattedTextField widthField = new JFormattedTextField(NumberFormat.getIntegerInstance());
        widthField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {}
            @Override
            public void focusLost(FocusEvent e) {
                gridCol = Integer.parseInt(widthField.getText());
            }
        });
        widthField.setText("20");
        widthField.setColumns(10);
        c.gridwidth = 4;
        gblayout.setConstraints(widthField, c);

        JLabel heightlabel = new JLabel("高:");
        heightlabel.setHorizontalAlignment(JLabel.CENTER);
        heightlabel.setVerticalAlignment(JLabel.CENTER);
        c.gridwidth = 1;
        gblayout.setConstraints(heightlabel, c);

        JFormattedTextField heightField = new JFormattedTextField(NumberFormat.getIntegerInstance());
        heightField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {}

            @Override
            public void focusLost(FocusEvent e) {
                gridRow = Integer.parseInt(heightField.getText());
            }
        });
        heightField.setText("20");
        heightField.setColumns(10);
        c.gridwidth = 4;
        gblayout.setConstraints(heightField, c);

        sizepanel.add(widthlabel);
        sizepanel.add(widthField);
        sizepanel.add(heightlabel);
        sizepanel.add(heightField);
        panel.add(sizepanel);
        return panel;
    }

    private JPanel createButtonPanel(){
        JPanel panel = new JPanel();
        panel.setPreferredSize(new Dimension(400, 50));
        JButton cancelButton = new JButton("取消"),
                okButton = new JButton("确定");
        cancelButton.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                dispose();
            }
            @Override
            public void mousePressed(MouseEvent e) {}
            @Override
            public void mouseReleased(MouseEvent e) {}
            @Override
            public void mouseEntered(MouseEvent e) {}
            @Override
            public void mouseExited(MouseEvent e) {}
        });
        okButton.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                MapEditor.CreateNewMapProject(projectPath, gridCol, gridRow);
                dispose();
            }
            @Override
            public void mousePressed(MouseEvent e) { }
            @Override
            public void mouseReleased(MouseEvent e) { }
            @Override
            public void mouseEntered(MouseEvent e) { }
            @Override
            public void mouseExited(MouseEvent e) { }
        });
        panel.add(cancelButton, BorderLayout.EAST);
        panel.add(okButton, BorderLayout.WEST);
        return panel;
    }

    public void Show(){
        this.setVisible(true);
    }

    private String projectPath = "";
    private int gridCol = Canva.DefaultGridNum.width;
    private int gridRow = Canva.DefaultGridNum.height;
}

/**
 * 主菜单
 */
class MainMenu extends JMenuBar{
    MainMenu(){
        super();
        this.add(createFileMenu());
        this.add(createWindowMenuInit());
    }

    private JMenu createFileMenu(){
        JMenu file_menu = new JMenu("文件");
        JMenuItem newmapItem = new JMenuItem("新建地图"),
                openmapItem = new JMenuItem("打开地图"),
                savemapItem = new JMenuItem("保存地图"),
                saveasItem = new JMenuItem("地图另存为"),
                loadimagesheetor = new JMenuItem("载入ImageSheet");
        file_menu.add(newmapItem);
        file_menu.add(openmapItem);
        file_menu.addSeparator();
        file_menu.add(savemapItem);
        file_menu.add(saveasItem);
        file_menu.addSeparator();
        file_menu.add(loadimagesheetor);
        newmapItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new NewMapDialog(MainMenu.this);
            }
        });
        savemapItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(GlobalFields.GetProjectPath()=="") {
                    JFileChooser saveChooser = new JFileChooser();
                    saveChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                    saveChooser.showSaveDialog(MainMenu.this);
                    File file = saveChooser.getSelectedFile();
                    if (file != null) {
                        String savePath = file.getAbsolutePath();
                        MapExporter exporter = new MapExporter(GlobalFields.GetMapSheetStructs(), canva.GetMapStruct(), savePath);
                        GlobalFields.SetProjectPath(savePath);
                    }
                }else {
                    MapExporter exporter = new MapExporter(GlobalFields.GetMapSheetStructs(), canva.GetMapStruct(), GlobalFields.GetProjectPath());
                }
            }
        });
        saveasItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser saveChooser = new JFileChooser();
                saveChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                saveChooser.showSaveDialog(MainMenu.this);
                File file = saveChooser.getSelectedFile();
                if (file != null) {
                    String savePath = file.getAbsolutePath();
                    MapExporter exporter = new MapExporter(GlobalFields.GetMapSheetStructs(), canva.GetMapStruct(), savePath);
                    GlobalFields.SetProjectPath(savePath);
                }
            }
        });
        loadimagesheetor.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser(".");
                fileChooser.setFileFilter(new FileNameExtensionFilter("ImageSheetor File(*.json)", "json"));
                fileChooser.showOpenDialog(null);
                File choosedFile = fileChooser.getSelectedFile();
                if(choosedFile!=null) {
                    ImageSheetorParser parser = new ImageSheetorParser(choosedFile.getPath());
                    mapSheetWindow.AddImageSheet(parser.GetJsonFileName(),choosedFile.getParent() + File.separator + parser.GetImageFileName(), parser.GetImageInfo());
                    System.out.println(parser.GetJsonFileName());
                }
            }
        });
        return file_menu;
    }

    private JMenu createWindowMenuInit(){
        JMenu window_menu = new JMenu("窗口");
        JMenuItem showMapSheetWindow = new JMenuItem("显示MapSheet窗口"),
                  mapCenter = new JMenuItem("地图居中");
        showMapSheetWindow.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                mapSheetWindow.Show();
            }
        });
        mapCenter.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canva.ResetPosition();
            }
        });
        window_menu.add(showMapSheetWindow);
        window_menu.addSeparator();
        window_menu.add(mapCenter);
        return window_menu;
    }

    public void AssociateMapSheetWindow(MapSheetWindow window){
        mapSheetWindow = window;
    }
    public void AssociateCanva(Canva canva){ this.canva = canva; }

    private MapSheetWindow mapSheetWindow;
    private Canva canva;
}
