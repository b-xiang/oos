//
// Created by sascha on 12/10/15.
//

#ifndef OBJECT_HOLDER_HPP
#define OBJECT_HOLDER_HPP

#ifdef _MSC_VER
#ifdef oos_EXPORTS
    #define OOS_API __declspec(dllexport)
    #define EXPIMP_TEMPLATE
  #else
    #define OOS_API __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
  #endif
  #pragma warning(disable: 4251)
#else
#define OOS_API
#endif

#include "tools/cascade_type.hpp"
#include "tools/identifiable_holder.hpp"

#include <memory>

namespace oos {

namespace detail {
class object_inserter;
class object_deleter;
class object_proxy_accessor;
}

class basic_identifier;
class object_proxy;
class object_store;

/**
 * @class object_holder
 * @brief Base class for the serializable pointer and reference class
 *
 * This is the base class for the serializable pointer
 * and reference class. The class holds the proxy
 * of the serializable and the id of the serializable.
 */
class OOS_API object_holder : public identifiable_holder
{
protected:
  /**
   * @brief Creates and empty base pointer.
   * 
   * Creates and empty base pointer. The boolean
   * tells the class if the serializable is handled
   * as a reference or an pointer. The difference
   * is that the reference couldn't be deleted
   * from the object_store and the pointer can.
   * 
   * @param is_internal True if the pointer is used internal, which means
   *                    it is used to describe an entity.
   */
  explicit object_holder(bool is_internal);

  /**
   * Copies from another object_holder
   * 
   * @param x the object_holder to copy from.
   */
  object_holder(const object_holder &x);

  /**
   * Assign operator.
   * 
   * @param x The object_holder to assign from.
   */
  object_holder & operator=(const object_holder &x);

  /**
   * @brief Creates an object_holder with a given object_proxy
   * 
   * Creates an object_holder with a given object_proxy. The
   * boolean tells the object_holder if it should be
   * handled as an internal.
   * 
   * @param is_internal If true the serializable is handled as an internal.
   * @param op The object_proxy of the object_holder
   */
  object_holder(bool is_internal, object_proxy *op);

  /**
   * Destroys the object_holder
   * and decides wether the underlaying
   * object_proxy is destroyed as well.
   *
   * It is destroyed if it is not inserted
   * into any object_store.
   */
  virtual ~object_holder();

public:

  /**
   * Equal to operator for the object_holder
   * 
   * @param x The object_holder to check equality with.
   */
  bool operator==(const object_holder &x) const;

  /**
   * Not equal to operator for the object_holder
   * 
   * @param x The object_holder to check unequality with.
   */
  bool operator!=(const object_holder &x) const;

  /**
   * Resets the object_holder with the given object_proxy.
   * 
   * @param proxy The new object_proxy for the object_holder.
   * @param cascade Sets the cascadable actions for the proxy.
   */
  void reset(object_proxy *proxy, cascade_type cascade);

  /**
   * Resets the object_holder with the given
   * identifier. If the type of identifier differs
   * from internal type an exception is thrown
   *
   * @param id The identifier to set
   */
  void reset(const std::shared_ptr<basic_identifier> &id);

  /**
   * Returns if the serializable is loaded.
   * 
   * @return True if the serializable is loaded.
   */
  bool is_loaded() const;

  /**
   * Returns the serializable id.
   * 
   * @return The id of the serializable.
   */
  unsigned long id() const;

  /**
   * Sets the serializable id. If a proxy
   * is set an exception is thrown.
   * 
   * @param i The new serializable id
   */
  void id(unsigned long i);

  /**
   * Returns the corresponding
   * object_store or nullptr
   */
  object_store* store() const;

  /**
   * Returns the serializable
   * 
   * @return The serializable.
   */
  void* ptr();

  /**
   * Returns the serializable
   *
   * @return The serializable.
   */
  const void* ptr() const;

  /**
   * Returns the serializable
   * 
   * @return The serializable.
   */
  void* lookup_object();

  /**
   * Returns the serializable
   *
   * @return The serializable.
   */
  void* lookup_object() const;

  /**
   * Returns if this object_holder is inside
   * of the object_store. This is important
   * to calculate the reference and pointer
   * counter.
   * 
   * @return True if the object_holder internal
   */
  bool is_internal() const;

  /**
   * Returns true if the underlying object
   * is inserted in an object_store
   *
   * @return True if object is inserted.
   */
  bool is_inserted() const;

  /**
   * Returns true if serializable has a primary key
   *
   * @return true if serializable has a primary key
   */
  bool has_primary_key() const;

  /**
   * Gets the primary key of the foreign serializable
   *
   * @return The primary key of the foreign serializable
   */
  virtual std::shared_ptr<basic_identifier> primary_key() const;

  /**
   * Returns the current reference count
   *
   * @return The current reference count
   */
  unsigned long reference_count() const;

  /**
   * Return the type string of the object
   *
   * @return The type string of the object.
   */
  virtual const char* type() const = 0;

  /**
   * Prints the underlaying serializable
   *
   * @param out The output stream to write on.
   * @param x The serializable pointer to print.
   * @return The output stream.
   */
  friend OOS_API std::ostream& operator<<(std::ostream &out, const object_holder &x);

private:
  friend class object_serializer;
  friend class object_proxy;
  friend class detail::object_deleter;
  friend class detail::object_inserter;
  friend class object_store;
  friend class object_container;
  friend class detail::object_proxy_accessor;

  // Todo: change interface to remove friend
  friend class session;
  // Todo: replace private access of proxy with call to reset
  friend class table_reader;

  template < class T > friend class object_ptr;
  template < class T > friend class has_one;

  object_proxy *proxy_ = nullptr;
  cascade_type cascade_ = cascade_type::NONE;
  bool is_internal_ = false;
  bool is_inserted_ = false;
  unsigned long oid_ = 0;
};

}

#endif //OBJECT_HOLDER_HPP
