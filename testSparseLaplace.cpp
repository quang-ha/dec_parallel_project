#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>
#include <vector>
#include <iostream>
#include <armadillo>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

void buildProblem(std::vector<T>& coefficients, Eigen::VectorXd& b, int n);
void saveAsBitmap(const Eigen::VectorXd& x, int n, const char* filename);

int main(int argc, char** argv)
{
  int n = 4;  // size of the image
  int m = n*n;  // number of unknows (=number of pixels)
  // Assembly:
  std::vector<T> coefficients;            // list of non-zeros coefficients
  Eigen::VectorXd b(m);                   // the right hand side-vector resulting from the constraints
  buildProblem(coefficients, b, n);
  SpMat A(m,m);
  A.setFromTriplets(coefficients.begin(), coefficients.end());
  std::cout << "Laplacian matrix A:" << std::endl
	    << A << std::endl << std::endl;

  Eigen::MatrixXd Adense = Eigen::MatrixXd(A);
  std::cout << "Dense Laplacian matrix A:" << std::endl
	    << Adense << std::endl << std::endl;
  
  // Getting the eigenvalue from A
  Eigen::EigenSolver<Eigen::MatrixXd> es(Adense);
  std::cout << "The eigenvalues of A are:" << std::endl
  	    << es.eigenvalues() << std::endl;
  
  // // Solving:
  // Eigen::SimplicialCholesky<SpMat> chol(A);  // performs a Cholesky factorization of A
  // Eigen::VectorXd x = chol.solve(b);         // use the factorization to solve for the given right hand side
  
  return 0;
}

/*=================================================================*/

void insertCoefficient(int id, int i, int j, double w, std::vector<T>& coeffs,
                       Eigen::VectorXd& b, const Eigen::VectorXd& boundary)
{
  int n = int(boundary.size());
  int id1 = i+j*n;
        if(i==-1 || i==n) b(id) -= w * boundary(j); // constrained coefficient
  else  if(j==-1 || j==n) b(id) -= w * boundary(i); // constrained coefficient
  else  coeffs.push_back(T(id,id1,w));              // unknown coefficient
}

/*=================================================================*/

void buildProblem(std::vector<T>& coefficients, Eigen::VectorXd& b, int n)
{
  b.setZero();
  Eigen::ArrayXd boundary = Eigen::ArrayXd::LinSpaced(n, 0,M_PI).sin().pow(2);
  for(int j=0; j<n; ++j)
  {
    for(int i=0; i<n; ++i)
    {
      int id = i+j*n;
      insertCoefficient(id, i-1,j, -1, coefficients, b, boundary);
      insertCoefficient(id, i+1,j, -1, coefficients, b, boundary);
      insertCoefficient(id, i,j-1, -1, coefficients, b, boundary);
      insertCoefficient(id, i,j+1, -1, coefficients, b, boundary);
      insertCoefficient(id, i,j,    4, coefficients, b, boundary);
    }
  }
}

/*=================================================================*/
