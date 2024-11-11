import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class HelloApplet extends Applet  
{
	private int x1, y1;
	private int x2, y2;
	private boolean flag = false;
	private boolean Dflag = false;

	
	public void init()
	{
		this.addMouseListener(new MouseMove());
        this.addMouseMotionListener(new MouseMove());

		
	}
    public void paint(Graphics g) 
	{
		
        g.drawLine(x1, y1 ,x2 ,y2);

    }
	
	
	class MouseMove extends MouseAdapter {
		public void mousePressed(MouseEvent e)
		{
			x1 = e.getX();
			y1 = e.getY(); 
		}
	
	
		public void mouseDragged(MouseEvent e) {
			if(!flag)
			{
				x2 = e.getX();
				y2 = e.getY(); 
				repaint();
			}
			Dflag = true;
		}
		
		public void mouseReleased(MouseEvent e)
		{
			if (Dflag == true)
			{
				flag = true;
			}
		}
	}
	
}
