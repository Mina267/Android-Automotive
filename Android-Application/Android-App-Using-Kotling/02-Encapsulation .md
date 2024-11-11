### Encapsulation in Kotlin

**Encapsulation** is one of the fundamental principles of object-oriented programming (OOP). It refers to the bundling of data (attributes) and behaviors (methods) within a single entity, typically a class. By doing this, you restrict direct access to some of the class's components and protect them from unwanted or unintended interference.

When we talk about encapsulation, the concept of **data hiding** often comes into play. In Kotlin (and many other languages), **access modifiers** such as `public`, `private`, `protected`, and `internal` are used to control the visibility and accessibility of class members (attributes and methods).

### Access Modifiers in Kotlin:

- **public**: The class or member is accessible from anywhere. This is the **default** modifier in Kotlin.
- **private**: The class or member is accessible only within the same class or file.
- **protected**: The class or member is accessible within the class and its subclasses (not applicable to top-level declarations).
- **internal**: The class or member is accessible within the same module.

Encapsulation helps prevent external misuse of a class's data by controlling how the data is accessed and modified.

### Declaring Properties in Kotlin:

Kotlin allows two ways to declare properties in a class:

1. **Within the primary constructor**:  
   When you declare properties inside the constructor (prefixed with `val` or `var`), you can control their visibility using access modifiers like `public` or `private`.
   - **`val`**: Declares a read-only property.
   - **`var`**: Declares a mutable property.
   
   Example:
   ```kotlin
   class Person(val name: String, private var age: Int) {
       fun getAge() = age
   }
   
   val person = Person("Alice", 25)
   println(person.name)  // Public property, accessible
   println(person.getAge())  // Accessing the private property through a method
   ```

2. **Within the class body**:  
   Properties can also be declared within the class body. When doing so, you can define **custom setters and getters** to control how the properties are accessed and modified.

   Example:
   ```kotlin
   class Rectangle {
       var width: Int = 0
       var height: Int = 0
       
       // Getter for area
       val area: Int
           get() = width * height
   }
   
   val rect = Rectangle()
   rect.width = 5
   rect.height = 10
   println("Area: ${rect.area}")  // Area: 50
   ```

### Setters and Getters in Kotlin:

Kotlin properties can have optional **getters** and **setters**, which allow you to control how a property's value is retrieved or modified. By default, Kotlin provides a **default getter and setter** for `var` properties and only a getter for `val` properties.

However, you can define custom getters and setters if needed. These are called automatically when you access or modify the property, except during initialization.

- **`field`**: Refers to the backing field, which stores the actual property value.
- **`value`**: Refers to the new value being assigned in the setter. You can use a custom name for `value`, but `value` is the default name.

#### Syntax for Setters and Getters:
```kotlin
var propertyName: PropertyType = initializer
    get() {
        // Custom getter logic
        return field
    }
    set(value) {
        // Custom setter logic
        field = value
    }
```

#### Example of Custom Getter and Setter:
```kotlin
class Circle {
    var radius: Double = 0.0
        set(value) {
            field = if (value < 0) 0.0 else value  // Prevent negative values
        }
    
    val circumference: Double
        get() = 2 * Math.PI * radius  // Custom getter for computed property
}

val circle = Circle()
circle.radius = -5.0  // Custom setter in action, will set radius to 0
println(circle.circumference)  // Custom getter, computes the circumference
```

### Important Points:
- **Getters** and **setters** are **optional** in Kotlin. If you don't provide them, Kotlin generates them for you by default.
- **Custom setters** are called every time a property is assigned a new value (except during initialization).
- **Custom getters** are called every time a property is accessed (except during initialization).
- **Backing field (`field`)**: Used in custom setters and getters to reference the actual property value stored in memory.

### Conclusion:
Encapsulation in Kotlin allows for controlled access to data through the use of properties, custom setters, and getters. By using access modifiers (`public`, `private`, etc.) and the ability to define custom behavior for property access, you can ensure that your data is only accessible and modifiable in the ways that you intend. This helps prevent unwanted or accidental changes to the state of an object, improving the robustness and reliability of your code.

---

### How Access Modifiers Affect Setters and Getters in Kotlin:

In Kotlin, **access modifiers** control the visibility of **setters** and **getters**, which determines whether they can be accessed or modified from outside the class. The access modifiers (`public`, `private`, `protected`, and `internal`) can be applied both to properties themselves and to the individual setter/getter functions, influencing how properties can be interacted with.

1. **Public (default)**:
   - If you declare a property without specifying an access modifier, it is `public` by default.
   - Both the **getter** and **setter** are public by default, meaning they can be accessed and modified from outside the class.
   - Example:
     ```kotlin
     class Person(var age: Int)  // Both getter and setter are public
     ```

   In the above example, you can read and modify the `age` property from any part of the code since it's public.

