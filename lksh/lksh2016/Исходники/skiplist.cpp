struct Node {
	Node *r, *d;
	int x, len;
	Node( Node *r, Node *d, int x, int len ) : r(r), d(d), x(x), len(len) { }
};

template <const int H>
struct SkipList {
	Node *root, *p[H];
	int pos[H];

	SkipList() : root(0) {
		forn(i, H)
			root = new Node(0, root, -1, INT_MAX / 2);
	}
	void path( int i ) {
		Node *v = root;
		forn(j, H) {
			while (v->len < i)
				i -= v->len, v = v->r;
			pos[j] = i, p[j] = v, v = v->d;
		}
	}
	void add( int i, int x ) {
	    path(++i);
	    Node *last = 0, *v;
	    for (int add = 1, j = H - 1; j >= 0; j--, add &= rand() & 1) {
	    	(v = p[j])->len++;
	    	if (add)
	    		last = v->r = new Node(v->r, last, x, v->len - pos[j]), v->len = pos[j];
	    } 
	}
	void del( int i ) {
	    path(i);
	    for (int j = H - 1; j >= 0; j--)
	    	if (--p[j]->len < pos[j])
	    		p[j]->len += p[j]->r->len, p[j]->r = p[j]->r->r;
	}
	void out() {
		Node *v = root;
		while (v->d)
			v = v->d;
		for (v = v->r; v; v = v->r)
			writeInt(v->x), writeChar(" \n"[!v->r]);
	}
};

SkipList<17> skipList;
