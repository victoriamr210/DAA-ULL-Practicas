#include <iostream>
#include <vector>

class table{

  private:
    std::string topString_;
    std::string subString_;
    int row;
    int col;
    std::vector<int> v_;

  public:
    table(std::string top, std::string sub);
    int pos(int i, int j);
    void build_empty(void);
    void write(void);

};
