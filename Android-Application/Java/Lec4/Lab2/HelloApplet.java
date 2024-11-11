import java.applet.Applet;
import java.awt.Graphics;
import java.awt.GraphicsEnvironment;
import java.awt.*;

public class HelloApplet extends Applet 
{
	private String[] fonts;
	public void init()
	{
		
	}
    public void paint(Graphics g) 
	{
		g.setColor(Color.RED);  
		g.fillOval(100, 100, 200, 50);
		
		g.setColor(Color.BLACK);  
		g.drawLine(100, 125, 70, 250);
		g.drawLine(300, 125, 330, 250);
		
		g.setColor(Color.RED);  
		g.fillOval(165, 175, 75, 100); 
		g.fillOval(270, 190, 40, 60); 
		g.fillOval(100, 190, 40, 60);
	
		g.setColor(Color.BLACK);  
		g.drawArc(70, 200, 260, 100, 180, 180);
		
		g.drawRect(125, 400, 150, 30);
		
		g.drawLine(185, 300, 170, 400);
		g.drawLine(215, 300, 230, 400);
    }
}
