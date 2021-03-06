//
// Created by sascha on 1/15/16.
//

#ifndef OOS_HAS_MANY_VECTOR_HPP
#define OOS_HAS_MANY_VECTOR_HPP

#include "object/basic_has_many.hpp"
#include "object/object_store.hpp"

#include <vector>

namespace oos {

/// @cond OOS_DEV

template < class T >
struct has_many_iterator_traits<T, std::vector, typename std::enable_if<!std::is_scalar<T>::value>::type>
  : public std::iterator<std::random_access_iterator_tag, T>
{
  typedef has_many_iterator_traits<T, std::vector> self;
  typedef object_ptr<T> value_type;
  typedef has_many_item<T> item_type;
  typedef has_one<item_type> internal_type;
  typedef object_ptr<item_type> relation_type;
  typedef std::vector<internal_type, std::allocator<internal_type>> container_type;
  typedef typename container_type::iterator container_iterator;
  typedef typename container_type::const_iterator const_container_iterator;
  typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
};

template < class T >
struct has_many_iterator_traits<T, std::vector, typename std::enable_if<std::is_scalar<T>::value>::type>
  : public std::iterator<std::random_access_iterator_tag, T>
{
  typedef has_many_iterator_traits<T, std::vector> self;
  typedef T value_type;
  typedef has_many_item<T> item_type;
  typedef has_one<item_type> internal_type;
  typedef object_ptr<item_type> relation_type;
  typedef std::vector<internal_type, std::allocator<internal_type>> container_type;
  typedef typename container_type::iterator container_iterator;
  typedef typename container_type::const_iterator const_container_iterator;
  typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
};

/// @endcond

/**
 * @brief Represents a has many iterator
 *
 * Represents a has many iterator for a has many
 * relationship with std::vector container
 *
 * @tparam T The type of the iterator/container
 */
template < class T >
class has_many_iterator<T, std::vector>
  : public has_many_iterator_traits<T, std::vector>
{
private:
  typedef has_many_iterator_traits<T, std::vector> traits;
  typedef typename traits::item_type item_type;
  typedef typename traits::internal_type internal_type;
  typedef typename traits::relation_type relation_type;
  typedef typename traits::container_type container_type;

public:
  typedef has_many_iterator<T, std::vector> self;                               /**< Shortcut value self */
  typedef typename traits::value_type value_type;                             /**< Shortcut value type */
  typedef typename traits::difference_type difference_type;                   /**< Shortcut to the difference type*/
  typedef typename traits::container_iterator container_iterator;             /**< Shortcut to the internal container iterator */
  typedef typename traits::const_container_iterator const_container_iterator; /**< Shortcut to the internal const container iterator */

public:
  /**
   * @brief Creates an empty has many iterator
   */
  has_many_iterator() {}

  /**
   * @brief Copy constructs an iterator from another iterator
   *
   * @param iter The iterator to copy from
   */
  has_many_iterator(const self &iter) : iter_(iter.iter_) {}

  /**
   * @brief Creates a has many iterator from given internal container iterator
   *
   * @param iter The iterator to create the has many iterator from
   */
  explicit has_many_iterator(container_iterator iter) : iter_(iter) {}

  /**
   * @brief Copy assign an iterator from another iterator
   *
   * @param iter The iterator to copy from
   * @return A reference to self
   */
  has_many_iterator& operator=(const self &iter)
  {
    iter_ = iter.iter_;
    return *this;
  }
  ~has_many_iterator() {}

  /**
   * @brief Compares equality iterator with another iterator.
   *
   * Compares iterator with another iterator. If other iterator contain
   * the same element true es returned.
   *
   * @param i The iterator to compare with
   * @return True if iterators contain the same element
   */
  bool operator==(const self &i) const { return (iter_ == i.iter_); }

  /**
   * @brief Compares unequality iterator with another iterator.
   *
   * Compares iterator with another iterator. If other iterator doesn't
   * contain the same element true es returned.
   *
   * @param i The iterator to compare with
   * @return True if iterators doesn't contain the same element
   */
  bool operator!=(const self &i) const { return !this->operator==(i); }

  /**
   * @brief Returns the difference of two iterators a and b.
   *
   * @param a The minuend iterator
   * @param b The subtrahend iterator
   * @return The difference between both iterators
   */
  friend difference_type operator-(self a, self b) { return a.iter_ - b.iter_; }

  /**
   * @brief Pre increments self
   *
   * @return A reference to incremented self
   */
  self& operator++()
  {
    ++iter_;
    return *this;
  }

  /**
   * @brief Post increments iterator
   *
   * Post increments iterator and returns a
   * new iterator object.
   *
   * @return Returns new incremented iterator
   */
  self operator++(int)
  {
    self tmp = *this;
    ++iter_;
    return tmp;
  }

  /**
   * @brief Pre decrements self
   *
   * @return A reference to decremented self
   */
  self& operator--()
  {
    --iter_;
    return *this;
  }

  /**
   * @brief Post decrements iterator
   *
   * Post decrements iterator and returns a
   * new iterator object.
   *
   * @return Returns new decremented iterator
   */
  self operator--(int)
  {
    --iter_;
    return self();
  }

  self& operator+=(difference_type offset)
  {
    iter_ += offset;
    return *this;
  }

  self& operator-=(difference_type offset)
  {
    iter_ -= offset;
    return *this;

  }

  self operator+(difference_type offset)
  {
    self tmp = *this;
    return tmp += offset;
  }

  self operator-(difference_type offset)
  {
    self tmp = *this;
    return tmp -= offset;
  }

  friend const self operator+(difference_type offset, self out)
  {
    out.iter_ += offset;
    return out;
  }

  value_type operator->() const { return (*iter_)->value(); }
  value_type operator*() const { return (*iter_)->value(); }
  value_type get() const { return (*iter_)->value(); }

private:
  friend class has_many<T, std::vector>;
  friend class const_has_many_iterator<T, std::vector>;
  friend class basic_has_many<T, std::vector>;
  friend class object_serializer;
  friend class detail::object_inserter;

  relation_type relation_item() const { return *iter_; }

  container_iterator iter_;
};

/// @cond OOS_DEV

template < class T >
struct const_has_many_iterator_traits<T, std::vector, typename std::enable_if<!std::is_scalar<T>::value>::type>
  : public std::iterator<std::random_access_iterator_tag, T>
{
  typedef has_many_iterator_traits<T, std::vector> self;
  typedef object_ptr<T> value_type;
  typedef has_many_item<T> item_type;
  typedef has_one<item_type> internal_type;
  typedef object_ptr<item_type> relation_type;
  typedef std::vector<internal_type, std::allocator<internal_type>> container_type;
  typedef typename container_type::iterator container_iterator;
  typedef typename container_type::const_iterator const_container_iterator;
  typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
};

template < class T >
struct const_has_many_iterator_traits<T, std::vector, typename std::enable_if<std::is_scalar<T>::value>::type>
  : public std::iterator<std::random_access_iterator_tag, T>
{
  typedef has_many_iterator_traits<T, std::vector> self;
  typedef T value_type;
  typedef has_many_item<T> item_type;
  typedef has_one<item_type> internal_type;
  typedef object_ptr<item_type> relation_type;
  typedef std::vector<internal_type, std::allocator<internal_type>> container_type;
  typedef typename container_type::iterator container_iterator;
  typedef typename container_type::const_iterator const_container_iterator;
  typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
};

/// @endcond

/**
 * @brief Represents a const has many iterator
 *
 * Represents a const has many iterator for a has many
 * relationship with std::vector container
 *
 * @tparam T The type of the iterator/container
 */
template < class T >
class const_has_many_iterator<T, std::vector>
  : public const_has_many_iterator_traits<T, std::list>
{
private:
  typedef const_has_many_iterator_traits<T, std::vector> traits;
  typedef typename traits::item_type item_type;
  typedef typename traits::internal_type internal_type;
  typedef typename traits::relation_type relation_type;
  typedef typename traits::container_type container_type;

public:
  typedef const_has_many_iterator<T, std::vector> self;                       /**< Shortcut value self */
  typedef typename traits::value_type value_type;                             /**< Shortcut value type */
  typedef typename traits::difference_type difference_type;                   /**< Shortcut to the difference type*/
  typedef typename traits::container_iterator container_iterator;             /**< Shortcut to the internal container iterator */
  typedef typename traits::const_container_iterator const_container_iterator; /**< Shortcut to the internal const container iterator */

public:
  /**
   * @brief Creates an empty const has many iterator
   */
  const_has_many_iterator() {}

  /**
   * @brief Creates a const has many iterator from given internal container iterator
   *
   * @param iter The iterator to create the const has many iterator from
   */
  explicit const_has_many_iterator(container_iterator iter) : iter_(iter) {}

  /**
   * @brief Creates a const has many iterator from given internal const container iterator
   *
   * @param iter The const iterator to create the const has many iterator from
   */
  explicit const_has_many_iterator(const_container_iterator iter) : iter_(iter) {}

  /**
   * @brief Creates a const has many iterator from a has many iterator
   *
   * @param iter The iterator to create the const has many iterator from
   */
  const_has_many_iterator(const has_many_iterator<T, std::vector> &iter) : iter_(iter.iter_) {}

  /**
   * @brief Copy assigns a new const has many iterator
   *
   * @param iter The iterator to be copy assigned from
   * @return Reference to the created iterator
   */
  const_has_many_iterator& operator=(const self &iter)
  {
    iter_ = iter.iter_;
    return *this;
  }

  /**
   * @brief Copy assigns a new const has many iterator
   *
   * Copy assigns a new const has many iterator from
   * a non const has many iterator
   *
   * @param iter The iterator to be copy assigned from
   * @return Reference to the created iterator
   */
  const_has_many_iterator& operator=(const has_many_iterator<T, std::vector> &iter)
  {
    iter_ = iter.iter_;
    return *this;
  }
  ~const_has_many_iterator() {}

  /**
   * @brief Compares equality iterator with another iterator.
   *
   * Compares iterator with another iterator. If other iterator contain
   * the same element true es returned.
   *
   * @param i The iterator to compare with
   * @return True if iterators contain the same element
   */
  bool operator==(const self &i) const { return (iter_ == i.iter_); }

  /**
   * @brief Compares unequality iterator with another iterator.
   *
   * Compares iterator with another iterator. If other iterator doesn't
   * contain the same element true es returned.
   *
   * @param i The iterator to compare with
   * @return True if iterators doesn't contain the same element
   */
  bool operator!=(const self &i) const { return !this->operator==(i); }

  /**
   * @brief Pre increments self
   *
   * @return A reference to incremented self
   */
  self& operator++()
  {
    ++iter_;
    return *this;
  }

  /**
   * @brief Post increments iterator
   *
   * Post increments iterator and returns a
   * new iterator object.
   *
   * @return Returns new incremented iterator
   */
  self operator++(int)
  {
    self tmp = *this;
    ++iter_;
    return tmp;
  }

  /**
   * @brief Pre decrements self
   *
   * @return A reference to decremented self
   */
  self& operator--()
  {
    --iter_;
    return *this;
  }

  /**
   * @brief Post decrements iterator
   *
   * Post decrements iterator and returns a
   * new iterator object.
   *
   * @return Returns new decremented iterator
   */
  self operator--(int)
  {
    --iter_;
    return self();
  }

  /**
   * @brief Increments iterator with offset
   *
   * @param offset The offset to be incremented
   * @return Reference to incremented iterator
   */
  self& operator+=(difference_type offset)
  {
    iter_ += offset;
    return *this;
  }

  /**
   * @brief Decrements iterator with offset
   *
   * @param offset The offset to be decremented
   * @return Reference to decremented iterator
   */
  self& operator-=(difference_type offset)
  {
    iter_ -= offset;
    return *this;

  }

  /**
   * @brief Increments iterator with offset
   *
   * @param offset The offset to be incremented
   * @return New incremented iterator
   */
  self operator+(difference_type offset) const
  {
    self tmp = *this;
    return tmp += offset;
  }

  /**
   * @brief Decrements iterator with offset
   *
   * @param offset The offset to be decremented
   * @return New decremented iterator
   */
  self operator-(difference_type offset) const
  {
    self tmp = *this;
    return tmp -= offset;
  }

  friend const self operator+(difference_type offset, self out)
  {
    out.iter_ += offset;
    return out;
  }

  const value_type operator->() const { return get(); }
  const value_type operator*() const { return get(); }
  const value_type get() const { return (*iter_)->value(); }
private:
  friend class has_many<T, std::vector>;
  friend class basic_has_many<T, std::vector>;
  friend class object_serializer;
  friend class detail::object_inserter;

  const relation_type relation_item() const { return *iter_; }

  const_container_iterator iter_;
};

/**
 * @brief Has many relation class using a std::vector as container
 *
 * The has many relation class uses a std::vector as internal
 * container to store the objects.
 *
 * It provides all main interface functions std::vector provides
 * - insert element at a iterator position
 * - access with bracket operator []
 * - push back an element
 * - erase an element at iterator position
 * - erase a range of elements within first and last iterator position
 * - clear the container
 *
 * All of these methods are wrappes around the std::vector methods plus
 * the modification in the corresponding object_store and notification
 * of the transaction observer
 *
 * The relation holds object_ptr elements as well as scalar data elements.
 *
 * @tparam T The type of the elements
 */
template < class T >
class has_many<T, std::vector> : public basic_has_many<T, std::vector>
{
public:
  typedef basic_has_many<T, std::vector> base;                     /**< Shortcut to self */
  typedef typename base::iterator iterator;                        /**< Shortcut to iterator type */
  typedef typename base::value_type value_type;                    /**< Shortcut to value_type */
  typedef typename base::item_type item_type;                      /**< Shortcut to item_type */
  typedef typename base::size_type size_type;                      /**< Shortcut to size_type */
  typedef typename base::relation_type relation_type;              /**< Shortcut to relation_type */

private:
  typedef typename base::container_iterator container_iterator;

public:
  /**
   * @brief Creates an empty has_many object
   *
   * Creates an empty has_many object with a
   * std::vector as container type
   */
  has_many() {}

