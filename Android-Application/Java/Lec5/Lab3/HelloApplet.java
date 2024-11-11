import java.applet.Applet;
import java.awt.Graphics;
import java.awt.*;
import java.lang.InterruptedException;

public class HelloApplet extends Applet implements Runnable 
{
	private Thread newThread;
	private int x;
	private boolean dirFlagX;
	private boolean dirFlagY;
	private int y;
	public void init()
	{
		newThread = new Thread(this);
		newThread.start();
		dirFlagX = true;
		y = getHeight() / 2;
	}
    public void paint(Graphics g) 
	{
		g.setColor(Color.RED);  
		g.fillOval(x, y, 50, 50);
        
    }
	
	public void run(){
		while(true){
			try{
				repaint();
				
				
				if (x >= getWidth() - 50)
					dirFlagX = false;
				else if (x == 0)
					dirFlagX = true;
				
				if (dirFlagX)
					x++;
				else
					x--;
				
				
				if (y >= getHeight() - 50)
					dirFlagY = false;
				else if (y == 0)
					dirFlagY = true;
				
				if (dirFlagY)
					y++;
				else
					y--;
				

				Thread.sleep(5);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		}
	}
}
