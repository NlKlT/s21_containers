#include <iostream>

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  typedef struct Node {
    value_type value;
    Node* ptr_prev;
    explicit Node(value_type value_in) noexcept
        : value(value_in), ptr_prev(nullptr) {}
  } Node;
  size_type m_size{};
  Node* tail{nullptr};

  void clear() {
    while (tail) pop();
  }

 public:
  // Стандартный конструктор по умолчанию
  stack() : m_size(0U), tail(nullptr) {}
  // Констурктор инициализации
  stack(std::initializer_list<value_type> const& items) noexcept
      : m_size(0), tail(nullptr) {
    for (value_type i : items) {
      push(i);
    }
  }
  // Консруктор копирования
  stack(const stack& other) : m_size(other.m_size), tail(nullptr) {
    if (other.tail) {
      tail = new Node(other.tail->value);
      Node* ptr = other.tail->ptr_prev;
      ;
      Node* ptr_curr = tail;
      while (ptr) {
        Node* new_node = new Node(ptr->value);
        ptr_curr->ptr_prev = new_node;
        ptr_curr = new_node;
        ptr = ptr->ptr_prev;
      }
      ptr_curr->ptr_prev = nullptr;
    }
  }
  //Конструктор перемещения
  stack(stack&& other) : m_size(other.m_size), tail(nullptr) {
    if (other.tail) {
      tail = other.tail;
      other.tail = nullptr;
      other.m_size = 0;
    }
  }
  // Деструктор
  ~stack() { clear(); }
  stack& operator=(stack&& other) noexcept {
    if (this != &other) {
      clear();
      tail = other.tail;
      m_size = other.m_size;
      other.tail = nullptr;
      other.m_size = 0;
    }
    return *this;
  }
  const_reference top() const {
    if (!tail) throw std::logic_error("stack if empty");
    return tail->value;
  }
  bool empty() const noexcept { return m_size == 0; }
  size_type size() const noexcept { return m_size; }
  void push(const_reference value) noexcept {
    Node* new_node = new Node(value);
    if (!tail) {
      tail = new_node;
    } else {
      new_node->ptr_prev = tail;
      tail = new_node;
    }
    m_size++;
  }
  void pop() {
    if (!tail) throw std::logic_error("stack is empty");
    Node* tmp = tail->ptr_prev;
    delete tail;
    tail = tmp;
    m_size--;
  }
  void swap(stack& other) noexcept {
    if (this != &other) {
      Node* tmp = other.tail;
      other.tail = tail;
      tail = tmp;
      size_type t = other.m_size;
      other.m_size = m_size;
      m_size = t;
    }
  }
};
}  // namespace s21