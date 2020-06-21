/*           untyped C++ (Version 0.1 - 2012/07)
    <https://github.com/peychart/untyped-cpp>

    Copyright (C) 2012  -  peychart

    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this program.
    If not, see <http://www.gnu.org/licenses/>.

    Details of this licence are available online under:
                        http://www.gnu.org/licenses/gpl-3.0.html
*/
#ifndef HEADER_F2792F1A2356431
#define HEADER_F2792F1A2356431

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>

#define nullptr   NULL


namespace noType
{
 class untyped : public std::vector<untyped*>, public std::map<std::string, untyped*>, public std::string
 {  static size_t json;

 protected:
  typedef std::pair<std::string, untyped*> typePair;
  typedef std::vector<untyped*>            typeVector;
  typedef std::map<std::string, untyped*>  typeMap;
  typedef unsigned char                    uchar;

 public:
  inline static char const* version() {return "0.2";};
  untyped ( void );                   //  0
  untyped ( bool           const   ); //  1
  untyped ( char           const   ); //  2
  untyped ( wchar_t        const   ); //  3
  untyped ( int8_t         const   ); //  4
  untyped ( uint8_t        const   ); //  5
  untyped ( int16_t        const   ); //  6
  untyped ( uint16_t       const   ); //  7
  untyped ( int32_t        const   ); //  8
  untyped ( uint32_t       const   ); //  9
  untyped ( int64_t        const   ); // 10
  untyped ( uint64_t       const   ); // 11
  untyped ( float          const   ); // 12
  untyped ( double         const   ); // 13
  untyped ( char           const * ); // 15
  untyped ( std::string    const & ); // 15
  untyped ( size_t s, void const * ); // 15
  untyped ( untyped        const & );
  untyped ( std::istream         & );
  virtual ~untyped() {clear();};

  inline size_t                       type        ( void )                const {return (size_t)_type;};
  inline size_t                       size        ( void )                const {return std::string::size();};
  inline size_t                       vectorSize  ( void )                const {return typeVector::size();};
  inline size_t                       mapSize     ( void )                const {return typeMap::size();};
  inline bool                         empty       ( void )                const {return( !size() && !vectorSize() && !mapSize() );};

  inline untyped&                     clear       ( void )                      {return clearValue().clearMap().clearVector();};
  inline untyped&                     clearValue  ( void )                      {std::string::clear(); _type=0; return *this;};
  untyped&                            clearVector ( void );
  untyped&                            clearMap    ( void );
  inline char const *                 data        ( void )                const {return std::string::data();};
  untyped&                            erase       ( size_t pos, size_t len=-1L ){if(size() && !_type) std::string::erase(pos, len); return *this;};

  untyped&                            assign      ( untyped const &  );
  template<class T> untyped&          assign      ( T       const &v )          {return assign( untyped( v ) );};
  template<class T> untyped&          assign      ( char    const *v )          {return assign( untyped( v ) );};
  inline untyped&                     assign      ( size_t s, void const *v )   {return assign( untyped( s, v ) );};

  template<typename T> inline T       value       ( T &v )                const {return  v=this->value<T>();};
  template<typename T> inline T*      value       ( T* &p )               const {return  p=reinterpret_cast<T*>(data());};
  template<typename T> inline T const *value      ( T const * &p )        const {return  p=reinterpret_cast<T const *>(data());};
  template<typename T> T              value       ( void )                const {
    switch( _type ) {
      case  1: if( size() ) return( *reinterpret_cast<bool     const *>(data()) ); break;
      case  2: if( size() ) return( *reinterpret_cast<char     const *>(data()) ); break;
      case  3: if( size() ) return( *reinterpret_cast<wchar_t  const *>(data()) ); break;
      case  4: if( size() ) return( *reinterpret_cast<int8_t   const *>(data()) ); break;
      case  5: if( size() ) return( *reinterpret_cast<uint8_t  const *>(data()) ); break;
      case  6: if( size() ) return( *reinterpret_cast<int16_t  const *>(data()) ); break;
      case  7: if( size() ) return( *reinterpret_cast<uint16_t const *>(data()) ); break;
      case  8: if( size() ) return( *reinterpret_cast<int32_t  const *>(data()) ); break;
      case  9: if( size() ) return( *reinterpret_cast<uint32_t const *>(data()) ); break;
      case 10: if( size() ) return( *reinterpret_cast<int64_t  const *>(data()) ); break;
      case 11: if( size() ) return( *reinterpret_cast<uint64_t const *>(data()) ); break;
      case 12: if( size() ) return( *reinterpret_cast<float    const *>(data()) ); break;
      case 13: if( size() ) return( *reinterpret_cast<double   const *>(data()) ); break;
      case 15: return( *data() );
    } return T();
  };

  template<typename T>                operator T  ( void )               const  {return value<T>();};
  template<typename T>                operator T* ( void )               const  {return reinterpret_cast<T*>(data());};

