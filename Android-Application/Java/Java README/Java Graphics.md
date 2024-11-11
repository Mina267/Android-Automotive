

# Java Graphics, Color, and Font Classes

## Introduction

This guide provides an overview of important Java classes used for graphical programming: `Graphics`, `Color`, and `Font`. These classes are fundamental when working with custom drawings in Java applications, such as creating shapes, text, and colors in applets or GUI components.

## Table of Contents

1. [Graphics Class](#graphics-class)
   - [Drawing Text](#drawing-text)
   - [Drawing Lines](#drawing-lines)
   - [Drawing Rectangles](#drawing-rectangles)
   - [Drawing Ovals and Circles](#drawing-ovals-and-circles)
2. [Color Class](#color-class)
   - [Setting Colors](#setting-colors)
   - [Working with RGB Values](#working-with-rgb-values)
   - [Predefined Colors](#predefined-colors)
   - [Adjusting Colors](#adjusting-colors)
3. [Font Class](#font-class)
   - [Creating a Font](#creating-a-font)
   - [Setting a Font](#setting-a-font)
   - [Listing Supported Fonts](#listing-supported-fonts)
4. [Examples](#examples)
5. [Immutability](#immutability)
6. [Additional Resources](#additional-resources)

## Graphics Class

The `Graphics` class is a crucial component for rendering graphics in Java. It provides various methods to draw shapes, text, and images on components.

### Drawing Text

You can draw text using the `drawString` method. It takes a string and the x, y coordinates as parameters.

```java
public void paint(Graphics g) {
    g.drawString("Hello, Java!", 50, 50);
}
```

### Drawing Lines

To draw a straight line, use the `drawLine` method, which requires the starting and ending coordinates.

```java
public void paint(Graphics g) {
    g.drawLine(10, 10, 100, 100);
}
```

### Drawing Rectangles

The `drawRect` method draws an unfilled rectangle, while `fillRect` draws a filled one.

```java
public void paint(Graphics g) {
    g.drawRect(50, 50, 100, 50);  // Unfilled rectangle
    g.fillRect(200, 50, 100, 50); // Filled rectangle
}
```

### Drawing Ovals and Circles

To draw ovals or circles, use the `drawOval` or `fillOval` methods. The method requires the x, y coordinates, width, and height of the bounding rectangle.

```java
public void paint(Graphics g) {
    g.drawOval(50, 100, 100, 50);  // Unfilled oval
    g.fillOval(200, 100, 50, 50);  // Filled circle
}
```

## Color Class

The `Color` class defines colors using RGB (Red, Green, Blue) values and provides methods to manipulate colors.

### Setting Colors

To set a color for drawing, use the `setColor` method of the `Graphics` class.

```java
public void paint(Graphics g) {
    g.setColor(Color.RED);  // Set drawing color to red
    g.fillRect(50, 50, 100, 50);
}
```

### Working with RGB Values

You can define custom colors by specifying RGB values.

```java
Color customColor = new Color(255, 0, 0); // Pure red
```

### Predefined Colors

Java provides a set of predefined colors, such as `Color.RED`, `Color.GREEN`, and `Color.BLUE`.

```java
g.setColor(Color.BLUE); // Set drawing color to blue
```

### Adjusting Colors

You can adjust the brightness of a color using the `brighter` and `darker` methods.

```java
Color darkerRed = Color.RED.darker();
Color brighterRed = Color.RED.brighter();
```

## Font Class

The `Font` class is used to define the font style, size, and family for drawing text.

### Creating a Font

You can create a new font by specifying the font family, style (e.g., plain, bold, italic), and size.

```java
Font font = new Font("Serif", Font.BOLD, 20);
```

### Setting a Font

To set a font for drawing text, use the `setFont` method of the `Graphics` class.

```java
public void paint(Graphics g) {
    Font font = new Font("Serif", Font.BOLD, 20);
    g.setFont(font);
    g.drawString("Bold Text", 50, 100);
}
```

### Listing Supported Fonts

You can retrieve a list of all available fonts on the system using the `Toolkit` class.

```java
GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
String[] fonts = ge.getAvailableFontFamilyNames();

for (String font : fonts) {
    System.out.println(font);
}
```

## Examples

### Example 1: Drawing Shapes with Colors and Fonts

```java
import java.awt.*;
import javax.swing.*;

public class MyApplet extends JApplet {
    public void paint(Graphics g) {
        // Set the color and draw a rectangle
        g.setColor(Color.RED);
        g.fillRect(50, 50, 100, 50);

        // Set a new color and draw a string
        g.setColor(Color.BLUE);
        g.drawString("Hello, Java!", 50, 150);

        // Set a font and draw another string
        Font font = new Font("Serif", Font.BOLD, 20);
        g.setFont(font);
        g.drawString("Bold Text", 50, 200);
    }
}
```

### Example 2: Drawing with Custom Colors and Shapes

```java
import java.awt.*;
import javax.swing.*;

public class CustomColorExample extends JApplet {
    public void paint(Graphics g) {
        // Define a custom color
        Color customColor = new Color(123, 234, 45);
        g.setColor(customColor);

        // Draw a filled oval with the custom color
        g.fillOval(50, 50, 150, 75);

        // Draw a darker rectangle
        g.setColor(customColor.darker());
        g.fillRect(50, 150, 100, 50);
    }
}
```

## Immutability

Both the `Color` and `Font` classes in Java are immutable. This means that once an object of these classes is created, it cannot be modified. If you need to change the properties of a `Color` or `Font` object, you must create a new instance. The old object becomes eligible for garbage collection.

For example:

```java
Color color = Color.RED;
Color newColor = color.brighter(); // Creates a new object
```

## Additional Resources

For more detailed information, refer to the official Java documentation:
- [Graphics Class Documentation](https://docs.oracle.com/javase/8/docs/api/java/awt/Graphics.html)
- [Color Class Documentation](https://docs.oracle.com/javase/8/docs/api/java/awt/Color.html)
- [Font Class Documentation](https://docs.oracle.com/javase/8/docs/api/java/awt/Font.html)

