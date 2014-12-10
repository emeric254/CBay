<?xml version="1.0" encoding="UTF-8"?>
<Algo>
    <description texte="" courant="AFFICHER &quot;Credits. Ce client a ete realise dans le cadre d'un projet de C par 3 etudiants en STRI.&quot;"/>
    <extension extnom="inactif"/>
    <fonction fctcode="" fctetat="inactif"/>
    <F2 F2defaut="" F2lignes="" F2etat="inactif" F2para=""/>
    <repere repetat="inactif" repcode="-10#10#-10#10#2#2"/>
    <item algoitem="VARIABLES" code="100#declarationsvariables">
        <item algoitem="identifiant EST_DU_TYPE CHAINE" code="1#CHAINE#identifiant"/>
        <item algoitem="motdepasse EST_DU_TYPE CHAINE" code="1#CHAINE#motdepasse"/>
        <item algoitem="etatconnexion EST_DU_TYPE NOMBRE" code="1#NOMBRE#etatconnexion"/>
        <item algoitem="choixmenu EST_DU_TYPE NOMBRE" code="1#NOMBRE#choixmenu"/>
        <item algoitem="encheres EST_DU_TYPE LISTE" code="1#LISTE#encheres"/>
        <item algoitem="nbrencheres EST_DU_TYPE NOMBRE" code="1#NOMBRE#nbrencheres"/>
        <item algoitem="iterateur EST_DU_TYPE NOMBRE" code="1#NOMBRE#iterateur"/>
    </item>
    <item algoitem="DEBUT_ALGORITHME" code="101#debutalgo">
        <item algoitem="etatconnexion PREND_LA_VALEUR 0" code="5#etatconnexion#0#pasliste"/>
        <item algoitem="AFFICHER &quot;Bienvenue sur le logiciel client CBAY utilisant le protocole BEEP&quot;" code="4#Bienvenue sur le logiciel client CBAY utilisant le protocole BEEP#1"/>
        <item algoitem="TANT_QUE (etatconnexion &lt;= 0) FAIRE" code="15#etatconnexion &lt;= 0">
            <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
            <item algoitem="SI (etatconnexion &lt; 0) ALORS" code="6#etatconnexion &lt; 0">
                <item algoitem="DEBUT_SI" code="7#debutsi"/>
                <item algoitem="//Erreur de connexion" code="19#Erreur de connexion"/>
                <item algoitem="AFFICHER &quot;Erreur de connexion !&quot;" code="4#Erreur de connexion !#1"/>
                <item algoitem="FIN_SI" code="8#finsi"/>
            </item>
            <item algoitem="AFFICHER &quot;Veuillez vous connecter. Saisissez votre identifiant : (rentrer 'quitter' pour quitter)&quot;" code="4#Veuillez vous connecter. Saisissez votre identifiant : (rentrer 'quitter' pour quitter)#1"/>
            <item algoitem="LIRE identifiant" code="2#identifiant#pasliste"/>
            <item algoitem="SI (identifiant == 'quitter') ALORS" code="6#identifiant == 'quitter'">
                <item algoitem="DEBUT_SI" code="7#debutsi"/>
                <item algoitem="//Quitter" code="19#Quitter"/>
                <item algoitem="etatconnexion PREND_LA_VALEUR 2" code="5#etatconnexion#2#pasliste"/>
                <item algoitem="FIN_SI" code="8#finsi"/>
                <item algoitem="SINON" code="9#sinon">
                    <item algoitem="DEBUT_SINON" code="10#debutsinon"/>
                    <item algoitem="AFFICHER &quot;votre mot de passe :&quot;" code="4#votre mot de passe :#1"/>
                    <item algoitem="LIRE motdepasse" code="2#motdepasse#pasliste"/>
                    <item algoitem="//Tentative de connexion ..." code="19#Tentative de connexion ..."/>
                    <item algoitem="FIN_SINON" code="11#finsinon"/>
                </item>
            </item>
            <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
        </item>
        <item algoitem="SI (etatconnexion == 1) ALORS" code="6#etatconnexion == 1">
            <item algoitem="DEBUT_SI" code="7#debutsi"/>
            <item algoitem="choixmenu PREND_LA_VALEUR -1" code="5#choixmenu#-1#pasliste"/>
            <item algoitem="TANT_QUE (choixmenu != 0) FAIRE" code="15#choixmenu != 0">
                <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
                <item algoitem="nbrencheres PREND_LA_VALEUR 0" code="5#nbrencheres#0#pasliste"/>
                <item algoitem="AFFICHER &quot;Menu Principal. Faites votre choix&quot;" code="4#Menu Principal. Faites votre choix#1"/>
                <item algoitem="//Affichage de la liste des choix" code="19#Affichage de la liste des choix"/>
                <item algoitem="AFFICHER &quot;0 - quitter&quot;" code="4#0 - quitter#0"/>
                <item algoitem="AFFICHER &quot;1 - liste des encheres&quot;" code="4#1 - liste des encheres#1"/>
                <item algoitem="AFFICHER &quot;2 - chercher un objet&quot;" code="4#2 - chercher un objet#1"/>
                <item algoitem="AFFICHER &quot;3 - Credits&quot;" code="4#3 - Credits#0"/>
                <item algoitem="LIRE choixmenu" code="2#choixmenu#pasliste"/>
                <item algoitem="//Controle de la saisie !" code="19#Controle de la saisie !"/>
                <item algoitem="SI (choixmenu == 1) ALORS" code="6#choixmenu == 1">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="choixmenu PREND_LA_VALEUR -1" code="5#choixmenu#-1#pasliste"/>
                    <item algoitem="AFFICHER &quot;Liste des encheres. Choisissez sur quel objet vous voulez encherir&quot;" code="4#Liste des encheres. Choisissez sur quel objet vous voulez encherir#1"/>
                    <item algoitem="//Recuperer la liste des encheres et leur nombre depuis le serveur" code="19#Recuperer la liste des encheres et leur nombre depuis le serveur"/>
                    <item algoitem="POUR iterateur ALLANT_DE 0 A nbrencheres-1" code="12#iterateur#0#nbrencheres-1">
                        <item algoitem="DEBUT_POUR" code="13#debutpour"/>
                        <item algoitem="AFFICHER iterateur" code="3#iterateur#0#pasliste"/>
                        <item algoitem="AFFICHER &quot; - &quot;" code="4# - #0"/>
                        <item algoitem="AFFICHER encheres[iterateur]" code="3#encheres#1#iterateur"/>
                        <item algoitem="FIN_POUR" code="14#finpour"/>
                    </item>
                    <item algoitem="TANT_QUE (choixmenu &lt; 0 OU choixmenu >= nbrencheres) FAIRE" code="15#choixmenu &lt; 0 OU choixmenu >= nbrencheres">
                        <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
                        <item algoitem="AFFICHER &quot;Erreur de frappe ? Veuillez resaisir quelque chose de valide&quot;" code="4#Erreur de frappe ? Veuillez resaisir quelque chose de valide#1"/>
                        <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
                    </item>
                    <item algoitem="//Menu d'enchere sur l'objet choisi" code="19#Menu d'enchere sur l'objet choisi"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (choixmenu == 2) ALORS" code="6#choixmenu == 2">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="choixmenu PREND_LA_VALEUR -1" code="5#choixmenu#-1#pasliste"/>
                    <item algoitem="AFFICHER &quot;Chercher un objet&quot;" code="4#Chercher un objet#1"/>
                    <item algoitem="//Recuperer la liste des encheres et leur nombre depuis le serveur" code="19#Recuperer la liste des encheres et leur nombre depuis le serveur"/>
                    <item algoitem="//Chercher dans cette liste" code="19#Chercher dans cette liste"/>
                    <item algoitem="//enlever les objets ne correspondant pas du tableau encheres et reduire nbrencheres" code="19#enlever les objets ne correspondant pas du tableau encheres et reduire nbrencheres"/>
                    <item algoitem="TANT_QUE (choixmenu &lt; 0 OU choixmenu >= nbrencheres) FAIRE" code="15#choixmenu &lt; 0 OU choixmenu >= nbrencheres">
                        <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
                        <item algoitem="AFFICHER &quot;Erreur de frappe ? Veuillez resaisir quelque chose de valide&quot;" code="4#Erreur de frappe ? Veuillez resaisir quelque chose de valide#1"/>
                        <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
                    </item>
                    <item algoitem="//Menu d'enchere sur l'objet choisi" code="19#Menu d'enchere sur l'objet choisi"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (choixmenu == 3) ALORS" code="6#choixmenu == 3">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="AFFICHER &quot;Credits. Ce client a ete realise dans le cadre d'un projet de C par 3 etudiants en STRI.&quot;" code="4#Credits. Ce client a ete realise dans le cadre d'un projet de C par 3 etudiants en STRI.#1"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
            </item>
            <item algoitem="FIN_SI" code="8#finsi"/>
        </item>
    </item>
    <item algoitem="FIN_ALGORITHME" code="102#finalgo"/>
</Algo>
