/**
 * @file   Singleton.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Thu Feb  4 17:15:41 2016
 * 
 * @brief  
 * 
 * 
 */

#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
  public:
    T& GetInstance() {
        if (Singleton::instance == nullptr) {
            Singleton::instance = createInstance();
        }
        return *(Singleton::instance);
    }

  protected:
    Singleton<T>() {

    }

  private:
    static T* instance;
    static T* createInstance() {
        return new T();
    }
};

#endif /* SINGLETON_H */
