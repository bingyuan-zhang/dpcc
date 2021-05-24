#' Return the lambda which causes all the points become fused into one cluster.
#'
#' @param X data matrix of n * p
#'
#' @return the biggest lambda
#' @export
#'
#' @examples
#'X = matrix(rnorm(3*2), 3, 2)
#'find_lambda(X)
find_lambda <- function(X) {
  .Call('_dpcc_find_lambda_c', PACKAGE = 'dpcc', X)
}
