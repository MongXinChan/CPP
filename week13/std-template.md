# C++ Standard Library - `std::` Containers and Utilities

## 1. `std::basic_string`
- **Description**: A sequence container that stores and manipulates sequences of characters or character-like objects.
- **Usage**:
  ```cpp
  std::string str = "Hello, World!";
  ```

## 2. `std::array`
- **Description**: A container that encapsulates fixed-size arrays.
- **Template Parameters**:
  - `T`: The type of elements stored in the array.
  - `N`: The size of the array (fixed at compile time).
- **Example**:
  ```cpp
  std::array<int, 3> a2 = {1, 2, 3};
  ```

## 3. `std::list`
- **Description**: A doubly-linked list container.
- **Template Parameters**:
  - `T`: The type of elements stored in the list.
  - `Allocator`: The allocator used to manage memory (default is `std::allocator<T>`).
- **Usage**:
  ```cpp
  std::list<int> myList = {1, 2, 3, 4};
  ```

## 4. `std::set`
- **Description**: A container that stores unique elements in sorted order.
- **Template Parameters**:
  - `Key`: The type of elements stored in the set.
  - `Compare`: The comparison function used to sort elements (default is `std::less<Key>`).
  - `Allocator`: The allocator used to manage memory (default is `std::allocator<Key>`).
- **Usage**:
  ```cpp
  std::set<int> mySet = {1, 2, 3, 4};
  ```

## 5. `std::vector`
- **Description**: A dynamic array container that can grow and shrink in size.
- **Template Parameters**:
  - `T`: The type of elements stored in the vector.
  - `Allocator`: The allocator used to manage memory (default is `std::allocator<T>`).
- **Usage**:
  ```cpp
  std::vector<int> myVector = {1, 2, 3, 4};
  ```

## 6. `std::map`
- **Description**: A container that stores key-value pairs in sorted order by key.
- **Template Parameters**:
  - `Key`: The type of the keys.
  - `T`: The type of the values.
  - `Compare`: The comparison function used to sort keys (default is `std::less<Key>`).
  - `Allocator`: The allocator used to manage memory (default is `std::allocator<std::pair<const Key, T>>`).
- **Usage**:
  ```cpp
  std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};
  ```

## 7. `std::stack`
- **Description**: A container adapter that provides a LIFO (last-in, first-out) data structure.
- **Template Parameters**:
  - `T`: The type of elements stored in the stack.
  - `Container`: The underlying container used to store elements (default is `std::deque<T>`).
- **Usage**:
  ```cpp
  std::stack<int> myStack;
  myStack.push(1);
  myStack.push(2);
  ```
