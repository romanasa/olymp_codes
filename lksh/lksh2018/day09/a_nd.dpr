program macro;
const MaxN = 50;  MaxM = 50;  MaxP = 10; MaxL = 10;
      MaxS = (*(MaxL-2)*MaxP+2*)100; {82 states}
      NumLen = 51;  {204 digits}
type str15 = string[15];
     Long  = array [1..NumLen] of word;
var N, M, P, S     : integer;
    SC             : string;
    SS             : set of char;
    PW             : array [1..MaxP] of str15;
    TS             : array [1..MaxS] of str15;
    A              : array [1..MaxS, 1..MaxS] of byte;
    B0, B1         : array [1..MaxS] of Long;
    Res            : Long;

procedure addml (var A : Long; var B : Long; q : longint);  {A:=A+B*q}
var i : integer; res : longint;
begin
  res := 0;
  for i := 1 to NumLen do begin
    res := res + A[i] + B[i]*q;
    A[i] := res mod 10000;
    res := res div 10000
  end;
  if res > 0 then runerror (239)
end;

procedure prt (x : word);
begin
  if x < 10 then write ('0');
  if x < 100 then write ('0');
  if x < 1000 then write ('0');
  write (x)
end;

procedure printl (var A : Long);
var i : integer;
begin
  i := NumLen;  while (A[i] = 0) and (i > 1) do dec(i);
  write (A[i]);
  while i > 1 do begin dec(i); prt(A[i]) end;
  writeln
end;

function addst (T : str15) : integer;
var i : integer;
begin
  for i := 1 to S do if TS[i] = T then begin addst:=i; exit end;
  if S = MaxS then runerror (239);
  inc(S); TS[S]:=T; addst := S
end;

function nextst (u : integer; C : char) : integer;
var S0, S1 : Str15; i : integer;
begin
  if (u <= 0) or (u > S) or not (C in SS) then runerror (239);
  if u = 2 then begin nextst := 2; exit end;
  S0 := TS[u] + C;
  S1 := S0;
  repeat
    for i := 1 to P do
      if S1 = PW[i] then begin nextst := 2; exit end;
    delete (S1, 1, 1)
  until S1 = '';
  repeat
    for i := 1 to S do
      if S0 = TS[i] then begin nextst := i; exit end;
    delete (S0, 1, 1)
  until false;
end;

var i, j, k, _ : integer;
begin
  assign (input, 'censored.in');  reset (input);
  assign (output, 'censored.out');  rewrite (output);
  _ := 0;
  repeat
    inc (_); {$IFNDEF MULTI} if _ > 1 then  runerror(239); {$ENDIF}
    read (M);  if (M < 1) or (M > MaxM) then runerror (239);
    read (N);  if (N < 1) or (N > MaxN) then runerror (239);
    readln (P);  if (P < 0) or (P > MaxP) then runerror (239);
    readln (SC);  if length (SC) <> M then runerror (239);
    SS := [];
    for i := 1 to length (SC) do
      if (SC[i] in [#0..#32]) or (SC[i] in SS) then runerror (239)
      else include (SS, SC[i]);
    for i := 1 to P do begin
      readln (PW[i]);
      if not (length(PW[i]) in [1..MaxL]) then runerror (239);
      if length (PW[i])>N then runerror (239);
      for j := 1 to length(PW[i]) do
        if not (PW[i,j] in SS) then runerror (239)
    end;
    S := 0;
    addst ('');  addst (#26'**END**');
    for i := 1 to P do
      for j := 1 to length(PW[i])-1 do
        addst (copy (PW[i], 1, j));
    fillchar (A, sizeof(A), 0);
    for i := 1 to S do
      for j := 1 to M do
        inc (A[i,nextst(i,SC[j])]);
    fillchar (B0, sizeof(B0), 0);
    B0[1,1] := 1;
    for i := 1 to N do begin
      B1 := B0;
      fillchar (B0, sizeof(B1), 0);
      for k := 1 to S do
        for j := 1 to S do if A[j,k] <> 0 then
          addml (B0[k], B1[j], A[j,k])
    end;
    fillchar (Res, sizeof(Res), 0);
    for j := 1 to S do if j <> 2 then addml (Res, B0[j], 1);
    printl (Res);
  until seekeof;
  {writeln (round(trunc(ln(MaxM)*MaxN/(4*ln(10))+1)));}
end.
