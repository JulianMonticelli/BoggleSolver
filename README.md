# BoggleSolver
A tool for cheating at Boggle. Utilizes the TWL06 wordlist - included. When executing, make sure that the .txt file is in the same directory as the executable.

Expects by default a 4x4 boggle board from left to right, in standard column-row order.

This utilizes a DLB-Trie to store its dictionary for efficient storage and retrieval. The size of the table itself (with the given word file) in memory is under 30 MB and also allows the program to execute in the range of hundreds of milliseconds.

This program sacrifices only absolutely optimal speeds in exchange for a considerable amount of space. The tradeoff is, in my opinion, worth it as the program can quickly analyze a boggle board while still not causing any detrimental amount of memory being consumed by the system.