  /**
   * @brief Inserts an element at the given position.
   *
   * @param pos The position to insert at
   * @param value The element to be inserted
   * @return The iterator at position of inserted element
   */
  iterator insert(iterator pos, const value_type &value)
  {
    // create new has_many
    if (indexed_) {

    }
    item_type *item = create_item(value);
    relation_type iptr(item);
    if (this->ostore_) {
      this->ostore_->insert(iptr);
      this->mark_modified_owner_(*this->ostore_, this->owner_);
    }
    return iterator(this->container_.insert(pos.iter_, iptr));
  }

  /**
   * @brief Inserts an element at last position.
   *
   * @param value The element to be inserted
   */
  void push_back(const value_type &value)
  {
    insert(this->end(), value);
  }

  /**
   * @brief Returns the element at specified location index.
   *
   * Returns the element at specified location index.
   * No bounds checking is performed.
   *
   * @param index Indx of the element to return
   * @return The requested element.
   */
  value_type operator[](size_type index)
  {
    return this->container_[index]->value();
  }

  /**
   * @brief Returns the const element at specified location index.
   *
   * Returns the const element at specified location index.
   * No bounds checking is performed.
   *
   * @param index Indx of the element to return
   * @return The requested const element.
   */
  const value_type operator[](size_type index) const
  {
    return this->container_[index]->value();
  }

