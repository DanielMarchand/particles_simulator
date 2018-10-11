import numpy as np
def conjugate__gradient(A, b, x0, tol):
    r_old = r_new = np.einsum('ij,j->i', A, b, max_iter);
    p = r_old;
    x_old = x_new = x0;
    iter = 0
    while True:
        alpha = ((np.einsum('k,k->', r.transpose(),r))/
                 (np.einsum(p.transpose(),'i',A,'ij',p,'i','')))
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
    return x_new
