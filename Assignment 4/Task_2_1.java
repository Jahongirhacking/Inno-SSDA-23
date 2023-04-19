import java.util.ArrayList;

// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
/*
    Identify the principle(s) being violated:
    Open-closed Principle, Interface Segregation, Dependency Inversion

    - according to OCP, The classes should open for extension and closed to
    modification. In old version, for example, If we were going to add new DailyEmployee
    we would have had a problem inside the Payroll class, because we only defined
    SalariedEmployee and HourlyEmployee in it.

    - according to ISP, Clients should not be forced to implement a function or a field
    which they do not need. In old version, SalariedEmployee used to accept
    hourlyRate property but never touch it and also for salary inside the HourlyEmployee.

    - according to DIP, our classes should depend on interfaces or abstract classes
    instead of concrete classes. In old version, both types of Employees depend on
    concrete Employee class.
 */
class Payroll {
    public double calculatePay(Employee employee) {
        return employee.calculatePay();
    }
}

abstract class Employee {
    private String name;

    public Employee(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public abstract double calculatePay();
}

class SalariedEmployee extends Employee {
    private double salary;
    public SalariedEmployee(String name, double salary) {
        super(name);
        this.salary = salary;
    }
    public double getSalary() {
        return salary;
    }
    @Override
    public double calculatePay() {
        return getSalary();
    }
}

class HourlyEmployee extends Employee {
    private double hoursWorked;
    private double hourlyRate;

    public HourlyEmployee(String name, double hourlyRate, double hoursWorked) {
        super(name);
        this.hoursWorked = hoursWorked;
        this.hourlyRate = hourlyRate;
    }

    public double getHourlyRate() {
        return hourlyRate;
    }
    @Override
    public double calculatePay() {
        return getHourlyRate() * hoursWorked;
    }
}

public class Task_2_1 {
    public static void main (String[] args) {
        Payroll payroll = new Payroll();
        // Adding Employees
        ArrayList<Employee> employees = new ArrayList<>();
        employees.add(new SalariedEmployee("Bobur", 2000));
        employees.add(new HourlyEmployee("Ozoda", 15, 50));
        employees.add(new SalariedEmployee("Mohammad", 1400));
        // Calculate Pay
        for(Employee employee : employees) {
            System.out.println(payroll.calculatePay(employee));
        }
    }
}
