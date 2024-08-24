#include <iostream>

template <class T>
class vector {
 private:
  size_t m_size{};
  size_t m_capacity{};
  T* arr{nullptr};

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

 private:
  void reserve_more_capacity(
      const size_type& size) {  // зарезервировать больше памяти
    if (size <= m_capacity) return;
    m_capacity = size ? size * 2 : 1;
    T* temp = new T[m_capacity];
    if (arr != nullptr) {
      for (size_type i = 0; i < m_size; i++) {
        if (arr[i]) temp[i] = arr[i];
      }
      delete[] arr;
    }
    arr = temp;
  }
  void shrink_to_fit() {
    if (m_capacity >
        m_size) {  // уменьшение разера (очистка не используемой памяти)
      T* new_arr = new T[m_size];
      for (size_t i = 0; i < m_size; ++i) {
        new_arr[i] = arr[i];
      }
      delete[] arr;
      arr = new_arr;
      m_capacity = m_size;
    }
  }

 public:
  vector(vector&& other) noexcept
      : m_size(other.m_size),
        m_capacity(other.m_capacity),
        arr(other.arr) {  // конструктор переноса
    other.m_size = 0;
    other.m_capacity = 0;
    other.arr = nullptr;
  }
  vector(const vector& other) {  // конструктор копирования
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    arr = new T[m_capacity];
    std::copy(other.arr, other.arr + m_size, arr);
  }
  vector(size_type n,
         const T& value) {  // конструктор, создающий вектор заданного размера и
                            // инициализирующий все элементы заданным значением
    m_size = n;
    m_capacity = 2 * n;
    n ? arr = new T[n] : arr = nullptr;
    if (arr != nullptr) {
      for (size_t i = 0; i < m_size; i++) {
        arr[i] = value;
      }
    }
  }
  vector()
      : m_size(0U), m_capacity(0U), arr(nullptr) {}  // стандартный конструктор
  explicit vector(size_type n)
      : m_size(n),
        m_capacity(n),
        arr(n ? new T[n]
              : nullptr) {  // конструктор с заданным размером вектора
  }
  vector(std::initializer_list<value_type> const& items)
      : m_size(items.size()),
        m_capacity(items.size() * 2),
        arr(items.size() ? new T[items.size()]
                         : nullptr) {  // конструктор со списком инициализации
    std::copy(items.begin(), items.end(), arr);
  }
  ~vector() { delete[] arr; }  // деструктор
  size_type size() const {     // гетер размера вектора
    return m_size;
  }
  size_type capacity() const {  // гетер вместимости вектора
    return m_capacity;
  }
  void resize(size_t count) {  // Изменение размера вектора
    if (m_size == count) return;
    size_t old_size = m_size;
    reserve_more_capacity(count);
    T* temp = new T[m_capacity];
    size_t copy_size = count < old_size ? count : old_size;
    for (size_t i = 0; i < copy_size; i++) {
      temp[i] = arr[i];
    }
    for (size_t i = old_size; i < count; i++) {
      temp[i] = T();
    }
    delete[] arr;
    arr = temp;
    m_size = count;
  }
  void resize(
      size_t count,
      const T& value) {  // Изменение размера вектора и заполнение значением
    if (m_size == count) return;
    size_t old_size = m_size;
    reserve_more_capacity(count);
    T* temp = new T[m_capacity];
    size_t copy_size = count < old_size ? count : old_size;
    for (size_t i = 0; i < copy_size; i++) {
      temp[i] = arr[i];
    }
    for (size_t i = old_size; i < count; i++) {
      temp[i] = value;
    }
    delete[] arr;
    arr = temp;
    m_size = count;
  }
  T& operator[](size_t index) {  // доступ к элементу по индексу
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    return arr[index];
  }
  const T& operator[](size_t index) const {  // доступ к элементу по индексу
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    return arr[index];
  }
  void push_back(const T& value) {  // добавляет элемент в конец вектора
    if (m_size == m_capacity) {
      reserve_more_capacity(m_size + 1);
    }
    arr[m_size++] = value;
  }
  void push_back(T&& value) {  // добавляет временный элемент в конец вектора
    if (m_size == m_capacity) {
      reserve_more_capacity(m_size + 1);
    }
    arr[m_size++] = value;
  }
  void pop_back() {  // удаляет последний элемент из вектора
    if (m_size > 0) {
      m_size--;
    }
    shrink_to_fit();
  }
  vector& operator=(const vector& other) {  // оператор присваивания копирования
    if (this != &other) {
      delete[] arr;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      arr = new T[m_capacity];
      std::copy(other.arr, other.arr + m_size, arr);
    }
    return *this;
  }
  vector& operator=(
      vector&& other) noexcept {  // ператор присваивания перемещения
    if (this != &other) {
      delete[] arr;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      arr = other.arr;
      other.m_size = 0;
      other.m_capacity = 0;
      other.arr = nullptr;
    }
    return *this;
  }
  bool empty() { return m_size == 0; }  // ture - если вктор пуст, иначе false
  T& at(size_t index) {  // возвращает ссылку на указанный элемент по индексу
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    if (m_size == 0) throw std::out_of_range("Index out of range");
    return arr[index];
  }
  T& front() {  // возвращает ссылку на первый элемент
    if (m_size == 0) throw std::out_of_range("Index out of range");
    return arr[0];
  }
  const T& front() const {  // возвращает ссылку на первый элемент
    if (m_size == 0) throw std::out_of_range("Index out of range");
    return arr[0];
  }
  T& back() {
    return arr[m_size - 1];
  }  // возвращает ссылку на последний элемент
  const T& back() const {
    return arr[m_size - 1];
  }  // возвращает ссылку на последний элемент
  T& data() noexcept { return arr; }  // возвращает указатель на данные массива
  const T& data() const noexcept {
    return arr;
  }  // возвращает указатель на данные массива
  void clear() {  // очищает вектор
    delete[] arr;
    m_size = 0;
    m_capacity = 0;
  }
  iterator begin() noexcept {
    return arr;
  }  // возвращает указатель на начало вектора
  const_iterator begin() const noexcept { return arr; }  // cosnt версия begin
  iterator end() noexcept {
    return arr + m_size;
  }  // возвращает указатель на следующий после конце элемент
  const_iterator end() const noexcept {
    return arr + m_size;
  }                                    // const версия end a
  void swap(vector& other) noexcept {  // обмен значениями с другим вектором
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(arr, other.arr);
  }
  iterator insert(const_iterator pos,
                  const T& value) {  // вставляет в указанное место элемент,
                                     // возвращает указатель это место
    if (pos < arr || pos > arr + m_size) {
      throw std::out_of_range("Position out of range");
    }
    size_t index = pos - arr;
    if (m_size == m_capacity) {
      reserve_more_capacity(m_size + 1);
    }
    std::copy_backward(arr + index, arr + m_size, arr + m_size + 1);
    arr[index] = value;
    ++m_size;
    return arr + index;
  }

  iterator erase(const_iterator pos) {  // удаляет элемент,по указанной позиции
                                        // и возвращает указатель на эту позицию
    if (pos < arr || pos >= arr + m_size) {
      throw std::out_of_range("Position out of range");
    }

    size_t index = pos - arr;

    std::copy(arr + index + 1, arr + m_size, arr + index);
    --m_size;

    return arr + index;
  }

  iterator erase(
      const_iterator first,
      const_iterator last) {  // удаляет диапозон элементов, возвращает
                              // указатель на начало диапозона
    if (first < arr || first >= arr + m_size || last < arr ||
        last >= arr + m_size || first > last) {
      throw std::out_of_range("Position out of range");
    }

    size_t indexF = first - arr;
    size_t indexL = last - arr;

    std::copy(arr + indexL, arr + m_size, arr + indexF);
    m_size -= (indexL - indexF);

    return arr + indexF;
  }
};