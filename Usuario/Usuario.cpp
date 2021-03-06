#include "Usuario.h"

Usuario::~Usuario()  {
  if (file_passwd_.is_open())
    file_passwd_.close();
  if (file_name_.is_open())
    file_name_.close();
}


bool
Usuario::CheckUser(std::string nombre)  {
  file_name_.open("../Usuario/Usuarios.txt", std::fstream::in);
  if (file_name_.is_open() )  {
    std::string nombre_en_linea;

    // Se comprueba linea por línea si un usuario existe o no.
    while (file_name_ >> nombre_en_linea ) {
      if (nombre == nombre_en_linea)  {
        file_name_.close();
        return true;
      }
    }
    file_name_.close();
    return false;
  }
  else  {
    std::cout << "Error al comprobar fichero de nombres.\n"; // Momentaneo.
    //throw "Error";
  }
  
}


bool
Usuario::CheckPasswd(std::string passwd)  {
  file_passwd_.open("../Usuario/Passwords.txt", std::fstream::in);
  if (file_passwd_.is_open() )  {
    std::string passwd_linea;

    while (std::getline(file_passwd_, passwd_linea, ':'))  {

      if (passwd_linea == nombre_)  {
        std::getline(file_passwd_,passwd_linea);
        if (passwd == passwd_linea)  {
          file_passwd_.close();
          return true;
        }
        else  {
          file_passwd_.close();
          return false;
        }
      }
      else 
        std::getline(file_passwd_, passwd_linea);
    }
    file_passwd_.close();
    return false;
  }
  else  {
    std::cout << "Error al comprobar fichero de passwd.\n"; //Momentaneo
    //throw "Error";
  }
  
}


bool
Usuario::AddName()  {
  if (CheckUser(nombre_))
    return false;
  
  else {
    file_name_.open( "../Usuario/Usuarios.txt", std::fstream::out | std::fstream::app);
    if (file_name_.is_open())  {
      file_name_ << nombre_ << "\n";
      file_name_.close();

      return AddPasswd();
    }
    else  {
      std::cout << "No se pudo abrir el fichero.\n";
      return false;
    }
  }
  return true;
}


bool
Usuario::AddPasswd()  {
  file_passwd_.open( "../Usuario/Passwords.txt", std::fstream::out | std::fstream::app);
  if (file_passwd_.is_open())  {
    file_passwd_ << nombre_ << ":" << passwd_ << "\n";
    file_passwd_.close();
  }
  else  {
    std::cout << "No se pudo abrir el fichero.\n";
    return false;
  }
  return true;
}


void
Usuario::WriteName(std::string new_name)  {
  if (file_name_.is_open())
    file_name_.close();
  if (file_passwd_.is_open())
    file_passwd_.close();
  std::string name;
  file_name_.open("../Usuario/Usuarios.txt", std::fstream::in);
  std::fstream temp_file;
  temp_file.open("Temp.txt", std::fstream::out);
  if (file_name_.is_open() && temp_file.is_open())  {
    while (file_name_ >> name)  {
        if (name == nombre_)  {
          name = new_name;
        }
        temp_file << name << "\n";
    }
    
    file_name_.close();
    remove("../Usuario/Usuarios.txt");
    temp_file.close();
    rename("Temp.txt", "../Usuario/Usuarios.txt");
    name = "";

    file_passwd_.open("../Usuario/Passwords.txt", std::fstream::in);
    temp_file.open("Temp.txt", std::fstream::out);
    if (file_passwd_.is_open() && temp_file.is_open())  {

      while (std::getline(file_passwd_, name, ':'))  {
        if (name == nombre_)  {
          temp_file << new_name << ":";
          std::getline(file_passwd_, name);
          
          temp_file << name << "\n";
        }
        else  {
          temp_file << name << ":";
          std::getline(file_passwd_, name);
          temp_file << name << "\n";      
        }
      }
    file_passwd_.close();
    remove("../Usuario/Passwords.txt");
    temp_file.close();
    rename("Temp.txt", "../Usuario/Passwords.txt");

    }
  }
  else {
    std::cout << "Error al cambiar el nombre\n";
  }
}


// La estructura en el fichero será del nombre del usuario seguido de un espacio y la contraseña en cada línea.
void
Usuario::WritePasswd(std::string new_passwd)  {
  if (file_passwd_.is_open())
    file_passwd_.close();
  std::string passwd;
  file_passwd_.open("../Usuario/Passwords.txt", std::fstream::in);
  std::fstream temp_file;
  temp_file.open("Temp.txt", std::fstream::out);
  if (file_passwd_.is_open() && temp_file.is_open())  {

    while (std::getline(file_passwd_, passwd, ':'))  {
      if (passwd == nombre_)  {
        temp_file << passwd << ":";
        std::getline(file_passwd_, passwd);
        if (passwd == passwd_)  {
          passwd = new_passwd;
        }
        temp_file << passwd << "\n";
      }
      else  {
        temp_file << passwd << ":";
        std::getline(file_passwd_, passwd);
        temp_file << passwd << "\n";      
      }
    }
    file_name_.close();
    remove("../Usuario/Passwords.txt");
    temp_file.close();
    rename("Temp.txt", "../Usuario/Passwords.txt");

  }
  else {
    std::cout << "Error al cambiar el nombre\n";
  }
  
}
