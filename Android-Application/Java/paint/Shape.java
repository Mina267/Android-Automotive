import java.awt.Color;
import java.awt.Graphics;
import java.awt.*;
import java.util.List;
import java.util.ArrayList;

abstract class Shape {
    protected Color color;
    protected boolean filled;
    protected Point start;
    protected Point end;
    
    Shape(Color color, boolean filled, Point start, Point end) {
        this.color = color;
        this.filled = filled;
        this.start = start;
        this.end = end;
    }

    abstract void draw(Graphics g);
    abstract boolean inRange(Point p);

    public Color getColor() {
        return color;
    }
    
    public void setColor(Color color) {
        this.color = color;
    }
    
    public boolean isFilled() {
        return filled;
    }

    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    public Point getStart() {
        return start;
    }
    
    public void setStart(Point start) {
        this.start = start;
    }
    
    public Point getEnd() {
        return end;
    }

    public void setEnd(Point end) {
        this.end = end;
    }

}

class Line extends Shape {
    Line(Color color, Point start, Point end) {
        super(color, false, start, end);
    }
    
    void draw(Graphics g) {
        g.setColor(color);
        g.drawLine(start.getX(), start.getY(), end.getX(), end.getY());
    }

    boolean inRange(Point p) {
		return true;
    }
    
}

class Rectangle extends Shape {
    Rectangle(Color color, boolean filled, Point start, Point end) {
        super(color, filled, start, end);
    }
    
    void draw(Graphics g) {
        g.setColor(color);
        int x = Math.min(start.getX(), end.getX());
        int y = Math.min(start.getY(), end.getY());
        int width = Math.abs(start.getX() - end.getX());
        int height = Math.abs(start.getY() - end.getY());
        if (filled) {
            g.fillRect(x, y, width, height);
        } else {
            g.drawRect(x, y, width, height);
        }
    }
    
    boolean inRange(Point p) {
		return true;
    }
}

class Ovel extends Shape {
    Ovel(Color color, boolean filled, Point start, Point end) {
        super(color, filled, start, end);
    }
    
    void draw(Graphics g) {
        g.setColor(color);
        int x = Math.min(start.getX(), end.getX());
        int y = Math.min(start.getY(), end.getY());
        int width = Math.abs(start.getX() - end.getX());
        int height = Math.abs(start.getY() - end.getY());
        if (filled) {
            g.fillOval(x, y, width, height);
        } else {
            g.drawOval(x, y, width, height);
        }
    }
    
    boolean inRange(Point p) {
		return true;

    }
}
class FreeHand extends Shape {
    private List<Point> points;

    FreeHand(Color color, Point start) {
        super(color, false, start, start);
        points = new ArrayList<>();
        points.add(start);
    }

    void draw(Graphics g) {
        g.setColor(color);
		Point p1;
		Point p2;
		
        for (int i = 1; i < points.size(); i++) {
			p1 = points.get(i - 1);
			p2 = points.get(i);
			g.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
		}
    }

    boolean inRange(Point p) {
        return false;
    }

    void addPoint(Point p) {
        points.add(p);
    }
}

class Erase extends Shape {
    private List<Point> points;

    Erase(Point start) {
        super(Color.WHITE, true, start, start);
        points = new ArrayList<>();
        points.add(start);
    }

    void draw(Graphics g) {
        g.setColor(color);
		Point p1;
		Point p2;
		
        for (int i = 1; i < points.size(); i++) {
			p1 = points.get(i - 1);
			p2 = points.get(i);
			int x = Math.min(p1.getX(), p2.getX());
			int y = Math.min(p1.getY(), p2.getY());
			
			g.fillOval(p1.getX(), p1.getY(), 30, 30);
		}
    }

    boolean inRange(Point p) {
        return false;
    }

    void addPoint(Point p) {
        points.add(p);
    }
}


class Point {
	private int x;
    private int y;
	
	
	public Point() {
         this.x = 0;
         this.y = 0;
    }
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public int getX() { return x; }
    public int getY() { return y; }
	public void setX(int x) { this.x = x; }
    public void setY(int y) { this.y = y; }
	public void setXY(int x, int y) { 
	this.x = x; 
	this.y = y; 
	}
}