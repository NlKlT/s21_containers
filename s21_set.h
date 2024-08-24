#include "s21_binary_tree.h"

namespace s21 {
template <typename K>

class set : public Tree<K, K> {
 public:
  using key_type = K;
  using value_type = K;
  using reference = K &;
  using const_reference = const K &;
  using size_type = size_t;

  using Tree<K, K>::insert;

  set() : Tree<K, K>() {}
  set(std::initializer_list<value_type> const &items) {
    for (value_type i : items) insert(i);
  };
  set(const set &s) : Tree<K, K>(s) {};
  set(set &&s) noexcept : Tree<K, K>(std::move(s)) {};
  ~set() = default;

  set &operator=(set &&s) noexcept {
    Tree<K, K>::operator=(std::move(s));
    return *this;
  }

 protected:
  class ConstSetIterator : public Tree<K, K>::ConstIterator {
   public:
    ConstSetIterator() noexcept : Tree<K, K>::ConstIterator() {}
    ConstSetIterator(const ConstSetIterator &other)
        : Tree<K, K>::ConstIterator(other) {}
    explicit ConstSetIterator(Tree<K, K> *tree) noexcept
        : Tree<K, K>::ConstIterator(tree) {}
    explicit ConstSetIterator(typename Tree<K, K>::ConstIterator &other) {
      Tree<K, K> *tr = other.GetTree();
      this->tree_ = tr;
    }

    ~ConstSetIterator() = default;

    ConstSetIterator &operator=(const ConstSetIterator &other) {
      ConstSetIterator tmp(other);
      this->tree_ = tmp.GetTree();
      return *this;
    }

    const_reference operator*() {
      typename Tree<K, K>::Node_ *rt = this->GetNode();
      return rt->element_.first;
    }
    const value_type *operator->() {}
  };

  class SetIterator : public ConstSetIterator {
   public:
    SetIterator() noexcept : ConstSetIterator() {}
    SetIterator(const SetIterator &other) : ConstSetIterator(other) {}
    explicit SetIterator(Tree<K, K> *tree) noexcept : ConstSetIterator(tree) {}
    explicit SetIterator(typename Tree<K, K>::Iterator &other) {
      Tree<K, K> *tr = other.GetTree();
      this->tree_ = tr;
    }

    ~SetIterator() = default;

    SetIterator &operator=(const SetIterator &other) {
      ConstSetIterator::operator=(other);
      return *this;
    }
  };

 public:
  using const_iterator = ConstSetIterator;
  using iterator = SetIterator;

  virtual std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<key_type, value_type> tmp_el{value, value};
    typename Tree<K, K>::iterator tree_it;
    bool is_inserted = false;
    std::pair<K, K> val{value, value};
    this->Insert_(val, tree_it, is_inserted);
    SetIterator set_it(tree_it);
    std::pair<SetIterator, bool> res{set_it, is_inserted};
    return res;
  }

  

  iterator begin() const {
    if (!this->left_ && !this->right_ && !this->root_)
      throw std::out_of_range("Tree does not exist");
    const Tree<K, K> *tmp_this = this;
    Tree<K, K> *min_tr = this->FindMin(this->left_ ? this->left_ : tmp_this);
    return SetIterator(min_tr);
  }
  iterator end() const {
    if (!this->left_ && !this->right_ && !this->root_)
      throw std::out_of_range("Tree does not exist");
    const Tree<K, K> *tmp_this = this;
    Tree<K, K> *max_tr = this->FindMax(this->right_ ? this->right_ : tmp_this);
    return SetIterator(max_tr);
  }
  iterator find(const K &key) const {
    if (!this->contains(key)) throw std::out_of_range("Key does not exist");
    auto it = begin();
    for (; *it != key; ++it);
    return it;
  }
  void erase(iterator pos) {
    typename Tree<K, K>::Iterator it;
    it.SetTree(pos.GetTree());
    Tree<K, K>::erase(it);
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res_set_vec;
    for (auto el : {std::forward<Args>(args)...})
      res_set_vec.push_back(set<K>::insert(el));
    return res_set_vec;
  }
};
}  // namespace s21
