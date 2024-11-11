import java.applet.Applet;
import java.awt.Graphics;
import java.awt.event.KeyAdapter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Button;
import java.awt.Color;
import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.ArrayList;
import java.awt.Component;
import java.awt.Checkbox;
import java.util.Stack;

/* Control color used with shapes */
class ControlColorPanel extends Panel  {
    private Button redBtn;
    private Button blueBtn;
    private Button greenBtn;
    private Color color;

    public ControlColorPanel() {
		/* Default color is red */
        color = Color.RED;
		
		/* Set buttons */
        redBtn = new Button("RED");
        blueBtn = new Button("BLUE");
        greenBtn = new Button("GREEN");
		redBtn.setBackground(Color.RED);
		blueBtn.setBackground(Color.BLUE);
		greenBtn.setBackground(Color.GREEN);
		
		
		/* Add action listener to Buttons usning inner class */
        redBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				color = Color.RED;
            }
        });
        add(redBtn);

        blueBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                color = Color.BLUE;
            }
        });
        add(blueBtn);


        greenBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
				color = Color.GREEN;
            }
        });
        add(greenBtn);
    }
	
	/* Use to set current color according to color choosen */
    void setCurrentColor(Graphics g) {
        g.setColor(color);
    }   
    Color getCurrentColor() {
        return color;
    }
	
	
}

/* Panel that control shape status */
class ControlShapesPanel extends Panel  {
    private Button rectangleBtn;
    private Button ovelBtn;
    private Button lineBtn;
    private Button freeHandBtn;
	private Button EraseBtn;
    private ShapeStatus shapeStatus;
	private Checkbox filledCheckBox;
	private boolean filledFlag;
	
    public ControlShapesPanel(boolean filled) {

        shapeStatus = ShapeStatus.RECTANGLE;
		filledFlag = filled;
		
		/* Create Shapes buutons */
        rectangleBtn = new Button("Rectangle");
        ovelBtn = new Button("Oval");
        lineBtn = new Button("Line");
        freeHandBtn = new Button("Freehand");
		EraseBtn = new Button("Erase");
		filledCheckBox = new Checkbox("Filled");
		
		/* Add Action Listener to change current using shape */
        rectangleBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                shapeStatus = ShapeStatus.RECTANGLE;
            }
        });
        add(rectangleBtn);

        ovelBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                shapeStatus = ShapeStatus.OVAL;
            }
        });
        add(ovelBtn);

        lineBtn.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) {
                shapeStatus = ShapeStatus.LINE;
            }
        });
        add(lineBtn);

        freeHandBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                shapeStatus = ShapeStatus.FREEHAND;
            }
        });
        add(freeHandBtn);
		
		EraseBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                shapeStatus = ShapeStatus.ERASE;
            }
        });
        add(EraseBtn);
		
		filledCheckBox.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				filledFlag = !filledFlag;
			}
		});
		
		add(filledCheckBox);

    }
	
	/* return current flag status */
    ShapeStatus getShapeStatus() {
        return shapeStatus;
    }
	
	boolean getFilledFlag()
	{
		return filledFlag;
	}
	
    public enum ShapeStatus {
        RECTANGLE, OVAL, LINE, FREEHAND, ERASE
    }
}



class ControlUtilPanel extends Panel {
    private Button clearAllBtn;
    private Button undoBtn;
    private Button redoBtn;
    private List<Shape> shapes;
	private PaintBrush paintBrush;
	private Stack<Shape> redoStack;

    public ControlUtilPanel(List<Shape> shapes, PaintBrush paintBrush, Stack<Shape> redoStack) {
        this.shapes = shapes;
		this.paintBrush = paintBrush;
		this.redoStack = redoStack;
        clearAllBtn = new Button("Clear ALL");
        undoBtn = new Button("Undo");
		redoBtn = new Button("Redo");

        clearAllBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                shapes.clear(); 
				redoStack.clear();
                paintBrush.repaint();
            }
        });
        add(clearAllBtn);

        undoBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (!shapes.isEmpty()) {
					redoStack.push(shapes.get(shapes.size() - 1));
                    shapes.remove(shapes.size() - 1); 
                    paintBrush.repaint();
                }
            }
        });
        add(undoBtn);
		
		redoBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (!redoStack.empty()) {
                    shapes.add(redoStack.pop()); 
                    paintBrush.repaint();
                }
            }
        });
        add(redoBtn);
    }
}