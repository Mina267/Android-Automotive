import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;

public class HelloApplet extends Applet implements Runnable {
    private Thread newThread;
    public static int Width;
    public static int Height;
    private Ball[] balls;
    private final int BALLS_NUM = 2;
	
    public void init() {
        Width = getWidth();
        Height = getHeight();
        
        balls = new Ball[BALLS_NUM]; 
        balls[0] = new Ball(0, Height / 2, 50, Color.RED, false ,true);
		balls[1] = new Ball(200, Height / 2, 50, Color.GREEN, true, false);

        newThread = new Thread(this);
        newThread.start();
    }

    public void paint(Graphics g) {
        for (Ball ball : balls) {
            ball.drawBall(g);
        }
    }

    public void run() {
        while (true) {
            try {
                repaint();
                Width = getWidth();
                Height = getHeight();
				
				int x_axis = balls[0].getX() - balls[1].getX();
				int y_axis = balls[0].getY() - balls[1].getY();
				int distance = (int)Math.sqrt(x_axis * x_axis + y_axis * y_axis);
				if ((balls[0].getDiameter() + balls[1].getDiameter()) / 2 >= distance)
				{
					
					if (x_axis == 0 && balls[0].getDirFlagX() != balls[1].getDirFlagX())
					{
						balls[0].reverseDirX();
						balls[1].reverseDirX();
					}
					else if (y_axis == 0 && balls[0].getDirFlagY() != balls[1].getDirFlagY())
					{
						balls[0].reverseDirY();
						balls[1].reverseDirY();
					}
					else
					{
						balls[0].reverseDirX();
						balls[1].reverseDirX();
						balls[0].reverseDirY();
						balls[1].reverseDirY();
					}
						
				}
				
                for (Ball ball : balls) {
                    ball.updatePosition();
                }
                Thread.sleep(5);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Ball {
    private int x;
    private int y;
    private int diameter;
    private boolean dirFlagX;
    private boolean dirFlagY;
    private Color color;

    public Ball(int x, int y, int diameter, Color color, boolean dirFlagX, boolean dirFlagY) {
        this.x = x;
        this.y = y;
        this.diameter = diameter;
        this.color = color;
        this.dirFlagX = dirFlagX;
        this.dirFlagY = dirFlagY;
    }

    public void updatePosition() {
        if (x >= HelloApplet.Width - diameter) {
            dirFlagX = false;
        } 
		else if (x <= 0) {
            dirFlagX = true;
        }

        if (dirFlagX) {
            x++;
        } 
		else {
            x--;
        }

        if (y >= HelloApplet.Height - diameter) {
            dirFlagY = false;
        } 
		else if (y <= 0) {
            dirFlagY = true;
        }

        if (dirFlagY) {
            y++;
        } 
		else {
            y--;
        }
    }

    public void drawBall(Graphics g) {
        g.setColor(color);
        g.fillOval(x, y, diameter, diameter);
    }
	
	public int getX() {return x;}
	public int getY() {return y;}
	public boolean getDirFlagX() {return dirFlagX;}
	public boolean getDirFlagY() {return dirFlagY;}
	
	public int getDiameter() {return diameter;}
	public void reverseDirX(){dirFlagX = !dirFlagX;}
	public void reverseDirY(){dirFlagY = !dirFlagY;}
	
}

