import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.Font;

public class HelloApplet extends Applet 
{
	private String str;
	private int x, y;
	
	public void init()
	{
		class KeyChange extends KeyAdapter {
			public void keyPressed(KeyEvent e) {
				/* Move according to pressed key */
				switch(e.getKeyCode()) {
					case KeyEvent.VK_UP:
						y -= 5;
    	                break;
    	            case KeyEvent.VK_DOWN:
						y += 5;
    	                break;
    	            case KeyEvent.VK_LEFT:
						x -= 5;
    	                break;
    	            case KeyEvent.VK_RIGHT:
						x += 5;
    	                break;
    	            default:

    	                break;
				}
				repaint();
				/* adjust */
				if (x < -10) {
					x = getWidth() - 10;
                }
				else if (x > getWidth() - 10) {
                    x = -10;
                }
				else if (y < -10) {
                    y = getHeight() - 10;
                }
				else if (y > getHeight() - 10) {
                    y = -10;
                }
			}
		}

		addKeyListener(new KeyChange());

        x = getWidth() / 2;
		y = getHeight() / 2;

		

		str = "JAVA";
		
	}
    public void paint(Graphics g) 
	{
		Font font = new Font("Serif", Font.BOLD, 20);
		g.setFont(font);
		g.setColor(Color.BLUE);
		g.drawString(str, x, y);

    }
}
