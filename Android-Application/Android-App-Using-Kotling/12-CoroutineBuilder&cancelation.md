### **Coroutine Builders** in Kotlin

Coroutine builders are functions used to create coroutines. These functions take **suspending lambdas** as arguments and start the execution of coroutines within different contexts. The most commonly used coroutine builders in Kotlin are `launch`, `async`, and `runBlocking`.

#### **1. `launch`**
- **Purpose**: Used when we want to create a coroutine but do **not expect a return value**. This is a "fire and forget" coroutine.
- **Job Reference**: It returns a `Job` object, which can be used to reference the coroutine, cancel it, or check its status.
  
```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    // Coroutine body
    println("Launching a coroutine")
}
job.cancel()  // You can cancel the coroutine if needed
```

- **Key Features**:
  - **Fire-and-forget**: Doesn't return a result.
  - The calling code does not wait for the coroutine to complete unless you explicitly use `job.join()`.

#### **2. `async`**
- **Purpose**: Used when we want the coroutine to **return a value**. It returns a `Deferred<T>` object, which represents a future result. To retrieve the result, you call `await()`.
  
```kotlin
val deferred = CoroutineScope(Dispatchers.Default).async {
    // Coroutine body
    delay(1000)
    "Result from async"
}
val result = deferred.await()  // Waiting for the result
println(result)  // Outputs: Result from async
```

- **Key Features**:
  - Returns a `Deferred<T>` object.
  - You call `await()` to get the result when the coroutine completes.
  - Like `launch`, it's non-blocking but allows for result retrieval.

#### **3. `runBlocking`**
- **Purpose**: Runs a new coroutine **and blocks the current thread** until its completion. This is generally used only in **unit tests or main functions** to bridge the gap between coroutine-based code and traditional blocking code.
  
```kotlin
runBlocking {
    println("Start")
    delay(1000)
    println("End")
}
```

- **Key Features**:
  - Blocks the current thread until the coroutine finishes.
  - Used for creating coroutines in non-coroutine environments (e.g., in the `main` function).

---

### **Coroutine Scope**

A **CoroutineScope** is an environment that defines the lifecycle and context of a coroutine. It helps in managing when coroutines start, cancel, and complete. **All coroutines must be launched within a scope**.

- **Example**:
```kotlin
val scope = CoroutineScope(Dispatchers.Default)
scope.launch {
    // Coroutine body
}
```

The **lifecycle** of coroutines is tied to their scope. When a scope is cancelled, all coroutines running within it are also cancelled.

---

### **Suspend Function**

A **suspend function** is a special type of function that can be paused and resumed later. It allows the execution to be suspended without blocking a thread.

#### **Syntax**:
```kotlin
suspend fun doSomething() {
    delay(1000)  // Suspends the execution for 1 second
}
```

#### **Calling Suspend Functions**:
- **Suspend functions can only be called** from another coroutine or another suspend function.
- You can't call a suspend function directly from regular code.

---

### **Structured Concurrency**

Kotlin coroutines follow the principle of **structured concurrency**, meaning that coroutines are tied to a specific scope, and their **lifecycle** is managed within that scope. This helps avoid memory leaks and ensures proper management of coroutines.

#### Key Aspects of Structured Concurrency:
1. **Scopes ensure coroutines don’t leak**: A coroutine launched in a scope cannot outlive that scope.
2. **Parent coroutines wait for their children**: A parent coroutine won’t finish until all its child coroutines complete.
3. **Proper error reporting**: If an error occurs in a child coroutine, it is propagated and reported in the parent coroutine.

```kotlin
val parentJob = CoroutineScope(Dispatchers.Default).launch {
    launch {
        delay(1000)
        println("Child Coroutine")
    }
    println("Parent Coroutine")
}
```

---

### **Jobs and Parent-Child Relationships**

A **Job** is a handle to the coroutine. It’s part of the coroutine’s context and helps manage its lifecycle (e.g., cancellation, status checking).

- **Parent-Child Relationship**: When a coroutine launches another coroutine, the launched coroutine becomes the **child** of the parent. The parent coroutine cannot complete until all of its children are complete.
  
- **Hierarchy**: If a parent coroutine is cancelled, all its children are cancelled. If a child throws an unhandled exception, it can propagate to the parent.

```kotlin
val parentJob = CoroutineScope(Dispatchers.Default).launch {
    val childJob = launch {
        delay(1000)
        println("Child coroutine")
    }
}
parentJob.cancel()  // Cancels the parent and the child
```

---

### **Cancelling Coroutines**

Sometimes we need to cancel coroutines to prevent resource wastage or improper behavior. Kotlin provides structured concurrency, which allows you to cancel a parent coroutine and cancel all of its child coroutines.

- **Cancellation of a Specific Coroutine**: You can cancel a specific coroutine using its `Job`.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    // Coroutine body
}
job.cancel()  // Cancels this specific coroutine
```

- **Non-Cancellable Context**: If you need to perform some work even when a coroutine is cancelled, you can use `withContext(NonCancellable)` to ensure that code runs no matter what.

```kotlin
withContext(NonCancellable) {
    // Code that should always execute
}
```

---

### **Cooperative Cancellation**

Cancellation in Kotlin coroutines is **cooperative**. This means that the coroutine must periodically check if it has been cancelled. If it doesn't, it might not stop when you cancel it.

Two ways to ensure cooperative cancellation:
1. **Use built-in suspending functions** like `delay()`, `yield()`, which automatically check for cancellation.
2. **Manually check for cancellation** using `isActive` within long-running loops or tasks.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    while (isActive) {
        // Work to be done
    }
}
```

---

### **Cancellation Exceptions**

When a coroutine is cancelled, it throws a `CancellationException`. This exception can be used to:
1. **Release resources**: Close files, network connections, etc.
2. **Show cancellation reason**: Provide a message explaining the cancellation.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    try {
        delay(10000)
    } catch (e: CancellationException) {
        println("Coroutine was cancelled")
    }
}
job.cancel(CancellationException("Cancelled by user"))
```

---

### **Conclusion:**

1. **Coroutine Builders** (`launch`, `async`, `runBlocking`) are used to create coroutines with different purposes (fire-and-forget, expecting a result, blocking).
2. **Coroutine Scope** is a key concept that manages the lifecycle of coroutines.
3. **Suspend Functions** are special functions that allow non-blocking asynchronous code execution.
4. **Structured Concurrency** ensures coroutines are managed safely within a scope, preventing leaks and improper error handling.
5. **Jobs** manage coroutines’ lifecycles, including cancellation.
6. **Cancellation** can be done cooperatively, and coroutines should be designed to handle cancellation properly to free up resources.

