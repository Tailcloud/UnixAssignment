# UnixAssignment
All .c files are seperated utilities.

1. lwc.c is implemented features as 'man wc' in Unix OS.
2. mydup2.c implemented features as dup2 without fnctl.
3. lcp.c is implemented features as 'man cp' in Unix OS.
  - cp with handling file hole.
  - In gerneral, file hole is not seems as file used; but we fill '\0' to make is in a block.
4. ftw8.c is modify original ftw8.c to make it search file with chdir.
