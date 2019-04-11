program grader;

uses tournament, graderhelplib;

type
GetBestPositionFunction = function (N : LongInt; C : LongInt; R : LongInt; K, S, E : array of LongInt) : LongInt; cdecl;

{$L graderlib.o}
{$IFDEF MSWINDOWS}
{$linklib msvcrt}
{$ELSE}
{$linklib c}
{$ENDIF}

procedure _main(GetBestPosition : GetBestPositionFunction); cdecl; external;

begin
    _main(@GetBestPosition);
end.
