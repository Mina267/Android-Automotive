import java.applet.Applet;
import java.awt.Graphics;
import java.awt.GraphicsEnvironment;
import java.awt.Font;

public class HelloApplet extends Applet {
    public void paint(Graphics g) {
        GraphicsEnvironment t = GraphicsEnvironment.getLocalGraphicsEnvironment();
        String[] fonts = t.getAvailableFontFamilyNames();

        int y = 20; // Starting y-coordinate for the text

        for (String font : fonts) {
            g.setFont(new Font(font, Font.PLAIN, 12)); // Create a Font object with the specified font name
            g.drawString(font, 10, y); // Draw the font name
            y += 15; // Move y-coordinate down for the next font
        }
    }
}
