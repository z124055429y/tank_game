#if !defined(_INPUT_HPP_)
#define _INPUT_HPP_

#include <string>
#include "base/element.hpp"

class Input: public Element
{
private:
    std::string mInput;
public:
    Input(int x, int y, int rows, int cols);
    ~Input();
    void input(int ch);
    std::string getInput() { return mInput; };
    void clear() { mInput.clear(); };
};



#endif // _INPUT_HPP_
