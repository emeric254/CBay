<?xml version="1.0" encoding="UTF-8"?>
<Algo>
    <description texte="" courant="AFFICHER &quot;Bienvenue sur le logiciel client utilisant le protocole BEEP&quot;"/>
    <extension extnom="inactif"/>
    <fonction fctcode="" fctetat="inactif"/>
    <F2 F2defaut="" F2lignes="" F2etat="inactif" F2para=""/>
    <repere repetat="inactif" repcode="-10#10#-10#10#2#2"/>
    <item algoitem="VARIABLES" code="100#declarationsvariables">
        <item algoitem="identifiant EST_DU_TYPE CHAINE" code="1#CHAINE#identifiant"/>
        <item algoitem="motdepasse EST_DU_TYPE CHAINE" code="1#CHAINE#motdepasse"/>
        <item algoitem="etatconnexion EST_DU_TYPE NOMBRE" code="1#NOMBRE#etatconnexion"/>
        <item algoitem="choixmenu EST_DU_TYPE NOMBRE" code="1#NOMBRE#choixmenu"/>
    </item>
    <item algoitem="DEBUT_ALGORITHME" code="101#debutalgo">
        <item algoitem="etatconnexion PREND_LA_VALEUR 0" code="5#etatconnexion#0#pasliste"/>
        <item algoitem="choixmenu PREND_LA_VALEUR 1" code="5#choixmenu#1#pasliste"/>
        <item algoitem="AFFICHER &quot;Bienvenue sur le logiciel client utilisant le protocole BEEP&quot;" code="4#Bienvenue sur le logiciel client utilisant le protocole BEEP#1"/>
        <item algoitem="TANT_QUE (identifiant &lt;= 0) FAIRE" code="15#identifiant &lt;= 0">
            <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
            <item algoitem="SI (motdepasse &lt; 0) ALORS" code="6#motdepasse &lt; 0">
                <item algoitem="DEBUT_SI" code="7#debutsi"/>
                <item algoitem="AFFICHER &quot;Erreur de connexion !&quot;" code="4#Erreur de connexion !#1"/>
                <item algoitem="FIN_SI" code="8#finsi"/>
            </item>
            <item algoitem="AFFICHER &quot;Veuillez vous connecter. Saisissez votre identifiant :&quot;" code="4#Veuillez vous connecter. Saisissez votre identifiant :#1"/>
            <item algoitem="LIRE identifiant" code="2#identifiant#pasliste"/>
            <item algoitem="AFFICHER &quot;votre mot de passe :&quot;" code="4#votre mot de passe :#1"/>
            <item algoitem="LIRE motdepasse" code="2#motdepasse#pasliste"/>
            <item algoitem="//Tentative de connexion ..." code="19#Tentative de connexion ..."/>
            <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
        </item>
        <item algoitem="TANT_QUE (choixmenu >= 1) FAIRE" code="15#choixmenu >= 1">
            <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
            <item algoitem="AFFICHER &quot;Menu Principal. Faites votre choix&quot;" code="4#Menu Principal. Faites votre choix#1"/>
            <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
        </item>
        <item algoitem="" code="103#commentaire"/>
    </item>
    <item algoitem="FIN_ALGORITHME" code="102#finalgo"/>
</Algo>
