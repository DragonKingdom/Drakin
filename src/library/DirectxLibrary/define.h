#ifndef DEFINE_H
#define DEFINE_H

#define SAFE_DELETE(p) if(p){ delete p; p = NULL; }
#define SAFE_RELEASE(p) if(p){ p->Release(); p = NULL;}
#define SAFE_DELETE_ARRAY(x) if(x) { delete[] x; x = NULL; }

typedef struct _FRECT
{
	float left;
	float top;
	float bottom;
	float right;

	_FRECT();

	_FRECT(float l,float t,float r,float b){
		left = l;
		top = t;
		right = r;
		bottom = b;

	};

}FRECT;

#endif /* DEFINE_H */