  template<class T> untyped&          operator=   ( T const &that )             {return operator=( untyped( that ) );};
  inline untyped&                     operator=   ( untyped const &that )       {return assign(that);};

  template<class T> bool              operator==  ( T const &that )       const {return  operator==( untyped( that ) );};
  bool                                operator==  ( untyped const &that ) const;
  template<class T> bool              operator!=  ( T const &that )       const {return  operator!=( untyped( that ) );};
  inline bool                         operator!=  ( untyped const &that ) const {return !operator==( that );};
  template<class T> bool              operator<   ( T const &that )       const {return  operator< ( untyped( that ) );};
  bool                                operator<   ( untyped const &that ) const;
  template<class T> bool              operator<=  ( T const &that )       const {return  operator<=( untyped( that ) );};
  inline bool                         operator<=  ( untyped const &that ) const {return( operator< ( that ) || operator==( that ) );};
  template<class T> bool              operator>   ( T const &that )       const {return  operator> ( untyped( that ) );};
  inline bool                         operator>   ( untyped const &that ) const {return !operator<=( that );};
  template<class T> bool              operator>=  ( T const &that )       const {return  operator>=( untyped( that ) );};
  inline bool                         operator>=  ( untyped const &that ) const {return !operator< ( that );};

  template<class T> inline untyped&   operator+=  ( T const &that )             {return  operator+=( untyped( that ) );};
  untyped&                            operator+=  ( untyped const & );
  template<class T> inline untyped    operator+   ( T const &that ) const       {return  operator+ ( untyped( that ) );};
  inline untyped                      operator+   ( untyped const &that ) const {return  untyped ( *this ).operator+=( that );};
  template<class T> inline untyped&   operator-=  ( T const &that )             {return  operator-=( untyped( that ) );};
  untyped&                            operator-=  ( untyped const &  );
  template<class T> inline untyped    operator-   ( T const &that ) const       {return  operator- ( untyped( that ) );};
  inline untyped                      operator-   ( untyped const &that ) const {return  untyped ( *this ).operator-=( that );};
  template<class T> inline untyped&   operator*=  ( T const &that )             {return  operator*=( untyped( that ) );};
  untyped&                            operator*=  ( untyped const &  );
  template<class T> inline untyped    operator*   ( T const &that ) const       {return  operator* ( untyped( that ) );};
  inline untyped                      operator*   ( untyped const &that ) const {return  untyped ( *this ).operator*=( that );};
  template<class T> inline untyped&   operator/=  ( T const &that )             {return  operator/=( untyped( that ) );};
  untyped&                            operator/=  ( untyped const &  );
  template<class T> inline untyped    operator/   ( T const &that ) const       {return  operator/ ( untyped( that ) );};
  inline untyped                      operator/   ( untyped const &that ) const {return  untyped ( *this ).operator/=( that );};
  template<class T> inline untyped&   operator%=  ( T const &that )             {return  operator%=( untyped( that ) );};
  untyped&                            operator%=  ( untyped const &  );
  template<class T> inline untyped    operator%   ( T const &that ) const       {return  operator% ( untyped( that ) );};
  inline untyped                      operator%   ( untyped const &that ) const {return  untyped ( *this ).operator%=( that );};
  template<class T> inline untyped&   operator&=  ( T const &that )             {return  operator&=( untyped( that ) );};
  untyped&                            operator&=  ( untyped const &  );
  template<class T> inline untyped    operator&   ( T const &that ) const       {return  operator& ( untyped( that ) );};
  inline untyped                      operator&   ( untyped const &that ) const {return  untyped ( *this ).operator&=( that );};
  template<class T> inline untyped&   operator|=  ( T const &that )             {return  operator|=( untyped( that ) );};
  untyped&                            operator|=  ( untyped const &  );
  template<class T> inline untyped    operator|   ( T const &that ) const       {return  operator| ( untyped( that ) );};
  inline untyped                      operator|   ( untyped const &that ) const {return  untyped ( *this ).operator|=( that );};

  virtual untyped&                    serialize      ( std::ostream & );
  virtual untyped&                    deserialize    ( std::string s )          {std::istringstream in(s); return(isJsonMode() ?deserializeJson(in) :deserialize(in));};
  virtual untyped&                    deserialize    ( std::istream & );
  virtual untyped&                    serializeJson  ( std::ostream &out )      {size_t b(untyped::json); if(isBinaryMode()) jsonMode(); out << *this; untyped::json=b; return *this;};
  virtual untyped&                    deserializeJson( std::string s )          {std::istringstream in(s); return deserializeJson(in);};
  virtual untyped&                    deserializeJson( std::istream & );
  untyped&                            operator()     ( std::string s )          {std::istringstream in(s); return deserialize( in );};
  untyped&                            operator()     ( std::istream &in )       {return deserialize( in );};

