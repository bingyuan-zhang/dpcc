#' L1 convex clustering with a lambda sequence.
#'
#' @param X a data matrix of n * p or a data vector with length n.
#' @param lam a sequence of lambdas.
#'
#' @return A sequence of estimated centroids.
#' @export
#'
#' @details A list with length p equal to the dimension of the data matrix. Each dimension includes a sequence of vectors. Each vector includes the estimated centroids with a certain tuning parameter lambda.
#'
#' @examples
#' # generate a data matrix with n = 10 and p = 2.
#' X = matrix(rnorm(10*2), 10, 2)
#' # set the biggest lambda in the sequence.
#' lam_max = find_lambda(X)
#' # set the length of the sequence.
#' K = 10
#' # equally separate the sequence with K.
#' Lam = sapply(1:K, function(i) i/K*lam_max)
#' cpaint(X,Lam)
cpaint= function(X,lam) {
  k = length(lam)
  res = list()
  if(is.matrix(X)){
    p = ncol(X)
    for (i in 1:p) {
      y = sort(X[,i])
      ord = order(X[,i])
      res_temp = NULL
      for (j in 1:k) {
        res_t = rep(0,length(ord))
        res_t[ord] = C_paint(y,lam[j])
        res_temp = rbind(res_temp,res_t)
      }
      row.names(res_temp) <- paste("lam", 1:k, sep = "")
      res[[i]] = res_temp
    }
    names(res) <- paste("dim", 1:p, sep = "")
  }
  if(is.vector(X)){
    y = sort(X)
    ord = order(X)
    res_temp = NULL
    for (j in 1:k) {
      res_t = rep(0,length(ord))
      res_t[ord] = C_paint(y,lam[j])
      res_temp = rbind(res_temp,res_t)
    }
    row.names(res_temp) <- paste("lam", 1:k, sep = "")
    res[[1]] = res_temp
  }
  return(res)
}

