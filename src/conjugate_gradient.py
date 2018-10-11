import numpy as np
import optimize.py


def ex_func_quad(A, b, c, x):
    return np.einsum(x.T,'i',A,'ij',p,'j','')) + np.einsum('i,ij->j', b, x) + c



def conjugate__gradient(coeffs, x0, tol):

    A = np.array([[coeff(2, 0)/1, coeff(1, 1)/2],
                  [coeff(1, 1)/2, coeff(0, 2)/1]])
    b = np.array([coeff(1, 0), coeff(0, 1)])
    c = coeff(0, 0)
    
    r_old = r_new = np.einsum('ij,j->i', A, b, max_iter);
    p = r_old;
    x_old = x_new = x0;
    ret_arr = np.append(x0, ex_func_quad(A, b, c, x0))
    iter = 0
    
    while True:
        alpha = ((np.einsum('k,k->', r.transpose(),r))/
                 (np.einsum(p.transpose(),'i',A,'ij',p,'j','')))
        x_new = x_old + aplha * p ;
        r_new = r_old - alpha * np.einsum('ij,j->i',A, p)
        r_norm = np.sqrt(np.einsum('i,i->', r.transpose(), r))
        if r_norm < tol or iter > max_iter:
            break
        else:
            beta = np.einsum('i,i->',r_new, r_new)/np.einsum('i,i->',r_old, r_old)
            p = beta * p + r_new
            iter = iter +1
            x_old = x_new
            r_old = r_new
            ret_tmp = np.append(x_new, ex_func_quad(A, b, c, x_new))
            np.append(ret_arr, ret_tmp, aix = 0)
    return ret_arr
