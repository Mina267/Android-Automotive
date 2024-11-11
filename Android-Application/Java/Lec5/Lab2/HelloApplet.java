import java.applet.Applet;
import java.awt.Graphics;
import java.awt.*;
import java.util.Date;
import java.lang.InterruptedException;

public class HelloApplet extends Applet implements Runnable 
{
	private Thread newThread;
	private int x;
	public void init()
	{
		newThread = new Thread(this);
		newThread.start();
		
	}
    public void paint(Graphics g) 
	{
		g.setColor(Color.RED);  
		Font font = new Font("Serif", Font.BOLD, 20);
		g.setFont(font);
		g.drawString("JAVA WORLD", x, getHeight() / 2);
        
    }
	
	public void run(){
		while(true){
			try{
				repaint();
				x++;
				if (x >= getWidth())
				{
					x = -150;
				}
				Thread.sleep(10);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		}
	}
}
