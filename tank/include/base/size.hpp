#if !defined(_SIZE_HPP_)
#define _SIZE_HPP_

/**
 * 大小信息
*/
class Size
{
private:
    /// @brief 行数，高度
    int mRows;
    /// @brief 列数，宽度 
    int mCols;
public:
    Size(): Size(0, 0) {}
    Size(int rows, int cols): mRows(rows), mCols(cols) {}
    Size(const Size &other) { set(other.mRows, other.mCols); }
    int getRows() { return mRows; }
    int getCols() { return mCols; }
    void set(int rows, int cols) { mRows = rows, mCols = cols; }
    bool operator==(const Size &other) const { return mRows == other.mRows && mCols == other.mCols; }
};

#endif // _SIZE_HPP_
