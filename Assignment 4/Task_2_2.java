// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
/*
    Identify the principle(s) being violated:
    Single Responsibility, Open-closed Principle, Liskov Substitution Principle,
    Interface Segregation, Dependency Inversion

    - according to SRP, A class should do one thing and has only one reason to change.
    In old version, doModificationsAndComputeArea method violated this principle,
    because it modified the sizes and computed the area at the same time.

    - according to OCP, The classes should open for extension and closed to
    modification. In old version, for example, If we were going to add new Circle class
    we would have had a problem inside the doModificationsAndComputeArea method,
    since it only accepted Rectangle class. Notice, doModificationsAndComputeArea also
    violated the SRP above.

    - according to LSP, Subclasses should be substitutable for their base classes.
    In old version, Square class extended Rectangle class. So we can think it as a
    Rectangle. If we Initially create Square(5) and call getArea, it should print 25.
    But if we modify its width to 4, it should print 20 because we are only modifying
    its width and think of it as a Rectangle. However, it will print 16.

    - according to ISP, Many client-specific interfaces are better than one general-purpose one.
    In new version, for instance, I implemented any shape class
    with IShapes and IModifications, for creating and modifying shapes separately.

    - according to DIP, our classes should depend on interfaces or abstract classes
    instead of concrete classes. In old version, Square class was depend on Rectangle class.
 */

class Calculator {
    public double computeArea(IShapes shape) {
        // Returns the area of the modified rectangle
        return shape.getArea();
    }
}

interface IModifications {
    public void doModifications(double ...params);
}

interface IShapes {
    public double getArea();
    public double getPerimeter();
}

class Rectangle implements IShapes, IModifications {
    private double length;
    private double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }
    public void setLength(double length) {
        this.length = length;
    }
    public void setWidth(double width) {
        this.width = width;
    }
    @Override
    public void doModifications(double ...params) {
        setLength(params[0]);
        setWidth(params[1]);
    }
    @Override
    public double getArea() {
        return length * width;
    }
    @Override
    public double getPerimeter() {
        return 2 * (length + width);
    }
}

class Square implements IShapes, IModifications {
    private double side;

    public Square(double side) {
        this.side = side;
    }
    public void setSide(double side) {
        this.side = side;
    }
    @Override
    public void doModifications(double ...params) {
        setSide(params[0]);
    }
    @Override
    public double getArea() {
        return side*side;
    }
    @Override
    public double getPerimeter() {
        return 4*side;
    }
}

class Circle implements IShapes, IModifications {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }
    public void setRadius(double radius) {
        this.radius = radius;
    }
    @Override
    public void doModifications(double ...params) {
        setRadius(params[0]);
    }
    @Override
    public double getArea() {
        return Math.PI*radius*radius;
    }
    @Override
    public double getPerimeter() {
        return 2*Math.PI*radius;
    }
}


public class Task_2_2 {
    public static void main(String[] args) {
        Calculator calculator = new Calculator();

        Rectangle rectangle = new Rectangle(3, 7);
        Square square = new Square(5);
        Circle circle = new Circle(1);

        System.out.println("Area of original rectangle: " + rectangle.getArea());
        rectangle.doModifications(2, 5);
        double areaRectangleAfter = calculator.computeArea(rectangle);
        System.out.println("Area of rectangle after modifications: " + areaRectangleAfter);

        System.out.println("\nArea of original square: " + square.getArea());
        square.doModifications(3);
        double areaSquareAfter = calculator.computeArea(square);
        System.out.println("Area of square after modifications: " + areaSquareAfter);

        System.out.println("\nArea of original circle: " + circle.getArea());
        circle.doModifications(2);
        double areaCircleAfter = calculator.computeArea(circle);
        System.out.println("Area of circle after modifications: " + areaCircleAfter);
    }
}
