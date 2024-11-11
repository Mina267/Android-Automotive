import java.applet.Applet;
import java.awt.Button;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HelloApplet extends Applet {
    private Thread newThread;
    private int x;
    private Button incBtn;
    private Button deBtn;

    public void init() {
        incBtn = new Button("Increment");
        incBtn.addActionListener(e -> {
            x++;
            repaint();
        }
		
		);
        add(incBtn);

        deBtn = new Button("Decrement");
        deBtn.addActionListener( e -> {
            x--;
            repaint();
        }
		
		);
        add(deBtn);
    }

    public void paint(Graphics g) {
        g.drawString("Click Count is: " + x, getWidth() / 2 - 50, getHeight() / 2);
    }

   

   
}


