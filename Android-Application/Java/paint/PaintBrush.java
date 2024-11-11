import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;
import java.awt.Color;
import java.util.ArrayList;
import java.awt.*;
import java.awt.BorderLayout;
import java.util.Stack;


/* Double buffer */
import java.awt.image.BufferedImage;

public class PaintBrush extends Applet {
    private Point start;
    private Point end;
    private List<Shape> shapes;
	private Stack<Shape> redoStack;
    private Shape currentShape;
    private Color currentColor;
    private ControlColorPanel controlColorPanel;
    private ControlShapesPanel controlShapesPanel;
    private ControlUtilPanel controlUtilPanel;
    private boolean drawingStatus;
	
	/* Double buffer */
	private BufferedImage backBuffer;
    private Graphics2D backBufferGraphics;
	
    public void init() {

        shapes = new ArrayList<>();
		redoStack = new Stack<>();
		drawingStatus = false;
        this.setLayout(new BorderLayout()); // Use BorderLayout for positioning the control panel
        
        controlShapesPanel = new ControlShapesPanel(false);
        controlColorPanel = new ControlColorPanel();
        controlUtilPanel = new ControlUtilPanel(shapes, this, redoStack);
        this.add(controlColorPanel, BorderLayout.WEST);  
        this.add(controlShapesPanel, BorderLayout.NORTH); 
        this.add(controlUtilPanel, BorderLayout.EAST);

        this.addMouseListener(new MouseMove());
        this.addMouseMotionListener(new MouseMove());
    }

    
    private void render(Graphics2D g) {
        // Clear the back buffer
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());

        /* Draw all the shapes */
        for (Shape shape : shapes) {
            shape.draw(g);
        }
        
        /* Draw the current shape being dragged */
        if (currentShape != null) {
            currentShape.draw(g);
        }
    }

    class MouseMove extends MouseAdapter {
        
        public void mousePressed(MouseEvent e) {
			
			
			/* Start point of the Shape */
			start = new Point(e.getX(), e.getY());

			/* Determine Shapes type required to create according to button status */
			switch (controlShapesPanel.getShapeStatus())
			{
				case RECTANGLE:
					currentShape = new Rectangle(controlColorPanel.getCurrentColor(), controlShapesPanel.getFilledFlag(), start, start);
					break;
				case OVAL:
					currentShape = new Oval(controlColorPanel.getCurrentColor(), controlShapesPanel.getFilledFlag(), start, start);
					break;
				case LINE:
					currentShape = new Line(controlColorPanel.getCurrentColor(), start, start);
					break;
				case FREEHAND:
					currentShape = new FreeHand(controlColorPanel.getCurrentColor(), start);
					break;
				case ERASE:
					currentShape = new Erase(start);
				break;
			}
			/* Start painting will empty redo stack */
			redoStack.clear();
		
            
        }

        
        public void mouseDragged(MouseEvent e) {
            
			
			/* Change end point of shape */
			end = new Point(e.getX(), e.getY());
			
			if (currentShape != null) {
				currentShape.setEnd(end);
			}
			
			if (controlShapesPanel.getShapeStatus() == ControlShapesPanel.ShapeStatus.FREEHAND)
			{
				/* down cast */
				((FreeHand) currentShape).addPoint(end);
			}
			else if (controlShapesPanel.getShapeStatus() == ControlShapesPanel.ShapeStatus.ERASE)
			{
				((Erase) currentShape).addPoint(end);
			}
			
			repaint();
			drawingStatus = true;
			
			
        }

        
        public void mouseReleased(MouseEvent e) {
			
			if (drawingStatus == true) {
				
				if (currentShape != null) {
					currentShape.setEnd(end);
					shapes.add(currentShape);
					currentShape = null; 
				}
				repaint();
				
				drawingStatus = false;
			}
			
			
        }
    }
	
	
	
	
	
	
	
	
	
	/* Double buffer */
	
	 public void update(Graphics g) {
        // Create back buffer if not already created
        if (backBuffer == null) {
            backBuffer = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
            backBufferGraphics = backBuffer.createGraphics();
            // Set initial background color
            backBufferGraphics.setColor(Color.WHITE);
            backBufferGraphics.fillRect(0, 0, getWidth(), getHeight());
        }
        // Render to back buffer
        render(backBufferGraphics);
        // Draw back buffer to screen
        g.drawImage(backBuffer, 0, 0, this);
    }
	
}
