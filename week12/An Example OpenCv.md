# Example in OpenCV

## Derived cv::Mat_

- Template matrix class derived from cv::Mat, a wrapper around the OpenCV matrix data structure, more C++ style .

cv::Matx

- A template  class for small matrices whose type and size are konwn at compilation time.

<img src=".\md-png\An example 1.png" alt="An example 1" style="zoom:50%;" />

> [!tip]
> In Computer-Vision, generally, we use a small matrix to represent a small image.
> We use the `Vector` to represent a small matrix.

## cv::Vec

- We define a class called `Vec`,it is a template class.
- Its base class is `Matx`,and `<Tp,cn,1>` means that the type of the matrix is `Tp`,and the number of channels is `cn`,and the number of rows is `1`.

<img src=".\md-png\An example 2.png" alt="An example 2" style="zoom:50%;" />

Such as:

```cpp
Vec<float,3>xyz(1.2f,2.3f,3.4f);
```

It means that the type of the matrix is `float` type, and the number of channels is `3`, and the number of rows is `1`(*because default 1*) .

### Comvined with typedef

<img src=".\md-png\An example 3.png" alt="An example 3" style="zoom:50%;" />

We could have the same effect as the `Vec3f` type.

```cpp
typedef Vec<float,3>Vec3f;
```
And there are some other types:

<img src=".\md-png\An example 4.png" alt="An example 4" style="zoom:50%;" />
```cpp
Matx33f m(1,2,3,
        4,5,6,
        7,8,9);
cout<<sum(Mat(m*m.t()))<<endl;
```