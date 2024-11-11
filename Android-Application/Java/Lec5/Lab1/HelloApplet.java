import java.applet.Applet;
import java.awt.Graphics;
import java.util.Date;
import java.lang.InterruptedException;
import java.awt.*;


public class HelloApplet extends Applet implements Runnable 
{
	private Thread newThread;
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
		Date d = new Date();
		g.drawString(d.toString(), getWidth() / 2 - 140, getHeight() / 2);
        
    }
	
	public void run(){
		while(true){
			try{
				repaint();
				Thread.sleep(1000);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		}
	}
}
