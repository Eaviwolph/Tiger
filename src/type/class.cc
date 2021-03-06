/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <ostream>

#include <range/v3/algorithm/find.hpp>
#include <type/class.hh>
#include <type/visitor.hh>

namespace type
{
  Class::Class(const Class* super)
    : Type()
    , id_(fresh_id())
    , super_(super)
    , subclasses_()
  {}

  void Class::accept(ConstVisitor& v) const { v(*this); }

  void Class::accept(Visitor& v) { v(*this); }

  const Type* Class::attr_type(misc::symbol key) const
  {
    // FIXME: Some code was deleted here.
    for (auto e : super_->attrs_)
      {
        if (e.name_get() == key)
          return &e.type_get();
      }
    return nullptr;
  }

  const Type* Class::meth_type(misc::symbol key) const
  {
    // FIXME: Some code was deleted here.
    for (auto e : super_->meths_)
      {
        if (e->name_get() == key)
          return &e->type_get();
      }
    return nullptr;
  }

  // FIXME: Some code was deleted here (Find common super class).

  // FIXME: Some code was deleted here (Super class soundness test).

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Class).

  const Class& Class::object_instance()
  {
    // FIXME: Some code was deleted here.
  }

  unsigned Class::fresh_id()
  {
    static unsigned counter_ = 0;
    return counter_++;
  }

} // namespace type
