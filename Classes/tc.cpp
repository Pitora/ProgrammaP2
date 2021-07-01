#ifndef TC_H
#define TC_H


template<class T>
class dList {
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

  dList() {
    first = last = nullptr;
  }
  
  dList(const dList& l) {
    deep_copy(l.first,first,last);
  }

  dList& operator=(const dList& l) {
    if(this != &l) {
      destroy(first);
      deep_copy(l.first,first,last);
    }
    return *this;
  }
    
  ~dList() { destroy(first); }

  void insertFront(const T& t) {
    first = new nodo(t,nullptr,first);
    if(first->next==nullptr) { // lista di invocazione era vuota
      last=first;
    }
    else { // lista di invocazione NON era vuota
      (first->next)->prev=first;
    }
  }
  
  void insertBack(const T& t) {
    if(last){ // lista non vuota
      last = new nodo(t,last,nullptr);
      (last->prev)->next=last;
    }
    else // lista vuota
      first=last=new nodo(t);
  }
  
  dList(unsigned int k, const T& t): first(nullptr), last(nullptr) {
    for(unsigned int j=0; j<k; ++j) insertFront(t);
  }
  
  
  class const_iterator {
    friend class dList <T>;
  private: // const_iterator indefinito IFF ptr==nullptr & past_the_end==false
    const nodo* ptr;
    bool past_the_end;

    // convertitore "privato" nodo* => const_iterator 
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
    return const_iterator(last+1,true); // attenzione: NON e' past the end
  }
  
};

#endif
