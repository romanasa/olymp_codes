struct node {
  static node *null;
  int x, h;
  node *l, *r;

  void calc() { h = 1 + max(l->h, r->h); }
  node() { l = r = this, h = 0, x = 0; }
  node( int x, node* l = null, node* r = null ) : x(x), l(l), r(r) { calc(); }
};
node* node::null = new node();

node* rot_left( node* t ) { // (t->l, t)
  return new node(t->l->x, t->l->l, new node(t->x, t->l->r, t->r));
}
node* rot_right( node* t ) { // (t, t->r)
  return new node(t->r->x, new node(t->x, t->l, t->r->l), t->r->r);
}

void add_slow( node* &t, int x ) {
  if (t == node::null) {
    t = new node(x);
    return;
  }
  if (x < t->x) {
    add_slow(t->l, x);
    if (t->l->h > t->r->h + 1)
      t = rot_left(t);
  } else {
    add_slow(t->r, x);
    if (t->r->h > t->l->h + 1)
      t = rot_right(t);
  }
  t->calc();
}