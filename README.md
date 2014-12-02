CBay (Projet C) - Enchères Distribuées
====

Le but du projet est de construire une application C en mode client/serveur (en utilisant les bibliothèques du TP 3) qui permet de gérer des enchères distribuées du même style que celles proposées sur le site eBay.
Mise aux enchères d'objets 

On s'intéresse tout d'abord à la mise aux enchères d'objets. L’application client devra envoyer un message au serveur qui contiendra tous les éléments d'un objet mis aux enchères : catégorie, nom, description, URL d'une image, prix de départ, quantité (note : on vendra le lot complet), lieu où se trouve l'objet...

L’application client pourra par la suite être utilisée pour consulter la liste complète des objets proposés aux enchères et leurs détails. L’application devra aussi permettre de chercher un objet en précisant un mot présent dans son nom ou sa description.

La liste des objets mis aux enchères sera conservée côté serveur dans un ou plusieurs fichiers.
Déroulement de l'enchère 

On développe maintenant le déroulement de l'enchère de manière simplifiée.
====

Un acheteur qui veut enchérir sur un objet précise, via le client, l’objet (avec son nom ou, mieux, un identifiant unique géré par le serveur), la somme proposée et son identité (nom, prénom, numéro de téléphone, adresse, …). Si la somme est supérieure au prix de départ ou au prix actuellement proposé (si une enchère a déjà été proposée) l’enchère est prise en compte et on conserve les informations de l’acheteur dans un fichier.

Le client permettra enfin de préciser qu’une enchère est terminée et le serveur devra alors préciser qui est l’acheteur de l’objet ou un message d’erreur si aucune enchère n’a été enregistrée.


Organisation du projet et travail attendu
====

Le projet est à faire par groupes de deux étudiants qui doivent faire partie du même groupe de niveau d’Anglais (étant donné que les séances d’encadrement projet sont le lundi après-midi).

Ecrivez une RFC pour votre application répartie.

Ecrivez les algorithmes des applications cliente et serveur.

Développez une version simplifiée de l’application.


La version finale du projet devra nous parvenir par mail à ... et ... le jour de la validation.

 
Options
====

Le système permettra d’authentifier les utilisateurs qui pourront être vendeurs, acheteurs ou administrateurs.

On veut désormais gérer les enchères comme sur eBay : une personne souhaitant faire une enchère indique le prix maximum qu'elle souhaite payer. Le programme fera lui-même les enchères jusqu'à cette valeur.

Exemple : Deux acheteurs A et B souhaitent acquérir un même objet. Si l'offre de prix maximal de B (notée y) est supérieure à l'offre de A (notée x), B remporte l'enchère. Le prix maximal courant devient y. Le cours de l'enchère est la somme dont devra s'acquitter celui qui mène l'enchère pour acquérir l'objet. Afin de permettre à A de renchérir, ce montant est fixé à x+p (p est le pas d'enchère en euros).
Le montant de l'enchère peut augmenter sensiblement si un acheteur propose un montant supérieur au prix maximal courant.  Si un nouvel acheteur (C) propose un prix maximum z tel que (z > y) et (z > x+p),  l'enchère devient (y+p) et c'est le client C qui remporte l'enchère. Par contre, si C ne peut pas monter au dessus de B (z<y), B reste en tête de l'enchère et l'enchère devient z+p.

Le pas d'enchère pourra être fixe ou paramétrable en fonction du prix de départ de l'objet. 
Interdire de mettre deux fois le même objet aux enchères.
  
Les enchères ont une durée limitée qui est fixée lors de la mise aux enchères. Modifiez votre programme pour gérer ce temps limité. 
Lorsqu'un acheteur propose une enchère au dernier moment, on laisse un peu de temps (typiquement 15 minutes) aux autres acheteurs pour qu'ils puissent surenchérir. Modifiez votre programme pour tenir compte de cela.

