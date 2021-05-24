#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
NumericVector C_dp (NumericVector x, double lam) {

  NumericVector y = clone(x);
  y = y.sort();
  int n = y.length();
  double beta;

  NumericVector U (n-1);
  NumericVector slope (n);
  NumericVector inter (n);
  NumericVector theta (n);
  NumericVector index (1);

  //*The lambda
  NumericVector lambda(n,0.0);
  for(int k=0;k<(n-1);k++){
    lambda(k) = (k+1)*(n-k-1)*lam;
  }
  //*The trivial case
  if(n==2){
    U(0) = y(0) + lambda(0);
    beta = -lambda[0] + y[1];

    if(beta < U[0]){
      beta =  (y[0] + y[1])/2;
    }
    theta[1] = beta;

    if(theta[1] > U[0]) theta[0] = U[0];
    else theta[0] = theta[1];

    return(theta);
  }

  //Deal with theta_1 case
  U(0) = y(0) + lambda(0);
  slope(0) = 1;
  inter(0) = y(0);
  index(0) = 0;

  for(int i=1; i<(n-1) ;i++){
    inter(i) = y(i);
    slope(i) = 1;
    beta = (lambda[i] - lambda[i-1] + inter(i))/slope(i);
    if (beta >= U(i-1)) {
      index.push_back(i);
    }
    else {
      for (int j= index.length()-1; j >= 0; j--) {
        int k = index[j];
        if (beta >= U[k]) {
          index.erase(j+1, index.length());
          index.push_back(i);
          break;
        }
        if (j == 0) {
          inter(i) = inter(i) + inter(k);
          slope(i) = slope(i) + slope(k);
          beta = (lambda(i) + inter(i))/slope(i);
          if (beta >= U(0)){
            index.erase(j+1, index.length());
            index.push_back(i);
          }
          else {
            NumericVector ind = (1);
            ind(0) = i;
            index = ind;
          }
          break;
        }
        else {
          inter(i) = inter(i) + inter(k);
          slope(i) = slope(i) + slope(k);
          beta = (lambda(i) - lambda(index(j-1)) + inter(i))/slope(i);
        }
      }
    }
    U(i) = beta;
  }

  // find theta_n
  beta = -lambda(n-2) + y(n-1);
  inter(n-1) = y(n-1);
  slope(n-1) = 1;
  for (int j = index.length()-1; j >= 0; j--) {
    int k = index[j];
    if (beta >= U[k]) {
      break;
    }
    if (j == 0) {
      inter(n-1) = inter(n-1) + inter(k);
      slope(n-1) = slope(n-1) + slope(k);
      beta = inter(n-1)/slope(n-1);
      break;
    }
    else {
      inter(n-1) = inter(n-1) + inter(k);
      slope(n-1) = slope(n-1) + slope(k);
      beta = (- lambda(index(j-1)) + inter(n-1))/slope(n-1);
    }
  }
  theta(n-1) = beta;

  // find all the theta_2, ..., theta_{n-1}
  for (int j = n-2; j>=0; j--){
    if (theta[j+1] > U[j]) theta[j] = U[j];
    else theta[j] = theta[j+1];
  }
  return(theta);
}

// [[Rcpp::export]]
NumericMatrix C_paint (NumericVector x, NumericVector lambda) {
  int n = x.length();
  int k = lambda.length();
  NumericMatrix Theta (k,n);
  for (int i = 0; i<k; i++) {
    Theta(i,_) = C_dp(x,lambda(i));
  }
  return(Theta);
}










