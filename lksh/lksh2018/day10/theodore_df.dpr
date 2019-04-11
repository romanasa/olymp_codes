{
	SPb ETU Contest in Petrozavodsk

	Problem:	Theodore Roosevelt
	Author:		Dmitry Filippov
	Solution:	Dmitry Filippov
	Date:		15.08.2004
}

{$apptype console}

const
  maxn = 100000;

var
  n, m, k, cx, cy, c, s, i, j, t, l, r, p: integer;
  x, y: array[1..maxn] of integer;

function svecmul(vx1, vy1, vx2, vy2: integer): integer;
var
  a, b: int64;
begin
  result := 0;

  a := vx1;
  a := a*vy2;
  b := vx2;
  b := b*vy1;

  if a > b then
    result := 1
  else
    if a < b then
      result := -1;
end;

begin
  assign(input, 'theodore.in'); reset(input);
  assign(output, 'theodore.out'); rewrite(output);

  read(n, m, k);

  s := 1;

  for i := 1 to n do begin
    read(x[i], y[i]);

    if (y[i] < y[s]) or ((y[i] = y[s]) and (x[i] < x[s])) then
      s := i;
  end;

  c := 0;

  for t := 1 to m do begin
    read(cx, cy);

    if cy >= y[s] then begin

      l := 0;
      r := n;

      while l < r do begin
        p := (l + r) shr 1;

        i := p + s;
        if i > n then
          dec(i, n);

        if svecmul(x[i] - x[s], y[i] - y[s], cx - x[s], cy - y[s]) >= 0 then
          l := p + 1
        else
          r := p;
      end;

      dec(l);

      if l = n - 1 then begin
        j := l + s;
        if j > n then
          dec(j, n);

        if svecmul(x[j] - x[s], y[j] - y[s], cx - x[s], cy - y[s]) = 0 then
          dec(l);
      end;

      if (l > 0) and (l < n - 1) then begin
        i := l + s;
        j := l + s + 1;
        if i > n then
          dec(i, n);
        if j > n then
          dec(j, n);

        if svecmul(x[j] - x[i], y[j] - y[i], cx - x[i], cy - y[i]) >= 0 then
          inc(c);
      end;
    end;
  end;

//{debug} writeln(c);

  if c >= k then
    writeln('YES')
  else
    writeln('NO');
end.
