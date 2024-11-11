# Coupling and Cohesion (Exam Objective 5.1)

#### Coupling
**Definition:** Coupling refers to the degree of dependency between two classes. If one class knows a lot about another class's internal implementation, they are said to be tightly coupled, which is generally considered bad in object-oriented design. Conversely, if a class interacts with another class only through its public API (methods and properties), the classes are loosely coupled, which is preferred.

**Example of Tight Coupling:**
```java
class DoTaxes {
    float rate;

    float doColorado() {
        SalesTaxRates str = new SalesTaxRates();
        rate = str.salesRate;  // Directly accessing a public field is bad
        // Better: rate = str.getSalesRate("CO");
        // Perform operations with the rate
        return rate;
    }
}

class SalesTaxRates {
    public float salesRate; // Should be private
    public float adjustedSalesRate; // Should be private

    public float getSalesRate(String region) {
        salesRate = new DoTaxes().doColorado();  // Poor design, tight coupling
        // Region-based calculations
        return adjustedSalesRate;
    }
}
```
In this example, `DoTaxes` and `SalesTaxRates` are tightly coupled because they access each other's internal data directly. This is problematic because changes in one class might unexpectedly break the other, making the code harder to maintain.

**Loose Coupling:** To achieve loose coupling, classes should interact only through well-defined interfaces. This reduces the interdependencies between classes, making the code easier to modify and extend without causing side effects.

#### Cohesion
**Definition:** Cohesion refers to how closely related and focused the responsibilities of a single class are. High cohesion means that a class is designed to do one thing and do it well, which leads to better maintainability and reusability.

**Example of Low Cohesion:**
```java
class BudgetReport {
    void connectToRDBMS() { }
    void generateBudgetReport() { }
    void saveToFile() { }
    void print() { }
}
```
In this example, the `BudgetReport` class is responsible for too many different tasks, such as connecting to a database, generating a report, saving to a file, and printing. This design makes the class difficult to maintain, as changes to one part of the class may impact the others.

**Example of High Cohesion:**
```java
class BudgetReport {
    void generateBudgetReport(Options options) { }
}

class ConnectToRDBMS {
    DBConnection getRDBMSConnection() { }
}

class PrintService {
    void printReport(PrintOptions options) { }
}

class FileSaver {
    void saveToFile(SaveOptions options) { }
}
```
Here, the responsibilities are split across multiple classes, each focusing on a specific task. This design improves cohesion, making each class easier to understand, maintain, and reuse in different contexts.

### Benefits of Loose Coupling and High Cohesion:
1. **Ease of Maintenance:** Changes in one part of the system are less likely to impact other parts.
2. **Reusability:** Highly cohesive classes can be more easily reused across different parts of the application or in different projects.
3. **Ease of Enhancement:** Adding new features or modifying existing ones is easier when classes are loosely coupled and highly cohesive, as changes are localized and do not ripple through the system.