2. **Private**:
   - Declaring a property as `private` makes it accessible only within the class.
   - By default, the **getter and setter** for `private` properties are also `private`.
   - You can make only the **setter** private, allowing the property to be read from outside but not modified.
   - Example:
     ```kotlin
     class Person(private var age: Int)  // Property is private
     ```

   Here, the `age` property is hidden from the outside world. You can define a public getter to allow read access without exposing the setter.

   **Custom Getter/Setter Example**:
   ```kotlin
   class Person(var name: String, private var age: Int) {
       // Public getter for private property
       fun getAge() = age
   }

   val person = Person("Alice", 30)
   println(person.name)  // Public property, can be accessed
   println(person.getAge())  // Access private property through the getter
   ```

3. **Protected**:
   - **Protected** properties and methods are accessible within the class and its subclasses.
   - However, `protected` is not allowed for **top-level** declarations (i.e., properties or functions outside a class).
   - Example:
     ```kotlin
     open class Animal(protected var species: String)
     class Dog(species: String) : Animal(species) {
         fun getSpecies() = species  // Accessible due to protected modifier
     }
     ```

4. **Internal**:
   - **Internal** properties are visible within the same module (i.e., a group of related Kotlin files compiled together).
   - Both the **getter and setter** are `internal` by default when the property is declared as `internal`, meaning they are accessible across the module but hidden from outside the module.
   - Example:
     ```kotlin
     internal class Person(var age: Int)
     ```

### Modifying Setters and Getters Individually:
In Kotlin, you can specify different access modifiers for the **getter** and **setter**. For example, you can make a getter `public` and a setter `private`, allowing the property to be read from outside the class but only modified from within the class.

- **Example of Private Setter with Public Getter**:
  ```kotlin
  class Person(name: String, age: Int) {
      var age: Int = age
          private set  // Setter is private
  }

  val person = Person("John", 30)
  println(person.age)  // Can be accessed
  // person.age = 35  // Error: Cannot access private setter
  ```

In this case, the `age` property is readable (`public getter`), but it can only be modified inside the class (`private setter`), protecting it from external modification.

---

### Why Kotlin Automatically Generates Setters and Getters:

Kotlin generates default setters and getters for `var` and `val` properties because they provide a **clean and concise way** to work with properties while still ensuring **encapsulation** and control over property access. This auto-generation offers simplicity, while still allowing for flexibility with custom setters and getters when needed.

#### Default Behavior:
- **`val` properties**: By default, Kotlin generates a **getter** but not a setter because the value is immutable (read-only).
  ```kotlin
  class Person(val name: String)
  ```

  In this case, only a getter is generated since `val` is read-only.

- **`var` properties**: For `var` properties, both a getter and a setter are generated by default, allowing you to both read and modify the value.
  ```kotlin
  class Person(var age: Int)
  ```

  In this case, Kotlin provides both a getter (`getAge()`) and a setter (`setAge()`).

#### Why Kotlin Uses This Approach:
1. **Encapsulation**: Setters and getters allow properties to be accessed in a controlled manner. Even if a property is `public`, you can intercept every read or write operation by using custom setters or getters, thus maintaining **encapsulation**.
   
2. **Flexibility**: You can easily customize the behavior of properties. For example, if you need to validate a value before assigning it, you can write a custom setter. If you need to compute a value on the fly (like `area` of a rectangle), you can define a custom getter.

3. **Consistency**: By generating default setters and getters, Kotlin standardizes property access, ensuring that there is a uniform way to work with data, regardless of whether you’re directly accessing the field or using a function.

4. **Safety**: Generated setters and getters can help prevent direct manipulation of a property’s backing field, reducing the risk of bugs from unexpected state changes.

---

### Custom Setters and Getters Example:

Here’s an example where Kotlin generates default setters and getters, but custom logic can be added when necessary:

```kotlin
class Rectangle(var width: Int, var height: Int) {
    // Custom getter for area property
    val area: Int
        get() = width * height  // Calculated property

    // Custom setter for width with validation
    var safeWidth: Int = width
        set(value) {
            field = if (value > 0) value else 0  // Ensure positive width
        }
}

fun main() {
    val rect = Rectangle(5, 10)
    println("Area: ${rect.area}")  // 50

    rect.safeWidth = -5  // Will be set to 0 due to custom setter logic
    println("Safe Width: ${rect.safeWidth}")  // 0
}
```

In this example:
- A custom getter for `area` is defined that calculates the area dynamically.
- A custom setter for `safeWidth` is defined that ensures the width cannot be set to a negative value.

### Summary:
1. **Access Modifiers** control the visibility of the **setter** and **getter** in Kotlin. You can make properties private, protected, or internal, and even control the visibility of setters and getters separately.
   
2. **Kotlin automatically generates setters and getters** to reduce boilerplate code, while still giving you full control over property access when needed. This provides simplicity and flexibility, making it easier to work with properties in a concise and encapsulated manner.

3. **Encapsulation and data safety** are the primary reasons for using setters and getters. Even if Kotlin auto-generates them, they serve as a key tool for controlling how data is accessed and modified, ensuring that you can enforce validation and manage the internal state of objects effectively.