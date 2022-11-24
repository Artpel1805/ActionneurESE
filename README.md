
# TP Actionneur et automatique appliqué

Le but de ce TP est de :

* Réaliser un shell pour commander le hacheur
* Réaliser la commande des 4 transistors du hacheur en commande complémentaire décalée
* Faire l'acquisition des différents capteurs
* Réaliser l'asservissement en temps réel
* Créer une documentation à partir de Doxygen


## TP1: Commande MCC basique 

L'objectif de cette partie est de :

* Générer 4 PWM en complémentaire décalée pour contrôler en boucle ouverte le moteur en respectant le cahier des charges,
* Inclure le temps mort,
* Vérifier les signaux de commande à l'oscilloscope,
* Prendre en main le hacheur,
* Câbler correctement la STM32 au hacheur
* Générer le signal de commande "start" en fonction de la datasheet
* Faire un premier essai de commande moteur

### Géneration de 4 PWM

Nous souhaitons les caractéristiques suivantes :

* Fréquence de la PWM : **16kHz**
* Temps mort minimum : **2us**
* Résolution minimum : **10bits**

#### Calcul du temps mort

La fréquence de la clock est de 170 MHz, on prend donc on configure le
dead time à 210 pour avoir une valeur minimum de 2us.

[Photo_dead_time]

Nous pouvons voir sur l'oscilloscope le dead time:

[Photo_oscillateur_4PWM]


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
d’au moins 2μs sur la pin Iso_reset (broche 33) pour pouvoir démarrer.

**A completer**

#### Commande de vitesse

Pour controler la vitesse du moteur, nous allons envoyer une séquence via la liaison UART (par l'USB) de la forme :

**speed=XXXX**

[Photo_vitesse_putty]

#### Premiers tests

On fait un premier test avec un rapport cyclique de 50% mais on remarque
que le moteur ne démarre pas, tandis que si on augmente le rapport à 55%
le moteur démarre.

De plus, un rapport cyclique de 70% est trop élevée et fait sauter le moteur,
affichant "hall overcurrent" et "shunt overcurrent".
En effet, cela est dû au fait que le démarrage n'est pas assez progressif,
nous appliquons donc un démarrage progressif pour résoudre ce problème.



## TP2: Mesure de vitesse et de courant

**A completer**

Dans cette partie nous allons :

* Mesurer la vitesse à partir du codeur présent sur chaque moteur,
* Mesurer le courant à partir de la / des pin(s) adéquates retourné par le hacheur