Unit tournament;

interface
function GetBestPosition(N : LongInt; C : LongInt; R : LongInt; K, S, E : array of LongInt) : LongInt; cdecl;

implementation

function GetBestPosition(N : LongInt; C : LongInt; R : LongInt; K, S, E : array of LongInt) : LongInt; cdecl;
begin
   GetBestPosition := 0;
end;

end.
