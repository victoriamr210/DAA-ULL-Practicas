#include <iostream>
#include <vector>
#include <fstream>

class graph {

  private:
    int nodes_;
    std::vector<float> d_;
    std::vector<int> sol_;
  
  public:
    graph(char file[]);
    void read(char file[]);
    int pos(int i, int j);
    void set_item(float r, int i, int j);
    void set_d(void);
    void write(void);


}; 