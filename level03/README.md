# level03: XOR CIPHER

### Première étape — tester le programme

```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:test

Invalid Password
```
Nous pouvons constater que nous devons trouver le password, allons voir le code.


### Ouvrir GDB

<details>

<summary>open asm</summary>

```s
   0x0804885a <+0>:	push   %ebp
   0x0804885b <+1>:	mov    %esp,%ebp
   0x0804885d <+3>:	and    $0xfffffff0,%esp
   0x08048860 <+6>:	sub    $0x20,%esp
   0x08048863 <+9>:	push   %eax
   0x08048864 <+10>:	xor    %eax,%eax
   0x08048866 <+12>:	je     0x804886b <main+17>
   0x08048868 <+14>:	add    $0x4,%esp
   0x0804886b <+17>:	pop    %eax
   0x0804886c <+18>:	movl   $0x0,(%esp)
   0x08048873 <+25>:	call   0x80484b0 <time@plt>
   0x08048878 <+30>:	mov    %eax,(%esp)
   0x0804887b <+33>:	call   0x8048500 <srand@plt>
   0x08048880 <+38>:	movl   $0x8048a48,(%esp)
   0x08048887 <+45>:	call   0x80484d0 <puts@plt>
   0x0804888c <+50>:	movl   $0x8048a6c,(%esp)
   0x08048893 <+57>:	call   0x80484d0 <puts@plt>
   0x08048898 <+62>:	movl   $0x8048a48,(%esp)
   0x0804889f <+69>:	call   0x80484d0 <puts@plt>
   0x080488a4 <+74>:	mov    $0x8048a7b,%eax
   0x080488a9 <+79>:	mov    %eax,(%esp)
   0x080488ac <+82>:	call   0x8048480 <printf@plt>
   0x080488b1 <+87>:	mov    $0x8048a85,%eax
   0x080488b6 <+92>:	lea    0x1c(%esp),%edx
   0x080488ba <+96>:	mov    %edx,0x4(%esp)
   0x080488be <+100>:	mov    %eax,(%esp)
   0x080488c1 <+103>:	call   0x8048530 <__isoc99_scanf@plt>
   0x080488c6 <+108>:	mov    0x1c(%esp),%eax
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)
   0x080488d2 <+120>:	mov    %eax,(%esp)
   0x080488d5 <+123>:	call   0x8048747 <test>
   0x080488da <+128>:	mov    $0x0,%eax
   0x080488df <+133>:	leave  
   0x080488e0 <+134>:	ret    


   0x08048747 <+0>:	push   %ebp
   0x08048748 <+1>:	mov    %esp,%ebp
   0x0804874a <+3>:	sub    $0x28,%esp
   0x0804874d <+6>:	mov    0x8(%ebp),%eax
   0x08048750 <+9>:	mov    0xc(%ebp),%edx
   0x08048753 <+12>:	mov    %edx,%ecx
   0x08048755 <+14>:	sub    %eax,%ecx
   0x08048757 <+16>:	mov    %ecx,%eax
   0x08048759 <+18>:	mov    %eax,-0xc(%ebp)
   0x0804875c <+21>:	cmpl   $0x15,-0xc(%ebp)
   0x08048760 <+25>:	ja     0x804884a <test+259>
   0x08048766 <+31>:	mov    -0xc(%ebp),%eax
   0x08048769 <+34>:	shl    $0x2,%eax
   0x0804876c <+37>:	add    $0x80489f0,%eax
   0x08048771 <+42>:	mov    (%eax),%eax
   0x08048773 <+44>:	jmp    *%eax
   0x08048775 <+46>:	mov    -0xc(%ebp),%eax
   0x08048778 <+49>:	mov    %eax,(%esp)
   0x0804877b <+52>:	call   0x8048660 <decrypt>
   0x08048780 <+57>:	jmp    0x8048858 <test+273>
   0x08048785 <+62>:	mov    -0xc(%ebp),%eax
   0x08048788 <+65>:	mov    %eax,(%esp)
   0x0804878b <+68>:	call   0x8048660 <decrypt>
   0x08048790 <+73>:	jmp    0x8048858 <test+273>
   0x08048795 <+78>:	mov    -0xc(%ebp),%eax
   0x08048798 <+81>:	mov    %eax,(%esp)
   0x0804879b <+84>:	call   0x8048660 <decrypt>
   0x080487a0 <+89>:	jmp    0x8048858 <test+273>
   0x080487a5 <+94>:	mov    -0xc(%ebp),%eax
   0x080487a8 <+97>:	mov    %eax,(%esp)
   0x080487ab <+100>:	call   0x8048660 <decrypt>
   0x080487b0 <+105>:	jmp    0x8048858 <test+273>
   0x080487b5 <+110>:	mov    -0xc(%ebp),%eax
   0x080487b8 <+113>:	mov    %eax,(%esp)
   0x080487bb <+116>:	call   0x8048660 <decrypt>
   0x080487c0 <+121>:	jmp    0x8048858 <test+273>
   0x080487c5 <+126>:	mov    -0xc(%ebp),%eax
   0x080487c8 <+129>:	mov    %eax,(%esp)
   0x080487cb <+132>:	call   0x8048660 <decrypt>
   0x080487d0 <+137>:	jmp    0x8048858 <test+273>
   0x080487d5 <+142>:	mov    -0xc(%ebp),%eax
   0x080487d8 <+145>:	mov    %eax,(%esp)
   0x080487db <+148>:	call   0x8048660 <decrypt>
   0x080487e0 <+153>:	jmp    0x8048858 <test+273>
   0x080487e2 <+155>:	mov    -0xc(%ebp),%eax
   0x080487e5 <+158>:	mov    %eax,(%esp)
   0x080487e8 <+161>:	call   0x8048660 <decrypt>
   0x080487ed <+166>:	jmp    0x8048858 <test+273>
   0x080487ef <+168>:	mov    -0xc(%ebp),%eax
   0x080487f2 <+171>:	mov    %eax,(%esp)
   0x080487f5 <+174>:	call   0x8048660 <decrypt>
   0x080487fa <+179>:	jmp    0x8048858 <test+273>
   0x080487fc <+181>:	mov    -0xc(%ebp),%eax
   0x080487ff <+184>:	mov    %eax,(%esp)
   0x08048802 <+187>:	call   0x8048660 <decrypt>
   0x08048807 <+192>:	jmp    0x8048858 <test+273>
   0x08048809 <+194>:	mov    -0xc(%ebp),%eax
   0x0804880c <+197>:	mov    %eax,(%esp)
   0x0804880f <+200>:	call   0x8048660 <decrypt>
   0x08048814 <+205>:	jmp    0x8048858 <test+273>
   0x08048816 <+207>:	mov    -0xc(%ebp),%eax
   0x08048819 <+210>:	mov    %eax,(%esp)
   0x0804881c <+213>:	call   0x8048660 <decrypt>
   0x08048821 <+218>:	jmp    0x8048858 <test+273>
   0x08048823 <+220>:	mov    -0xc(%ebp),%eax
   0x08048826 <+223>:	mov    %eax,(%esp)
   0x08048829 <+226>:	call   0x8048660 <decrypt>
   0x0804882e <+231>:	jmp    0x8048858 <test+273>
   0x08048830 <+233>:	mov    -0xc(%ebp),%eax
   0x08048833 <+236>:	mov    %eax,(%esp)
   0x08048836 <+239>:	call   0x8048660 <decrypt>
   0x0804883b <+244>:	jmp    0x8048858 <test+273>
   0x0804883d <+246>:	mov    -0xc(%ebp),%eax
```
</details>

