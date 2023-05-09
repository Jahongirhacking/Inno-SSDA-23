// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university

import java.util.*;

// Color choices
enum Color {
    YELLOW("Yellow"),
    BLUE("Blue"),
    BLACK("Black"),
    WHITE("White"),
    PURPLE("Purple");
    
    String colorName;
    
    Color(String colorName) {
        this.colorName = colorName;
    }
    
    public String toString() {
        return this.colorName;
    }
}

abstract class Shape {
    private ShapeType shapeType;
    private double coordinateX;
    private double coordinateY;
    private Color fillColor;
    // Setters and Getters
    public void setShapeType(ShapeType shapeType) {
        this.shapeType = shapeType;
    }
    public ShapeType getShapeType() {
        return this.shapeType;
    }
    public void setCoordinateX(double x) {
        this.coordinateX = x;
    }
    public double getCoordinateX() {
        return this.coordinateX;
    };
    public void setCoordinateY(double y) {
        this.coordinateY = y;
    }
    public double getCoordinateY(){
        return this.coordinateY;
    }
    public void setFillColor(Color color) {
        this.fillColor = color;
    }
    public Color getFillColor() {
        return this.fillColor;
    }
}

interface IShape {
    void accept(ShapeVisitor shape);
}

class ShapeType {
    private Color borderColor;
    private double thickness;
    
    public ShapeType(Color borderColor, double thickness) {
        this.borderColor = borderColor;
        this.thickness = thickness;
    }

}
// Visitor for shapes
// We should use Visitor Pattern 
// to implement  appropriate algorithms for specific objects
interface ShapeVisitor {
    void visit(Triangle triangle);
    void visit(Rectangle rectangle);
    void visit(Circle circle);
    void visit(Line line);
}

// Triangle shape
class Triangle extends Shape implements IShape{
    double side1;
    double side2;
    double side3;

    @Override
    public void accept(ShapeVisitor visitor) {
        visitor.visit(this);
    }
}

// Circle Shape
class Circle extends Shape implements IShape {
    double radius;
    
    @Override
    public void accept(ShapeVisitor visitor) {
        visitor.visit(this);
    }
}

// Rectangle shape
class Rectangle extends Shape implements IShape{
    double length;
    double width;

    @Override
    public void accept(ShapeVisitor visitor) {
        visitor.visit(this);
    }
}

// Line shape
class Line extends Shape implements IShape {
    double lineLength;

    @Override
    public void accept(ShapeVisitor visitor) {
        visitor.visit(this);
    }
}

// We are using FlyWeight Pattern 
class ShapeFactory {
    private static final Map<String, ShapeType> checkShape = new HashMap<>();
    
    // Extrinsic properties are borderColor and thickness
    // Line has no fillColor
    public static ShapeType getShapeType(Color borderColor, double thickness){
        String key = borderColor.toString() + "," + String.valueOf(thickness);
        ShapeType shapeType = checkShape.get(key);
        if(shapeType == null){
            shapeType = new ShapeType(borderColor, thickness);
            checkShape.put(key, shapeType);
            System.out.println("Creating shapeType ...");
        }
        else {
            System.out.println("Using an already existing shapeType ...");
        }
        return shapeType;
    }
}

class DrawVisitor implements ShapeVisitor{
    @Override
    public void visit(Rectangle rectangle) {
        System.out.println("Drawing rectangle: coordinates "+
                    rectangle.getCoordinateX() + " " + rectangle.getCoordinateY());
    }

    @Override
    public void visit(Circle circle) {
        System.out.println("Drawing circle: coordinates "+
                    circle.getCoordinateX() + " " + circle.getCoordinateY());
    }

    @Override
    public void visit(Triangle triangle) {
        System.out.println("Drawing triangle: coordinates "+
                    triangle.getCoordinateX() + " " + triangle.getCoordinateY());
    }

    @Override
    public void visit(Line line) {
        System.out.println("Drawing line: coordinates "+line.getCoordinateX()
                        +" "+line.getCoordinateY());
    }
}

class ExportVisitor implements ShapeVisitor{
    @Override
    public void visit(Rectangle rectangle) {
        System.out.println("Exporting rectangle...");
    }

    @Override
    public void visit(Circle circle) {
        System.out.println("Exporting circle...");
    }

    @Override
    public void visit(Triangle triangle) {
        System.out.println("Exporting triangle...");
    }

    @Override
    public void visit(Line line) {
        System.out.println("Exporting line...");
    }
}

public class Runner {
    public static void main(String[] args) {
        List<IShape> shapes = new ArrayList<IShape>();
        // Shape styles
        ShapeType shapeTypeOne = ShapeFactory.getShapeType(Color.YELLOW, 2.7);
        ShapeType shapeTypeTwo = ShapeFactory.getShapeType(Color.BLUE, 6.2);
        ShapeType shapeTypeThree = ShapeFactory.getShapeType(Color.YELLOW, 2.7);
        
        // Triangle
        Triangle triangle = new Triangle( );
        triangle.setCoordinateX(31.4);
        triangle.setCoordinateY(12.4);
        triangle.side1 = 12;
        triangle.side2 = 11;
        triangle.side3 = 20;
        triangle.setShapeType(shapeTypeOne);
        shapes.add(triangle);
        
        // Rectangle
        Rectangle rectangle = new Rectangle( );
        rectangle.setCoordinateX(17.3);
        rectangle.setCoordinateY(24.6);
        rectangle.width = 10;
        rectangle.length = 4;
        rectangle.setShapeType(shapeTypeTwo);
        shapes.add(rectangle);
        
        // Circle
        Circle circle = new Circle();
        circle.setCoordinateX(14.9);
        circle.setCoordinateY(19.7);
        circle.radius = 12;
        circle.setShapeType(shapeTypeThree);
        shapes.add(circle);
        
        // Line
        Line line = new Line();
        line.setCoordinateY(22.2);
        line.setCoordinateX(30.4);
        line.lineLength = 14;
        line.setShapeType(shapeTypeTwo);
        shapes.add(line);

        // Create Corresponding Visitors Draw & Export
        DrawVisitor drawVisitor = new DrawVisitor();
        ExportVisitor exportVisitor = new ExportVisitor();
        for (IShape shape : shapes) {
            shape.accept(drawVisitor);
            shape.accept(exportVisitor);
        }
    }
}

