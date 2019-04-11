const MaxN = 50000009;

var a, b, i, j, k: Longint;
  ok: Boolean;

BEGIN
  read (a, b);
  assert ((1 <= a) AND (a <= b) AND (b <= 50000000));
  if a = 1 then inc (a);
  k := 0;
  for i := a to b do begin
    ok := True;
    for j := 2 to trunc(sqrt(i)) do
      if i mod j = 0 then begin
        ok := False;
        break;
      end;
    if ok then inc (k);
  end;
  writeln (k);
END.
