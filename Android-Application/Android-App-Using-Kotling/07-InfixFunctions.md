### Infix Functions

**Infix functions** in Kotlin allow you to write function calls in a more readable way, without the need for the dot (`.`) and parentheses (`()`), which makes the code more natural when calling specific operations.

#### Requirements for Infix Functions:
1. They must be **member functions** or **extension functions**.
2. They must have a **single parameter**.
3. The parameter must **not accept variable arguments** and **must not have a default value**.

#### Example:
```kotlin
infix fun Int.shl(x: Int): Int {
    return this.shl(x)  // Shift left (bitwise)
}

fun main() {
    val result = 1 shl 2  // Using infix notation
    println(result)       // Output: 4 (binary shift left operation)
}
```

Here, the function `shl` (shift left) is defined as an infix function. It can be called either using the infix notation (`1 shl 2`) or the regular function call notation (`1.shl(2)`).

#### Precedence of Infix Functions:
- **Lower precedence** than arithmetic operators (`+`, `-`, `*`, `/`), type casts, and the `rangeTo` operator (`..`).
- **Higher precedence** than boolean operators (`&&`, `||`), `is`, `in` checks, and a few other operators.

#### Explicit `this`:
When calling an infix function on the current receiver, you can use `this` explicitly to avoid ambiguity:

```kotlin
class Person(val name: String) {
    infix fun greet(other: Person) {
        println("${this.name} greets ${other.name}")
    }
}

fun main() {
    val person1 = Person("Mina")
    val person2 = Person("Magdy")
    
    person1 greet person2  // Mina greets Magdy
}
```

---

### Operator Overloading

Kotlin supports **limited operator overloading**, allowing you to provide custom implementations for a **predefined set of operators** on specific types.

#### Rules for Operator Overloading:
1. **Limited set of operators** can be overloaded.
2. Operators have **predefined symbolic representations** and **precedence**.
3. Functions that overload operators must be marked with the `operator` modifier.
4. Overloaded operators must be defined using a **member function** or an **extension function**.

#### Unary Prefix Operators:
- `+a`, `-a`, `!a`
- Corresponding functions: `unaryPlus()`, `unaryMinus()`, `not()`

```kotlin
data class Point(val x: Int, val y: Int) {
    operator fun unaryMinus() = Point(-x, -y)
}

fun main() {
    val point = Point(10, 20)
    val negatedPoint = -point  // Calls operator function
    println(negatedPoint)      // Output: Point(x=-10, y=-20)
}
```

#### Increments and Decrements:
- `a++`, `a--`
- Corresponding functions: `inc()`, `dec()`

#### Binary Operations:
- `+`, `-`, `*`, `/`, `%`
- Corresponding functions: `plus()`, `minus()`, `times()`, `div()`, `rem()`

```kotlin
operator fun Point.plus(other: Point) = Point(x + other.x, y + other.y)

fun main() {
    val point1 = Point(1, 2)
    val point2 = Point(3, 4)
    
    val result = point1 + point2  // Calls plus() operator
    println(result)               // Output: Point(x=4, y=6)
}
```

#### `in` and `!in` operators:
- Corresponding functions: `contains()`
  
```kotlin
data class Box(val items: List<String>)

operator fun Box.contains(item: String): Boolean {
    return items.contains(item)
}

fun main() {
    val box = Box(listOf("apple", "banana"))
    println("apple" in box)  // Output: true
    println("cherry" !in box) // Output: true
}
```

#### Indexed Access Operator:
- `a[i]`
- Corresponding function: `get(index)`

```kotlin
class Matrix(val rows: Int, val cols: Int) {
    private val matrix = Array(rows) { IntArray(cols) }

    operator fun get(row: Int, col: Int): Int {
        return matrix[row][col]
    }
}

fun main() {
    val matrix = Matrix(2, 2)
    println(matrix[0, 0])  // Calls get(row, col)
}
```

#### Invoke Operator:
- `a()`
- Corresponding function: `invoke()`

```kotlin
class Greeter(val greeting: String) {
    operator fun invoke(name: String) {
        println("$greeting, $name!")
    }
}

fun main() {
    val greeter = Greeter("Hello")
    greeter("Mina")  // Calls invoke function
    // Output: Hello, Mina!
}
```

#### Augmented Assignment Operators:
- `+=`, `-=`, `*=`, `/=`, `%=`
- Corresponding functions: `plusAssign()`, `minusAssign()`, `timesAssign()`, `divAssign()`, `remAssign()`

```kotlin
class Counter(var count: Int) {
    operator fun plusAssign(value: Int) {
        count += value
    }
}

fun main() {
    val counter = Counter(0)
    counter += 5  // Calls plusAssign()
    println(counter.count)  // Output: 5
}
```

#### Comparison Operators:
- `==`, `!=`, `>`, `<`, `>=`, `<=`
- Corresponding functions: `equals()`, `compareTo()`

---

### Summary

- **Infix functions** allow more readable function calls without dots and parentheses and must meet specific requirements.
- **Operator overloading** lets you provide custom implementations for predefined operators by defining functions with specific names and marking them with the `operator` modifier.
