#ifndef GENERICPROXY_HPP_
#define GENERICPROXY_HPP_
#include <string>
#include <memory>
#include <iostream>
#include <type_traits>
namespace GenericFactory {
  /*! A simple proxy for registering into a factory.

    It provides the builder as static method 
    and the automatic registration mechanism.

    \param Factory The type of the factory.  
    \param ConcreteProduct is the derived (concrete) type to be 
    registered in the factory
    
    @note I have to use the default builder provided by the factory. No check is made to verify it
    @todo Add check un builder type using type_traits and static_assert
  */
  template
  <typename Factory, typename ConcreteProduct>
  class Proxy {
  public:
    
    typedef typename  Factory::AbstractProduct_type AbstractProduct_type;
    typedef typename  Factory::Identifier_type Identifier_type;
    typedef typename  Factory::Builder_type Builder_type;
    // The type returned by the builder
    typedef typename  std::result_of<Builder_type()>::type Result_type;
    typedef           Factory Factory_type;
    
    //! The constructor does the registration.
    Proxy(Identifier_type const &);

    //! The builder. Must comply with the signature.
    /*!
      Actually you do not need to use the proxy to define the builder, you may do it in a simpler way.
      I assume that the builder is type that returns Result_type
      and that Result_type can be constructed with a pointer the
      concrete product. I also assume that Result_type takes
      care of memory handling (i.e. is a unique_ptr or something
      that behaves like a unique_prt.
     */
    static Result_type Build()
    {
      return Result_type(new ConcreteProduct());
    }
    //! This is a more explicit version
    //    static std::unique_ptr<AbstractProduct_type> Build(){
    //return std::make_unique<ConcreteProduct>();
    //}
    
  private:
    Proxy(Proxy const &)=delete; //
    Proxy & operator=(Proxy const &)=delete; //
  };
  
  
  template<typename F, typename C>
  Proxy<F,C>::Proxy(Identifier_type const & name) {
    // get the factory. First time creates it.
    Factory_type & factory(Factory_type::Instance());
    // Insert the builder. The & is not needed.
    factory.add(name,&Proxy<F,C>::Build);
    std::cout<<"Added "<< name << " to factory"<<std::endl;
  }
}

#endif /* RULESHANDLER_HPP_ */