  /**
   * @brief Clears the vector
   */
  void clear()
  {
    erase(this->begin(), this->end());
  }

  /**
   * @brief Remove the element at given position.
   *
   * Erase the element at given position and return the iterator
   * following the last removed element.
   *
   * @param i Iterator to the element to remove
   * @return Iterator following the last removed element
   */
  iterator erase(iterator i)
  {
    if (this->ostore_) {
      relation_type iptr = i.relation_item();
      this->ostore_->remove(iptr);
    }
    container_iterator ci = this->container_.erase(i.iter_);
    return iterator(ci);
  }

  /**
   * @brief Remove the elements of given range.
   *
   * Remove the elements of the given range identified
   * by the first and last iterator position. Where the first
   * iterator is included and the last iterator is not included
   * [first; last)
   *
   * @param start First iterator of the range
   * @param end Last iterator of the range
   * @return Iterator following the last removed element
   */
  iterator erase(iterator start, iterator end)
  {
    iterator i = start;
    if (this->ostore_) {
      while (i != end) {
          typename base::relation_type iptr = (i++).relation_item();
          this->ostore_->remove(iptr);
      }
    }
    return iterator(this->container_.erase(start.iter_, end.iter_));
  }

private:
  item_type* create_item(const value_type &value)
  {
    return new item_type(this->owner_field_, this->item_field_, this->owner_id_, value);
  }

private:
  bool indexed_ = false;
};

}
#endif //OOS_HAS_MANY_VECTOR_HPP
