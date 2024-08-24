#include <iostream>

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  typedef struct Node {
    value_type value;
    Node* ptr_next;
    explicit Node(value_type value_in) noexcept
        : value(value_in), ptr_next(nullptr) {}
  } Node;
  Node* tail = nullptr;
  Node* head = nullptr;
  size_type m_size = 0;
  void clear() {
    while (head) pop();
    if (tail) tail = nullptr;
  }

 public:
  template <typename... Args>
  void emplace_back(Args&&... args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push(elem);
    }
  }
  queue() : tail(nullptr), head(nullptr), m_size(0){};
  queue(const std::initializer_list<value_type>& items) noexcept
      : tail(nullptr), head(nullptr), m_size(0) {
    for (value_type i : items) {
      push(i);
    }
  }
  queue(const queue& other) noexcept : tail(nullptr), head(nullptr), m_size(0) {
    *this = other;
  }
  queue(queue&& other) noexcept : tail(nullptr), head(nullptr), m_size(0) {
    *this = std::move(other);
  }
  ~queue() { clear(); }
  value_type At_(int i) const {
    if (i < 0 || i >= (int)m_size)
      throw std::out_of_range("Index out of range");
    value_type result = T();
    Node* tmp_head = head;
    for (int j = 0; j < i; j++) {
      tmp_head = tmp_head->ptr_next;
    }
    result = tmp_head->value;
    return result;
  }
  queue& operator=(const queue& other) noexcept {
    if (this != &other) {
      clear();
      size_type i = 0;
      while (i < other.m_size) {
        push(other.At_(i));
        i++;
      }
    }
    return *this;
  }

  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      clear();
      tail = other.tail;
      head = other.head;
      m_size = other.m_size;
      other.tail = nullptr;
      other.head = nullptr;
      other.m_size = 0;
    }
    return *this;
  }

  const_reference front() {
    if (!head) throw std::logic_error("queue is empty");
    return head->value;
  }
  const_reference back() {
    if (!tail) throw std::logic_error("queue is empty");
    return tail->value;
  }
  bool empty() { return m_size == 0; }
  size_type size() { return m_size; }
  void push(const_reference value) {
    Node* new_node = new Node(value);
    if (!head) {
      head = new_node;
      tail = new_node;
    } else if (!tail) {
      head->ptr_next = new_node;
      tail = new_node;
    } else {
      tail->ptr_next = new_node;
      tail = new_node;
    }
    ++m_size;
  }
  void pop() {
    if (!head) throw std::logic_error("queue is empty");
    Node* temp = head->ptr_next;
    delete head;
    head = temp;
    m_size--;
  }
  void swap(queue& other) noexcept {
    if (this != &other) {
      Node* tmp_tail = other.tail;
      Node* tmp_head = other.head;
      size_type tmp_size = other.m_size;
      if (head && other.head) {
        other.head = head;
        head = tmp_head;
      }

      if (tail && other.tail) {
        other.tail = tail;
        tail = tmp_tail;
      }
      other.m_size = m_size;
      m_size = tmp_size;
    }
  }
};
}  // namespace s21