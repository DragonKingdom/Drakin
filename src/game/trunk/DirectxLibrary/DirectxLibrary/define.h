#ifndef DEFINE_H
#define DEFINE_H

#define SAFE_DELETE(p) if(p){ delete p; p = NULL; }
#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL;}
#define SAFE_DELETE_ARRAY(x) if(x) { delete[] x; x = NULL; }

#endif /* DEFINE_H */
