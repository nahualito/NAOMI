/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 3/10/98 8:31 PM                                  $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  tree.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_TREE_H
#define MSIPL_TREE_H

/*
Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen, 
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990), 
except that

 (1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin (), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union, 
etc.);

 (2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.
*/

#include <mcompile.h>

#include <memory>       // hh 971220 fixed MOD_INCLUDE
#include <algobase.h>   // hh 971220 fixed MOD_INCLUDE
#include <functional>   // hh 971220 fixed MOD_INCLUDE

// hh 980111 commented out.  Not needed
//#ifdef MSIPL_ANSI_HEADER
//#include <stdexcept>    // hh 971220 fixed MOD_INCLUDE
//#else
//#include <mexcept.h>    // hh 971220 fixed MOD_INCLUDE
//#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
	namespace std {
#endif

#define TREE_TEMPLATE template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
#define RB_TREE_TYPE rb_tree<Key, Value, KeyOfValue, Compare, Allocator>

template <class Key, class Value, class KeyOfValue, 
          class Compare, class DEFTEMPARG (Allocator, allocator<Value>) >
class rb_tree {

public:
// forward declarations/friend declarations/typedefs
     struct rb_tree_node;
     class iterator; friend class iterator;
     class const_iterator; friend class const_iterator;
     typedef ALLOC_BIND (rb_tree_node) rb_tree_node_allocator_type;
     enum color_type {red, black};

     typedef          Key                                key_type;
     typedef          Value                              value_type;
     typedef          Allocator                          allocator_type;
     typedef typename Allocator::pointer                 pointer;
     typedef typename Allocator::const_pointer           const_pointer;
     typedef typename Allocator::reference               reference;
     typedef typename Allocator::const_reference         const_reference;
     typedef reverse_iterator<const_iterator>            const_reverse_iterator;
     typedef reverse_iterator<iterator>                  reverse_iterator;
     typedef typename rb_tree_node_allocator_type::pointer   link_type;
     typedef typename rb_tree_node_allocator_type::size_type size_type;
     typedef typename rb_tree_node_allocator_type::difference_type 
                                                             difference_type;
     typedef pair<iterator, bool> pair_iterator_bool;
     typedef pair<iterator, iterator> pair_iterator_iterator;
     typedef pair<const_iterator, const_iterator> pair_citerator_citerator;

     struct rb_tree_node {
          Value value;
          color_type color;
          link_type parent;
          link_type left;
          link_type right;
     };

     class iterator 
     : public MSIPLSTD::iterator<bidirectional_iterator_tag, 
                                        Value, difference_type, pointer, reference>
     {
          friend class const_iterator;
          friend class rb_tree<Key, Value, KeyOfValue, Compare, Allocator>;

     protected:
          link_type node;
          RB_TREE_TYPE *ptr_to_rbtree;
          DEC_OBJ_LOCK(*iter_mutex)

          iterator (const RB_TREE_TYPE *p)
               : node (NULL) , ptr_to_rbtree ((RB_TREE_TYPE*)p)
     #ifdef MSIPL_OBJECT_LOCK
               , iter_mutex (&(ptr_to_rbtree->_mutex))
     #endif
          {}

     public:
          iterator ()
               : node (NULL) , ptr_to_rbtree (NULL)
     #ifdef MSIPL_OBJECT_LOCK
               , iter_mutex (0)
     #endif
          {}

          iterator (link_type x, const RB_TREE_TYPE *p)
               : node (x) , ptr_to_rbtree ((RB_TREE_TYPE*)p)
     #ifdef MSIPL_OBJECT_LOCK
               , iter_mutex (&(ptr_to_rbtree->_mutex))
     #endif
          {}

          ~iterator () {}

          bool operator== (const iterator& y) const
          {
               READ_LOCK(*iter_mutex);
               { READ_LOCK(*(y.iter_mutex));
               return node == y.node; }
          }
          bool operator== (const const_iterator& y) const
          {
               READ_LOCK(*iter_mutex);
               { READ_LOCK(*(y.citer_mutex));
               return node == y.node; }
          }
          bool operator!= (const iterator& y) const
          {
               READ_LOCK(*iter_mutex);
               { READ_LOCK(*(y.iter_mutex));
               return node != y.node; }
          }
          bool operator!= (const const_iterator& y) const
          {
               READ_LOCK(*iter_mutex);
               { READ_LOCK(*(y.citer_mutex));
               return node != y.node; }
          }
          reference operator* () const
          {
               READ_LOCK(*iter_mutex);
               return node->value;
          }
          pointer operator-> () const
          {
               READ_LOCK(*iter_mutex);
               return &(operator* ());
          }
          iterator& operator++ ()
          {
               WRITE_LOCK(*iter_mutex);
               if (node->right != NULL) {
                    node = node->right;
                    while (node->left != NULL)
                         node = node->left;
               }
               else {
                    link_type y = node->parent;
                    while (node == y->right) {
                         node = y;
                         y = y->parent;
                    }
                    if (node->right != y)
                         node = y;
               }
               return *this;
          }
          iterator operator++ (int)
          {
               iterator tmp = *this; 
               ++*this;
               return tmp;
          }
          iterator& operator-- ()
          {
               WRITE_LOCK(*iter_mutex);
               if (node->color == red && node->parent->parent == node)
                    node = node->right;
               else if (node->left != NULL) {
                         link_type y = node->left;
                         while (y->right != NULL)
                              y = y->right;
                         node = y;
               }
               else {
                    link_type y = node->parent;
                    while (node == y->left) {
                         node = y;
                         y = y->parent;
                    }
                    node = y;
               }
               return *this;
          }
          iterator operator-- (int)
          {
               iterator tmp = *this; 
               --*this;
               return tmp;
          }
     };

     class const_iterator 
     : public MSIPLSTD::iterator<bidirectional_iterator_tag, 
                                 Value, difference_type, const_pointer, const_reference>   // hh 980105 changed pointer & reference to const versions
     {
          friend class rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator;  // hh 980105 Added qualified name to iterator
          friend class rb_tree<Key, Value, KeyOfValue, Compare, Allocator>;

     protected:
          link_type node;
          RB_TREE_TYPE *ptr_to_rbtree;
          DEC_OBJ_LOCK(*citer_mutex)

          const_iterator (const RB_TREE_TYPE *p)
               : node (NULL), ptr_to_rbtree ((RB_TREE_TYPE*)p)
     #ifdef MSIPL_OBJECT_LOCK
                 , citer_mutex (&(ptr_to_rbtree->_mutex))
     #endif
          {}

     public:
          const_iterator ()
               : node (NULL), ptr_to_rbtree (NULL)
     #ifdef MSIPL_OBJECT_LOCK
                 , citer_mutex (0)
     #endif
          {}

          const_iterator (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator& x)  // hh 980105 Added qualified name to iterator
               : node (x.node), ptr_to_rbtree (x.ptr_to_rbtree)
     #ifdef MSIPL_OBJECT_LOCK
                 , citer_mutex (x.iter_mutex)
     #endif
          {}

          const_iterator (link_type x, const RB_TREE_TYPE *p)
               : node (x), ptr_to_rbtree ((RB_TREE_TYPE*)p)
     #ifdef MSIPL_OBJECT_LOCK
                 , citer_mutex (&(ptr_to_rbtree->_mutex))
     #endif
          {}

          ~const_iterator () {}

          bool operator== (const const_iterator& y) const
          {
               READ_LOCK(*citer_mutex);
               { READ_LOCK(*(y.citer_mutex));
               return node == y.node; }
          }
          bool operator!= (const const_iterator& y) const
          {
               READ_LOCK(*citer_mutex);
               { READ_LOCK(*(y.citer_mutex));
               return node != y.node; }
          }
          bool operator== (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator& y) const  // hh 980105 Added qualified name to iterator
          {
               READ_LOCK(*citer_mutex);
               { READ_LOCK(*(y.iter_mutex));
               return node == y.node; }
          }
          bool operator!= (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator& y) const  // hh 980105 Added qualified name to iterator
          {
               READ_LOCK(*citer_mutex);
               { READ_LOCK(*(y.iter_mutex));
               return node != y.node; }
          }
          const_reference operator* () const
          {
               READ_LOCK(*citer_mutex);
               return node->value;
          }
          const_pointer operator-> () const
          {
               READ_LOCK(*citer_mutex);
               return &(operator* ());
          }
          const_iterator& operator++ ()
          {
               WRITE_LOCK(*citer_mutex);
               if (node->right != NULL) {
                    node = node->right;
                    while (node->left != NULL)
                         node = node->left;
               }
               else {
                    link_type y = node->parent;
                    while (node == y->right) {
                         node = y;
                         y = y->parent;
                    }
                    if (node->right != y)
                         node = y;
               }
               return *this;
          }
          const_iterator operator++ (int)
          {
               const_iterator tmp = *this; 
               ++*this;
               return tmp;
          }   
          const_iterator& operator-- ()
          {
               WRITE_LOCK(*citer_mutex);
               if (node->color == red && node->parent->parent == node)
                    node = node->right;
               else if (node->left != NULL) {
                    link_type y = node->left;
                    while (y->right != NULL)
                         y = y->right;
                    node = y;
               }
               else {
                    link_type y = node->parent;
                    while (node == y->left) {
                         node = y;
                         y = y->parent;
                    }
                    node = y;
               }
               return *this;
          }
          const_iterator operator-- (int)
          {
               const_iterator tmp = *this;
               --*this;
               return tmp;
          }
     };

private:
     iterator    __insert (link_type x, link_type y, const value_type& v);
     link_type   __copy_aux (link_type x, link_type p);
     link_type   __copy (link_type x, link_type p);
     void        __rb_tree_rebalance (link_type x, link_type& p);
     link_type   __rb_tree_rebalance_for_erase (link_type z, link_type& root, 
                                             link_type& leftmost, link_type& rightmost);
     void        __erase (link_type x);

protected:
     link_type                    free_list;
     link_type                    header;
     Compare                      key_compare;
     size_type                    node_count;
     Allocator                    value_allocator;
     rb_tree_node_allocator_type  rb_tree_node_allocator;
     DEC_OBJ_LOCK(_mutex)

    link_type&      root ()            { return header->parent; }
    link_type&      root ()      const { return header->parent; }
    link_type&      leftmost ()        { return header->left; }
    link_type&      leftmost ()  const { return header->left; }
    link_type&      rightmost ()       { return header->right; }
    link_type&      rightmost () const { return header->right; }

     link_type get_node ()
     {
          WRITE_LOCK(_mutex);
          link_type tmp = free_list;
          if (tmp)
               free_list = (link_type) (free_list->left);
          else
               tmp = rb_tree_node_allocator.allocate ((size_type)1);
          return tmp;
     }

     link_type __new_node (const Value& v)
     {
          link_type tmp = get_node ();
          MSIPL_TRY
          {
               value_allocator.construct (&(tmp->value), v);
               tmp->left = tmp->right = NULL;
          }
          MSIPL_CATCH
          {
               rb_tree_node_allocator.deallocate (tmp, 1);
               throw;
          }
          return tmp;
     }

     void clean_up ()
     {
          if (node_count != 0) {
               destroy_and_deallocate (root ());
               leftmost () = header;
               root () = NULL;
               rightmost () = header;
               node_count = 0;
          }
     }
     
     void destroy_and_deallocate (link_type x)
     {
          while (x != NULL) {
               destroy_and_deallocate (x->right);
               link_type y = x->left;
               value_allocator.destroy (&(x->value));
               rb_tree_node_allocator.deallocate (x, 1);
               x = y;
          }
     }

     static const Key& key (const link_type x)
     {
          return KeyOfValue () (x->value);
     }

     static link_type minimum (link_type x)
     {
          while (x->left != NULL)
               x = x->left;
          return x;
     }
     static link_type maximum (link_type x)
     {
          while (x->right != NULL)
               x = x->right;
          return x;
     }

     void init ()
     {
          header = get_node ();
          header->color = red;  // used to distinguish header from root, 
                                     // in operator++
          root () = NULL;
          leftmost () = header;
          rightmost () = header;
     }

public:
     // constructors/destructors
     rb_tree (const Compare& comp = Compare (), 
                    const Allocator& alloc = Allocator ())
          : key_compare (comp), node_count (0), free_list (NULL), 
                value_allocator (alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
               , rb_tree_node_allocator (alloc)
#endif
     { 
          init (); 
     }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    rb_tree (InputIterator first, InputIterator last, 
             const Compare& comp = Compare (), 
             const Allocator& alloc = Allocator ())
    : key_compare (comp), free_list (NULL), value_allocator (alloc), 
      rb_tree_node_allocator (alloc), node_count (0)
    { 
          init (); 
          insert_equal (first, last); 
     }
#else
    rb_tree (const_iterator first, const_iterator last, 
             const Compare& comp = Compare (), 
             const Allocator& alloc = Allocator ())
    : key_compare (comp), node_count (0), free_list (NULL), value_allocator (alloc)
     { 
          init (); 
          insert_equal (first, last); 
     }

    rb_tree (const value_type* first, const value_type* last, 
             const Compare& comp = Compare (), 
             const Allocator& alloc = Allocator ())
    : key_compare (comp), node_count (0), free_list (NULL), value_allocator (alloc)
    { 
          init (); 
          insert_equal (first, last); 
     }
#endif

     rb_tree (const RB_TREE_TYPE& x)
          : node_count (0), key_compare (x.key_compare), 
               free_list (NULL), value_allocator (x.value_allocator)
#ifdef MSIPL_MEMBER_TEMPLATE
               , rb_tree_node_allocator (x.rb_tree_node_allocator)
#endif
     { 
          header = get_node ();
          header->color = red; 
          if (x.root () == NULL) {
               root () = NULL;
               leftmost () = header;
               rightmost () = header;
          } 
          else {
               MSIPL_TRY
               {
                    root () = __copy (x.root (), header);
               }
               MSIPL_CATCH
               {
                    rb_tree_node_allocator.deallocate (header, 1);
                    throw;
               }
               leftmost () = minimum (root ());
               rightmost () = maximum (root ());
          }
          node_count = x.node_count;
     }

     ~rb_tree ()
     {
          clean_up ();
          rb_tree_node_allocator.deallocate (header, 1);

          link_type tmp;
          while (free_list) { 
               tmp = free_list; 
               free_list = (link_type)free_list->left;
               rb_tree_node_allocator.deallocate (tmp, 1);
          }
     }

    RB_TREE_TYPE& operator= (const RB_TREE_TYPE& x);

     allocator_type get_allocator () const
     {
          READ_LOCK(_mutex);
          return value_allocator;
     }

     // observers
     Compare key_comp () const
     {
          READ_LOCK(_mutex);
          return key_compare;
     }

     // iterators
     iterator begin ()
     {
          READ_LOCK(_mutex);
          return iterator (leftmost (), this);
     }
     const_iterator begin () const
     {
          READ_LOCK(_mutex);
          return const_iterator (leftmost (), this);
     }
     iterator end ()
     {
          READ_LOCK(_mutex);
          return iterator (header, this);
     }
     const_iterator end () const
     {
          READ_LOCK(_mutex);
          return const_iterator (header, this);
     }

     // reverse iterators
     reverse_iterator rbegin ()
     {
          return reverse_iterator (end ());
     }
     const_reverse_iterator rbegin () const
     {
          return const_reverse_iterator (end ());
     }
     reverse_iterator rend ()
     {
          return reverse_iterator (begin ());
     }
     const_reverse_iterator rend () const
     {
          return const_reverse_iterator (begin ());
     }

    // size/capacity
     bool empty () const
     {
          READ_LOCK(_mutex);
          return node_count == 0;
     }
     size_type size () const
     {
          READ_LOCK(_mutex);
          return node_count;
     }
     size_type max_size () const
     {
          return rb_tree_node_allocator.max_size ();
     }

    // swap trees
     void swap (rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& t)
     {
          WRITE_LOCK(_mutex);
          { WRITE_LOCK(t._mutex);
          MSIPLSTD::swap (header, t.header);
          MSIPLSTD::swap (node_count, t.node_count);
          MSIPLSTD::swap (key_compare, t.key_compare);
          MSIPLSTD::swap (rb_tree_node_allocator, t.rb_tree_node_allocator);
          MSIPLSTD::swap (value_allocator, t.value_allocator);
          MSIPLSTD::swap (free_list, t.free_list); }
     }

    // insert/erase
     pair_iterator_bool insert_unique (const value_type& x);
     iterator insert_equal (const value_type& x);

     iterator   insert_unique (iterator position, const value_type& x);
     iterator   insert_equal (iterator position, const value_type& x);

#ifdef MSIPL_MEMBER_TEMPLATE
     template <class InputIterator>
     void insert_unique (InputIterator first, InputIterator last)
     {
          for (; first != last; ++first)
               insert_unique (*first);
     }

     template <class InputIterator>
     void insert_equal (InputIterator first, InputIterator last)
     {
          for (; first != last; ++first)
               insert_equal (*first);
     }

#else
     void insert_unique (const_iterator first, const_iterator last)
     {
          for (; first != last; ++first)
               insert_unique (*first);
     }

     void insert_equal (const_iterator first, const_iterator last)
     {
          for (; first != last; ++first)
               insert_equal (*first);
     }

     void insert_unique (iterator first, iterator last)
     {
          for (; first != last; ++first)
               insert_unique (*first);
     }

     void insert_equal (iterator first, iterator last)
     {
          for (; first != last; ++first)
               insert_equal (*first);
     }

     void insert_unique (const Value* first, const Value* last)
     {
          for (; first != last; ++first)
               insert_unique (*first);
     }

     void insert_equal (const Value* first, const Value* last)
     {
          for (; first != last; ++first)
               insert_equal (*first);
     }
#endif

     void       erase (iterator position);
     size_type  erase (const key_type& x);
     void       erase (iterator first, iterator last);
     void       erase (const key_type* first, const key_type* last);

     // search operations:
     iterator         find       (const key_type& x);
     const_iterator   find       (const key_type& x) const;
     size_type        count      (const key_type& x) const;

     iterator         lower_bound (const key_type& x);
     const_iterator   lower_bound (const key_type& x) const;
     iterator         upper_bound (const key_type& x);
     const_iterator   upper_bound (const key_type& x) const;

     pair_iterator_iterator   equal_range (const key_type& x);
     pair_citerator_citerator equal_range (const key_type& x) const;

     inline void rotate_left (link_type x, link_type& root);
     inline void rotate_right (link_type x, link_type& root);

    void clear ()
    {
        if (node_count != NULL) {
            __erase (root ());
            leftmost () = header;
            root () = NULL;
            rightmost () = header;
            node_count = 0;
        }
    }
};

TREE_TEMPLATE 
inline bool
operator== (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ());
}

TREE_TEMPLATE 
inline bool
operator< (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

TREE_TEMPLATE 
inline bool
operator!= (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return ! (x == y);
}

TREE_TEMPLATE 
inline bool
operator> (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return (y < x);
}

TREE_TEMPLATE 
inline bool
operator<= (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return ! (y < x);
}

TREE_TEMPLATE 
inline bool
operator>= (const RB_TREE_TYPE &x, const RB_TREE_TYPE &y)
{
     return ! (x < y);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE&
RB_TREE_TYPE::operator= (const RB_TREE_TYPE &x)
{
     if (this == &x) return *this;
     WRITE_LOCK(_mutex);
     READ_LOCK(_mutex);

     clear ();
     node_count = 0;
     key_compare = x.key_compare;
     if (x.root () == NULL) {
          root () = NULL;
          leftmost () = header;
          rightmost () = header;
     } 
     else {
          root () = __copy (x.root (), header);
          leftmost () = minimum (root ());
          rightmost () = maximum (root ());
          node_count = x.node_count;
     }
     return *this;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator
RB_TREE_TYPE::__insert (link_type x, link_type y, const Value& v)
{
     // determine link before allocating new node
     bool link_to_left = y == header || x != NULL || key_compare (KeyOfValue () (v), key (y));
     link_type z = __new_node (v);
     if (link_to_left) {
          y->left = z;// also makes leftmost () = z when y == header
          if (y == header) {
               root () = z;
               rightmost () = z;
          } 
          else if (y == leftmost ())
               leftmost () = z;// maintain leftmost () pointing to minimum node
     } 
     else {
          y->right = z;
          if (y == rightmost ())
               rightmost () = z;// maintain rightmost () pointing to maximum node
     }
     z->parent = y;
     __rb_tree_rebalance (z, header->parent);
     ++node_count;
     return iterator (z, this);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator
RB_TREE_TYPE::insert_equal (const Value& v)
{
     WRITE_LOCK(_mutex);
     link_type y = header;
     link_type x = root ();
     while (x != NULL) {
          y = x;
          x = key_compare (KeyOfValue () (v), key (x)) ? x->left : x->right;
     }
     return __insert (x, y, v);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator
RB_TREE_TYPE::insert_equal (iterator position, const Value& v)
{
    WRITE_LOCK(_mutex);
    if (position.node == header->left) // begin ()
        if (size () > 0 && key_compare (KeyOfValue () (v), key (position.node)))
            return __insert (position.node, position.node, v);
        // first argument just needs to be non-null
        else
            return insert_equal (v);
    else if (position.node == header) // end ()
        if (!key_compare (KeyOfValue () (v), key (rightmost ())))
            return __insert (NULL, rightmost (), v);
        else
            return insert_equal (v);
    else {
        iterator before = position;
        --before;
        if (!key_compare (KeyOfValue () (v), key (before.node))
            && !key_compare (key (position.node), KeyOfValue () (v)))
            if ((before.node)->right == NULL)
                return __insert (NULL, before.node, v);
            else
                return __insert (position.node, position.node, v);
            // first argument just needs to be non-null
            else
                return insert_equal (v);
    }
}

TREE_TEMPLATE inline RB_TREE_TYPE::pair_iterator_bool
RB_TREE_TYPE::insert_unique (const Value& v)
{
    WRITE_LOCK(_mutex);
    link_type y = header;
    link_type x = root ();
    bool comp = true;
    while (x != NULL) {
        y = x;
        comp = key_compare (KeyOfValue () (v), key (x));
        x = comp ? x->left : x->right;
    }
    iterator j (y, this);
    if (comp)
        if (j == begin ())
            return pair<iterator, bool> (__insert (x, y, v), true);
        else
            --j;
    if (key_compare (key (j.node), KeyOfValue () (v)))
        return pair<iterator, bool> (__insert (x, y, v), true);
    return pair<iterator, bool> (j, false);
}

TREE_TEMPLATE inline RB_TREE_TYPE::iterator
RB_TREE_TYPE::insert_unique (iterator position, const Value& v)
{
    WRITE_LOCK(_mutex);
    if (position.node == header->left) // begin ()
        if (size () > 0 && key_compare (KeyOfValue () (v), key (position.node)))
            return __insert (position.node, position.node, v);
        // first argument just needs to be non-null
        else
            return insert_unique (v).first;
    else if (position.node == header) // end ()
        if (key_compare (key (rightmost ()), KeyOfValue () (v)))
            return __insert (NULL, rightmost (), v);
        else
            return insert_unique (v).first;
    else {
        iterator before = position;
        --before;
        if (key_compare (key (before.node), KeyOfValue () (v))
            && key_compare (KeyOfValue () (v), key (position.node)))
            if ((before.node)->right == NULL)
                return __insert (NULL, before.node, v);
            else
                return __insert (position.node, position.node, v);
            // first argument just needs to be non-null
            else
                return insert_unique (v).first;
    }
}

TREE_TEMPLATE inline RB_TREE_TYPE::link_type
RB_TREE_TYPE::__copy_aux (link_type x, link_type p)
{
     // structural copy
     link_type r = x;
     while (x != NULL) {
          link_type y = __new_node (x->value);
          if (r == x) r = y;  // save for return value
          p->left = y;
          y->parent = p;
          y->color = x->color;
          y->right = __copy_aux (x->right, y);
          y->left = NULL;
          p = y;
          x = x->left;
     }
     p->left = NULL;
     return r;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::link_type
RB_TREE_TYPE::__copy (link_type x, link_type p)
{
     link_type l = p->left;
     MSIPL_TRY 
     {
          l =  __copy_aux (x, p);
     }
     MSIPL_CATCH 
     {
          if (p->left != l) {
               __erase (p->left);
               p->left = l;
          }
          throw;
     }
    return l;
}

TREE_TEMPLATE 
inline void
RB_TREE_TYPE::erase (iterator position)
{
     WRITE_LOCK(_mutex);
     link_type y = __rb_tree_rebalance_for_erase (position.node, header->parent, 
                                                            header->left, header->right);
     value_allocator.destroy (&(y->value));
     y->left = free_list;
     free_list = y;
     --node_count;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::size_type
RB_TREE_TYPE::erase (const Key& x)
{
     pair_iterator_iterator p = equal_range (x);
     size_type n = distance (p.first, p.second);
     erase (p.first, p.second);
     return n;
}

TREE_TEMPLATE 
inline void
RB_TREE_TYPE::__erase (link_type x)
{   // erase without rebalancing
     while (x != NULL) {
          __erase (x->right);
          link_type y = x->left;
          value_allocator.destroy (&(x->value));
          x->left = free_list;
          free_list = x;
          x = y;
     }
}

TREE_TEMPLATE 
inline void
RB_TREE_TYPE::erase (iterator first, iterator last)
{
     WRITE_LOCK(_mutex);
     if (first == begin () && last == end ())
          clear ();
     else
          while (first != last)
               erase (first++);
}

TREE_TEMPLATE 
inline void
RB_TREE_TYPE::erase (const Key* first, const Key* last)
{ 
     WRITE_LOCK(_mutex);
     while (first != last) 
          erase (*first++); 
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator
RB_TREE_TYPE::find (const Key& k)
{
   READ_LOCK(_mutex);
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root (); /* Current node. */

   while (x != NULL)
         if (!key_compare (key (x), k))
           y = x, x = x->left;
         else
           x = x->right;

   iterator j (y, this);
   return (j == end () || key_compare (k, key (j.node))) ? end () : j;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::const_iterator 
RB_TREE_TYPE::find (const Key& k) const
{
     READ_LOCK(_mutex);
     link_type y = header; /* Last node which is not less than k. */
     link_type x = root (); /* Current node. */
     while (x != NULL) {
          if (!key_compare (key (x), k))
               y = x, x = x->left;
          else
               x = x->right;
     }
     const_iterator j (y, this);
     return (j == end () || key_compare (k, key (j.node))) ? end () : j;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::size_type 
RB_TREE_TYPE::count (const Key& k) const
{
     pair<const_iterator, const_iterator> p = equal_range (k);
     size_type n = distance (p.first, p.second);
     return n;
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator 
RB_TREE_TYPE::lower_bound (const Key& k)
{
     READ_LOCK(_mutex);
     link_type y = header;  /* Last node which is not less than k. */
     link_type x = root (); /* Current node. */
     while (x != NULL)
          if (!key_compare (KeyOfValue () (x->value), k))
               y = x, x = x->left;
          else
               x = x->right;
     return iterator (y, this);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::const_iterator 
RB_TREE_TYPE::lower_bound (const Key& k) const
{
     READ_LOCK(_mutex);
     link_type y = header;  /* Last node which is not less than k. */
     link_type x = root (); /* Current node. */
     while (x != NULL)
          if (!key_compare (KeyOfValue () (x->value), k))
               y = x, x = x->left;
          else
               x = x->right;
     return const_iterator (y, this);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::iterator 
RB_TREE_TYPE::upper_bound (const Key& k)
{
     READ_LOCK(_mutex);
     link_type y = header;  /* Last node which is greater than k. */
     link_type x = root (); /* Current node. */
     while (x != NULL)
          if (key_compare (k, KeyOfValue () (x->value)))
               y = x, x = x->left;
          else
               x = x->right;
     return iterator (y, this);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::const_iterator 
RB_TREE_TYPE::upper_bound (const Key& k) const
{
     READ_LOCK(_mutex);
     link_type y = header; /* Last node which is greater than k. */
     link_type x = root (); /* Current node. */
     while (x != NULL)
          if (key_compare (k, KeyOfValue () (x->value)))
               y = x, x = x->left;
          else
               x = x->right;
     return const_iterator (y, this);
}

TREE_TEMPLATE 
inline RB_TREE_TYPE::pair_iterator_iterator 
RB_TREE_TYPE::equal_range (const Key& k)
{ return pair_iterator_iterator (lower_bound (k), upper_bound (k)); }

TREE_TEMPLATE 
inline RB_TREE_TYPE::pair_citerator_citerator 
RB_TREE_TYPE::equal_range (const Key& k) const
{ return pair_citerator_citerator (lower_bound (k), upper_bound (k)); }

TREE_TEMPLATE inline void 
RB_TREE_TYPE::rotate_left (link_type x, link_type& root)
{
    WRITE_LOCK(_mutex);
    link_type y = x->right;
    x->right = y->left;
    if (y->left !=NULL)
          y->left->parent = x;
    y->parent = x->parent;
    if (x == root)
          root = y;
    else if (x == x->parent->left)
          x->parent->left = y;
    else
          x->parent->right = y;
    y->left = x;
    x->parent = y;
}

TREE_TEMPLATE 
inline void 
RB_TREE_TYPE::rotate_right (link_type x, link_type& root)
{
     WRITE_LOCK(_mutex);
     link_type y = x->left;
     x->left = y->right;
     if (y->right != NULL)
          y->right->parent = x;
     y->parent = x->parent;
     if (x == root)
          root = y;
     else if (x == x->parent->right)
          x->parent->right = y;
     else
          x->parent->left = y;
     y->right = x;
     x->parent = y;
}

TREE_TEMPLATE 
inline void 
RB_TREE_TYPE::__rb_tree_rebalance (link_type x, link_type& root)
{
     x->color = red;
     while (x != root && x->parent->color == red) {
          if (x->parent == x->parent->parent->left) {
               link_type y = x->parent->parent->right;
               if (y && y->color == red) {
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
               }
               else {
                    if (x == x->parent->right) {
                         x = x->parent;
                         rotate_left (x, root);
                    }
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    rotate_right (x->parent->parent, root);
               }
          }
          else {
               link_type y = x->parent->parent->left;
               if (y && y->color == red) {
                    x->parent->color = black;
                    y->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
               }
               else {
                    if (x == x->parent->left) {
                         x = x->parent;
                         rotate_right (x, root);
                    }
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    rotate_left (x->parent->parent, root);
               }
          }
     }
     root->color = black;
}

TREE_TEMPLATE 
inline typename RB_TREE_TYPE::link_type
RB_TREE_TYPE::__rb_tree_rebalance_for_erase (link_type z, 
                                                       link_type& root, 
                                                       link_type& leftmost, 
                                                       link_type& rightmost)
{
     link_type y = z;
     link_type x = NULL;
     link_type x_parent = NULL;
     if (y->left == NULL)           // z has at most one non-null child. y == z.
          x = y->right;             // x might be null.
     else
          if (y->right == NULL)     // z has exactly one non-null child.  y == z.
               x = y->left;         // x is not null.
          else {                    // z has two non-null children.  Set y to
               y = y->right;        //   z's successor.  x might be null.
               while (y->left != NULL)
                    y = y->left;
               x = y->right;
          }
     if (y != z) {                // relink y in place of z.  y is z's successor
          z->left->parent = y;
          y->left = z->left;
          if (y != z->right) {
               x_parent = y->parent;
               if (x) 
                    x->parent = y->parent;
               y->parent->left = x;  // y must be a left child
               y->right = z->right;
               z->right->parent = y;
          }
          else
               x_parent = y;
          if (root == z)
               root = y;
          else if (z->parent->left == z)
               z->parent->left = y;
          else
               z->parent->right = y;
          y->parent = z->parent;
          MSIPLSTD::swap (y->color, z->color);
          y = z;
                              // y now points to node to be actually deleted
     }
     else {                   // y == z
          x_parent = y->parent;
          if (x) x->parent = y->parent;
          if (root == z)
               root = x;
          else
               if (z->parent->left == z)
                    z->parent->left = x;
               else
                    z->parent->right = x;
          if (leftmost == z)
               if (z->right == NULL)            // z->left must be null also
                    leftmost = z->parent;
               // makes leftmost == header if z == root
               else
                    leftmost = minimum (x);
          if (rightmost == z)
               if (z->left == NULL)             // z->right must be null also
                    rightmost = z->parent;
               // makes rightmost == header if z == root
               else                             // x == z->left
                    rightmost = maximum (x);
     }
     if (y->color != red) {
          while (x != root && (x == NULL || x->color == black))
               if (x == x_parent->left) {
                    link_type w = x_parent->right;
                    if (w->color == red) {
                         w->color = black;
                         x_parent->color = red;
                         rotate_left (x_parent, root);
                         w = x_parent->right;
                    }
                    if ((w->left == NULL || w->left->color == black) &&
                         (w->right == NULL || w->right->color == black)) {
                         w->color = red;
                         x = x_parent;
                         x_parent = x_parent->parent;
                    } 
                    else {
                         if (w->right == NULL || w->right->color == black) {
                              if (w->left) w->left->color = black;
                         w->color = red;
                         rotate_right (w, root);
                         w = x_parent->right;
                    }
                    w->color = x_parent->color;
                    x_parent->color = black;
                    if (w->right) w->right->color = black;
                    rotate_left (x_parent, root);
                    break;
                    }
               } 
               else {                     // same as above, with right <-> left.
                    link_type w = x_parent->left;
                    if (w->color == red) {
                         w->color = black;
                         x_parent->color = red;
                         rotate_right (x_parent, root);
                         w = x_parent->left;
               }
               if ((w->right == NULL || w->right->color == black) &&
                    (w->left == NULL || w->left->color == black)) {
                    w->color = red;
                    x = x_parent;
                    x_parent = x_parent->parent;
               } 
               else {
                    if (w->left == NULL || w->left->color == black) {
                         if (w->right) w->right->color = black;
                         w->color = red;
                         rotate_left (w, root);
                         w = x_parent->left;
                    }
                    w->color = x_parent->color;
                    x_parent->color = black;
                    if (w->left) w->left->color = black;
                    rotate_right (x_parent, root);
                    break;
               }
          }
          if (x) x->color = black;
     }
     return y;
}

#ifdef MSIPL_USING_NAMESPACE
	} // namespace std
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_TREE_H */

// hh 971220 fixed MOD_INCLUDE
// hh 971226 added alignment wrapper
// hh 980105 changed pointer & reference to const versions in const_iterator base class
// hh 980105 Added qualified name to iterator
// hh 980111 <stdexcept> commented out.  Not needed
