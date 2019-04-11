{$o-,r+,q+}
const
    max_t = 100000;

function gcd(a, b: longint): longint;
var
    t: longint;
begin
    while a <> 0 do begin
        t := b mod a;
        b := a;
        a := t;
    end;
    gcd := b;
end;

const
    INIT = 0;
    ON_A = 1;
    ON_B = 2;
    READY = 0;
    FLIP_A = 4;
    FLIP_B = 8;

var
    a, b, t, g: longint;
    p: array [0..max_t] of longint;
    script: array [1..max_t] of longint;
    sl: longint;
    time: longint;
    u: array [0..max_t] of boolean;

procedure mark(s: longint);
var
    i: longint;
begin
    if not u[s] then begin
        u[s] := true;
        for i := t downto s do begin
            if (p[i] <> 0) and (p[i - s] = 0) then begin
                p[i - s] := s;
            end;
        end;
    end;
end;

function check(tm: longint): boolean;
begin
    time := tm;
    check := (tm <= t) and (p[tm] <> 0);
end;

procedure append(condition, action: longint);
begin
    script[sl] := script[sl] + condition;
    inc(sl);
    script[sl] := action;
end;

procedure modifyAction(command: longint);
begin
    if script[sl] and (FLIP_A or FLIP_B) <> 0 then begin
        script[sl] := script[sl] xor command;
    end;
end;

function finda(ca, cb: longint): boolean; forward;

function findb(ca, cB: longint): boolean;
var
    dt: longint;
    tm: longint;
begin
    dt := b * cb - a * ca;
    tm := a * ca;

    if tm > t then begin
        findb := false;
        exit;
    end;

    //writeln(0, ' ', dt, ' ', tm);
    if dt > a then begin
        if findb(1 + ca, cb) then begin
            append(ON_A, FLIP_A);
            findb := true;
        end else begin
            findb := false;
        end;
    end else begin
        mark(2 * dt);
        if check(tm) then begin
            findb := true;
        end else if check(tm + dt) then begin
            append(ON_B, FLIP_A);
            findb := true;
        end else if finda(1 + ca, cb) then begin
            append(ON_B, FLIP_A);
            findb := true;
        end else begin
            findb := false
        end;
        if findb then begin
            while p[time] = 2 * dt do begin
                modifyAction(FLIP_B);
                append(ON_A, FLIP_A or FLIP_B);
                append(ON_B, FLIP_A);
                time := time + 2 * dt;
            end;
        end;
    end;
end;

function finda(ca, cb: longint): boolean;
var
    dt: longint;
    tm: longint;
begin
    dt := a * ca - b * cb;
    tm := b * cb;

    if tm > t then begin
        finda := false;
        exit;
    end;

    //writeln(dt, ' ', 0, ' ', tm);
    if dt > b then begin
        if finda(ca, 1 + cb) then begin
            append(ON_B, FLIP_B);
            finda := true;
        end else begin
            finda := false;
        end;
    end else begin
        mark(2 * dt);
        if check(tm) then begin
            finda := true;
        end else if check(tm + dt) then begin
            append(ON_A, FLIP_B);
            finda := true;
        end else if findb(ca, 1 + cb) then begin
            append(ON_A, FLIP_B);
            finda := true;
        end else begin
            finda := false
        end;
        if finda then begin
            while p[time] = 2 * dt do begin
                modifyAction(FLIP_A);
                append(ON_B, FLIP_A or FLIP_B);
                append(ON_A, FLIP_B);
                time := time + 2 * dt;
            end;
        end;
    end;
end;

var
    i: longint;
    f: boolean;
begin
    assign(input, 'clocks.in'); reset(input);
    assign(output, 'clocks.out'); rewrite(output);

    read(a, b, t);

    g := gcd(a, b);
    if t mod g <> 0 then begin
        writeln('Impossible');
        exit;
    end;

    t := t div g;
    a := a div g;
    b := b div g;

    p[t] := -1;
    mark(a);
    mark(b);

    sl := 1;
    if a < b then begin
        f := findb(1, 1);
        append(ON_A, FLIP_A or FLIP_B);
    end else begin
        f := finda(1, 1);
        append(ON_B, FLIP_A or FLIP_B);
    end;
    if f then begin
        while p[time] = b do begin
            append(ON_B, FLIP_B);
            time := time + b;
        end;
        while p[time] = a do begin
            append(ON_A, FLIP_A);
            time := time + a;
        end;
        for i := sl downto 1 do begin
            if script[i] and ON_A = ON_A then begin
                write('When A stops: ');
            end else if script[i] and ON_B = ON_B then begin
                write('When B stops: ');
            end else begin
                write('Initially: ');
            end;
            if script[i] and FLIP_A = FLIP_A then begin
                if script[i] and FLIP_B = FLIP_B then begin
                    write('flip A and B');
                end else begin
                    write('flip A');
                end;
            end else begin
                if script[i] and FLIP_B = FLIP_B then begin
                    write('flip B');
                end else begin
                    write('ready');
                end;
            end;
            writeln;
        end;
    end else begin
        writeln('Impossible');
    end;

    close(input);
    close(output);
end.