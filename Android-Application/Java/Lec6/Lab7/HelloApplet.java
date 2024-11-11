import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;
import java.util.ArrayList;

public class HelloApplet extends Applet  
{
    private int x1, y1;
    private int x2, y2;
    private List<Line> lines;

    public void init()
    {
        this.addMouseListener(new MouseMove());
        this.addMouseMotionListener(new MouseMove());
        lines = new ArrayList<>(); 
    }

    public void paint(Graphics g) 
    {
        for (Line line : lines) {
            g.drawLine(line.getX1(), line.getY1(), line.getX2(), line.getY2());
        }
        g.drawLine(x1, y1, x2, y2); 
    }

    class MouseMove extends MouseAdapter {
        public void mousePressed(MouseEvent e)
        {
            x1 = e.getX();
            y1 = e.getY();
        }

        public void mouseDragged(MouseEvent e) {
            x2 = e.getX();
            y2 = e.getY();
            repaint();
        }

        public void mouseReleased(MouseEvent e)
        {
            lines.add(new Line(x1, y1, x2, y2)); 
        }
    }

    class Line {
        private int x1, y1;
        private int x2, y2;

        public Line(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }

        public int getX1() { return x1; }
        public int getY1() { return y1; }
        public int getX2() { return x2; }
        public int getY2() { return y2; }
    }
}
