package MapEditor.src;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.Border;

class PropertyPanel extends JPanel{
    public PropertyPanel(){
        this.setSize(GlobalFields.WindowSize.width/3, GlobalFields.WindowSize.height-100);
        this.setMinimumSize(new Dimension(200, GlobalFields.WindowSize.height-100));
        this.setPreferredSize(new Dimension(200, GlobalFields.WindowSize.height-100));
        Border border = BorderFactory.createLineBorder(Color.BLACK);
        this.setBorder(border);
        this.setLayout(new GridLayout(1, 1));
        this.setVisible(true);
    }

    public void SetPanel(JPanel panel){
        this.removeAll();
        this.add(panel);
    }
}
