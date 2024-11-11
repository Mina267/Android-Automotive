import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;

public class HelloApplet extends Applet  
{
	private int x, y;
	private boolean hovered = false;
	private int diameter = 50;
	private int radius;
	
	public void init()
	{
		this.addMouseListener(new MouseMove());
        this.addMouseMotionListener(new MouseMove());
		x = getWidth() / 2;
		y = getHeight() / 2;
		diameter = 50;
		radius = diameter / 2;
		
	}
    public void paint(Graphics g) 
	{
		
        g.setColor(Color.RED);  
		g.fillOval(x, y, diameter, diameter);

    }
	
	
	class MouseMove extends MouseAdapter {
		public void mousePressed(MouseEvent e)
		{
			/* x-y of the mouse pointer relative to x-y of the center of the circle */
			int dx = e.getX() - (x + radius);
			int dy = e.getY() - (y + radius);
			/* if distance between them smaller or equal to reduis mouse pressed inside the circle */
			if (Math.sqrt(dx * dx + dy * dy) <= radius)
			{
				hovered = true;
				repaint();
			}		
		}
	
	
		public void mouseDragged(MouseEvent e) {
			if(hovered == true)
			{
				/* condition as boundry for oval to not go out */
				if (e.getX() >= radius && e.getX() <= getWidth() - radius)
				{
					/* shift oval center where mouse point */
					x = e.getX() - radius;
				}
				if (e.getY() >= radius && e.getY() <= getHeight() - radius)
				{
					y = e.getY() - radius;
				}
				repaint();
			}
		}
		
		public void mouseReleased(MouseEvent e)
		{
			hovered = false;
		}
	}
	
}
