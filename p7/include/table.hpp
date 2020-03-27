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
    void fill_table(void);
    int LCS(int i, int j);
    void solution(void);

};
