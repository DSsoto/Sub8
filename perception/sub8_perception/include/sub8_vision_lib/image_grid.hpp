#include <opencv2/core.hpp>
#include <vector>
#include <stdexcept>

template<typename T>
class ImageGrid
{
public:
  ImageGrid(cv::Mat full_img, int grid_rows, int grid_cols);
  cv::Mat img() const noexcept { return __full_img; }
  cv::Mat operator()(int row, int col);

private:
  cv::Mat_<T> __full_img;
  std::vector<std::vector<cv::Mat>> __image_grid;
};


template<typename T>
ImageGrid<T>::ImageGrid(cv::Mat full_img, int grid_rows, int grid_cols)
{
  __full_img = full_img.clone();
  auto orig_size = __full_img.size();
  auto roi_height = orig_size.height / grid_rows;
  auto roi_width = orig_size.width / grid_cols;

  // Set up rois
  auto roi = cv::Rect(-roi_width, -roi_height, roi_width, roi_height);
  for(int row = 0; row < grid_rows; ++row)
  {
    ++roi.y;
    for(int col = 0; col < grid_cols; ++col)
    {
      ++roi.x;
      __image_grid[row][col] = __full_img(roi);
    }
  }
}

template<typename T>
cv::Mat ImageGrid<T>::operator()(int row, int col)
{
  return __image_grid[row][col];
}


