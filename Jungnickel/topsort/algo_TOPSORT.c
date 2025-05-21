// Procedure TOPSORT (G; topnr,acyclic)
// (1) N ← 1, L ← ∅;
// (2) for i = 1 to n do ind(i) ← 0 od
// (3) for i = 1 to n do
// (4) for j ∈ Ai do ind(j) ← ind(j)+1 od
// (5) od
// (6) for i = 1 to n do if ind(i)=0 then append i to L fi od
// (7) while L = ∅ do
// (8) delete the first vertex v from L;
// (9) topnr(v) ← N; N ← N + 1;
// (10) for w ∈ Av do
// (11) ind(w) ← ind(w) − 1;
// (12) if ind(w)=0 then append w to L fi
// (13) od
// (14) od
// (15) if N = n + 1 then acyclic ← true else acyclic ← false f
