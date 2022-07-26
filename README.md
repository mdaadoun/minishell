# Minishell

Objective : Write a shell

## Partie obligatoire (dossier ./src/core)

- [x] display **prompt**
> Afficher un prompt en l’attente d’une nouvelle commande.

- [x] Launch any **program** (using path env to find programs) 
>    Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement PATH, ou sur un chemin relatif ou absolu).

- [x] **History**
> Posséder un historique fonctionnel.

- [x] **single quote '**
> Gérer ' (single quote) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets.

- [x] **double quote "**
> Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets sauf le $ (signe dollar)

* [x] **redirections**
    * [x] **<**
    * [x] **>**
    * [x] **<<**
    * [x] **>>**
>Implémenter les redirections :
> - < doit rediriger l’entrée.  
> - \> doit rediriger la sortie.  
> - << doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
> - \>\> doit rediriger la sortie en mode append.

* [x] **pipes: |**
> Implémenter les pipes (caractère |). La sortie de chaque commande de la pipeline est connectée à l’entrée de la commande suivante grâce à un pipe.

* [x] **env variables: $**
> Gérer les variables d’environnement (un $ suivi d’une séquence de caractères) qui doivent être substituées par leur contenu.

* [x] **$?**
> Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan.

* [x] **Interactive commands**
    * [x] **ctrl-C**
    * [x] **ctrl-D**
    * [x] **ctrl-\\**

> Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
> En mode interactif :
> * ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
> * ctrl-D quitte le shell.
> * ctrl-\ ne fait rien.

* [x] **builtins commands**
    * [x] **echo -n**
    * [x] **cd**
    * [x] **pwd**
    * [x] **export**
    * [x] **unset**
    * [x] **env**
    * [x] **exit**

>Votre shell doit implémenter les builtins suivantes :
> * echo et l’option -n
> * cd uniquement avec un chemin relatif ou absolu
> * pwd sans aucune option
> * export sans aucune option
> * unset sans aucune option
> * env sans aucune option ni argument
> * exit sans aucune option

Notes :
> Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez justifier son utilisation.

> Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule)

> La fonction readline() peut causer des fuites de mémoire. Vous n’avez pas à les gérer. Attention, cela ne veut pas pour autant dire que votre code, oui celui que vous avez écrit, peut avoir des fuites de mémoire.

## Partie bonus (dossier ./src/bonus)

- [ ] && and || with (parentheses) for priority in operations.
- [ ] The wildcard * in the current directory.
