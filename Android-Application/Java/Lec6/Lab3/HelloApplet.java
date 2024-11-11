import java.applet.Applet;
import java.awt.Graphics;
import java.lang.InterruptedException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Button;
import java.awt.Color;

public class HelloApplet extends Applet implements Runnable 
{
	private Thread newThread;
	private int x;
	private int y;
	private boolean dirFlagX;
	private boolean dirFlagY;
	private Button stopBtn;
    private Button startBtn;
	private boolean flag = true;
	private boolean status = false;
	
	public void init()
	{
		newThread = new Thread(this);
		dirFlagX = true;
		y = getHeight() / 2;
		
		stopBtn = new Button("Stop");
        stopBtn.addActionListener(new MyButtonListener());
        add(stopBtn);

        startBtn = new Button("Start");
        startBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ev) {
				if (flag)
				{
					
					newThread.start();
					flag = false;
				}
				else if (status == true)
				{
					newThread.resume();
					status = false;
				}
				
                repaint();
            }
        });
        add(startBtn);
		
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
	
	class MyButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent ev) {
			
			if (status == false)
			{
				newThread.suspend();
				status = true;
			}
			
            repaint();
        }
    }
}
