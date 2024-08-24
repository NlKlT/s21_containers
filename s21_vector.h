#include <iostream>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

 private:
  size_t m_size{};
  size_t m_capacity{};
  T* arr{nullptr};

 public:
  vector();  // стандартный конструктор
  explicit vector(size_type n);  // конструктор с заданным размером вектора
  vector(std::initializer_list<value_type> const&
             items);  // конструктор со списком инициализации
  vector(const vector& other);  // конструктор копирования
  vector(vector&& other);       // конструктор переноса
  ~vector();                    // деструктор
  s21::vector<T>& operator=(
      s21::vector<T>&& other);  // Оператор присваивания перемещения
  // vector& operator=(
  //     vector&& other);
  reference at(
      size_type index);  // возвращает ссылку на указанный элемент по индексу
  reference operator[](size_type index);  // доступ к элементу по индексу
  const_reference front();  // возвращает ссылку на первый элемент
  const_reference back();  // возвращает ссылку на последний элемент
  iterator data() noexcept;  // возвращает указатель на данные массива
  iterator begin();  // возвращает указатель на начало вектора
  iterator end();  // возвращает указатель на следующий после конце элемент
  bool empty() const noexcept;  // ture - если вктор пуст, иначе false
  size_type size();             // гетер размера вектора
  void reserve(size_type size);  // зарезервировать больше памяти
  size_type capacity();  // гетер вместимости вектора
  void shrink_to_fit();  // уменьшение разера (очистка не используемой памяти)
  void clear();          // очищает вектор
  iterator insert(
      const_iterator pos,
      const_reference value);  // вставляет в указанное место элемент,
                               // возвращает указатель это место
  iterator erase(iterator pos);  // удаляет элемент,по указанной позиции и
                                 // возвращает указатель на эту позицию
  void push_back(const_reference value);  // добавляет элемент в конец вектора
  void pop_back();  // удаляет последний элемент из вектора
  void swap(vector& other) noexcept;  // обмен значениями с другим вектором
};

// стандартный конструктор
template <typename T>
vector<T>::vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
// конструктор с заданным размером вектора
template <typename T>
vector<T>::vector(size_type n)
    : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
// конструктор со списком инициализации
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : m_size(items.size()),
      m_capacity(items.size()),
      arr(items.size() ? new T[items.size()] : nullptr) {
  std::copy(items.begin(), items.end(), arr);
}
// конструктор копирования
template <typename T>
vector<T>::vector(const vector& other) {
  m_size = other.m_size;
  m_capacity = other.m_capacity;
  arr = new T[m_capacity];
  std::copy(other.arr, other.arr + m_size, arr);
}
// конструктор переноса
template <typename T>
vector<T>::vector(vector&& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), arr(other.arr) {
  other.m_size = 0U;
  other.m_capacity = 0U;
  other.arr = nullptr;
}
// деструктор
template <typename T>
vector<T>::~vector() {
  delete[] arr;
}
// Оператор присваивания перемещения
template <typename T>
s21::vector<T>& s21::vector<T>::operator=(s21::vector<T>&& other) {
  if (this != &other) {
    this->swap(other);
  }
  return *this;
}

// возвращает ссылку на указанный элемент по индексу
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= m_size) {
    throw std::out_of_range("Index out of range");
  }
  if (m_size == 0) throw std::out_of_range("Index out of range");
  return arr[pos];
}
// доступ к элементу по индексу

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= m_size) {
    throw std::out_of_range("Index out of range");
  }
  return arr[pos];
}
// возвращает ссылку на первый элемент
template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (m_size == 0) throw std::out_of_range("Index out of range");
  return arr[0];
}
// возвращает ссылку на последний элемент
template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return arr[m_size - 1];
}
// возвращает указатель на данные массива
template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::data() noexcept {
  return arr;
}
// возвращает указатель на начало вектора
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return arr;
}
// возвращает указатель на следующий после конце элемент
template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return arr + m_size;
}
// ture - если вктор пуст, иначе false

template <typename T>
bool vector<T>::empty() const noexcept {
  return m_size == 0;
}
// гетер размера вектора
template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return m_size;
}
// зарезервировать больше памяти
template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= m_capacity) return;
  m_capacity = size ? size : 1;
  T* temp = new T[m_capacity];
  if (arr != nullptr) {
    for (size_type i = 0; i < m_size; i++) {
      temp[i] = arr[i];
    }
    delete[] arr;
  }
  arr = temp;
}
// гетер вместимости вектора
template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return m_capacity;
}
// уменьшение разера (очистка не используемой памяти)
template <typename T>
void vector<T>::shrink_to_fit() {
  if (m_capacity > m_size) {
    T* new_arr = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
      new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    m_capacity = m_size;
  }
}
// очищает вектор
template <typename T>
void vector<T>::clear() {
  delete[] arr;
  m_size = 0;
  m_capacity = 0;
}
// вставляет в указанное место элемент, возвращает указатель это место

template <typename T>
T* vector<T>::insert(const_iterator pos, const_reference value) {
  if (pos < arr || pos > arr + m_size) {
    throw std::out_of_range("Position out of range");
  }
  size_t index = pos - arr;
  if (m_size == m_capacity) {
    reserve(m_size + 1);
  }
  std::copy_backward(arr + index, arr + m_size, arr + m_size + 1);
  arr[index] = value;
  ++m_size;
  return arr + index;
}
// удаляет элемент,по указанной позиции и возвращает указатель на эту позицию

template <typename T>
T* vector<T>::erase(iterator pos) {
  if (pos < arr || pos >= arr + m_size) {
    throw std::out_of_range("Position out of range");
  }
  size_t index = pos - arr;
  std::copy(arr + index + 1, arr + m_size, arr + index);
  --m_size;
  return arr + index;
}
// добавляет элемент в конец вектора
template <typename T>
void vector<T>::push_back(const_reference value) {
  if (m_size == m_capacity) {
    reserve(m_size + 1);
  }
  arr[m_size++] = value;
}
// удаляет последний элемент из вектора
template <typename T>
void vector<T>::pop_back() {
  if (m_size > 0) {
    m_size--;
  }
  // shrink_to_fit();
}
// обмен значениями с другим вектором
template <typename T>
void vector<T>::swap(vector& other) noexcept {
  std::swap(m_size, other.m_size);
  std::swap(m_capacity, other.m_capacity);
  std::swap(arr, other.arr);
}
}  // namespace s21
