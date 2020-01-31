package MapEditor.src;

import java.awt.*;
import javax.swing.*;

class LayerPropertyTab extends JPanel{
    /**
     * 用于显示当前选择图块的面板
     */
    class ImagePanel extends JPanel{
        public ImagePanel(){
            this.setPreferredSize(new Dimension(190, 190));
            this.setBorder(BorderFactory.createTitledBorder("当前图块"));
            this.setLayout(new BorderLayout());
            this.add(label, BorderLayout.NORTH);
            this.label.setHorizontalAlignment(JLabel.CENTER);
            this.add(imageRegion, BorderLayout.CENTER);
            this.setVisible(true);
        }

        @Override
        public void paint(Graphics g){
            super.paint(g);
            imageRegion.repaint();
        }

        public void NotifyImage(){
            this.image = GlobalFields.GetSelectedImage().GetImage();
            this.label.setText(GlobalFields.GetSelectedImage().GetName());
            this.repaint();
        }
        private Image image = null;
        private JLabel label = new JLabel();
        private JPanel imageRegion = new JPanel(){
            @Override
            public void paint(Graphics g){
                super.paint(g);
                if(image!=null) {
                    final int padding = 25;
                    g.drawImage(image, padding, padding, this.getWidth()-padding*2, this.getHeight()-padding*2, this);
                }
            }
        };
    }

    public LayerPropertyTab(){
        super();
        this.setLayout(new BorderLayout());
        this.add(layerPanel, BorderLayout.NORTH);
        this.add(imagePanel, BorderLayout.SOUTH);
        this.setVisible(true);
    }

    private JPanel createLayerPanel(){
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createTitledBorder("选择图层"));
        panel.setLayout(new GridLayout(3, 1));
        JButton mapButton = new JButton("地图图层", new ImageIcon("resources/tab_map.png"));
        JButton actionButton = new JButton("行为图层", new ImageIcon("resources/tab_action.png"));
        JButton collisionButton = new JButton("碰撞图层", new ImageIcon("resources/tab_collision.png"));
        panel.add(mapButton);
        panel.add(collisionButton);
        panel.add(actionButton);
        panel.setVisible(true);
        return panel;
    }

    private ImagePanel createImagePanel(){
        return new ImagePanel();
    }

    public JPanel GetLayerPanel(){
        return layerPanel;
    }

    public ImagePanel GetImagePanel(){
        return imagePanel;
    }

    private JPanel layerPanel = createLayerPanel();
    private ImagePanel imagePanel = createImagePanel();
}
