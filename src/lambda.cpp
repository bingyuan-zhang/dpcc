#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double find_lambda_c (NumericMatrix X) {
  NumericMatrix x = clone(X);
  int n = x.nrow();
  int p = x.ncol();
  NumericVector lam (n-1);
  double lam_int = 0;
  double lam_max = 0;

  if (p != 1) {
    double lam_max = 0;
    for (int i = 0; i<p; i++){
      NumericVector y = x(_,i);
      y = y.sort();
      double y_mean = 0;
      double mean_y = mean(y);
      for (int j = 0; j<(n-1); j++){
        y_mean = (j*y_mean + y[j])/(j+1);
        lam[j] = (mean_y - y_mean)/(n-j-1);
      }
      lam_int = max(lam);
      if (lam_int > lam_max) lam_max = lam_int;
    }
    return lam_max;
  }

  else {
    NumericVector y = clone(x);
    y = y.sort();
    double y_mean = 0;
    double mean_y = mean(y);
    for (int j = 0; j<(n-1); j++){
      y_mean = (j*y_mean + y[j])/(j+1);
      lam[j] = (mean_y - y_mean)/(n-j-1);
    }
    lam_int = max(lam);
    if (lam_int > lam_max) lam_max = lam_int;
    return lam_max;
  }
}

