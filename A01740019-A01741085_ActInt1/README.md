Actividad Integradora 1
- Ana Cristina Munguia Romero, A01740019
- Carlos Noel Ojeda Angulo, A01741085

This code is an implementation of different algorithms to **find substrings within a given string, longest palindromes, and the longest common substring between two strings**.

Here we specify the meaning behind every output line and how to correctly interpret it.

- The output is composed of three sections that are delimited by linebreaks.

    1. The first section shows if the transmission files (transmission1.txt & transmission2.txt) contain any malicious code (mcode1.txt, mcode2.txt & mcode3.txt). This is depicted by a 'true' or 'false' followed by an integer number, in case of 'true' (this is the position within a transmission file where the malicious code starts; we assume first position of text file as 0).
    2. The second section shows the starting and ending positions of the longest palindrome in each transmission file (starting with transmission1.txt), separated by a single space. We assume first position of text file as 1.
    3. The third section shows the starting and ending positions of the longest common substring that occurs in both transmission files (these positions are relative to transmission1.txt). We assume first position of text file as 1.


- Expected output:

        true 1200
        true 2220
        false
        false
        false
        true 960

        1 1200
        361 960

        1621 2220