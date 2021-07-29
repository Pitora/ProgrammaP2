#ifndef TC_H
#define TC_H

#include <iostream>
#include "exceptions.h"

template<class T>
class C {
private:

  class nodo {
  public:
    T info;
    nodo *prev, *next;
    nodo(const T& t, nodo* p = 0, nodo* n=0): info(t), prev(p), next(n) {}
  };

  nodo *first, *last; 

  static void destroy(nodo* n) {
    if (n != nullptr) {
      destroy(n->next);
      delete n;
    }
  }
  
  static void deep_copy(nodo *src, nodo*& fst, nodo*& last) {
    if (src) {
      fst = last = new nodo(src->info);
      nodo* src_sc = src->next;
	while (src_sc) {
	  last = new nodo(src_sc->info, last);
	  last->prev->next = last;
	  src_sc = src_sc->next;
	}
    }
    else {
      fst = last = nullptr;
    }
  }
  
  
public:

  C() {
    first = last = nullptr;
  }
  
  C(const C& l) {
    deep_copy(l.first,first,last);
  }

  C& operator=(const C& l) {
    if(this != &l) {
      destroy(first);
      deep_copy(l.first,first,last);
    }
    return *this;
  }
    
  ~C() { 
    destroy(first); 
  }

  void insertFront(const T& t) {
    first = new nodo(t,nullptr,first);
    if(first->next==nullptr) { 
      last=first;
    }
    else {
      (first->next)->prev=first;
    }
  }
  
  void insertBack(const T& t) {
    if(last){ 
      last = new nodo(t,last,nullptr);
      (last->prev)->next=last;
    }
    else 
      first=last=new nodo(t);
  }

  void remove(const T& t){
    nodo* n = first;
    bool found = false;
    while(!found && n != nullptr)
    {
        if (n->info == t)
        {
          found = true;
        }else{
          n = n->next;
        }
    }
    if (found)
    {
      if (n == first && n == last)
      {
        first = last = nullptr;
      }
      else if (n == first)
      {
        n->next->prev = nullptr;
        first = n->next;
      }
      else if (n == last)
      {
        n->prev->next = nullptr;
        last = n->prev;
      }else{
        n->prev->next = n->next;
        n->next->prev = n->prev;
      }
      delete n;     
    }else throw err_nodeNotFound();
  }
  
  C(unsigned int k, const T& t): first(nullptr), last(nullptr) {
    for(unsigned int j=0; j<k; ++j) insertFront(t);
  }
  
  
  class const_iterator {
    friend class C <T>;
  private: 
    const nodo* ptr;
    bool past_the_end;

    const_iterator(nodo* p, bool pte = false): ptr(p), past_the_end(pte) {}
  public:
    
    const_iterator(): ptr(nullptr), past_the_end(false) {}

    const_iterator& operator++() {
      if(ptr!= nullptr) {
	if(!past_the_end) {
	  if(ptr->next != nullptr) {ptr = ptr->next;}
	  else { ptr = ptr+1; past_the_end = true; }
	}
      }
      return *this;
    }
    
    const_iterator operator++(int){
      const_iterator aux(*this);
      if(ptr!= nullptr) {
	if(!past_the_end) {
	  if(ptr->next != nullptr) ptr = ptr->next;
	  else {ptr = ptr+1; past_the_end = true;}
	}
      }
      return aux;
    }
      
    const_iterator& operator--() {
      if(ptr != nullptr) {
	if(ptr->prev == nullptr) ptr=nullptr;
	else if(!past_the_end) ptr = ptr->prev;
	else {ptr = ptr-1; past_the_end = false;}
      }
      return *this;
    }
      
    const_iterator operator--(int){
      const_iterator aux(*this);
      if(ptr != nullptr) {
	if(ptr->prev == nullptr) ptr=nullptr;
	else if(!past_the_end) ptr = ptr->prev;
	else {ptr = ptr-1; past_the_end = false;}
      }
      return aux;
    }

    bool operator==(const const_iterator& cit) const {
      return ptr == cit.ptr;
    }
    
    bool operator!=(const const_iterator& cit) const {
      return ptr != cit.ptr;
    }
    
    const T& operator*() const {
      return ptr->info;
    }

    const T* operator->() const {
      return &(ptr->info);
    }
  };

  const_iterator begin() const {
    return const_iterator(first);
  }
  
  const_iterator end() const {
    if(!last) return const_iterator();
    return const_iterator(last+1,true); 
  }

  //Metodo che ritorna un iteratore che punta all'elemento in posizione i
  const_iterator position(int i) const {
      const_iterator c = begin();
      const_iterator c2 = end();
      for (int i2 = 0; i2 < i; i2++)
      {
          if (c != c2){
          c++;
          }
          else throw err_outOfBounds();
      }
      return c;
  }

  
};

#endif
