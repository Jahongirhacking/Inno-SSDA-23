// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university

import java.io.*;
import java.util.*;

interface Iterator{
    public Product next();
    public boolean hasNext();
}

interface IterableData {
    Iterator createIterator();
}

interface ItemCollection {
    public void addProduct(Product product);
    public void removeProduct(Product product);
}

class Product {
    private String name;
    private int quantity;

    public Product(String name, int quantity){
        this.quantity = quantity;
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
    
    public int getQuantity() {
        return quantity;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}

// List of Products
class Products implements IterableData, ItemCollection{
    private ArrayList<Product> productsList;
    
    public Products() {
        this.productsList = new ArrayList<Product>();
    }
    
    public ArrayList<Product> getProducts() {
        return this.productsList;
    }
    
    @Override
    public void addProduct(Product product) {
        this.productsList.add(product);
    }
    
    @Override
    public void removeProduct(Product product) {
        int index = this.productsList.indexOf(product);
        if(index >= 0) {
            this.productsList.remove(index);
        }
    }
    
    @Override
    public Iterator createIterator() {
        return new ProductIterator(this);
    }
}

// Iterator for products
// We only need to implement algo. for hasNext() and next()
// products <ArrayList>
class ProductIterator implements Iterator{
    Products products;
    int position;
    
    ProductIterator(Products products) {
        this.products = products;
        this.position = -1;
    }
    
    @Override
    public boolean hasNext() {
        if(this.position < products.getProducts().size()-1) return true;
        return false;
    }
    
    @Override
    public Product next() {
        return products.getProducts().get(++position);
    }
}

class Shop {
    Products products;
    boolean flag = true;
    
    Shop(Products products) {
        this.products = products;
    }
    
    public void display() {
        Iterator productIterator = products.createIterator();
        if(flag) System.out.println("Grocery shop list:");
        else System.out.println("Updated grocery shop list:");
        
        while(productIterator.hasNext()) {
            Product product = productIterator.next();
            System.out.println(product.getName() + ", " + product.getQuantity());
        }
        System.out.println();
        
        this.flag = false;
    }
    
    // Implement a mechanism to handle cases when 
    // a product is out of stock and display an appropriate message on the screen
    public void makeAction(Customer customer) {
        Iterator customerProductIterator = 
                        customer.getCustomerProducts().createIterator();
        while(customerProductIterator.hasNext()) {
            boolean isExist = false;
            Product tempCustomerProduct = customerProductIterator.next();
            Iterator shopProductIterator = this.products.createIterator();
            // Check with store products
            while(shopProductIterator.hasNext()) {
                Product tempShopProduct = shopProductIterator.next();
                // If the names of the products are equal
                if(tempShopProduct.getName().equals(tempCustomerProduct.getName())) {
                    isExist = true;
                    if(tempShopProduct.getQuantity() > tempCustomerProduct.getQuantity()) {
                        tempShopProduct.setQuantity(tempShopProduct.getQuantity()
                                                - tempCustomerProduct.getQuantity());
                    } else if(tempShopProduct.getQuantity() == tempCustomerProduct.getQuantity()) {
                        products.removeProduct(tempShopProduct);
                    } else {
                        System.out.println("Sorry, you can buy only "
                                + tempShopProduct.getQuantity() + " " + tempShopProduct.getName());
                        products.removeProduct(tempShopProduct);
                    }
                }
            }
            if(!isExist) {
                System.out.println("Sorry, " + tempCustomerProduct.getName() + " are not available");
            }
        }
        
    }
}

class Customer {
    private int order;
    private Products products;
    
    Customer(Products products, int order) {
        this.products = products;
        this.order = order;
    }
    
    public ArrayList<Product> getProducts() {
        return this.products.getProducts();
    }
    
    public Products getCustomerProducts() {
        return this.products;
    }

    public void display() {
        System.out.println("Customer "+this.order+" list:");
        for(Product product: getProducts()) {
            System.out.println(product.getName()+", "+product.getQuantity());
        }
        System.out.println();
    }
}


public class Runner {
    public static void main(String[] args) throws FileNotFoundException {
        // Products
        Products shopProducts = new Products();
        Products customerProducts;
        // Customers
        Customer customer;
        // File Handling
        try {
            File file = new File("shop.txt");
            Scanner scanner = new Scanner(file);
            while(scanner.hasNextLine()) {
                String[] arr = scanner.nextLine().split(", ");
                String name = arr[0];
                int quantity = Integer.parseInt(arr[1]); 
                shopProducts.addProduct(new Product(name, quantity));
            }
        } 
        catch (FileNotFoundException e) {
            System.err.print(e);
        }
        
        // Runtime
        Shop shop = new Shop(shopProducts);
        shop.display();
        
        // Customer 1
        customerProducts = new Products();
        customer = new Customer(customerProducts, 1);
        customerProducts.addProduct(new Product("lemon", 1));
        customerProducts.addProduct(new Product("bread", 1));
        customer.display();
        shop.makeAction(customer);
        shop.display();
        
        // Customer 2
        customerProducts = new Products();
        customer = new Customer(customerProducts, 2);
        customerProducts.addProduct(new Product("milk", 5));
        customerProducts.addProduct(new Product("bread", 3));
        customer.display();
        shop.makeAction(customer);
        shop.display();
        
        // Customer 3
        customerProducts = new Products();
        customer = new Customer(customerProducts, 3);
        customerProducts.addProduct(new Product("lemon", 1));
        customerProducts.addProduct(new Product("apples", 20));
        customer.display();
        shop.makeAction(customer);
        shop.display();
    }
}

