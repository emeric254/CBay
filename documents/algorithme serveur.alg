<?xml version="1.0" encoding="UTF-8"?>
<Algo>
    <description courant="//repondre a une requete GET" texte=""/>
    <extension extnom="inactif"/>
    <fonction fctetat="inactif" fctcode=""/>
    <F2 F2etat="inactif" F2lignes="" F2para="" F2defaut=""/>
    <repere repetat="inactif" repcode="-10#10#-10#10#2#2"/>
    <item algoitem="VARIABLES" code="100#declarationsvariables">
        <item algoitem="encheres EST_DU_TYPE LISTE" code="1#LISTE#encheres"/>
        <item algoitem="nomServeur EST_DU_TYPE CHAINE" code="1#CHAINE#nomServeur"/>
        <item algoitem="port EST_DU_TYPE NOMBRE" code="1#NOMBRE#port"/>
        <item algoitem="connecte EST_DU_TYPE NOMBRE" code="1#NOMBRE#connecte"/>
        <item algoitem="requete EST_DU_TYPE CHAINE" code="1#CHAINE#requete"/>
        <item algoitem="reponse EST_DU_TYPE CHAINE" code="1#CHAINE#reponse"/>
        <item algoitem="erreur EST_DU_TYPE NOMBRE" code="1#NOMBRE#erreur"/>
        <item algoitem="authentifie EST_DU_TYPE NOMBRE" code="1#NOMBRE#authentifie"/>
    </item>
    <item algoitem="DEBUT_ALGORITHME" code="101#debutalgo">
        <item algoitem="port PREND_LA_VALEUR 20000" code="5#port#20000#pasliste"/>
        <item algoitem="AFFICHER &quot;Serveur démaré sur le port &quot;" code="4#Serveur démaré sur le port #0"/>
        <item algoitem="AFFICHER port" code="3#port#1#pasliste"/>
        <item algoitem="TANT_QUE (1) FAIRE" code="15#1">
            <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
            <item algoitem="//attente de connection client" code="19#attente de connection client"/>
            <item algoitem="PAUSE" code="18#pause"/>
            <item algoitem="TANT_QUE (connecte) FAIRE" code="15#connecte">
                <item algoitem="DEBUT_TANT_QUE" code="16#debuttantque"/>
                <item algoitem="//attendre requete" code="19#attendre requete"/>
                <item algoitem="PAUSE" code="18#pause"/>
                <item algoitem="erreur PREND_LA_VALEUR 0" code="5#erreur#0#pasliste"/>
                <item algoitem="SI (requete = Connect) ALORS" code="6#requete = Connect">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="//repondre a une requete CONECT" code="19#repondre a une requete CONECT"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (requete = GET) ALORS" code="6#requete = GET">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="SI (authentifie) ALORS" code="6#authentifie">
                        <item algoitem="DEBUT_SI" code="7#debutsi"/>
                        <item algoitem="//repondre a une requete GET" code="19#repondre a une requete GET"/>
                        <item algoitem="FIN_SI" code="8#finsi"/>
                    </item>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (requete = PUT) ALORS" code="6#requete = PUT">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="//repondre a une requete PUT" code="19#repondre a une requete PUT"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (requete = Delete) ALORS" code="6#requete = Delete">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="SI (authentifie) ALORS" code="6#authentifie">
                        <item algoitem="DEBUT_SI" code="7#debutsi"/>
                        <item algoitem="//repondre a une requete DELETE" code="19#repondre a une requete DELETE"/>
                        <item algoitem="FIN_SI" code="8#finsi"/>
                    </item>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                </item>
                <item algoitem="SI (reponse) ALORS" code="6#reponse">
                    <item algoitem="DEBUT_SI" code="7#debutsi"/>
                    <item algoitem="//envoi reponse" code="19#envoi reponse"/>
                    <item algoitem="FIN_SI" code="8#finsi"/>
                    <item algoitem="SINON" code="9#sinon">
                        <item algoitem="DEBUT_SINON" code="10#debutsinon"/>
                        <item algoitem="//erreur requete" code="19#erreur requete"/>
                        <item algoitem="FIN_SINON" code="11#finsinon"/>
                    </item>
                </item>
                <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
            </item>
            <item algoitem="" code="103#commentaire"/>
            <item algoitem="FIN_TANT_QUE" code="17#fintantque"/>
        </item>
        <item algoitem="//vider la memoire" code="19#vider la memoire"/>
    </item>
    <item algoitem="FIN_ALGORITHME" code="102#finalgo"/>
</Algo>