> _**REMARQUES:**_ Nous pouvons constater qu'il y a une methode de chiffrement du mot de passe, le **XOR Cipher**, un algorithme de chiffrement cryptographique mais pas securise et tres faible dans ce contexte.

### ASEMBLY TO C


*Clique [**ICI**](./Ressources/main.c) si tu veux voir tous le code en **C***

### XOR CIPHER

##### C'est quoi le XOR CIPHER ?

```Le XOR cipher est une méthode de chiffrement très simple qui consiste à combiner chaque bit du message avec une clé, en utilisant l’opération logique XOR (^)```

##### Quel est le principe algorithmique du XOR CIPHER ?

Le principe pour que cette algorithme de chiffrement soit optimiser:

- la cle le doit pas etre courte
- Ne pas le reutiliser sur plusieur message

> _**REMARQUE:**_ les mathématiques du XOR sont simples donc si tu connais une partie du texte original, tu peux retrouver la clé immédiatement. Pour notre cas grace au reverse nous savons que le texte original est "Congratulation!"

##### le XOR CIPHER est t-il reversible ?

La Reponse est **Oui**! Totalement et c'est ce que nous allons faire avec ce petit script en C.

*Clique [**ici**](./Sources/Decrypt.c) pour voir le script*


### Decryptage

##### Testons le script de decryptage pour trouver la bonne cle !

```bash
Sources@main✗✗✗✗✗✗ sben-tay% ./decrypt
Key  1: P|}targfrgz|}`2
Key  2: S~wbqde|qdy~c1
Key  3: R~vcped}pex~b0
Key  4: Uyxqdwbczwbyxe7
Key  5: Txypevcb{vc~xyd6
Key  6: W{zsfu`axu`}{zg5
Key  7: Vz{rgta`yta|z{f4
Key  8: Yut}h{nov{nsuti;
Key  9: Xtu|izonwzortuh:
Key 10: [wvjylmtylqwvk9
Key 11: Zvw~kxmluxmpvwj8
Key 12: ]qpyljkrjwqpm?
Key 13: \pqxm~kjs~kvpql>
Key 14: _sr{n}hip}husro=
Key 15: ^rszo|ihq|itrsn<
Key 16: Amlepcvwncvkmlq#
Key 17: @lmdqbwvobwjlmp"
Key 18: Congratulations! <----------- Voici la cle !
Key 19: Bnofs`utm`uhnor 
Key 20: Eihatgrsjgroihu'
Key 21: Dhi`ufsrkfsnhit&
```

### PAYLOAD

- 1ᵉʳ constat : Nous avons la bonne cle (18)
- 2ᵉᵐᵉ constat : Nous connaissons notre chiffre magique

Cette ligne nous impose une logique mathematique malgre le fait que nous avons la bonne cle :
```c
void test(char *input, char *magic_ptr)
{
    int key = (int)((long)magic_ptr - (long)atoi(input));
    if (key >= 1 && key <= 21) {
        decrypt(key);
  //  ...
}
```

Alors nous allons soustraire 18 avec la valeur magique !

```c
test(buffer, (char *)0x1337d00d);
```

- la valeur decimal de l'adresse `0x1337d00d` est `322424845`
- `322424845` - `18` = **322424827**


> Notre mot de passe est **_322424827_**

### EXEC
```bash
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

**CONGRATULATIONS — you owned it ! 🎉**