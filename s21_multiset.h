#include "s21_set.h"

namespace s21 {
template <typename K>
class multiset : public set<K> {
 public:
  using key_type = typename set<K>::key_type;
  using value_type = typename set<K>::value_type;

  multiset() : set<K>() {}
  multiset(std::initializer_list<value_type> const &items) : set<K>(items) {}
  multiset(const multiset &s) : set<K>(s) {};
  multiset(multiset &&s) noexcept : set<K>(std::move(s)) {};
  ~multiset() = default;

  multiset &operator=(multiset &&s) noexcept {
    set<K>::operator=(std::move(s));
    return *this;
  }

  std::pair<typename set<K>::iterator, bool> Insert(
      const value_type &value) noexcept {
    std::pair<key_type, value_type> tmp_el{value, value};
    typename Tree<K, K>::iterator tree_it;
    bool is_inserted = false;
    std::pair<K, K> val{value, value};
    this->MultiSetInsert_(val, tree_it, is_inserted);
    typename set<K>::SetIterator set_it(tree_it);
    std::pair<typename set<K>::SetIterator, bool> res{set_it, is_inserted};
    return res;
  }
};
}  // namespace s21
