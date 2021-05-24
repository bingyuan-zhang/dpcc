#' L1 convex clustering with a single lambda.
#'
#' @param X a data matrix of n * p or a data vector with length n.
#' @param lam a tuning parameter.
#'
#' @return the estimated centroids.
#' @export
#'
#' @details A list with length p equal to the dimension of the data matrix. Each dimension includes a vector of the estimated centroids.
#'
#' @examples
#' # generate a data matrix with n = 10 and p = 2.
#' X = matrix(rnorm(10*2), 10, 2)
#' lam = find_lambda(X)/2
#' # set a tuning parameter lambda.
#' cdp(X, lam)
#'
cdp = function(X,lam) {
  res = list()
  if(is.vector(X)){
    y = sort(X)
    ord = order(X)
    res_t = C_dp(y,lam)
    res[[1]][ord] = res_t
  }
  if(is.matrix(X)){
    p = ncol(X)
    for (i in 1:p) {
      y = sort(X[,i])
      ord = order(X[,i])
      res_t = C_dp(y,lam)
      res[[i]] = rep(0,length(ord))
      res[[i]][ord] = res_t
    }
  }
  return(res)
}
