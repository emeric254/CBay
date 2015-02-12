# CBay (Projet C) - Enchères Distribuées
========================================
[documentation du projet](http://emeric254.github.io/CBay/)
----------------------------------------

> Le but du projet est de construire une application C 'serveur', et une 'client' (en recyclant le code du TP 3).
Ces deux aplications permettent de gérer des enchères distribuées.


## Mise aux enchères d'objets

L’application client devra envoyer un message au serveur qui contiendra tous les éléments d'un objet mis aux enchères : catégorie, nom, description, URL d'une image, prix de départ, quantité (note : on vendra le lot complet), lieu où se trouve l'objet...

L’application client pourra par la suite être utilisée pour consulter la liste complète des objets proposés aux enchères et leurs détails. L’application devra aussi permettre de chercher un objet en précisant un mot présent dans son nom ou sa description.

La liste des objets mis aux enchères sera conservée côté serveur dans un ou plusieurs fichiers.


## Déroulement de l'enchère

On développe maintenant le déroulement de l'enchère de manière simplifiée :

- Un acheteur qui veut enchérir sur un objet précise, via le client, l’objet (avec son nom ou, mieux, un identifiant unique géré par le serveur), la somme proposée et son identité (nom, prénom, numéro de téléphone, adresse, …).
  - Si la somme est supérieure au prix de départ ou au prix actuellement proposé (si une enchère a déjà été proposée) l’enchère est prise en compte et on conserve les informations de l’acheteur dans un fichier.
- Le client permettra enfin de préciser qu’une enchère est terminée et le serveur devra alors préciser qui est l’acheteur de l’objet ou un message d’erreur si aucune enchère n’a été enregistrée.


##Organisation du projet et travail attendu

Une partie documentaire:

- Ecrivez une RFC pour votre application répartie.
- Ecrivez les algorithmes des applications cliente et serveur.

La version finale du projet devra parvenir par mail à A.A et P.T le jour de la validation (ou avant).

##Options

- Le système permettra d’authentifier les utilisateurs qui pourront être vendeurs, acheteurs ou administrateurs.
- On veut désormais gérer les enchères comme sur eBay : une personne souhaitant faire une enchère indique le prix maximum qu'elle souhaite payer.
  - Le programme client fera lui-même les enchères jusqu'à cette valeur.
- Le pas d'enchère pourra être fixe ou paramétrable en fonction du prix de départ de l'objet.
- Interdire de mettre deux fois le même objet aux enchères.
- Les enchères ont une durée limitée qui est fixée lors de la mise aux enchères.
- Lorsqu'un acheteur propose une enchère au dernier moment, on laisse un peu de temps (typiquement 15 minutes) aux autres acheteurs pour qu'ils puissent surenchérir.