  inline untyped&                     operator[] ( size_t n )                   {//clearMap();
    for(size_t i(vectorSize()); i<=n; i++ ) {typeVector::push_back(new untyped);} return *(typeVector::operator[](n));};
  inline untyped&                     operator[] ( std::string s )              {//clearVector();
    typeMap::const_iterator it=typeMap::find(s); if(it!=typeMap::end()) return *it->second; return *(typeMap::operator[](s)=new untyped);};

  friend std::ostream&                operator<< ( std::ostream &, untyped const & );
  friend std::ostream&                operator<< ( std::ostream &, typeMap const & );
  friend std::ostream&                operator<< ( std::ostream &, typeVector const & );
  friend std::ostream&                operator<< ( std::ostream &out, typePair const &that ) {return out << that.first << ": " << that.second;};

  inline bool                         isBinaryMode    ( void )            const {return( !untyped::json );};
  inline bool                         isJsonMode      ( void )            const {return(  untyped::json );};
  inline bool                         isPrettyJsonMode( void )            const {return( untyped::json > 1 );};
  inline void                         binaryMode      ( void )                  {(untyped::json)=0;};
  inline void                         jsonMode        ( void )                  {(untyped::json)=1;};
  inline void                         prettyJsonMode  ( void )                  {(untyped::json)=2;};

 protected:
  static bool                         isNetFormat     ( void )                  {short isNotNet=1; return( !*reinterpret_cast<char const *>(&isNotNet) );};
  template<typename T> static char const *hton        ( T val )                 {
    static T tmp; tmp=val; ntoh( reinterpret_cast<char*>(&tmp), sizeof(T) );
    return( reinterpret_cast<char const *>(&tmp) );
  };  // Net to Host format...
  inline void                         ntoh            ( std::string& p )        {
    if (p.size() && !isNetFormat() )
      for(size_t i(0), j(p.size()-1); i<j; i++, j--) {
//std::cout << "\n char1=" << (int)p[i] << " char2=" << (int)p[j] << std::endl;
        std::swap( p[i], p[j] );
//std::cout << " char1=" << (int)p[i] << " char2=" << (int)p[j] << std::endl << std::endl;
      }
  };
  template<typename T> static inline void ntoh        ( T *p, size_t const size ){
    if (p && !isNetFormat())
      for( char *pt1=reinterpret_cast<char*>(p),*pt2 = pt1+size-1; pt1<pt2; pt1++,pt2-- )
        std::swap( *pt1, *pt2 );
  };

  static inline size_t                stringSize      ( char const *v )         {size_t s(0); if (v) while( *v++ ) s++; return s;};

 private:
  uchar                  _type; /// WARNING: type must be < 32 [5+3 bits shared with desc(structure) in a char for the serialization methods...]

  inline void                         _set            ( size_t l,char const* v ){std::string::assign(v, l);};
  inline void                         _set            ( typeVector   const &v ) {for(size_t i(0); i<v.size(); i++) operator[](i)= *(v[i]);};
  inline void                         _set            ( typeMap      const &v ) {for(typeMap::const_iterator it=v.begin(); it!=v.end(); it++) operator[](it->first)= *(it->second);};
  static void                         _writeTypeAndStructure( std::ostream&, uchar, uchar const & );
  static inline void                  _writeSize      ( std::ostream& o, size_t s ) {o.write( hton(s), sizeof(s) );};
  static uchar                        _readTypeAndStructure( std::istream&, uchar & );
  static inline void                  _readSize       ( std::istream &in, size_t &s ){if( in.read(reinterpret_cast<char*>(&s), sizeof(s)) ) ntoh( &s, sizeof(s) );};

  static untyped                      _getJsonObject  ( std::istream &, char & );
  static untyped                      _getJsonArray   ( std::istream &, char & );
  static untyped                      _getJsonValue   ( std::istream &, char & );
  static untyped                      _getJsonString  ( std::istream &, char & );
  static untyped                      _getJsonChar    ( std::istream &, char & );
  static untyped                      _getJsonNumber  ( std::istream &, char & );
  static untyped                      _getJsonBool    ( std::istream &, char & );
  static void                         _getJsonNull    ( std::istream &, char & );
  static void                         _getJsonComment ( std::istream &, char & );
  static inline void                  _jsonTAB        ( std::ostream &o )       {if(untyped::json>1) for(size_t i(untyped::json-2); i; i--) o.write(" ", 1);};
  static inline void                  _jsonNL         ( std::ostream &o )       {if(untyped::json>1) o.write("\n", 1);};
  static inline void                  _jsonINCR       ( void )                  {if(untyped::json>1) untyped::json++;};
  static inline void                  _jsonDECR       ( void )                  {if(untyped::json>2) untyped::json--;};

  static inline bool                  _isWhiteSpace   ( char &c )               {if(c==' ' || c=='\t' || c=='\r' || c=='\n') return true; return false;};
  static inline untyped               _exitJsonObject ( std::istream &in,char x){char c;while(in.read(&c, 1) && c!=x); return untyped();};

 };

}
using namespace noType;
#endif