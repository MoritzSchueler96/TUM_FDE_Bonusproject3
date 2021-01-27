#include "../include/KNN.hpp"
#include "../include/Util.hpp"
#include <gtest/gtest.h>

using namespace std;
//---------------------------------------------------------------------------
TEST(KNearestNeighbors, Top1NearestNeighbor)
/// Test if we find even one neighbor
{
  // Read the matrix file and store it as internal matrix.
  auto matrix_file = getDir(__FILE__) + "/data/dataSmall.mtx";
  Matrix matrix = Matrix::readFile(matrix_file);

  unsigned start_node = 205;
  unsigned k = 1; // The number of neighbors we are interested in.

  auto result = getKNN(matrix, start_node, k);

  std::sort(result.begin(), result.end());
  std::vector<Matrix::Entry> expected = {{1874456, 0.60409999999999997}};

  ASSERT_EQ(result.size(), expected.size())
      << "Result does not contain correct number of elements.";

  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected[i])
        << "Result and expected result differ at index " << i << endl
        << "result[i]: " << result[i] << endl
        << "expected[i]: " << expected[i];
  }
}
//---------------------------------------------------------------------------
TEST(KNearestNeighbors, Top3NearestNeighbors)
/// Test if we find even one neighbor
{
  // Read the matrix file and store it as internal matrix.
  auto matrix_file = getDir(__FILE__) + "/data/dataSmall.mtx";
  Matrix matrix = Matrix::readFile(matrix_file);

  unsigned start_node = 205;
  unsigned k = 3; // The number of neighbors we are interested in.

  auto result = getKNN(matrix, start_node, k);

  std::sort(result.begin(), result.end());

  std::vector<Matrix::Entry> expected = {{1874456, 0.60409999999999997},
                                         {1552034, 1.3064519999999999},
                                         {1901000, 1.510168}};

  ASSERT_EQ(result.size(), expected.size())
      << "Result does not contain correct number of elements.";

  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected[i])
        << "Result and expected result differ at index " << i << endl
        << "result[i]: " << result[i] << endl
        << "expected[i]: " << expected[i];
  }
}
//---------------------------------------------------------------------------
TEST(KNearestNeighbors, Top10NotReachable)
/// Test if we find even one neighbor
{
  // Read the matrix file and store it as internal matrix.
  auto matrix_file = getDir(__FILE__) + "/data/dataSmall.mtx";
  Matrix matrix = Matrix::readFile(matrix_file);

  unsigned start_node = 205;
  unsigned k = 10; // The number of neighbors we are interested in.

  auto result = getKNN(matrix, start_node, k);

  std::sort(result.begin(), result.end());

  std::sort(result.begin(), result.end());

  // We can find at most 7 neighbors, although we search for 10
  std::vector<Matrix::Entry> expected{{1874456, 0.6041},  {1552034, 1.30645},
                                      {1901000, 1.51017}, {1836251, 1.97767},
                                      {569161, 2.29636},  {572469, 2.78174},
                                      {1253738, 3.14601}};
  ASSERT_EQ(result.size(), expected.size())
      << "Result does not contain correct number of elements.";

  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected[i])
        << "Result and expected result differ at index " << i << endl
        << "result[i]: " << result[i] << endl
        << "expected[i]: " << expected[i];
  }
}
//---------------------------------------------------------------------------
TEST(KNearestNeighbors, Top10NearestNeighbors)
/// Test if we find even one neighbor
{
  // Read the matrix file and store it as internal matrix.
  auto matrix_file = getDir(__FILE__) + "/data/dataSmall.mtx";
  Matrix matrix = Matrix::readFile(matrix_file);

  unsigned start_node = 210;
  unsigned k = 10; // The number of neighbors we are interested in.

  auto result = getKNN(matrix, start_node, k);

  std::sort(result.begin(), result.end());
  std::vector<Matrix::Entry> expected{{764770, 0.664075}, {141882, 0.768491},
                                      {1666237, 1.27067}, {1753834, 1.5857},
                                      {107535, 1.60894},  {460877, 1.76713},
                                      {172760, 2.0208},   {1171827, 2.2021},
                                      {1139888, 2.34425}, {390238, 2.488}};
  ASSERT_EQ(result.size(), expected.size())
      << "Result does not contain correct number of elements.";

  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected[i])
        << "Result and expected result differ at index " << i << endl
        << "result[i]: " << result[i] << endl
        << "expected[i]: " << expected[i];
  }
}