#ifndef H_VPTRLIST
#define H_VPTRLIST

class pvlist;
/*!
 *  @brief  Node that contains the void* pointer of the value and the linked list elements
 *
 *  @author &copy;2010, Serge Lussier (bretzel) and `Arknowledge Creations`
 *  @usage
 *  \code
 *  vplist list;
 *  char*   cc;
 *  list << "dummy1" << "dummy2" << "dummy3" << "...";
 *  vplist::iptr i = list.begin();
 *  _iterate(list){ // `_iterate` is a macro that easy the for-loop and provides a list::iptr variable inside the for-loop nammed `iter`
 *      iter >> cc;
 *      std::cout << '[' << cc << '] '; // output: "[dummy1] [dummy2] [dummy3] [...] "
 *  }
 *  std::cout << std::endl;
 *  i >> cc;
 *  std::cout << cc << std::endl; // ouput : "dummy1"
 *  list.remove(i);
 *  i >> cc;
 *  std::cout << cc << std::endl; // ouput : "dummy1" - yes, i not changed and is a separated copy of list's internal iptr
 *  i++;
 *  i >> cc;
 *  std::cout << cc << std::endl; // ouput :" dummy2"
 *  list.clear();
 * \endcode
 * @note
 *    vptr::__value is the actual pointer that holds the value of the given address of the data. the destructor does not delete/free resource helds by this pointer. It is the responsability of the programmer to know what to do with this resource.
 */
class vptr {
    void* __value;
    vptr*  _previous;
    vptr*  _next;
    vptr*  _parent;

    pvlist* __cnt;
    vptr(void* v) {
        __value = v;
        _previous = _next = _parent = 0;
    }
    void _set_cnt(pvlist* sl) {
        __cnt = sl;
    }
    vptr(vptr* parent);

    friend class pvlist;
    void _detach();
    friend vptr& operator++(vptr&);
    friend vptr& operator++(vptr&,int);

    friend vptr& operator--(vptr&);
    friend vptr& operator--(vptr&,int);

public:
    ~vptr();
    vptr() {
        __value = 0;
        _previous = _next = _parent = 0;
    }
    void*& value() {
        return __value;
    }
    bool operator ==(vptr& other){
        return  (other.__value == __value) && (other._previous == _previous) && (other._next == _next);
    }
    bool operator !=(vptr& other){
        return  (other.__value != __value) || (other._previous != _previous) || (other._next != _next);
    }

    /*!
     *  @brief  I hate when std::[CNT]::iterator i; v = *i crashes! | return 0(NULL) or valid stored ptr value! just do `if(v){...}`!!!
     *  @author Serge Lussier (bretzel)
     */
    void* operator*() {
        return __value;
    }
    /*!
     *  @brief  I hate i == containe.end() | every nodes that have __value==0 is `!` positive, used to test if _node is in splist bounds
     *  @author Serge Lussier
     *
     */
    bool operator !() {
        return __value == (void*)0;
    }
    static vptr z;
    template<typename T> vptr& operator >>(T& rv) {
        //UseLog
        //mInfo << " ?" << Endl;
        if (!__value) {
            return *this;
        }
        rv = *((T*)&__value);
        return *this;
    }
//     template<typename T> _node& operator >>(T* rv){
//         UseLog
//         mInfo << " ?" << Endl;
//
//         if(!__value){
//             return *this;
//         }
//         rv = (T*)__value;
//         return *this;
//     }
    const vptr* next() const { return _next; }
    const vptr* previous() const { return _previous; }
    const vptr* parent() const { return _parent; }
};


vptr& operator++(vptr&);
vptr& operator++(vptr&,int);

vptr& operator--(vptr&);
vptr& operator--(vptr&,int);

/*!
 *  @brief  vplist : (Very Powerfull but very dangerous) double linked list of void* pointers container
 *  @author Serge Lussier (bretzel)
 *  @note <p>
 *  I hate STL / stdlibc++ ( excepted their std::map<> dictionary feature ) for the `iterator != container.end()` just to check if the iterator position valid or not...
 *  </p>
 *  <p>
 *  So here is a class for a double-linked list of pointers to void* values that like the old dangerous C construct <b><i> `type function(...)` </i></b>,which lets to construct <i>`v = function("str", 45, ptr, etc)`</i>. vplist  provides the power of storing pointers of any types.
 *  <h4>but</h4>  it is not doing <i>type-checking and validations</i> for the new <strong>idiots pseudo programmers generations</strong>.
 *
 *  </p>
 */
class pvlist
{
    vptr*  __first;
    vptr*  __last;
    int     __count;
public:
    typedef vptr iptr;
    typedef vptr iterator;
    pvlist();
    pvlist(const pvlist& other);
    virtual ~pvlist();
    virtual pvlist& operator=(const pvlist& other);
    virtual bool operator==(const pvlist& other) const;
    pvlist& operator << (void* v);
    pvlist& operator << (const void* v);
    vptr&  begin();
    vptr&  end();
    void remove(vptr& n);
    bool remove(void* ptr);
    vptr&  operator()(void*);
    int clear();
    int count() {
        return __count;
    }
    int size(){
        return __count;
    }
    bool empty(){
        return __count == 0;
    }

};



#define _iterate(c) for(pvlist::iptr iter =(c).begin(); *(iter); ++(iter))
#endif // H_VPTRLIST
// kate: indent-mode cstyle; space-indent on; indent-width 0;
