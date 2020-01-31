package MapEditor.src;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

class TopToolBar extends JToolBar {
    TopToolBar(){
        this.setFloatable(false);
        this.setOrientation(SwingConstants.HORIZONTAL);
        this.setBorderPainted(true);
        addButtons();
        this.setVisible(true);
    }

    public void AssociateCanva(Canva c){
        canva = c;
    }

    private void addButtons(){
        addGroupButtons1();
        this.addSeparator();
        addGroupButtons2();
    }

    private void addGroupButtons1(){
        bgrab.setPressedIcon(new ImageIcon("resources/toolbar_grab_pressed.png"));
        bgrab.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                canva.SetOperation(OperatorType.GRAB);
            }
        });
        bmouse.setPressedIcon(new ImageIcon("resources/toolbar_normal_pressed.png"));
        bmouse.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                canva.SetOperation(OperatorType.SELECT);
            }
        });
        beraser.setPressedIcon(new ImageIcon("resources/toolbar_eraser_pressed.png"));
        beraser.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                canva.SetOperation(OperatorType.ERASE);
            }
        });
        radiogroup.add(bgrab);
        radiogroup.add(bmouse);
        radiogroup.add(beraser);
        this.add(bgrab);
        this.add(bmouse);
        this.add(beraser);
    }

    private void addGroupButtons2(){
        JButton bbomb = new JButton(new ImageIcon("resources/toolbar_bomb.png"));
        bbomb.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                canva.GetMapStruct().Clear();
            }
            @Override
            public void mousePressed(MouseEvent e) {
            }
            @Override
            public void mouseReleased(MouseEvent e) {
            }
            @Override
            public void mouseEntered(MouseEvent e) {
            }
            @Override
            public void mouseExited(MouseEvent e) {
            }
        });
        this.add(bbomb);
    }

    private ButtonGroup radiogroup = new ButtonGroup();
    private JRadioButton bmouse = new JRadioButton(new ImageIcon("resources/toolbar_normal.png"), true);
    private JRadioButton bgrab = new JRadioButton(new ImageIcon("resources/toolbar_grab.png"), false);
    private JRadioButton beraser = new JRadioButton(new ImageIcon("resources/toolbar_eraser.png"), false);
    private Canva canva;
}
