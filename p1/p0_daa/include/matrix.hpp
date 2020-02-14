#pragma once
#include <iostream>
//modificacion metodo que calcule la traspuesta

class Matrix{
  private:
    int n_; //filas
    int m_; //columnas
    // std::vector<int> v_;
    int **v_; //doble puntero, representa la matriz
    int **t_;

  public:
    //constructor con semilla
    Matrix(int n, int m, int seed){
      n_=n;
      m_=m;
      v_ = new int*[n_];
      for(int i=0; i<n_; i++){
        v_[i]=new int[m_];
      }
      srand(seed);
      set();
    }

    //constructor incia matriz a 0
    Matrix(int n, int m){
      n_=n;
      m_=m;
      v_ = new int *[n_];
      for (int i = 0; i < n_; i++){
        v_[i] = new int[m_];
      }

      set_toz();
    }

    //destructor, realiza delete de los punteros
    ~Matrix(){
      for(int i=0; i<n_; i++){
        delete [] v_[i];
      }
      delete [] v_;
    }

    //devuelve elemento de la posicion i,j
    int pos(int i, int j){
      return v_[i][j];
    }

    int pos_t(int i, int j){
      return t_[i][j];
    }

    void set_item(int i, int j, int val){
      v_[i][j]=val;
    }
    
    //rellena matriz con numeros aleatorios
    void set(void){
      for(int i=0; i<n_; i++){
        for(int j=0; j<m_; j++)
        v_[i][j]=rand() % 10;
      }
    }

    //rellena matriz con ceros
    void set_toz(void){
      for(int i=0; i<n_; i++){
        for(int j=0; j<m_; j++)
        v_[i][j]=0;
      }
    }
    
    void trasponer(void){
      
      t_ = new int*[m_];
      for(int i=0; i<m_; i++){
        t_[i]= new int[n_];
      }

      for(int i=0; i<m_; i++){
        for(int j=0; j<n_; j++){
          t_[i][j]=v_[j][i];
        }
      }
    }

    void write(void){
      for(int i=0; i<n_; i++){
        for(int j=0; j<m_; j++){
          std::cout << v_[i][j] << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }

    void write_t(void){
      for(int i=0; i<n_; i++){
        for(int j=0; j<m_; j++){
          std::cout << t_[i][j] << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }

    //numero de filas
    int get_n(void){ return n_;}
    
    //numero de columnas
    int get_m(void){return m_;}

};