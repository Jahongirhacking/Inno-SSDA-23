// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university

import java.util.*;

interface IMenu {
    public void print();
    public double getPrice();
    public String getName();
    
}

// Concrete MenuItem Class
class MenuItem implements IMenu {
    private String name;
    private double price;
    
    public MenuItem(String name, double price)
    {
        this.name = name;
        this.price = price;
    }

    @Override
    public void print() {
        System.out.println(this.getName()+" [ $"+this.getPrice()+" ]");
    }
    
    @Override
    public double getPrice() {
        return this.price;
    }
    
    @Override
    public String getName() {
        return this.name;
    }
}

// Menu Items wrapper
class CompositeMenu implements IMenu {
    private ArrayList<IMenu> menuItems;
    private String name;
    private double totalPrice;
    
    public CompositeMenu(String menuName) {
        menuItems = new ArrayList<IMenu>();
        this.name = menuName;
        this.totalPrice = 0.0;
    }
    
    public void addMenuItem(IMenu menuItem) {
        menuItems.add(menuItem);
        this.totalPrice += menuItem.getPrice();
    }
    
    public void removeMenuItem(IMenu menuItem) {
        int index = menuItems.indexOf(menuItem);
        if(index >= 0) {
            menuItems.remove(menuItem);
            this.totalPrice -= menuItem.getPrice();
        }
    }
    public List<IMenu> getMenuItems() {
        return menuItems;
    }
    @Override
    public void print() {
        System.out.println(name+" [ $"+getPrice()+" ]\n------------------");
        for (IMenu menuItem : menuItems) {
            menuItem.print();
        }
        System.out.println();
    }

    @Override
    public double getPrice() {
        return this.totalPrice;
    }
    
    @Override
    public String getName() {
        return this.name;
    }


}

abstract class MenuItemDecorator implements IMenu {
    public abstract void print();
    public abstract double getPrice();
    public abstract String getName();
}

class SpicyDecorator extends MenuItemDecorator{
    public IMenu menuItem;
    
    public SpicyDecorator(IMenu menuItem) {
        this.menuItem = menuItem;
    };

    @Override
    public void print() {
        this.menuItem.print();
        displayInfo();
    }

    @Override
    public double getPrice() {
        // Spice Decorator increases the cost by $2
        return this.menuItem.getPrice() + 2.0;
    }
    
    @Override
    public String getName()
    {
        return this.menuItem.getName();
    }
    
    private void displayInfo()
    {
        System.out.println("  -- this item is spicy  (+ $2)");
    }
}

class VegetarianDecorator extends MenuItemDecorator{
    public IMenu menuItem;
    
    public VegetarianDecorator(IMenu menuItem) {
        this.menuItem = menuItem;
    };

    @Override
    public void print() {
        this.menuItem.print();
        displayInfo();
    }

    @Override
    public double getPrice() {
        // Vegetarian Decorator increases the cost by $4
        return this.menuItem.getPrice() + 4.0;
    }
    
    @Override
    public String getName()
    {
        return this.menuItem.getName();
    }
    
    private void displayInfo()
    {
        System.out.println("  -- this item is vegetarian   (+ $4)");
    }
}

public class Runner {
    public static void main(String[] args) {
        // Composite Menus
        CompositeMenu mainMenu = new CompositeMenu("Main Menu");
        CompositeMenu dessertMenu = new CompositeMenu("Dessert Menu");
        CompositeMenu appetizerMenu = new CompositeMenu("Appetizer Menu");
        // Create Menu Items
        IMenu garlicBread = new VegetarianDecorator(new MenuItem("Garlic Bread", 5.5));
        IMenu chickenWings = new SpicyDecorator(new MenuItem("Chicken Wings", 12.5));
        IMenu tomatoSoup = new VegetarianDecorator(new SpicyDecorator(new MenuItem("Tomato Soup", 10.5))) ;
        IMenu normalPie = new MenuItem("Pie", 4.5);
        IMenu spicyPie = new SpicyDecorator(new MenuItem("Pie", 4.5));
        IMenu iceCream = new MenuItem("Ice Cream", 3.0);
        // Add Menu Items to Composite Menu
        appetizerMenu.addMenuItem(garlicBread);
        appetizerMenu.addMenuItem(chickenWings);
        appetizerMenu.addMenuItem(tomatoSoup);
        dessertMenu.addMenuItem(normalPie);
        dessertMenu.addMenuItem(spicyPie);
        dessertMenu.addMenuItem(iceCream);
        mainMenu.addMenuItem(appetizerMenu);
        mainMenu.addMenuItem(dessertMenu);
        // Begin to print with outermost - mainMenu
        mainMenu.print();
    }
}
