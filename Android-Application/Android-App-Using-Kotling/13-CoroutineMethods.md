### **Coroutine Methods in Kotlin**

Kotlin coroutines come with several useful methods for controlling, managing, and monitoring their lifecycle. Here's a breakdown of some key methods:

#### **1. `isActive`**
- **Purpose**: A property available inside coroutines that checks whether the coroutine is still active. It returns `true` if the coroutine is still running, and `false` if it has been cancelled or completed.
  
```kotlin
CoroutineScope(Dispatchers.Default).launch {
    while (isActive) {
        // Perform some work
    }
}
```

#### **2. `join()`**
- **Purpose**: Suspends the current coroutine until the coroutine that called `join()` finishes its execution. It's a way to wait for another coroutine to complete.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    delay(1000)
    println("Coroutine completed")
}
job.join()  // Wait for the coroutine to finish
println("Joined after coroutine completion")
```

#### **3. `yield()`**
- **Purpose**: Suspends the current coroutine, allowing other coroutines to run. It gives the current thread (or dispatcher) to other coroutines if possible, effectively pausing the current coroutine for a brief moment.
  
```kotlin
CoroutineScope(Dispatchers.Default).launch {
    repeat(5) {
        println("Coroutine working")
        yield()  // Yield the thread to other coroutines
    }
}
```

#### **4. `ensureActive()`**
- **Purpose**: Checks whether the coroutine is active, and if not, it will throw a `CancellationException`. This is useful for checking and handling cancellation in long-running loops or operations.
  
```kotlin
CoroutineScope(Dispatchers.Default).launch {
    while (true) {
        ensureActive()  // Throws an exception if coroutine is cancelled
        // Perform some work
    }
}
```

#### **5. `cancelAndJoin()`**
- **Purpose**: Cancels the coroutine and then suspends the caller until the coroutine has finished cancellation. This ensures that the coroutine is fully cancelled before moving forward.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    delay(2000)
    println("Coroutine still running")
}
job.cancelAndJoin()  // Cancels and waits for completion
println("Coroutine cancelled and joined")
```

- **Behavior**:
  - The coroutine enters a "cancelling" state and will wait until it finishes this state before moving forward.
  - Once the coroutine is completely cancelled, the next part of the code proceeds.

#### **6. `await()`**
- **Purpose**: Awaits the result of a `Deferred` coroutine (created by `async`). It suspends until the `Deferred` result is ready, returning the result or throwing an exception if the coroutine failed.
  
```kotlin
val deferred = CoroutineScope(Dispatchers.Default).async {
    delay(1000)
    return@async "Result"
}
val result = deferred.await()
println(result)  // Outputs: Result
```

#### **7. `invokeOnCompletion()`**
- **Purpose**: Registers a handler that will be called once the coroutine's `Job` completes. The handler is invoked when the coroutine finishes, whether successfully or due to cancellation or failure.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    delay(1000)
}
job.invokeOnCompletion {
    println("Coroutine completed")
}
```

#### **8. `withContext()`**
- **Purpose**: Used to switch between different dispatchers (or contexts) within the same coroutine. It suspends the current coroutine, switches the context, and resumes execution in the new context.

```kotlin
CoroutineScope(Dispatchers.Default).launch {
    withContext(Dispatchers.IO) {
        // Perform IO work
    }
    // Switch back to the Default dispatcher
}
```

---

### **Cancellation Methods**

There are different ways to cancel coroutines depending on whether we want to wait for the cancellation process to finish or proceed immediately.

#### **1. Using `cancelAndJoin()`**
When using `cancelAndJoin()`, the coroutine:
1. Waits until the cancelling state of the coroutine is fully completed.
2. Proceeds to the next part of the code only after cancellation is fully done.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    delay(2000)
}
job.cancelAndJoin()  // Cancels and waits for completion
println("Cancelled and joined")
```

#### **2. Using `cancel()`**
When using `cancel()`, the coroutine:
1. Cancels the job and proceeds immediately to the next part of the code.
2. The cancellation state finishes later in the background.

```kotlin
val job = CoroutineScope(Dispatchers.Default).launch {
    delay(2000)
}
job.cancel()  // Cancels without waiting for completion
println("Cancelled without waiting")
```

---

### **Timeout in Coroutines**

Timeout is a common scenario where we might want to cancel a coroutine. Kotlin provides two coroutine builders for handling timeouts: `withTimeout` and `withTimeoutOrNull`.

#### **1. `withTimeout()`**
- **Purpose**: This builder lets the coroutine run for a specified amount of time. If it exceeds the time limit, it throws a `TimeoutCancellationException` and stops the coroutine.

```kotlin
try {
    withTimeout(1000) {
        delay(2000)
        println("This will not be printed")
    }
} catch (e: TimeoutCancellationException) {
    println("Timeout occurred")
}
```

- **Behavior**: If the time limit is exceeded, the coroutine is cancelled, and an exception is thrown.

#### **2. `withTimeoutOrNull()`**
- **Purpose**: This builder also runs a coroutine for a specified time, but instead of throwing an exception if the time is exceeded, it returns `null`.

```kotlin
val result = withTimeoutOrNull(1000) {
    delay(2000)
    "This will not be returned"
}
println(result)  // Outputs: null
```

- **Behavior**: If the time limit is exceeded, the coroutine is cancelled, but no exception is thrown, and the result is `null`.

---

### **Summary of Key Methods**

| **Method**              | **Description**                                                                 |
|-------------------------|---------------------------------------------------------------------------------|
| `isActive`              | Checks if the coroutine is still active.                                         |
| `join()`                | Waits for another coroutine to finish.                                           |
| `yield()`               | Yields the current thread to let other coroutines run.                           |
| `ensureActive()`        | Ensures the coroutine is active; throws an exception if cancelled.               |
| `cancelAndJoin()`       | Cancels the coroutine and waits until it is fully cancelled.                     |
| `await()`               | Waits for the result of a `Deferred` coroutine.                                  |
| `invokeOnCompletion()`  | Registers a callback that runs when the coroutine completes.                     |
| `withContext()`         | Switches between different coroutine contexts within the same coroutine.         |
| `cancel()`              | Cancels the coroutine but does not wait for the cancellation to complete.        |
| `withTimeout()`         | Cancels the coroutine after a specified timeout and throws an exception.         |
| `withTimeoutOrNull()`   | Cancels the coroutine after a specified timeout and returns `null` instead.      |

These methods provide fine-grained control over coroutine execution, cancellation, and lifecycle management.