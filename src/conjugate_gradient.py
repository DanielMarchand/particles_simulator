import numpy as np


def ex_func_quad(A, b, c, x):
    arr_tmp = np.einsum('i,ij->j', x, A)
    z = np.einsum('j,j->', arr_tmp, x)
    z = z - np.einsum('i,i->', b, x) + c
    return z


def ret_val_creator(ret_arr, A, b, c, x):
    ret_tmp = np.append(x, ex_func_quad(A, b, c, x))
    ret_tmp = np.array([ret_tmp])
    ret_arr = np.append(ret_arr, ret_tmp, axis=0)
    return ret_arr


def weighted_norm_cal(v, A):
    return np.einsum('k,k->', np.einsum('i,ij->j', v, A), v)


def norm_cal(v):
    return np.einsum('i,i->', v, v)


def conjugate__gradient(coeff, x0, tol, max_iter):

    A = np.array([[coeff[2, 0]/1, coeff[1, 1]/2],
                  [coeff[1, 1]/2, coeff[0, 2]/1]])
    b = np.array([-coeff[1, 0], -coeff[0, 1]])
    c = coeff[0, 0]
    A2 = 2 * A;
    r_old = b - np.einsum('ij,j->i', A2, x0)
    p = r_old
    x = x0
    ret_arr = np.append(x0, ex_func_quad(A, b, c, x0)).T
    ret_arr = np.array([ret_arr])
    iter = 0

    while True:
        alpha = (norm_cal(r_old) / weighted_norm_cal(p, A2))
        x = x + alpha * p
        r_new = r_old - alpha * np.einsum('ij,j->i', A2, p)
        r_norm = np.sqrt(norm_cal(r_new))
        if r_norm < tol or iter > max_iter:
            ret_arr = ret_val_creator(ret_arr, A, b, c, x)
            break
        else:
            beta = (norm_cal(r_new) / norm_cal(r_old))
            p = beta * p + r_new
            r_old = r_new
            iter = iter + 1
            ret_arr = ret_val_creator(ret_arr, A, b, c, x)
    return ret_arr
