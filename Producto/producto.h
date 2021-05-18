/*
 *  Clase Producto
 *  
 * 
 * 
 * 
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#define IDLENGHT 10

// categorias
#define C_SPORT 1
#define C_HOME 2
#define C_CLOTHES 3
#define C_CAR 4
#define C_TECH 5
#define C_OTHER 6
#define C_NONE 0

class producto {
  protected:
    unsigned id_ = C_NONE;
    std::string name_ = "Default";
    unsigned category_ = 0;
    float price_ = -1;
    bool available_;
    std::fstream product_list_;
  public:
    producto()  {}
    /* ************************************************************************************
    * Necesario para devolver objetos producto.
    * Posiblemente hay que rellenar para que haga una copia (probar antes codigo con create)
    * Es posible que return create de Búsqueda_id no funcione bien, que devuelva algo vacío.
    * ************************************************************************************/
    producto(const producto& prod)  {}  
    ~producto()  {}
    producto& create(std::string name, unsigned category, float price);
    std::string get_name() { return name_; }
    unsigned get_category() { return category_; }
    float get_price() { return price_; }
    unsigned get_id() { return id_; }
    bool get_available() { return available_; }
    void print();
    producto Busqueda_id(unsigned id = 0);
};


// Yo usaría esto en el constructor, pasandole al constructor los parametros name, category, price.
producto& producto::create(std::string name, unsigned category, float price) {
  name_ = name;
  category_ = category; 
  price_ = price;
  int aux = 0;

  int seed = (stoi(name_) + category_);
  srand(seed);
  for(unsigned i = 1; i < IDLENGHT; i++) {
    aux += rand() % 10;
    aux *= 10;
  }
  id_ = aux;
  return *this;
}

void producto::print() {
  std::cout << "ID: " << id_ 
            << "\nNombre: " << name_ 
            << "\nCategoria: ";
  switch (category_) {

    case C_SPORT:
      std::cout << "Deportes";
      break;

    case C_HOME:
      std::cout << "Articulos del hogar";
      break;

    case C_CLOTHES:
      std::cout << "Ropa y calzado";
      break;

    case C_CAR:
      std::cout << "Articulos para el coche";
      break;

    case C_TECH:
      std::cout << "Tecnología y electrónica";
      break;

    case C_OTHER:
      std::cout << "Otros";
      break;

    case C_NONE:
      std::cout << "Ninguna";
      break;

    default:
      std::cout << "ERROR";
      break;
  }
  std::cout << "\nPrecio: " << price_ << "\n";
}
