# <div align="center">Commande et Asservissement MCC</div>

## Objectifs

Le but de ce TP est de commander puis d'asservir une MCC grâce à une STM32 et une interface de contrôle

**Materiel utlisé :**

* Nucleo-STM32G474RE
* Carte Electronique De transition (STM32 vers Hacheur)
* Un Hacheur dsPICDEMTM MC1L 3-PHASE
* STM32CubeIDE
* Une MCC avec sa géneratrice Tachymétrique

**On réalise un Schémas du montage :**

![img](assets/Schemas_Global.png)


## Commande MCC basique 

L'objectif de cette partie est de :

* Générer 4 PWM en complémentaire décalée pour contrôler en boucle ouverte le moteur en respectant le cahier des charges,
* Inclure le temps mort.
* Vérifier les signaux de commande à l'oscilloscope.
* Prendre en main le hacheur.
* Câbler correctement la STM32 au hacheur.
* Générer le signal de commande "start" en fonction de la datasheet.
* Faire un premier essai de commande moteur.

### Géneration de 4 PWM

Nous souhaitons les caractéristiques suivantes :

* Fréquence de la PWM : **16kHz**
* Temps mort minimum : **2us**
* Résolution minimum : **10bits**
* PWM en commande complémentaire décalée

**Calcul de la fréquence :**

On configure donc le TIM1 pour génerer des PWM sur les channels 1 et 2 ainsi que leurs complémentaires respectivent. 

On veut une résolution de 10bits on doit donc avoir 2^10-1 = 1024-1 tics de timer. On a donc `ARR = 1024 -1`

On veut de plus une fréquence de travail de 16kHz. Notre fréquence d'horloge est de 170MHz on a donc `f_timer = f_horloge / (ARR + 1)(PSC + 1 )`

On a donc `PSC = 10 - 1` pour obtenir une fréquence de `f_timer = 16,6kHz`. Soit 3,75% d'erreur ce qui est satisfaisant.

On décide de choisir un rapport cyclique `a=0,6` et `a'=1-0,6` pour les tests.

On doit aussi génerer des commandes complémentaires décalée donc on met l'option `Counter Mode: Center Align Mode 1`

#### Calcul du temps mort

Le tick du temps mort est syncronisé sur la SysTick, qui est 170 MHz sur notre projet

On configure `dead time = 210 ticks` ce qui nous donne un ` temps mort = 12us > 2us` .

Nous pouvons voir sur l'oscilloscope les PWM et le dead time:
![img](assets/Schemas_Global.png)

#### Prise en main du hacheur et cablâge

Nous travaillons sur les phases bleu et jaune, la configuration est la suivante:


|Fonction | Broche|
|---------|--------|
| GND|36 |
| PWN 1|11 |
| PWN 1N| 29|
| PWM 2| 12|
| PWM 2N| 30|
| Iso reset|15 |

#### Commande start

Le hacheur a besoin d'une séquence d'amorçage pour obtenir une tension de sortie.
En regardant dans la datasheet, on lit que le hacheur a besoin d’avoir une impulsion
d’au moins 2ms sur la pin Iso_reset (broche 33) pour pouvoir démarrer.

**A completer**


#### Premiers tests

On fait un premier test avec un rapport cyclique de 50% mais on remarque
que le moteur ne démarre pas, tandis que si on augmente le rapport à 55%
le moteur démarre.

De plus, un rapport cyclique de 70% est trop élevée et fait sauter le moteur,
affichant "hall overcurrent" et "shunt overcurrent".
En effet, cela est dû au fait que le démarrage n'est pas assez progressif,
nous appliquons donc un démarrage progressif pour résoudre ce problème.



## Interface de contrôle

**A completer**

Dans cette partie nous allons :

* Mesurer la vitesse à partir du codeur présent sur chaque moteur,
* Mesurer le courant à partir de la / des pin(s) adéquates retourné par le hacheur

Rajouter les screens de Doxygen



#### Commande de vitesse

Pour controler la vitesse du moteur, nous allons envoyer une séquence via la liaison UART (par l'USB) de la forme :

**speed=XXXX**

[Photo_vitesse_putty]

## Asservissement
