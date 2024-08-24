#include <iostream>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    value_type elem;
    Node* next;
    Node* prev;
    Node(const value_type& Aelem) : elem(Aelem), next(nullptr), prev(nullptr){};
  };

  Node* head = nullptr;
  Node* tail = nullptr;
  Node* fake = nullptr;
  size_type m_size = 0;

  void init_fake() {
    fake = new Node(T());
    fake->next = fake;
    fake->prev = fake;
  }

 public:
  list() : head(nullptr), tail(nullptr), m_size(0) { init_fake(); }
  list(size_type n) : list() {
    if (n <= 0) throw std::out_of_range("Index out of range");
    for (size_type i = 0; i < n; i++) {
      push_back(T());
    }
  }
  list(std::initializer_list<value_type> const& items) : list() {
    for (const value_type& item : items) {
      push_back(item);
    }
  }
  list(const list& other) : list() {
    for (Node* current = other.head; current != other.fake;
         current = current->next) {
      push_back(current->elem);
    }
  }
  list(list&& other) noexcept
      : head(other.head),
        tail(other.tail),
        fake(other.fake),
        m_size(other.m_size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.fake = nullptr;
    other.m_size = 0;
    other.init_fake();
  }
  ~list() {
    clear();
    delete fake;
  }

  void clear() {
    Node* temp = head;
    while (temp && temp != fake) {
      Node* next = temp->next;
      delete temp;
      temp = next;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    fake->next = fake;
    fake->prev = fake;
  }
  void push_back(const_reference temp) {
    Node* new_node = new Node(temp);
    if (!head) {
      head = tail = new_node;
      head->next = fake;
      head->prev = fake;
      fake->next = head;
      fake->prev = head;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      new_node->next = fake;
      fake->prev = new_node;
      tail = new_node;
    }
    m_size++;
  }
  list& operator=(const list& other) {
    if (this != &other) {
      clear();
      if (!fake) init_fake();
      Node* tmp_node = other.head;
      if (tmp_node) {
        while (tmp_node != other.fake) {
          push_back(tmp_node->elem);
          tmp_node = tmp_node->next;
        }
      }
    }
    return *this;
  }
  list& operator=(list&& other) noexcept {
    if (this != &other) {
      clear();
      delete fake;
      head = other.head;
      tail = other.tail;
      fake = other.fake;
      m_size = other.m_size;
      other.head = nullptr;
      other.tail = nullptr;
      other.fake = nullptr;
      other.m_size = 0;
      other.init_fake();
    }
    return *this;
  }
  const_reference front() const { return head ? head->elem : fake->elem; }
  const_reference back() const { return tail ? tail->elem : front(); }
  bool empty() const { return m_size == 0; }
  size_type size() const { return m_size; }
  size_type max_size() const {
    return (std::numeric_limits<std::size_t>::max() / sizeof(Node) / 2);
  }
  void pop_back() {
    if (empty()) {
      throw std::underflow_error("List is empty, cannot pop back");
    }
    if (tail) {
      Node* ptr = tail;
      if (tail == head) {
        head = tail = nullptr;
        fake->next = fake->prev = fake;
      } else {
        tail = tail->prev;
        tail->next = fake;
        fake->prev = tail;
      }
      delete ptr;
      m_size--;
    }
  }
  void push_front(const_reference value) {
    Node* new_node = new Node(value);
    if (!head) {
      head = tail = new_node;
      head->next = fake;
      head->prev = fake;
      fake->next = head;
      fake->prev = head;
    } else {
      new_node->next = head;
      new_node->prev = fake;
      head->prev = new_node;
      head = new_node;
      fake->next = head;
    }
    m_size++;
    fake->elem = m_size;
  }
  void pop_front() {
    if (empty()) {
      throw std::underflow_error("List is empty, cannot pop front");
    }
    Node* old_head = head;
    if (head == tail) {
      head = tail = nullptr;
      fake->next = fake->prev = fake;
    } else {
      head = head->next;
      head->prev = fake;
      fake->next = head;
    }

    delete old_head;
    m_size--;
    fake->elem = m_size;
  }
  void swap(list& other) {
    if (this != &other) {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(fake, other.fake);
      std::swap(m_size, other.m_size);
    }
  }
  void merge(list& other) {
    if (this == &other) return;
    Node* s_head = head;
    Node* o_head = other.head;
    if (m_size == 0) {
      s_head = fake;
    }
    if (other.m_size == 0) {
      o_head = other.fake;
    }
    list result;
    while (s_head != this->fake && o_head != other.fake) {
      if (s_head->elem <= o_head->elem) {
        result.push_back(s_head->elem);
        s_head = s_head->next;
      } else {
        result.push_back(o_head->elem);
        o_head = o_head->next;
      }
    }
    while (s_head != this->fake) {
      result.push_back(s_head->elem);
      s_head = s_head->next;
    }
    while (o_head != other.fake) {
      result.push_back(o_head->elem);
      o_head = o_head->next;
    }
    swap(result);
    other.clear();
  }
  void reverse() {
    if (m_size < 2) return;
    Node* current = head;
    Node* temp = nullptr;

    while (current != fake) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      if (temp == fake) {
        fake->prev = current;
      }
      current = current->prev;
    }
    temp = head;
    head = tail;
    tail = temp;
  }

  class ConstIterator {
   public:
    ConstIterator() noexcept { ptr = nullptr; };
    explicit ConstIterator(list::Node* node) noexcept { ptr = node; };
    ConstIterator(const ConstIterator& other) noexcept { ptr = other.ptr; };
    ~ConstIterator() = default;

    bool operator!=(const ConstIterator& other) const noexcept {
      return ptr != other.ptr;
    }

    bool operator==(const ConstIterator& other) const noexcept {
      return ptr == other.ptr;
    }

    ConstIterator& operator=(const ConstIterator& other) noexcept {
      if (this != &other) ptr = other.ptr;
      return *this;
    }

    const_reference operator*() noexcept { return ptr->elem; }

    ConstIterator operator++(int) noexcept {
      ConstIterator tmp(*this);
      Operation_(true);
      return tmp;
    }

    ConstIterator& operator++() noexcept {
      Operation_(true);
      return *this;
    }

    ConstIterator operator--(int) noexcept {
      ConstIterator tmp(*this);
      Operation_(false);
      return tmp;
    }

    ConstIterator& operator--() noexcept {
      Operation_(false);
      return *this;
    }

    ConstIterator operator+(size_type n) noexcept {
      auto it_tmp = *this;
      while (n-- > 0) it_tmp.Operation_(true);
      return it_tmp;
    }

    ConstIterator operator-(size_type n) noexcept {
      auto it_tmp = *this;
      while (n-- > 0) it_tmp.Operation_(false);
      return it_tmp;
    }

    ConstIterator& operator+=(size_type n) noexcept {
      while (n-- > 0) Operation_(true);
      return *this;
    }

    ConstIterator& operator-=(size_type n) noexcept {
      while (n-- > 0) Operation_(false);
      return *this;
    }

    Node* GetNode_() const noexcept { return ptr; }

   protected:
    Node* ptr;
    void Operation_(bool isPlus) noexcept {
      if (isPlus)
        ptr = ptr->next;
      else
        ptr = ptr->prev;
    }
  };

  class Iterator : public ConstIterator {
   public:
    Iterator() noexcept : ConstIterator(){};
    explicit Iterator(Node* node) noexcept : ConstIterator(node){};
    Iterator(const Iterator& other) noexcept : ConstIterator(other){};
    ~Iterator() = default;

    Iterator& operator=(const Iterator& other) noexcept {
      if (this != &other) this->ptr = other.ptr;
      return *this;
    }

    reference operator*() noexcept { return (reference)this->ptr->elem; }
  };
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(fake); }

  iterator insert(iterator pos, const_reference value) {
    Node* cur_node = GetIteratorNode_(pos);
    auto* new_node_ = new Node(value);
    if (m_size <= 1) {
      if (cur_node == fake)
        push_back(value);
      else if (cur_node == head)
        push_front(value);
      delete new_node_;
      new_node_ = nullptr;
      return Iterator(head);
    } else {
      Node* prev_node = cur_node->prev;
      new_node_->prev = prev_node;
      new_node_->next = cur_node;
      cur_node->prev = new_node_;
      prev_node->next = new_node_;
      if (cur_node == fake)
        tail = new_node_;
      else if (cur_node == head)
        head = new_node_;
      ++m_size;
    }
    return Iterator(new_node_);
  }
  void erase(iterator pos) {
    Node* ptr = GetIteratorNode_(pos);
    if (ptr == fake) return;
    if (ptr == head) {
      pop_front();
    } else if (ptr == tail) {
      pop_back();
    } else {
      Node* prev = ptr->prev;
      Node* next = ptr->next;
      prev->next = next;
      next->prev = prev;
      delete ptr;
      m_size--;
    }
  }
  void splice(const iterator pos, list& other) {
    if (this != &other) {
      for (auto itr = other.begin(); itr != other.end(); ++itr)
        insert(pos, *itr);
      other.clear();
    }
  }
  void sort() {
    if (m_size > 1) {
      list new_list;
      while (m_size > 0) {
        iterator min = begin();
        for (iterator it = begin(); it != end(); ++it) {
          if (*it < *min) min = it;
        }
        new_list.push_back(*min);
        erase(min);
      }
      swap(new_list);
    }
  }
  void unique() {
    if (m_size < 2) return;
    iterator cur = begin();
    iterator it = begin();
    ++it;
    for (; it != end();) {
      if (*it == *cur) {
        iterator del_it = it;
        ++it;
        erase(del_it);
      } else {
        cur = it;
        ++it;
      }
    }
  }

 private:
  Node* GetIteratorNode_(const_iterator iter) const noexcept {
    return iter.GetNode_();
  }
};

}  // namespace s21