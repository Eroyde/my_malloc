# my_malloc

My rewrite of malloc().

It's pretty fast for Epitech's standards with two linked lists (malloc'ed memory and free'd memory).

Fusion between two free'd blocks. Split for when malloc needs a smaller size than the free'd blocks have.

It can move the memory break backwards if all the free'd memory is at the end.

And it uses brk() with only PAGE_SIZE compliant values to be even faster.

Epitech forbids the use of mmap for requesting memory so only sbrk() is used here.
