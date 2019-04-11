{$o-,r-,q-}
const
  maxN = 2001;
  P: int64 = 301703;
  Q: int64 = 239017;

var
  w, h: longint;
  a: array[0..maxN, 0..maxN] of char;
  res, z: array[0..maxN] of longint;
  ha: array[0..maxN, 0..maxN] of int64;
  PP, QQ: array[0..maxN] of int64;

function min( a, b: longint ): longint;
  begin
    if (a < b) then begin
      min := a
    end else begin
      min := b
    end;
  end;

function solve( w, h: longint ): longint;
  var
    i, j, l, r, shift: longint;
  begin
    for shift := 1 to w do begin
      res[shift] := 0;
    end;
    for i := 0 to h - 1 do begin
      z[0] := w;
      l := -1; r := -1;
      for j := 1 to w - 1 do begin
        z[j] := 0;
        if (j <= r) then begin
          z[j] := min(r - j + 1, z[j - l]);
        end;
        while ((j + z[j] < w) and (a[i][z[j]] = a[i][j + z[j]])) do begin
          inc(z[j]);
        end;
        if (j + z[j] - 1 > r) then begin
          l := j;
          r := j + z[j] - 1;
        end;
      end;
      for j := 1 to w - 1 do begin
        if (j + z[j] = w) then begin
          inc(res[j]);
        end;
      end;
      inc(res[w]);
    end;
    for shift := 1 to w div 2 do begin
      if (res[shift] = h) then begin
        solve := shift;
        exit;
      end;
    end;
    solve := -1;
  end;

var
  i, j: longint;
  xw, xh, xs: longint;
  l, k, sh: longint;

begin
  assign(input, 'shuttle.in');
  reset(input);
  assign(output, 'shuttle.out');
  rewrite(output);

  readln(h, w);
  for i := 0 to h - 1 do begin
    for j := 0 to w - 1 do begin
      read(a[i][j]);
    end;
    readln;
  end;
  writeln(erroutput, 'read end');
  PP[0] := 1;
  QQ[0] := 1;
  for i := 1 to maxN - 1 do begin
    PP[i] := PP[i - 1] * P;
    QQ[i] := QQ[i - 1] * Q;
  end;
  fillchar(ha, sizeof(ha), 0);
  for i := h - 1 downto 0 do begin
    for j := w - 1 downto 0 do begin
      ha[i][j] :=
        int64(a[i][j]) +
        ha[i + 1][j] * P +
        ha[i][j + 1] * Q -
        ha[i + 1][j + 1] * P * Q;
    end;
  end;
  writeln(erroutput, ha[h][w]);
  writeln(erroutput, 'hash count end');
  xw := w;
  xh := h;
  xs := 0;
  l := solve(w, h);
  writeln(erroutput, l);
  writeln(erroutput, 'solve end');
  for k := 1 to h div 2 do begin
    for sh := 0 to l - 1 do begin
      if (int64(ha[0][0] -
        ha[h - k][0] * PP[h - k] -
        ha[0][w - sh] * QQ[w - sh] +
        ha[h - k][w - sh] * PP[h - k] * QQ[w - sh]) = ha[k][sh]) then begin
        if (xw * xh > k * l) then begin
	  xw := l;
	  xh := k;
          xs := sh;
	end;
      end;
    end;
  end;
  writeln(erroutput, 'end');
  writeln(xh, ' ', xw, ' ', xs);
end.
