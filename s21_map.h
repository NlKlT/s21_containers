#include "s21_binary_tree.h"

namespace s21 {
template <typename K, typename V>
class map : public Tree<K, V> {
 public:
  // CONSTRUCTORS
  map() : Tree<K, V>() {};
  map(std::initializer_list<typename Tree<K, V>::value_type> const& items)
      : Tree<K, V>(items) {};
  map(const map& m) : Tree<K, V>(m) {};
  map(map&& m) noexcept : Tree<K, V>(std::move(m)) {};

  // DESTRUCTOR
  ~map() = default;

  // OVERLOAD OPERATORS
  map& operator=(map&& m) noexcept {
    Tree<K, V>::operator=(std::move(m));
    return *this;
  }

  V& operator[](const K& key) {
    if (!this->contains(key)) {
      std::pair<K, V> el{key, V()};
      std::pair<typename Tree<K, V>::Iterator, bool> res_it = this->insert(el);
      return res_it.first->second;
    } else {
      auto it = this->begin();
      for (; it != this->end(); ++it)
        if (it->first == key) return it->second;
      return it->second;
    }
  }

  // BASIC METHODS
  const V& at(const K& key) const {
    V& res = (V&)fake;
    auto tmp = this;
    At_(key, res, (map<K, V>*)tmp);
    return res;
  }
  std::pair<typename Tree<K, V>::Iterator, bool> insert(
      const typename Tree<K, V>::value_type& value) noexcept override {
    return Tree<K, V>::insert(value);
  }
  std::pair<typename Tree<K, V>::Iterator, bool> insert(const K& key,
                                                        const V& obj) {
    typename Tree<K, V>::Iterator it;
    bool is_inserted = false;
    std::pair<K, V> elem{key, obj};
    this->Insert_(elem, it, is_inserted);
    std::pair<typename Tree<K, V>::Iterator, bool> res = {it, is_inserted};
    return res;
  }
  std::pair<typename Tree<K, V>::Iterator, bool> insert_or_assign(
      const K& key, const V& obj) {
    std::pair<typename Tree<K, V>::Iterator, bool> res_it;
    res_it = insert(key, obj);
    if (!res_it.second) {
      auto it = this->begin();
      while (it->first != key) ++it;
      res_it.first.SetTree(it.GetTree());
      res_it.first->second = obj;
    }
    return res_it;
  }

 private:
  V fake = V();
  void At_(const K& key, V& res, map<K, V>* tr) const {
    if (!tr->root_ ||
        (!tr->left_ && !tr->right_ && tr->root_->element_.first != key))
      throw std::out_of_range("Key does not exist");

    if (key < tr->root_->element_.first) {
      map<K, V>::At_(key, res, (map<K, V>*)tr->left_);
    } else if (key > tr->root_->element_.first) {
      map<K, V>::At_(key, res, (map<K, V>*)tr->right_);
    } else {
      res = tr->root_->element_.second;
    }
  }
};
}  // namespace s21