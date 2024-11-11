import java.applet.Applet;
import java.awt.Graphics;
import java.awt.GraphicsEnvironment;
import java.awt.Font;

public class HelloApplet extends Applet 
{
	private String[] fonts;
	public void init()
	{
		GraphicsEnvironment t = GraphicsEnvironment.getLocalGraphicsEnvironment();
        fonts  = t.getAvailableFontFamilyNames();
		
	}
    public void paint(Graphics g) 
	{
		int y = 25;
        
		
		
        for (String fontName : fonts) {
			
			Font font = new Font(fontName, Font.BOLD, 20);
			g.setFont(font);
			g.drawString(fontName, 100, y);
			y += 25;
        }
        
    }
}
